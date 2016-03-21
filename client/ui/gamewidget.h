#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

namespace Ui {
class GameWidget;
}

class CardWidget;
class MainWindows;

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

private:
    Ui::GameWidget *ui;

    CardWidget* _cardWidget;
};


#endif // GAMEWIDGET_H
