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
class QSettings;

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

    void cardClicked(Card* c);
};

#endif // MAINWINDOW_H
