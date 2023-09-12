#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include "loginwidget.h"
#include "ui_loginwidget.h"

namespace Ui {
class SignUpWidget;
}

class SignUpWidget : public QWidget
{
    Q_OBJECT

public:
    Ui::SignUpWidget *ui;

    explicit SignUpWidget(QWidget *parent = nullptr);
    ~SignUpWidget();

private slots:
    void on_goback_clicked();
    void on_SignUp_clicked();

signals:
    void sendBackSignal();

private:

};

#endif // SIGNUPWIDGET_H
