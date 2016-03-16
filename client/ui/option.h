#ifndef OPTION_H
#define OPTION_H

#include <QWidget>

namespace Ui {
class Option;
}

class Option : public QWidget
{
    Q_OBJECT

public:
    explicit Option(QWidget *parent = 0);
    ~Option();

signals:
    void done();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::Option *ui;
};

#endif // OPTION_H
