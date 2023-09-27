#include "addgroup.h"
#include "ui_addgroup.h"


addgroup::addgroup(QJsonObject object, QJsonArray arr ,QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::addgroup)
{
    ui->setupUi(this);
    parsingJsonObjects(object);
    ui->te_label->setText(m_groupname);
    addUserList(arr);


}

addgroup::~addgroup()
{
    delete ui;
}

void addgroup::parsingJsonObjects(QJsonObject obj){
    QString user, group;
    user = obj.value("user").toString();
    group = obj.value("group").toString();
    qDebug() << obj;
    bool found = false;
    for (int i = 0; i < ui->lw_users->count(); ++i){
        StatusListWidgetItem *item = dynamic_cast<StatusListWidgetItem *>(ui->lw_users->item(i));
        found = item->updateUserName(user);
        if (found) break;
    }if(!found) {
        m_username = user;
        ui->lw_users->addItem(new StatusListWidgetItem(user));
    }
    m_groupname = group;

}

void addgroup::addUserList(const QJsonArray &array_in){
    for(const auto &start : array_in){
        QJsonObject start_obj = start.toObject();
        QJsonArray arr_group = start_obj.value("groups").toArray();
        for(const auto &gr : arr_group){
            QJsonObject group = gr.toObject();
            if (m_groupname == group.value("namegroup").toString()){
                QJsonArray arr_user = group.value("users").toArray();
                for(const auto &us : arr_user){
                    QJsonObject obj_user = us.toObject();
                    QString user = obj_user.value("user").toString();
                    MessageHelper::STATUS status = MessageHelper::statusStringToEnum(obj_user["status"].toString());
                    bool found = false;
                    for (int i = 0; i < ui->lw_users->count();++i){
                        StatusListWidgetItem *item = dynamic_cast<StatusListWidgetItem *>(ui->lw_users->item(i));
                        found = item->updateStatus(user, status);
                        if (found) break;
                    }
                    if (!found) ui->lw_users->addItem(new StatusListWidgetItem(user, status));
                }
            }
        }
    }
}






