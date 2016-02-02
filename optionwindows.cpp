#include "optionwindows.h"
#include "ui_optionwindows.h"

#include <QSettings>

OptionWindows::OptionWindows(QWidget *parent) :
    OptionWindows(new QSettings("config.ini", QSettings::IniFormat),
                  parent)
{
}

OptionWindows::OptionWindows(QSettings *config, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::OptionWindows),
    config(config)
{

    ui->setupUi(this);
}

OptionWindows::~OptionWindows()
{
    delete ui;
}

void OptionWindows::showEvent(QShowEvent *)
{
    ui->input_autohost->setChecked(config->value("autohost", false).toBool());

    ui->input_port->setValue(config->value("port", 6112).toInt());
}

void OptionWindows::closeEvent(QCloseEvent *)
{
    emit closed(this);
}

void OptionWindows::save()
{
    config->setValue("autohost", ui->input_autohost->checkState() == Qt::Checked);

    config->setValue("port", ui->input_port->value());
}

void OptionWindows::on_button_ok_clicked()
{
    this->hide();
    this->save();

    emit done();
}

void OptionWindows::on_button_cancel_clicked()
{
    this->hide();

    emit done();
}
