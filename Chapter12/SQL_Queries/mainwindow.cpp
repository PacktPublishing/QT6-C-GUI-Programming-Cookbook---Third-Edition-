#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/User/Desktop/book/Qt5-CPP-GUI-Programming-Cookbook-Second-Edition/Chapter11/SQL_Queries/database.db3");

    connected = db.open();

    if (connected)
    {
        QSqlQuery query;
        if (query.exec("SELECT emp_id, emp_name, emp_age, emp_gender, emp_married FROM employee"))
        {
            while (query.next())
            {
                currentID = query.value(0).toInt();

                ui->name->setText(query.value(1).toString());
                ui->age->setText(query.value(2).toString());
                ui->gender->setCurrentIndex(query.value(3).toInt());
                ui->married->setChecked(query.value(4).toBool());
            }
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }
}

MainWindow::~MainWindow()
{
    db.close();

    delete ui;
}

void MainWindow::on_updateButton_clicked()
{
    if (connected)
    {
        if (currentID == 0)
        {
            qDebug() << "Nothing to update.";
        }
        else
        {
            QString id = QString::number(currentID);
            QString name = ui->name->text();
            QString age = ui->age->text();
            QString gender = QString::number(ui->gender->currentIndex());
            QString married = QString::number(ui->married->isChecked());

            qDebug() << "UPDATE employee SET emp_name = '" + name + "', emp_age = '" + age + "', emp_gender = " + gender + ", emp_married = " + married + " WHERE emp_id = " + id;

            QSqlQuery query;
            if (query.exec("UPDATE employee SET emp_name = '" + name + "', emp_age = '" + age + "', emp_gender = " + gender + ", emp_married = " + married + " WHERE emp_id = " + id))
            {
                qDebug() << "Update success.";
            }
            else
            {
                qDebug() << query.lastError().text();
            }
        }
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }
}

void MainWindow::on_insertButton_clicked()
{
    if (connected)
    {
        QString name = ui->name->text();
        QString age = ui->age->text();
        QString gender = QString::number(ui->gender->currentIndex());
        QString married = QString::number(ui->married->isChecked());

        qDebug() << "INSERT INTO employee (emp_name, emp_age, emp_gender, emp_married) VALUES ('" + name + "','" + age + "'," + gender + "," + married + ")";

        QSqlQuery query;
        if (query.exec("INSERT INTO employee (emp_name, emp_age, emp_gender, emp_married) VALUES ('" + name + "','" + age + "'," + gender + "," + married + ")"))
        {
            currentID = query.lastInsertId().toInt();

            qDebug() << "Insert success.";
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if (connected)
    {
        if (currentID == 0)
        {
            qDebug() << "Nothing to delete.";
        }
        else
        {
            QString id = QString::number(currentID);

            qDebug() << "DELETE FROM employee WHERE emp_id = " + id;

            QSqlQuery query;
            if (query.exec("DELETE FROM employee WHERE emp_id = " + id))
            {
                currentID = 0;

                qDebug() << "Delete success.";
            }
            else
            {
                qDebug() << query.lastError().text();
            }
        }
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }
}
