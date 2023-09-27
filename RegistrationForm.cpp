#include "RegistrationForm.h"
#include "ui_RegistrationForm.h"
#include "mainwindow.h"
#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    m_login = ui->le_login->text();
    m_pass = ui->le_password->text();
    m_username = ui->le_username->text();
    connect(ui->pushButton, &QAbstractButton::clicked,this, &RegistrationForm::registration);
    ui->le_password->setEchoMode(QLineEdit::EchoMode::Password);
    connect(ui->pushButton, &QAbstractButton::clicked, this, &RegistrationForm::setWindow);
}

void RegistrationForm::setWindow() {
    this->close();
}

const QString &RegistrationForm::currentLoginReg(){
    m_login = ui->le_login->text();
    return m_login;
}
const QString &RegistrationForm::currentPasswordReg(){
    m_pass = ui->le_password->text();
    return m_pass;
}
const QString &RegistrationForm::currentUserNameReg(){
    m_username = ui->le_username->text();
    return m_username;
}

void RegistrationForm::showEvent(QShowEvent *e) {
    stateOpenedChanged(true);
    QDialog::showEvent(e);
}

void RegistrationForm::closeEvent(QCloseEvent *e) {
    stateOpenedChanged(false);
    QDialog::closeEvent(e);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_pushButton_clicked()
{
}


