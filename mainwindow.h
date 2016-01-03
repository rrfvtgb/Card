#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAbstractSocket>
#include <QHash>

namespace Ui {
class MainWindow;
class GameLayout;
}

class QTcpSocket;
class QStringListModel;
class QSettings;

class Card;
class CardElement;
class CardWidget;

class Player;

class Game;

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
    QHash<int, CardWidget*> cardUI;
    QHash<int, CardElement*> cards;

    CardWidget* getCardWidgetByType(int type);

    QSettings* config;

public slots:
    void tryConnect();
    void onConnect();

    void resetUI();

    void displayError(QAbstractSocket::SocketError);
    void socketStateChanged(QAbstractSocket::SocketState);

    void readMessage();
    void receiveMessage(QString message);

    void addNewCard(Card* c);
    void addNewPlayer(Player* p);

    void disableCard(Card* c);
    void enableCard(Card* c);

    void cardClicked(Card* c);
};

#endif // MAINWINDOW_H
