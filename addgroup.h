#ifndef ADDGROUP_H
#define ADDGROUP_H
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>
#include <QDialog>
#include <QMainWindow>
#include "StatusListWidgetItem.h"
#include "MessageHelper.h"
#include <QFile>
#include <QJsonArray>
#include "StatusListWidgetItem.h"

namespace Ui {
class addgroup;
}

class addgroup : public QDialog
{
    Q_OBJECT

public:
    explicit addgroup(QJsonObject object, QJsonArray arr, QWidget *parent = nullptr);
    ~addgroup();
    void sendMessageGroup(const QString& username, const QString& message);
    void addUserList(const QJsonArray& array_in);
    void parsingJsonObjects(QJsonObject obj);



private:
    Ui::addgroup *ui;


    QString m_username;
    QString m_groupname;
    QTcpSocket* m_socket;
    QString group_file_path = "/home/nikita/QTproject/CHAT_TeSSt/build-ChatServer-Desktop_Qt_5_14_2_GCC_64bit-Debug/groups.json";
};

#endif // ADDGROUP_H
