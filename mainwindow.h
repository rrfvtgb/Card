#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAbstractSocket>

namespace Ui {
class MainWindow;
class GameLayout;
}

class QTcpSocket;
class Game;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *mainUI;
    Ui::GameLayout *gameUI;

    QTcpSocket* socket;
    Game *game;

public slots:
    void tryConnect();
    void onConnect();

    void resetUI();

    void displayError(QAbstractSocket::SocketError);
    void socketStateChanged(QAbstractSocket::SocketState);

    void readMessage();
    void receiveMessage(QString message);
};

#endif // MAINWINDOW_H
