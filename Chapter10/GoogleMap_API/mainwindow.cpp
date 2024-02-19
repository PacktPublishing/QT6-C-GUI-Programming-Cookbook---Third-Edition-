#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addressRequest = new QNetworkAccessManager();
    connect(addressRequest, &QNetworkAccessManager::finished, this, &MainWindow::getAddressFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getAddressFinished(QNetworkReply* reply)
{
    QByteArray bytes = reply->readAll();
    //qDebug() << QString::fromUtf8(bytes.data(), bytes.size());
    QJsonDocument json = QJsonDocument::fromJson(bytes);

    QJsonObject object = json.object();
    QJsonArray results = object["results"].toArray();

    QJsonObject first = results.at(0).toObject();
    QString address = first["formatted_address"].toString();

    qDebug() << "Address:" << address;
}

void MainWindow::on_getAddressButton_clicked()
{
    QString latitude = ui->latitude->text();
    QString longitude = ui->longitude->text();
    QNetworkRequest request;
    request.setUrl(QUrl("https://maps.googleapis.com/maps/api/geocode/json?latlng=" + latitude + "," + longitude + "&key=AIzaSyDYBOjJhv3dylDZenrvUZ-X8dUVtZsxnGc"));
    addressRequest->get(request);
}

