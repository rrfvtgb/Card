#include "optionwindows.h"
#include "ui_optionwindows.h"

#include <QSettings>
#include <QFileDialog>

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

    ui->input_scriptfolder->setText(config->value("scriptfolder", QDir::currentPath()).toString());
}

void OptionWindows::closeEvent(QCloseEvent *)
{
    emit closed(this);
}

void OptionWindows::save()
{
    config->setValue("autohost", ui->input_autohost->checkState() == Qt::Checked);

    config->setValue("port", ui->input_port->value());

    config->setValue("scriptfolder", ui->input_scriptfolder->text());
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

void OptionWindows::on_browse_scriptfolder_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                tr("Find Files"), ui->input_scriptfolder->text());

    if (!directory.isEmpty()) {
        ui->input_scriptfolder->setText(directory);
    }
}
