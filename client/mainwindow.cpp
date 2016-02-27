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
#include "playerwidget.h"

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
    }

    return c;
}

void MainWindow::disconnectUI(){
    disconnect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),  this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)),         this, SLOT(displayError(QAbstractSocket::SocketError)));

    disconnect(mainUI->pushButton, SIGNAL(pressed()), this, SLOT(tryConnect()));

    disconnect(game, SIGNAL(receiveMessage(QString)),   this, SLOT(receiveMessage(QString)));
    disconnect(game, SIGNAL(newCard(Card*)),            this, SLOT(addNewCard(Card*)));
    disconnect(game, SIGNAL(removeCard(Card*)),         this, SLOT(removeCard(Card*)));
    disconnect(game, SIGNAL(disableCard(Card*)),        this, SLOT(disableCard(Card*)));
    disconnect(game, SIGNAL(enableCard(Card*)),         this, SLOT(enableCard(Card*)));
    disconnect(game, SIGNAL(newPlayer(Player*)),        this, SLOT(addNewPlayer(Player*)));
}

void MainWindow::resetUI(){
    mainUI->setupUi(this);
    this->disconnectUI();

    QVariant host = config->value("lasthost", "");
    mainUI->lineEdit->setText(host.toString());

    // SIGNAL / SLOT
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),        this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(mainUI->pushButton, SIGNAL(pressed()), this, SLOT(tryConnect()));

    connect(game, SIGNAL(receiveMessage(QString)),  this, SLOT(receiveMessage(QString)));
    connect(game, SIGNAL(newCard(Card*)),           this, SLOT(addNewCard(Card*)));
    connect(game, SIGNAL(removeCard(Card*)),        this, SLOT(removeCard(Card*)));
    connect(game, SIGNAL(disableCard(Card*)),       this, SLOT(disableCard(Card*)));
    connect(game, SIGNAL(enableCard(Card*)),        this, SLOT(enableCard(Card*)));
    connect(game, SIGNAL(newPlayer(Player*)),       this, SLOT(addNewPlayer(Player*)));

    game->reset();
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
        QMessageBox::information(this, QApplication::applicationDisplayName(),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, QApplication::applicationDisplayName(),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, QApplication::applicationDisplayName(),
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
        QString command(message.mid(1));

        if(command.compare("deckbuilder", Qt::CaseInsensitive) == 0){
            disconnect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
            game->sendCommand("DECKBUILDER");
            game->setMode(Game::DeckBuilder);
        }else if(command.startsWith("save", Qt::CaseInsensitive)
                 && game->getMode() == Game::DeckBuilder){
            QString name = "";
            QString deck = game->getDeckAsString();
            int pos = command.indexOf(" ");

            if(pos != -1){
                name = command.mid(pos+1);
            }else{
                name = QString::number(qrand());
            }

            config->setValue("deck-"+name, deck);
            this->receiveMessage("Deck saved as "+name);
        }else if(command.startsWith("load ", Qt::CaseInsensitive)){
            QString name = command.mid(5);
            if(config->contains("deck-"+name)){
                QString deck = config->value("deck-"+name, "").toString();

                if(game->getMode() == Game::DeckBuilder){
                    QStringList l = deck.split(' ');
                    QVector<Card*> deck;

                    bool ok;
                    int id;

                    foreach(QString card, l){
                        id = card.toInt(&ok);
                        if(ok){
                            deck.append(game->getCardById(id));
                        }
                    }

                    game->setNewDeck(deck);
                }else if(game->getMode() == Game::Classic){
                    game->sendCommand("DECK"+deck);
                }
            }else{
                this->receiveMessage("Deck not found: "+name);
            }
        }else{
            game->sendCommand(command);
        }
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
    QLayout* l = w->layout();

    connect(el, SIGNAL(onCardClicked(Card*)), this, SLOT(cardClicked(Card*)));

    el->disable();
    cards.insert(c->id(), el);

    el->setCard(c);
    l->addWidget(el);
}

void MainWindow::addNewPlayer(Player *p)
{
    PlayerWidget* w = new PlayerWidget();
    w->setPlayer(p);

    gameUI->creepDisplay->addWidget(w);
}

void MainWindow::removeCard(Card *c)
{
    QHash<int, CardElement*>::iterator it = this->cards.find(c->id());
    CardElement* el;

    if(it != this->cards.end()){ // Card Widget exist
        el = it.value();
        delete el;

        this->cards.remove(c->id());
    }
}

void MainWindow::disableCard(Card *c)
{
    QHash<int, CardElement*>::iterator it = this->cards.find(c->id());
    CardElement* el;

    if(it != this->cards.end()){ // Card Widget exist
        el = it.value();
        el->disable();
    }
}

void MainWindow::enableCard(Card *c)
{
    QHash<int, CardElement*>::iterator it = this->cards.find(c->id());
    CardElement* el;

    if(it != this->cards.end()){ // Card Widget exist
        el = it.value();
        el->enable();
    }
}

void MainWindow::cardClicked(Card *c){
    game->onCardClick(c);
}
