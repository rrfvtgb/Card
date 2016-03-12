#include "serverinfo.h"
#include "ui_serverinfo.h"

ServerInfo::ServerInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerInfo)
{
    ui->setupUi(this);
}

ServerInfo::~ServerInfo()
{
    delete ui;
}

QString ServerInfo::name() const
{
    return ui->lineEdit_name->text();
}

void ServerInfo::setName(const QString &text)
{
    return ui->lineEdit_name->setText(text);
}

QString ServerInfo::address() const
{
    return ui->lineEdit_address->text();
}

void ServerInfo::setAddress(const QString &text)
{
    return ui->lineEdit_address->setText(text);
}

void ServerInfo::reset()
{
    ui->lineEdit_address->setText("");
    ui->lineEdit_name->setText("");
}
