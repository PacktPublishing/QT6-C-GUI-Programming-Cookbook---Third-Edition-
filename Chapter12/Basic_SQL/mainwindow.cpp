#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/User/Desktop/book/Qt5-CPP-GUI-Programming-Cookbook-Second-Edition/Chapter11/Basic_SQL/database.db3");

    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT emp_name, emp_age, emp_gender, emp_married FROM employee"))
        {
            while (query.next())
            {
                qDebug() << query.value(0) << query.value(1) << query.value(2) << query.value(3);

                ui->name->setText(query.value(0).toString());
                ui->age->setText(query.value(1).toString());
                ui->gender->setCurrentIndex(query.value(2).toInt());
                ui->married->setChecked(query.value(3).toBool());
            }
        }
        else
        {
            qDebug() << query.lastError().text();
        }

        db.close();
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
