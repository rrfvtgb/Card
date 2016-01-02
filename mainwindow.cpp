#include <QUrl>
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
#include <QStringListModel>
#include <QScrollBar>
#include <QSettings>
#include <qmath.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_gamelayout.h"

#include "game.h"
#include "card.h"
#include "cardwidget.h"
#include "cardelement.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow),
    gameUI(new Ui::GameLayout),
    socket(new QTcpSocket(this)),
    game(new Game),
    chat(new QStringListModel(this)),
    config(new QSettings("config.ini", QSettings::IniFormat))
{
    game->setSocket(socket);

    if(!config->contains("type-1")){
        config->setValue("type-1", "Channel");
        config->setValue("type-2", "Summon");
        config->setValue("type-3", "Spell");
    }

    this->resetUI();
}

MainWindow::~MainWindow()
{
    this->disconnectUI();

    socket->close();

    delete socket;
    delete game;
    delete config;
    delete mainUI;
    delete gameUI;
}

void MainWindow::disconnectUI(){
    disconnect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    disconnect(mainUI->pushButton, SIGNAL(pressed()), this, SLOT(tryConnect()));

    disconnect(game, SIGNAL(receiveMessage(QString)), this, SLOT(receiveMessage(QString)));
    disconnect(game, SIGNAL(newCard(Card*)), this, SLOT(addNewCard(Card*)));
}

CardWidget *MainWindow::getCardWidgetByType(int type)
{
    QHash<int, CardWidget*>::iterator it = this->cardUI.find(type);
    CardWidget* c;

    if(it != this->cardUI.end()){ // Card Widget exist
        c = it.value();

    }else{ // Insert new card widget
        QString t("type-");
        t.append(QString::number(type));

        QString name = config->value(t, t).toString();

        c = new CardWidget();

        this->cardUI.insert(type, c);
        gameUI->cardTab->addTab(c, name);

        qDebug() << type << "::type-> "<< name << t;
    }

    return c;
}

void MainWindow::resetUI(){
    mainUI->setupUi(this);
    this->disconnectUI();

    QVariant host = config->value("lasthost", "");
    mainUI->lineEdit->setText(host.toString());

    // SIGNAL / SLOT
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(mainUI->pushButton, SIGNAL(pressed()), this, SLOT(tryConnect()));

    connect(game, SIGNAL(receiveMessage(QString)), this, SLOT(receiveMessage(QString)));
    connect(game, SIGNAL(newCard(Card*)), this, SLOT(addNewCard(Card*)));
}

void MainWindow::onConnect(){
    mainUI->pushButton->setEnabled(true);

    centralWidget()->setParent(0);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString("centralWidget"));
    setCentralWidget(centralWidget);

    gameUI->setupUi(centralWidget);

    QStringList list;
    list << "Connected !";

    chat->setStringList(list);
    gameUI->chat->setModel(chat);

    connect(gameUI->message, SIGNAL(returnPressed()), this, SLOT(readMessage()));
}

void MainWindow::tryConnect(){
    if(mainUI->pushButton->isEnabled()){
        QUrl url= QUrl::fromUserInput(mainUI->lineEdit->displayText());

        mainUI->pushButton->setEnabled(false);

        socket->abort();
        socket->connectToHost(url.host(), url.port(6112));

        qDebug()<< "Host " << url.host();
        qDebug()<< "Port " << url.port(6112);

        this->config->setValue("lasthost", mainUI->lineEdit->displayText());
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(socket->errorString()));
    }

    mainUI->pushButton->setEnabled(true);
}

void MainWindow::socketStateChanged(QAbstractSocket::SocketState s){
    if(s == QAbstractSocket::ConnectedState){
        this->onConnect();
    }else if(s == QAbstractSocket::UnconnectedState){
        this->resetUI();
    }
}

void MainWindow::readMessage(){
    QString message = gameUI->message->text();
    gameUI->message->setText("");

    if(message.startsWith("/")){
        game->sendCommand(message.mid(1));
    }else{
        game->say(message);
    }
}

void MainWindow::receiveMessage(QString message){
    QScrollBar* sb = gameUI->chat->verticalScrollBar();
    bool t = (sb->value() == sb->maximum());

    chat->insertRow(chat->rowCount());

    QModelIndex index = chat->index(chat->rowCount()-1);
    chat->setData(index, message);

    gameUI->chat->repaint();

    if(t){
        sb->setValue(sb->maximum());
    }
}

void MainWindow::addNewCard(Card *c)
{
    CardWidget* w = getCardWidgetByType(c->type());
    CardElement* el = new CardElement(w);
    QGridLayout* l = dynamic_cast<QGridLayout *>(w->layout());

    connect(el, SIGNAL(onCardClicked(Card*)), this, SLOT(cardClicked(Card*)));

    el->setCard(c);

    l->addWidget(el);

    int n = qCeil(qSqrt(l->count()));
    QList<QLayoutItem*> list;

    for (int i = l->count()-1; i >= 0; i--){
        QLayoutItem* item = l->itemAt(i);
        list << item;
        l->removeItem(item);
    }

    int x = 0;
    int y = 0;

    while(!list.isEmpty()){
        QLayoutItem* item = list.first();
        list.pop_front();

        if(item != NULL){
            l->addItem(item, y, x);
            x++;
            if(x==n){
                x = 0;
                y++;
            }
        }
    }
}

void MainWindow::cardClicked(Card *c){
    qDebug() << "Card clicked: "<< c->name();
}
