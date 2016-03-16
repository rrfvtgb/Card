#include "option.h"
#include "ui_option.h"

#include <QSettings>

Option::Option(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Option)
{
    ui->setupUi(this);

    QSettings options("option.ini", QSettings::IniFormat);

    ui->lineEdit_username->setText(options.value("username", "Guest").toString());
}

Option::~Option()
{
    delete ui;
}

void Option::on_pushButton_confirm_clicked()
{
    QSettings options("option.ini", QSettings::IniFormat);

    options.setValue("username", ui->lineEdit_username->text());

    emit done();
}

void Option::on_pushButton_cancel_clicked()
{
    emit done();
}
