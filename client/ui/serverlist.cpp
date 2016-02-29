#include "serverlist.h"
#include "ui_serverlist.h"

ServerList::ServerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerList)
{
    ui->setupUi(this);
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
    emit join(ui->display_server->currentItem()->data(3, Qt::EditRole).toString());
}

void ServerList::on_button_host_clicked()
{
    emit host();
}

void ServerList::on_button_close_clicked()
{
    emit exit();
}
