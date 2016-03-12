#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Menu;
class GameWidget;
class ServerList;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Ui{
        MenuUi,
        ServerListUi,
        GameUi
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
     * @brief connectTo Try to connect to a specific server
     * @param address the server adress
     */
    void connectTo(QString address);

protected:
    /// Current Widget used in display
    QStackedWidget* _view;

    // Different Widget which can be used in display
    Menu* _menu;
    ServerList* _list;
    GameWidget* _game;
};

#endif // MAINWINDOW_H
