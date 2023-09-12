#ifndef PROBLEMSWIDGET_H
#define PROBLEMSWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkProxyFactory>

namespace Ui {
class ProblemsWidget;
}

class ProblemsWidget : public QWidget
{
    Q_OBJECT

public:
    Ui::ProblemsWidget *ui;

    explicit ProblemsWidget(QWidget *parent = nullptr);
    ~ProblemsWidget();

private slots:
    void on_next_clicked();

    void on_previous_clicked();

    void on_send_clicked();

private:
    int i; // page number
    double t; // correct number
    double sum; // total number
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // PROBLEMSWIDGET_H
