#include "problemswidget.h"
#include "ui_problemswidget.h"

ProblemsWidget::ProblemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProblemsWidget)
{
    ui->setupUi(this);

    i = 1;
    t = 0;
    sum = 0;

    QNetworkProxyFactory::setUseSystemConfiguration(false);

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);

    tcpServer->listen(QHostAddress("172.16.0.237"), 6666);

    connect(tcpServer, &QTcpServer::newConnection, this, [=](){
        tcpSocket = tcpServer->nextPendingConnection();
        QMessageBox::information(nullptr, "information", "TCP connect success!", QMessageBox::Ok);

        QString clientIp = tcpSocket->peerAddress().toString();
//        quint16 clientPort = tcpSocket->peerPort();

        connect(tcpSocket, &QTcpSocket::readyRead, this, [=](){
            QByteArray arr = tcpSocket->readAll();

            QSqlQuery query;
            query.prepare("select answer from problems where id=:id;");
            query.bindValue(":id", i);

            if(query.exec() && query.next())
            {
                sum++;

                if(arr == query.value(0).toString())
                    t++;
            }
            ui->RecvLine->setText(arr);
//            ui->RecvLine->setText(QString::number(t/sum, '.', 2));
            ui->RecvLine->append(clientIp);
//            ui->RecvLine->append(QString::number(clientPort));
        });
    });
}

ProblemsWidget::~ProblemsWidget()
{
    delete tcpServer;
    delete tcpSocket;
    delete ui;
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

    tcpSocket->write(query.value(1).toString().append("\r\n").toUtf8());
    tcpSocket->write(query.value(2).toString().append("\r\n").toUtf8());
    tcpSocket->write(query.value(3).toString().append("\r\n").toUtf8());
    tcpSocket->write(query.value(4).toString().append("\r\n").toUtf8());
    tcpSocket->write(query.value(5).toString().append("\r\n").toUtf8());
    tcpSocket->write(query.value(6).toString().append("\r\n").toUtf8());
}
