#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Menu;
class GameWidget;
class ServerList;
class Game;
class Option;

class QStackedWidget;
class QMessageBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Ui{
        MenuUi,
        ServerListUi,
        GameUi,
        OptionUi
    };

    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief setView Set the widget to be display
     * @param type Type of widget to be used (will use old widget if possible)
     */
    void setView(Ui type);

    /**
     * @brief setView setView Set the widget to be display
     * @param widget Widget to be displayed
     */
    void setView(QWidget* widget);

private slots:
    /**
     * @brief showMenu Set the view on the menu
     */
    void showMenu();

    /**
     * @brief showServerList Set the view on the server list
     */
    void showServerList();

    /**
     * @brief showServerList Set the view on the option menu
     */
    void showOption();

    /**
     * @brief connectTo Try to connect to a specific server
     * @param address the server adress
     */
    void connectTo(QString address);

    /**
     * @brief cancelConnection Cancel current connection between client and server
     */
    void cancelConnection(int);

    void connected();

    /**
     * @brief disconnected Remove game instance and return to servers list
     */
    void disconnected(QString reason);

protected:
    /// Current Widget used in display
    QStackedWidget* _view;

    // Different Widget which can be used in display
    Menu* _menu;
    ServerList* _list;
    GameWidget* _game;
    Option* _option;

    /**
     * @brief _instance The game object
     */
    Game* _instance;

    /**
     * @brief _msgBox Display the connection status when connecting to server
     */
    QMessageBox* _msgBox;
};

#endif // MAINWINDOW_H
