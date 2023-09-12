#include "loginwidget.h"
#include <QApplication>

bool MySQL_connect()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("project_db");
    db.setUserName("root");
    db.setPassword("020124");

    if(db.open())
        return true;
    else
        return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWidget lw;
    if(MySQL_connect())
    {
        QMessageBox::information(nullptr, "information", "connect success!", QMessageBox::Ok);
        lw.SPWidget_Config();
        lw.show();
    }

    return a.exec();
}
