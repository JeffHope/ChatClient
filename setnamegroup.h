#ifndef SETNAMEGROUP_H
#define SETNAMEGROUP_H
#include <QDialog>
#include <QWidget>
#include "addgroup.h"
#include "MessageHelper.h"

namespace Ui {
class setnamegroup;
}

class setnamegroup : public QDialog
{
    Q_OBJECT
signals:
    void addgroupname();

public:
    explicit setnamegroup(QWidget *parent = nullptr);
    ~setnamegroup();
    QString makeNameGroup();
    void closeWindow();
    void openGroup();
    const QString addNameGroup();


private:
    Ui::setnamegroup *ui;
    QString m_namegroup;
    addgroup* addg;
};

#endif // SETNAMEGROUP_H
