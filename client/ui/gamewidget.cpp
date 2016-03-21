#include "gamewidget.h"
#include "ui_gamewidget.h"

#include <QPlainTextEdit>

#include <view/cardwidget.h>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget),
    _cardWidget(new CardWidget)
{
    ui->setupUi(this);

    QPlainTextEdit* chat = new QPlainTextEdit();
    QPlainTextEdit* console = new QPlainTextEdit();

    chat->setReadOnly(true);
    console->setReadOnly(true);

    ui->tabWidget->clear();
    ui->tabWidget->insertTab(0, chat, tr("Chat"));
    ui->tabWidget->insertTab(1, console, tr("Console"));

    ui->cardArea->setWidget(_cardWidget);
}

GameWidget::~GameWidget()
{
    delete ui;
}
