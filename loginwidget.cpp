#include "loginwidget.h"
#include "ui_loginwidget.h"

#include "problemswidget.h"
#include "ui_problemswidget.h"

#include "signupwidget.h"
#include "ui_signupwidget.h"

bool user_login(QString username, QString password)
{
    QSqlQuery query;

    query.prepare("select psw from users where usr=:usr;");
    query.bindValue(":usr", username);

    if(query.exec() && query.next())
    {
        if(password == query.value(0).toString())
            return true;
        else
            return false;
    }
    else
        return false;
}

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    sw = new SignUpWidget(nullptr);
    connect(sw,&SignUpWidget::sendBackSignal,this,[=](){
        sw->close();
        this->show();
    });
}

void LoginWidget::SPWidget_Config()
{
    pw = new ProblemsWidget(nullptr);
}

LoginWidget::~LoginWidget()
{
    delete pw;
    delete sw;
    delete ui;
}

void LoginWidget::on_SignIn_clicked()
{
    QSqlQuery query;

    QString username = ui->UsrLine->text();
    QString password = ui->PswLine->text();

    if(user_login(username, password))
    {
        QMessageBox::information(nullptr, "information", "login success!", QMessageBox::Ok);

        this->hide();
        pw->show();

        query.prepare("select * from problems where id=1;");
        query.exec();
        query.next();

        pw->ui->problem->setText(query.value(1).toString());
        pw->ui->choiceA->setText(query.value(3).toString());
        pw->ui->choiceB->setText(query.value(4).toString());
        pw->ui->choiceC->setText(query.value(5).toString());
        pw->ui->choiceD->setText(query.value(6).toString());
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "login failed!", QMessageBox::Ok);

        ui->UsrLine->clear();
        ui->PswLine->clear();
    }
}

void LoginWidget::on_SignUp_clicked()
{
    this->hide();
    sw->ui->stackedWidget->setCurrentIndex(0);
    sw->show();
}
