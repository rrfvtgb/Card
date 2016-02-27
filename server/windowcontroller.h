#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include <QSettings>

class OptionWindows;
class ServerWindows;

class QMainWindow;

class WindowController : public QObject
{
    Q_OBJECT
public:
    explicit WindowController(QObject *parent = 0);
    ~WindowController();

signals:

public slots:
    void load();
    void startServer();
    void openOptions();

    void windowsClosed(QMainWindow* windows);

protected:
    QSettings* config;
    OptionWindows* opt;
    ServerWindows* serv;
};

#endif // WINDOWCONTROLLER_H
