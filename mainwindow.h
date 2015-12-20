#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAbstractSocket>
#include <QHash>

namespace Ui {
class MainWindow;
class GameLayout;
}

class CardWidget;
class QTcpSocket;
class Game;
class QStringListModel;
class Card;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void disconnectUI();
private:
    Ui::MainWindow *mainUI;
    Ui::GameLayout *gameUI;

    QTcpSocket* socket;
    Game *game;

    QStringListModel* chat;
    QHash<QString, CardWidget*> cardUI;

    CardWidget* getCardWidgetByType(QString type);

public slots:
    void tryConnect();
    void onConnect();

    void resetUI();

    void displayError(QAbstractSocket::SocketError);
    void socketStateChanged(QAbstractSocket::SocketState);

    void readMessage();
    void receiveMessage(QString message);
    void addNewCard(Card* c);
};

#endif // MAINWINDOW_H
