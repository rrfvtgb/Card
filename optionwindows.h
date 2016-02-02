#ifndef OPTIONWINDOWS_H
#define OPTIONWINDOWS_H

#include <QMainWindow>

namespace Ui {
class OptionWindows;
}

class QSettings;

class OptionWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit OptionWindows(QWidget *parent = 0);
    OptionWindows(QSettings* config, QWidget *parent = 0);
    ~OptionWindows();

public slots:
    void save();

signals:
    void done();
    void closed(QMainWindow*);

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void on_button_ok_clicked();

    void on_button_cancel_clicked();

private:
    Ui::OptionWindows *ui;
    QSettings *config;
};

#endif // OPTIONWINDOWS_H
