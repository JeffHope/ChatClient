#include "SignForm.h"
#include "ui_SignForm.h"
#include <QDebug>
#include <mainwindow.h>
#include <QMessageBox>
#include "MessageHelper.h"

SignForm::SignForm(RegistrationForm *regform, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignForm)
{
    ui->setupUi(this);
    connect(ui->pb_signin, &QAbstractButton::clicked, this, &SignForm::authorize);
    connect(ui->pb_reg, &QAbstractButton::clicked, regform, &QDialog::exec);
    ui->le_password->setEchoMode(QLineEdit::EchoMode::Password);

    // TODO: remove
    ui->le_login->setText("AAA");
    ui->le_password->setText("111");
}


const QString &SignForm::currentLogin() {
    m_login = ui->le_login->text();
    return m_login;
}

const QString &SignForm::currentPassword() {
    m_pass = ui->le_password->text();
    return m_pass;
}

void SignForm::showEvent(QShowEvent *e) {
    m_state_opened = true;
    stateOpenedChanged(m_state_opened);
    QDialog::showEvent(e);
}

void SignForm::closeEvent(QCloseEvent *e) {
    m_state_opened = false;
    stateOpenedChanged(m_state_opened);
    QDialog::closeEvent(e);
}

SignForm::~SignForm() {
    delete ui;
}
