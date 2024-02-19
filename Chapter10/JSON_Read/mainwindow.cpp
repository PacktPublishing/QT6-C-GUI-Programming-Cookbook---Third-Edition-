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

