#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QMessageBox>
#include "StatusListWidgetItem.h"
#include "directmessage.h"
#include <QMouseEvent>
#include <QAction>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);
    reg = new RegistrationForm(this);
    sign = new SignForm(reg, this);
   // group = new addgroup(this);
    setnamegr = new setnamegroup(this);

    ui->te_chat->setReadOnly(true);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(m_socket, &QTcpSocket::stateChanged, this, &MainWindow::stateChanged);
    connect(m_socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &MainWindow::connectError);

    connect(ui->pb_sign, &QAbstractButton::clicked, sign, &QDialog::exec);
    connect(ui->pb_send, &QAbstractButton::clicked, this, &MainWindow::pushMessage);
    connect(ui->le_message, &QLineEdit::returnPressed, this, &MainWindow::pushMessage);
    connect(ui->pb_addgroup, &QAbstractButton::clicked, setnamegr, &QDialog::exec);
    connect(sign, &SignForm::authorize, this, &MainWindow::authorize);
    connect(reg, &RegistrationForm::registration, this, &MainWindow::registration);
    connect(setnamegr, &setnamegroup::addgroupname, this, &MainWindow::addgroupname);

    // connect(sign, &SignForm::stateOpenedChanged, this, [ & ](bool opened) {
    //     qDebug() << "Sign: " << opened;
    //     if (opened) {
    //         m_client_state = ClientState::onAuth;
    //         return;
    //     }
    //     if (reg->stateOpened()) {
    //         m_client_state = ClientState::onReg;
    //         return;
    //     }
    //     m_client_state = ClientState::onMain;
    // });
    // connect(reg, &RegistrationForm::stateOpenedChanged, this, [ & ](bool opened) {
    //     qDebug() << "Reg: " << opened;
    //     if (opened) {
    //         m_client_state = ClientState::onReg;
    //         return;
    //     }
    //     if (sign->stateOpened()) {
    //         m_client_state = ClientState::onAuth;
    //         return;
    //     }
    //     m_client_state = ClientState::onMain;
    // });

    ui->cb_status->addItem(MessageHelper::enumStatusToString(MessageHelper::STATUS::Online));
    ui->cb_status->addItem(MessageHelper::enumStatusToString(MessageHelper::STATUS::Idle));
    ui->cb_status->setCurrentIndex(0);

    show();
    sign->exec();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createGroup(const QJsonArray& array){
    for(const auto& var : array){
        QJsonObject obj = var.toObject();
        QJsonArray arr = obj.value("groups").toArray();
        for(const auto &gr : arr){
            QJsonObject group = gr.toObject();
        QString name = group["namegroup"].toString();
        m_groupname = name;
        bool found = false;
        for (int i = 0; i < ui->lw_group->count();++i){
            StatusListWidgetItem *item = dynamic_cast<StatusListWidgetItem *>(ui->lw_group->item(i));
            found = item->updateGroup(name);
            if (found) break;
        }
        if (!found) ui->lw_group->addItem(new StatusListWidgetItem(name));
        }

    }

}
QString MainWindow::selectedStatus() {
    m_current_status_idx = ui->cb_status->currentIndex();
    return ui->cb_status->itemText(m_current_status_idx);
}

void MainWindow::updateStatus(const QJsonArray &json_array) {
    for (const auto &account : json_array) {
        QJsonObject obj = account.toObject();
        QJsonArray arr = obj["accounts"].toArray();
        for(const auto &check : arr){
            QJsonObject obj_name = check.toObject();
        QString username = obj_name["username"].toString();
        MessageHelper::STATUS status = MessageHelper::statusStringToEnum(obj_name["status"].toString());
        bool found = false;
        for (int i = 0; i < ui->lw_status->count(); i++) {
            StatusListWidgetItem *item = dynamic_cast<StatusListWidgetItem *>(ui->lw_status->item(i));
            found = item->updateStatus(username, status);
            if (found) break;
        }
        if (!found) ui->lw_status->addItem(new StatusListWidgetItem(username, status));
        }
    }
}

void MainWindow::updateMessages(const QString &username, const QString &msg) {
    QTime time = time.currentTime();
    QString chat_message = QString("%1: %2: %3").arg(time.toString()).arg(username).arg(msg);
    ui->te_chat->append(chat_message);
}

void MainWindow::updateUsername(const QString &username) {
    m_current_username = username;
}

void MainWindow::pushMessage() {
    QString msg = ui->le_message->text();
    if (!msg.isEmpty()) {
        sendMessage(m_current_username, msg);
        ui->le_message->clear();
    }
}

void MainWindow::authorize() {
    m_client_state = ClientState::onAuth;
    if(sign->currentLogin().isEmpty() || sign->currentPassword().isEmpty()) {
        QMessageBox msg;
        msg.setText("Одно из полей ввода данных не заполнено!");
        msg.exec();
        return;
    }

    m_socket->connectToHost("127.0.0.1", 65000);
}
void MainWindow::registration() {
    m_client_state = ClientState::onReg;
    if(reg->currentLoginReg().isEmpty() || reg->currentPasswordReg().isEmpty() || reg->currentUserNameReg().isEmpty()) {
        QMessageBox msg;
        msg.setText("Одно из полей ввода данных не заполнено!");
        msg.exec();
        return;
    }
    m_socket->connectToHost("127.0.0.1", 65000);
}

void MainWindow::addgroupname(){
    if(setnamegr->makeNameGroup().isEmpty()){
        QMessageBox msg;
        msg.setText("Поле данных не заполнено.");
        msg.exec();
        return;
    }

        m_socket->write(MessageHelper::makeAddGroup(setnamegr->makeNameGroup(), m_current_username));
        qDebug() << "group is added.";

}

void MainWindow::connectError(QAbstractSocket::SocketError error) {
    QMessageBox msg;
    msg.setText("Не удалось установить подключение: " + m_socket->errorString());
    msg.exec();
}

void MainWindow::stateChanged(QAbstractSocket::SocketState state) {

    switch (state) {
    case QAbstractSocket::SocketState::UnconnectedState:

        break;
    case QAbstractSocket::SocketState::ConnectedState:
        // продумать условие при регистрации пользователя
        switch(m_client_state) {
        case ClientState::onAuth:
            m_socket->write(MessageHelper::makeAuth(sign->currentLogin(), sign->currentPassword()));
            break;
        case ClientState::onReg:
            m_socket->write(MessageHelper::makeRegistration(reg->currentLoginReg(), reg->currentPasswordReg(), reg->currentUserNameReg()));
            break;
        }
    default:
        break;
    }
}

void MainWindow::slotReadyRead() {
    QByteArray data = m_socket->readAll();
    QJsonDocument recv_doc = QJsonDocument::fromBinaryData(data);
    QJsonObject recv_json = recv_doc.object();

    QMessageBox msg;
    if(recv_json.contains("type")) {
        if (recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::Message)) {
            updateMessages(recv_json["username"].toString(), recv_json["message"].toString());
        }

        if (recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::Broadcast)) {
            updateStatus(recv_json["objects"].toArray());
            createGroup(recv_json["objects"].toArray());
            array_jsonobjects_from_server = recv_json["objects"].toArray();
            QJsonObject status_obj, group_obj;
            status_obj["username"] = m_current_username;
            status_obj["status"] = selectedStatus();
            m_socket->write(MessageHelper::make(MessageHelper::TYPE::Status, status_obj));
        }

        if (recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::Access)) {
            updateUsername(recv_json["username"].toString());
            sign->close();
        }

        if (recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::RegistrationAccess)) {
            updateUsername(recv_json["username"].toString());
            reg->close();
        }

        if (recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::Error)) {
            m_socket->disconnectFromHost();
            msg.setText("Неверный логин/пароль");
            msg.exec();
        }

        if (recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::RegistrationError)) {
            m_socket->disconnectFromHost();
            msg.setText("Пользователь уже зарегистрирован.");
            msg.exec();
        }

        if(recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::DoubleSigned)) {
            m_socket->disconnectFromHost();
            msg.setText("Пользователь уже авторизован");
            msg.exec();
        }
        if(recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::ErrorGroup)) {
            msg.setText("Группа с данным именем уже есть в списке");
            msg.exec();
        }
        if(recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::AccessGroup)) {
            msg.setText("Группа создана!");
            msg.exec();
        }
        if(recv_json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::AddGroup)) {
            createGroup(recv_json["groups"].toArray());
        }
    }
}

void MainWindow::sendMessage(const QString &username, const QString &msg) {
    m_socket->write(MessageHelper::makeMessage(username, msg));
}
QString MainWindow::returnGroupUser(const QString &name){
    m_current_username = name;
    return m_current_username;
}

void MainWindow::on_lw_group_itemDoubleClicked(QListWidgetItem *item)
{
    QString label_group = item->text();
    QJsonObject obj;
    obj["group"] = label_group;
    obj["user"] = m_current_username;
    QJsonArray arr = array_jsonobjects_from_server;
    addgroup *group = new addgroup(obj,arr);
    m_socket->write(MessageHelper::makeAddUserInGroup(m_current_username, label_group));
    group->exec();

}

