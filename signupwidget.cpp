#include "signupwidget.h"
#include "ui_signupwidget.h"

SignUpWidget::SignUpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpWidget)
{
    ui->setupUi(this);
}

SignUpWidget::~SignUpWidget()
{
    delete ui;
}

void SignUpWidget::on_goback_clicked()
{
    emit sendBackSignal();
}

void SignUpWidget::on_SignUp_clicked()
{
    QSqlQuery query;

    QString username = ui->UsrLine->text();
    QString password = ui->PswLine->text();
    QString code = ui->CodeLine->text();
    QString opcode = "";

    query.prepare("select count(*) from users where usr=:usr;");
    query.bindValue(":usr", username);

    if(query.exec() && query.next())
    {
        if(!query.value(0).toInt() && code == opcode)
        {
            query.prepare("insert into users (usr, psw) values (:usr, :psw);");
            query.bindValue(":usr", username);
            query.bindValue(":psw", password);
            if(query.exec())
            {
                ui->stackedWidget->setCurrentIndex(1);
            }
        }
        else
        {
            QMessageBox::warning(nullptr, "Warning", "sign up failed!", QMessageBox::Ok);

            ui->UsrLine->clear();
            ui->PswLine->clear();
            ui->CodeLine->clear();
        }
    }
}
