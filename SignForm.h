#ifndef SIGNIN_H
#define SIGNIN_H
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QWidget>
#include <QDialog>
#include <QTcpSocket>
#include "RegistrationForm.h"

namespace Ui {
class SignForm;
}

class SignForm : public QDialog
{
    Q_OBJECT

public:
    explicit SignForm(RegistrationForm *regform, QWidget *parent = nullptr);
    ~SignForm();

    const QString &currentLogin();
    const QString &currentPassword();
    bool stateOpened() { return m_state_opened; };

signals:
    void authorize();
    void stateOpenedChanged(bool opened);

protected:
    void showEvent(QShowEvent *e) override final;
    void closeEvent(QCloseEvent *e) override final;

private:
    Ui::SignForm *ui;
    RegistrationForm* regIn;
    QString m_login;
    QString m_pass;
    bool m_state_opened = false;
};

#endif // SIGNIN_H
