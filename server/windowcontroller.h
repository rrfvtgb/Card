#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include <QSettings>

#ifndef SERVER_CONSOLE
class OptionWindows;
#endif

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

#ifndef SERVER_CONSOLE
    void windowsClosed(QMainWindow* windows);
#endif

protected:
    QSettings* config;
    ServerWindows* serv;

#ifndef SERVER_CONSOLE
    OptionWindows* opt;
#endif
};

#endif // WINDOWCONTROLLER_H
