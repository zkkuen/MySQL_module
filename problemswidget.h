#ifndef PROBLEMSWIDGET_H
#define PROBLEMSWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
//#include <QTime>

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
    void TCP();

private slots:
    void on_next_clicked();

    void on_previous_clicked();

    void on_send_clicked();

private:
    int i;                   // page number
    unsigned int flag;       // flag
    unsigned int user_id;    // user id
    QString str;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    std::vector<QTcpSocket*> tcpSocket_vector;
    std::vector<QString> ip_vector;
    std::vector<unsigned int> port_vector;
    std::vector<double> t;   // correct number
    std::vector<double> sum; // total number
    std::vector<double> ratio_vector;
};

#endif // PROBLEMSWIDGET_H
