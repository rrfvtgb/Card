#include "serverconnection.h"
#include "ui_serverconnection.h"

#include <QSettings>
#include <QStandardItemModel>

ServerConnection::ServerConnection(QString serverName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConnection)
{
    ui->setupUi(this);
    ui->text_server->setText(serverName);

    QSettings config("server.ini", QSettings::IniFormat);
    QStringList l = config.allKeys();

    bool hasDeck = false;

    foreach(QString key, l){
        if(key.startsWith(serverName+"/deck/")){
            ui->comboBox_deck->addItem(key.mid(serverName.length()+6));
            hasDeck = true;
        }
    }

    if(!hasDeck){
        ui->comboBox_mode->setCurrentIndex(1);

        const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>(ui->comboBox_mode->model());
        QStandardItem* item = model->item(0);

        item->setFlags(item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled));
    }

    connect(ui->comboBox_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSelection(int)));

    updateSelection(0);
}

ServerConnection::~ServerConnection()
{
    delete ui;
}

int ServerConnection::gamemode()
{
    return ui->comboBox_mode->currentIndex();
}

QString ServerConnection::deckname()
{
    if(ui->comboBox_deck->currentIndex() != 0)
        return ui->comboBox_deck->currentText();
    return QString();
}

void ServerConnection::updateSelection(int)
{
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>(ui->comboBox_deck->model());
    QStandardItem* item = model->item(0);

    if(ui->comboBox_mode->currentIndex() == 0){ // Standard
        ui->comboBox_deck->setEnabled(true);
        item->setFlags(item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled));
    }else if(ui->comboBox_mode->currentIndex() == 1){ // Deck builder
        ui->comboBox_deck->setEnabled(true);
        item->setFlags(item->flags() | (Qt::ItemIsSelectable|Qt::ItemIsEnabled));
    }else if(ui->comboBox_mode->currentIndex() == 2){ // Spectator
        ui->comboBox_deck->setEnabled(false);
    }
}
