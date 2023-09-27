#ifndef STATUSLISTWIDGETITEM_H
#define STATUSLISTWIDGETITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include "MessageHelper.h"

class StatusListWidgetItem : public QListWidgetItem {

public:

    explicit StatusListWidgetItem(QListWidget *listview = nullptr, int type = Type);
    explicit StatusListWidgetItem(const QString &text, QListWidget *listview = nullptr, int type = Type);
    explicit StatusListWidgetItem(const QIcon &icon, const QString &text, QListWidget *listview = nullptr, int type = Type);
    StatusListWidgetItem(const QListWidgetItem &other);

    explicit StatusListWidgetItem(const QString &username, MessageHelper::STATUS status, QListWidget *listview = nullptr, int type = Type);
    
    ~StatusListWidgetItem();

    bool updateStatus(const QString &username, MessageHelper::STATUS status);
    bool updateUserName(const QString &username);
    bool updateGroup(const QString& namegroup);


protected:
    QIcon statusIcon(MessageHelper::STATUS status);
    QString statusText(const QString &username, MessageHelper::STATUS status);
    QString usernameText(const QString &username);
    QString namegroupText(const QString &namegroup);

private:
    
};

#endif /* STATUSLISTWIDGETITEM_H */
