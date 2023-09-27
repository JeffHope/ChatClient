#include "StatusListWidgetItem.h"

StatusListWidgetItem::StatusListWidgetItem(QListWidget *listview, int type) : QListWidgetItem(listview, type) {

}

StatusListWidgetItem::StatusListWidgetItem(const QString &text, QListWidget *listview, int type) : QListWidgetItem(text, listview, type) {

}

StatusListWidgetItem::StatusListWidgetItem(const QIcon &icon, const QString &text, QListWidget *listview, int type) : QListWidgetItem(icon, text, listview, type) {

}

StatusListWidgetItem::StatusListWidgetItem(const QString &username, MessageHelper::STATUS status, QListWidget *listview, int type) {
    setIcon(statusIcon(status));
    setText(statusText(username, status));
}

StatusListWidgetItem::StatusListWidgetItem(const QListWidgetItem &other) : QListWidgetItem(other) {

}

QIcon StatusListWidgetItem::statusIcon(MessageHelper::STATUS status) {
    QIcon icon;
    switch (status) {
    case MessageHelper::STATUS::Online:
        icon.addFile(":/pic/green.png");
        break;
    case MessageHelper::STATUS::Idle:
        icon.addFile(":/pic/blue.png");
        break;
    default:
        icon.addFile(":/pic/red.png");
        break;
    }

    return icon;
}

bool StatusListWidgetItem::updateStatus(const QString &username, MessageHelper::STATUS status) {
    QString username_status = statusText(username, status);

    if (text().contains(username)) {
        setIcon(statusIcon(status));
        setText(username_status);
        return true;
    }
    return false;
}

bool StatusListWidgetItem::updateUserName(const QString &username){
    QString username_update = usernameText(username);
    if(text().contains(username)){
        usernameText(username_update);
        return true;
    }
    return false;
}
bool StatusListWidgetItem::updateGroup(const QString &namegroup){
    QString new_namegroup = namegroupText(namegroup);
    if(text().contains(namegroup)){
        namegroupText(new_namegroup);
        return true;
    }
    return false;
}
QString StatusListWidgetItem::namegroupText(const QString &namegroup){
    QString name_group = namegroup;
    return name_group;
}
QString StatusListWidgetItem::usernameText(const QString &username){
    QString username_text = username;
    return username_text;
}

QString StatusListWidgetItem::statusText(const QString &username, MessageHelper::STATUS status) {
    QString status_text = QString("%1: %2").arg(username).arg(MessageHelper::enumStatusToString(status));
    return status_text;
}

StatusListWidgetItem::~StatusListWidgetItem() {
}
