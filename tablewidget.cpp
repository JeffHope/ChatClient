#include "tablewidget.h"
#include "ui_tablewidget.h"

tablewidget::tablewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tablewidget)
{
    ui->setupUi(this);
    tablewidget *model = new tablewidget;
    ui->tableView->setModel(model);
}

tablewidget::~tablewidget()
{
    delete ui;
}
int tablewidget::rowCount(const QModelIndex& parent)const{
    return 5;
}
int tablewidget::columnCount(const QModelIndex &parent) const{
    return 4;
}
QVariant tablewidget::data(const QModelIndex &index, int role) const{
    if(role == Qt::DisplayRole){
        QString unswer = QString("row = ") + QString::number(index.row()) + "col = " + QString::number(index.column());
        return QVariant(unswer);
    }
    return QVariant();
}
