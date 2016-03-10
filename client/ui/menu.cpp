#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_button_exit_clicked()
{
    emit exit();
}

void Menu::on_button_option_clicked()
{
    emit option();
}

void Menu::on_button_play_clicked()
{
    emit play();
}
