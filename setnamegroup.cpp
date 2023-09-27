#include "setnamegroup.h"
#include "ui_setnamegroup.h"

setnamegroup::setnamegroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setnamegroup)
{
    ui->setupUi(this);
    m_namegroup = ui->le_write->text();
    connect(ui->pb_accept, &QAbstractButton::clicked, this, &setnamegroup::addgroupname);
    connect(ui->pb_accept, &QAbstractButton::clicked,this, &setnamegroup::openGroup);
}

setnamegroup::~setnamegroup()
{
    delete ui;
}

QString setnamegroup::makeNameGroup(){
    m_namegroup = ui->le_write->text();
    return  m_namegroup;
}

void setnamegroup::closeWindow(){
    this->close();
}
void setnamegroup::openGroup(){
    QString str = ui->le_write->text();
    QJsonObject obj;
    obj["group"] = str;
    QJsonArray arr;
    addgroup* addg = new addgroup(obj,arr);
    addg->exec();
    ui->le_write->clear();
    this->close();
}



