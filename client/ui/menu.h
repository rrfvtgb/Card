#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

signals:
    void play();
    void option();
    void exit();

private slots:
    void on_button_exit_clicked();

    void on_button_option_clicked();

    void on_button_play_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
