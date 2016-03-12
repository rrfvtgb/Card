#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <QWidget>

namespace Ui {
class ServerList;
}

class ServerInfo;

class QTreeWidgetItem;

class ServerList : public QWidget
{
    Q_OBJECT

public:
    explicit ServerList(QWidget *parent = 0);
    ~ServerList();

signals:
    void join(const QString& address);

    void exit();
    void host();

private slots:
    void on_display_server_itemSelectionChanged();

    void on_button_join_clicked();

    void on_button_host_clicked();

    void on_button_close_clicked();

    void on_button_add_clicked();

    void on_button_edit_clicked();

    void dialog_accepted();

    void on_button_delete_clicked();

public slots:
    void loadList();
    void saveList();


private:
    Ui::ServerList *ui;
    ServerInfo* _dialog;

    int _id;
};

#endif // SERVERLIST_H
