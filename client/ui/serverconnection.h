#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QDialog>

namespace Ui {
class ServerConnection;
}

class ServerConnection : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConnection(QString serverName, QWidget *parent = 0);
    ~ServerConnection();

    int gamemode();
    QString deckname();

protected slots:
    void updateSelection(int);

private:
    Ui::ServerConnection *ui;
};

#endif // SERVERCONNECTION_H
