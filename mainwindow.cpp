#include <QUrl>
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
#include <QStringListModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_gamelayout.h"

#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow),
    gameUI(new Ui::GameLayout),
    socket(new QTcpSocket(this)),
    game(new Game)
{
    mainUI->setupUi(this);

    game->setSocket(socket);

    // SIGNAL / SLOT
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(mainUI->pushButton, SIGNAL(pressed()), this, SLOT(tryConnect()));

    connect(game, SIGNAL(receiveMessage(QString)), this, SLOT(receiveMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete mainUI;
    delete gameUI;
    delete game;
    delete socket;
}

void MainWindow::resetUI(){
    mainUI->setupUi(this);
}

void MainWindow::onConnect(){
    mainUI->pushButton->setEnabled(true);

    centralWidget()->setParent(0);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    setCentralWidget(centralWidget);

    qDebug() << "Init game UI";
    gameUI->setupUi(centralWidget);

    QStringListModel* model = new QStringListModel(this);
    QStringList list;

    list << "Connected !";

    model->setStringList(list);
    gameUI->chat->setModel(model);

    connect(gameUI->message, SIGNAL(returnPressed()), this, SLOT(readMessage()));
}

void MainWindow::tryConnect(){
    QUrl url= QUrl::fromUserInput(mainUI->lineEdit->displayText());

    mainUI->pushButton->setEnabled(false);

    socket->abort();
    socket->connectToHost(url.host(), url.port(6112));

    qDebug()<< "Host " << url.host();
    qDebug()<< "Port " << url.port(6112);
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
    game->say(gameUI->message->text());
    gameUI->message->setText("");
}

void MainWindow::receiveMessage(QString message){
    QStringListModel* model = dynamic_cast<QStringListModel*>(gameUI->chat->model());
    model->insertRow(model->rowCount());

    QModelIndex index = model->index(model->rowCount()-1);
    model->setData(index, message);
}
