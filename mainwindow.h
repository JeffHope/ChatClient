#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTcpSocket>
#include <QMainWindow>
#include <QString>
#include <QMetaEnum>
#include <QMetaObject>
#include "SignForm.h"
#include "RegistrationForm.h"
#include <QDialog>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "addgroup.h"
#include "directmessage.h"
#include "MessageHelper.h"
#include "setnamegroup.h"
#include "contextmenuLW.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum ClientState{
        onAuth = 0x00,
        onReg = 0x01,
        onMain = 0xfe
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void updateStatus(const QJsonArray &json_array);
    void updateMessages(const QString &username, const QString &msg);
    void updateUsername(const QString &username);
    QString selectedStatus();
    //void openDirectMsg();
    void createGroup(const QJsonArray& array);
    void addUser(const QJsonArray& array);

public slots:
    QString returnGroupUser(const QString& name);


protected:
    void pushMessage();
    void sendMessage(const QString &username, const QString &msg);

    void slotReadyRead();
    void authorize();
    void registration();
    void addgroupname();
    void stateChanged(QAbstractSocket::SocketState state);
    void connectError(QAbstractSocket::SocketError error);


private slots:
    void on_lw_group_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    SignForm *sign;
    RegistrationForm *reg;
    //DirectMessage *ls_msg;
   // addgroup *group;
    setnamegroup *setnamegr;

    QString m_groupname;
    QString m_current_username;
    int m_current_status_idx = 0;

    QJsonArray array_jsonobjects_from_server;
    QTcpSocket *m_socket = nullptr;
    QByteArray mData;
    ClientState m_client_state = ClientState::onMain;

};
#endif // MAINWINDOW_H
