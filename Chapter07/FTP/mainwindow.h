#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QThread>

#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void getFileList();

private slots:
	void on_openButton_clicked();
	void on_uploadButton_clicked();
	void on_setFolderButton_clicked();
	void on_fileList_itemDoubleClicked(QListWidgetItem *item);

    void serverConnected(const QHostAddress &address, int port);
    void serverReply(int code, const QString &parameters);
    void dataReceived(const QByteArray &data);

private:
	Ui::MainWindow *ui;

    FtpDataChannel* dataChannel;
    FtpControlChannel* controlChannel;

	QString ftpAddress;
	QString username;
	QString password;

	QStringList fileList;
	QString uploadFileName;
	QString downloadFileName;
};

#endif // MAINWINDOW_H
