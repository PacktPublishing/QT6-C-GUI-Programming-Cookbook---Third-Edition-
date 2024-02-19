#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadJsonButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open JSON", ".", "JSON files (*.json)");
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Error loading JSON file.";
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(data);

    if (json.isArray())
    {
        QJsonArray array = json.array();
        if (array.size() > 0)
        {
            for (int i = 0; i < array.size(); ++i)
            {
                qDebug() << "[Object]=================================";

                QJsonObject object = json[i].toObject();
                QStringList keys = object.keys();
                for (int j = 0; j < keys.size(); ++j)
                {
                    qDebug() << keys.at(j) << object.value(keys.at(j));
                }

                qDebug() << "=========================================";
            }
        }
    }
}


void MainWindow::on_saveJsonButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save JSON", ".", "JSON files (*.json)");
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        qDebug() << "Error saving JSON file.";

    QJsonDocument json;
    QJsonArray array;

    QJsonObject contact1;
    contact1["category"] = "Friend";
    contact1["name"] = "John Doe";
    contact1["age"] = 32;
    contact1["address"] = "114B, 2nd Floor, Sterling Apartment, Morrison Town";
    contact1["phone"] = "0221743566";
    array.append(contact1);

    QJsonObject contact2;
    contact2["category"] = "Family";
    contact2["name"] = "Jane Smith";
    contact2["age"] = 24;
    contact2["address"] = "13, Ave Park, Alexandria";
    contact2["phone"] = "0025728396";
    array.append(contact2);

    json.setArray(array);
    file.write(json.toJson());
    file.close();
}

