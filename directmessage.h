#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H
#include <QMainWindow>
#include "MessageHelper.h"
#include "mainwindow.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QTime>
#include <QDialog>

namespace Ui {
class DirectMessage;
}

class DirectMessage : public QMainWindow
{
    Q_OBJECT

public:
    explicit DirectMessage(QWidget *parent = nullptr);
    ~DirectMessage();
    void slotReadyRead();
    void updateMessages(const QString &username, const QString &msg);
    void pushMessage();
    void sendMessage(const QString &username, const QString &msg);


private:
    Ui::DirectMessage *ui;
    QTcpSocket* m_socket;
    QString m_username;
};

#endif // DIRECTMESSAGE_H
