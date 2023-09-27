#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QAbstractTableModel>

namespace Ui {
class tablewidget;
}

class tablewidget : public QWidget
{
    Q_OBJECT

public:
    explicit tablewidget(QWidget *parent = nullptr);
    ~tablewidget();
    int rowCount(const QModelIndex& parent)const;
    int columnCount(const QModelIndex& parent)const;
    QVariant data(const QModelIndex& index, int role)const;

private:
    Ui::tablewidget *ui;

};

#endif // TABLEWIDGET_H
