#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QDialog>

namespace Ui {
class ServerInfo;
}

class ServerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ServerInfo(QWidget *parent = 0);
    ~ServerInfo();

    QString name() const;
    void setName(const QString& text);

    QString address() const;
    void setAddress(const QString& text);

public slots:
    void reset();

private:
    Ui::ServerInfo *ui;
};

#endif // SERVERINFO_H
