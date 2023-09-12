#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

class ProblemsWidget;
class SignUpWidget;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    Ui::LoginWidget *ui;

    explicit LoginWidget(QWidget *parent = nullptr);
    void SPWidget_Config();
    ~LoginWidget();

private slots:
    void on_SignIn_clicked();

    void on_SignUp_clicked();

private:
    ProblemsWidget *pw;
    SignUpWidget *sw;
};

#endif // LOGINWIDGET_H
