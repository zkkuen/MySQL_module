#include "problemswidget.h"
#include "ui_problemswidget.h"

ProblemsWidget::ProblemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProblemsWidget)
{
    ui->setupUi(this);

    i = 1;
    flag = 0;
    user_id = 0;
    str = "OK\r\n";

    TCP();
}

ProblemsWidget::~ProblemsWidget()
{
    delete tcpServer;
    delete tcpSocket;
    delete ui;
}

void ProblemsWidget::TCP()
{
    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);

    tcpServer->listen(QHostAddress("172.16.0.237"), 6666);

    connect(tcpServer, &QTcpServer::newConnection, this, [=](){
        tcpSocket = tcpServer->nextPendingConnection();
        tcpSocket_vector.push_back(tcpSocket);
        t.push_back(0);
        sum.push_back(0);
        QMessageBox::information(nullptr, "information", "TCP connect success!", QMessageBox::Ok);

        connect(tcpSocket, &QTcpSocket::readyRead, this, [=](){
            QByteArray arr;

            for(unsigned int j = 0 ; j < tcpSocket_vector.size() ; j++)
            {
                tcpSocket = tcpSocket_vector[j];
                arr = tcpSocket->readAll();
                if(arr == "response" && flag)
                {
                    tcpSocket->write(str.toUtf8());
                    flag = 0;
                    user_id = j;
                }
                if(!flag && j == user_id && arr.length() != 0 && arr != "response")
                {
                    QSqlQuery query;
                    query.prepare("select answer from problems where id=:id;");
                    query.bindValue(":id", i);

                    if(query.exec() && query.next())
                    {
                        sum[j]++;

                        if(arr == query.value(0).toString())
                            t[j]++;


                        ui->Usr1Line->setText(QString::number(t[j]/sum[j], '.', 2));
                    }

                    QString clientIp = tcpSocket->peerAddress().toString();
                    quint16 clientPort = tcpSocket->peerPort();
                    ui->RecvLine->setText(arr);
                    ui->RecvLine->append(clientIp);
                    ui->RecvLine->append(QString::number(clientPort));
                }
            }
        });
    });
}

void ProblemsWidget::on_next_clicked()
{
    QSqlQuery query;

    query.exec("select count(*) from problems;");
    query.next();
    if(i < query.value(0).toInt())
    {
        i++;
        query.prepare("select * from problems where id=:id;");
        query.bindValue(":id", QString::number(i));
        query.exec();
        query.next();

        ui->problem->setText(query.value(1).toString());
        ui->choiceA->setText(query.value(3).toString());
        ui->choiceB->setText(query.value(4).toString());
        ui->choiceC->setText(query.value(5).toString());
        ui->choiceD->setText(query.value(6).toString());
    }
}

void ProblemsWidget::on_previous_clicked()
{
    QSqlQuery query;

    if(i > 1)
    {
        i--;
        query.prepare("select * from problems where id=:id;");
        query.bindValue(":id", QString::number(i));
        query.exec();
        query.next();

        ui->problem->setText(query.value(1).toString());
        ui->choiceA->setText(query.value(3).toString());
        ui->choiceB->setText(query.value(4).toString());
        ui->choiceC->setText(query.value(5).toString());
        ui->choiceD->setText(query.value(6).toString());
    }
}

void ProblemsWidget::on_send_clicked()
{
    QSqlQuery query;

    query.prepare("select * from problems where id=:id;");
    query.bindValue(":id", QString::number(i));
    query.exec();
    query.next();

    for(unsigned int j = 0 ; j < tcpSocket_vector.size() ; j++)
    {
        tcpSocket = tcpSocket_vector[j];

        tcpSocket->write(query.value(1).toString().append("\r\n").toUtf8());
        tcpSocket->write(query.value(2).toString().append("\r\n").toUtf8());
        tcpSocket->write(query.value(3).toString().append("\r\n").toUtf8());
        tcpSocket->write(query.value(4).toString().append("\r\n").toUtf8());
        tcpSocket->write(query.value(5).toString().append("\r\n").toUtf8());
        tcpSocket->write(query.value(6).toString().append("\r\n").toUtf8());
    }

    flag = 1;
}
