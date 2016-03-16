#include "serverlist.h"
#include "ui_serverlist.h"

#include "serverinfo.h"

#include <QSettings>

ServerList::ServerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerList),
    _dialog(new ServerInfo(this)),
    _id(-1)
{
    ui->setupUi(this);

    this->loadList();

    connect(_dialog, SIGNAL(accepted()), this, SLOT(dialog_accepted()));
}

ServerList::~ServerList()
{
    delete ui;
}
void ServerList::on_display_server_itemSelectionChanged()
{
    if(ui->display_server->selectedItems().size() != 1){
        ui->button_edit->setEnabled(false);
        ui->button_delete->setEnabled(false);
        ui->button_join->setEnabled(false);
    }else{
        ui->button_edit->setEnabled(true);
        ui->button_delete->setEnabled(true);
        ui->button_join->setEnabled(true);
    }
}

void ServerList::on_button_join_clicked()
{
    if(ui->display_server->selectedItems().size() == 1){
        emit join(ui->display_server->selectedItems()[0]->text(2));
    }
}

void ServerList::on_button_host_clicked()
{
    emit host();
}

void ServerList::on_button_close_clicked()
{
    emit exit();
}

void ServerList::on_button_add_clicked()
{
    _id = -1;

    _dialog->reset();
    _dialog->show();
}

void ServerList::on_button_edit_clicked()
{
    if(ui->display_server->selectedItems().size() == 1){
        QTreeWidgetItem* item = ui->display_server->selectedItems()[0];

        _id = ui->display_server->indexOfTopLevelItem(item);

        _dialog->setName(item->text(0));
        _dialog->setAddress(item->text(2));

        _dialog->show();
    }
}

void ServerList::on_button_delete_clicked()
{
    foreach(QTreeWidgetItem* item, ui->display_server->selectedItems()){
        delete item;
    }
}

void ServerList::dialog_accepted()
{
    QString name = _dialog->name();
    QString address = _dialog->address();

    if(_id == -1){
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->display_server);

        item->setText(0, name);
        item->setText(1, "?? / ??");
        item->setText(2, address);
    }else{
        QTreeWidgetItem* item = ui->display_server->topLevelItem(_id);

        if(item != 0){
            item->setText(0, name);
            item->setText(2, address);
        }
    }

    this->saveList();
}

void ServerList::loadList()
{
    QSettings data("server.ini", QSettings::IniFormat);
    QStringList keys = data.allKeys();

    ui->display_server->clear();

    foreach(QString key, keys){
        if(key.startsWith("server/")){
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->display_server);

            item->setText(0, key.mid(7));
            item->setText(1, "?? / ??");
            item->setText(2, data.value(key).toString());
        }
    }
}

void ServerList::saveList()
{
    QSettings data("server.ini", QSettings::IniFormat);
    int len = ui->display_server->topLevelItemCount();
    int i;

    for(i=0;i<len;i++){
        QTreeWidgetItem* item = ui->display_server->topLevelItem(i);

        data.setValue("server/"+item->text(0),
                      item->text(2));
    }
}
