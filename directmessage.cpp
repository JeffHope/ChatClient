#include "directmessage.h"
#include "ui_directmessage.h"

DirectMessage::DirectMessage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DirectMessage)
{
    ui->setupUi(this);

}

DirectMessage::~DirectMessage()
{
    delete ui;
}
void DirectMessage::updateMessages(const QString &username, const QString &msg) {
    QTime time = time.currentTime();
    m_username = username;
    QString chat_message = QString("%1: %2: %3").arg(time.toString()).arg(username).arg(msg);
    ui->te_out->append(chat_message);
}
void DirectMessage::pushMessage() {
    QString msg = ui->le_write->text();

    if (!msg.isEmpty()) {
        sendMessage(m_username, msg);
        ui->le_write->clear();
    }
}
void DirectMessage::slotReadyRead(){
    QByteArray dataArray = m_socket->readAll();
    QJsonDocument doc = QJsonDocument::fromBinaryData(dataArray);
    QJsonObject json = doc.object();

    if(json["type"] == MessageHelper::enumTypeToString(MessageHelper::TYPE::Message)){
        updateMessages(json["username"].toString(), json["message"].toString());
    }
}
void DirectMessage::sendMessage(const QString &username, const QString &msg) {
    m_socket->write(MessageHelper::makeMessage(username, msg));
}
