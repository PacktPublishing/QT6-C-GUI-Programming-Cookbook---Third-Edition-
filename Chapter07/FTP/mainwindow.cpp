#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    dataChannel = new FtpDataChannel(this);
    controlChannel = new FtpControlChannel(this);

    connect(dataChannel, &FtpDataChannel::dataReceived, this, &MainWindow::dataReceived);
    connect(controlChannel, &FtpControlChannel::reply, this, &MainWindow::serverReply);
    connect(controlChannel, &FtpControlChannel::opened, this, &MainWindow::serverConnected);

    ftpAddress = "127.0.0.1";
	username = "myuser";
	password = "123456";

    controlChannel->connectToServer(ftpAddress);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::getFileList()
{
    controlChannel->command("PORT", dataChannel->portspec().toUtf8());
    controlChannel->command("MLSD", "");
}

void MainWindow::on_openButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Select File", qApp->applicationDirPath());

	ui->uploadFileInput->setText(fileName);
}

void MainWindow::on_uploadButton_clicked()
{
    QFile* file = new QFile(ui->uploadFileInput->text());
    QFileInfo fileInfo(*file);
    uploadFileName = fileInfo.fileName();

    controlChannel->command("PORT", dataChannel->portspec().toUtf8());
    controlChannel->command("STOR", uploadFileName.toUtf8());
}

void MainWindow::on_setFolderButton_clicked()
{
	QString folder = QFileDialog::getExistingDirectory(this, tr("Open Directory"), qApp->applicationDirPath(), QFileDialog::ShowDirsOnly);

	ui->downloadPath->setText(folder);
}

void MainWindow::on_fileList_itemDoubleClicked(QListWidgetItem *item)
{
	downloadFileName = item->text();

	// Check folder
	QString folder = ui->downloadPath->text();
	if (folder != "" && QDir(folder).exists())
    {
        controlChannel->command("PORT", dataChannel->portspec().toUtf8());
        controlChannel->command("RETR", downloadFileName.toUtf8());
	}
	else
	{
		QMessageBox::warning(this, "Invalid Path", "Please set the download path before download.");
	}
}

void MainWindow::serverConnected(const QHostAddress &address, int port)
{
    qDebug() << "Listening to:" << address << port;
    dataChannel->listen(address);

    controlChannel->command("USER", username.toUtf8());
    controlChannel->command("PASS", password.toUtf8());

    getFileList();
}

void MainWindow::serverReply(int code, const QString &parameters)
{
    qDebug() << "Server reply:" << code << parameters;

    if (code == 150 && uploadFileName != "")
    {
        QFile* file = new QFile(ui->uploadFileInput->text());
        QFileInfo fileInfo(*file);
        uploadFileName = fileInfo.fileName();

        if (file->open(QIODevice::ReadOnly))
        {
            // Wait for a bit to make sure the connection has been connected (not the best way to do this)
            QThread::msleep(1000);

            QByteArray data = file->readAll();
            dataChannel->sendData(data + "\n\r");

            qDebug() << data;
        }
        else
        {
            QMessageBox::warning(this, "Invalid File", "Failed to open file for upload.");
        }
    }

    if (code == 226 && uploadFileName != "")
    {
        uploadFileName = "";

        QMessageBox::warning(this, "Upload Success", "File successfully uploaded.");
    }
}

void MainWindow::dataReceived(const QByteArray &data)
{
    qDebug() << "Data received:" << data;

    if (data.startsWith("type=file"))
    {
        ui->fileList->clear();

        QStringList fileList = QString(data).split("\r\n");

        if (fileList.length() > 0)
        {
            for (int i = 0; i < fileList.length(); ++i)
            {
                if (fileList.at(i) != "")
                {
                    QStringList fileInfo = fileList.at(i).split(";");
                    QString fileName = fileInfo.at(4).simplified();

                    qDebug() << fileName;

                    // Display file list
                    ui->fileList->addItem(fileName);
                }
             }
        }
    }
    else
    {
        // Download finished
        QString folder = ui->downloadPath->text();
        QFile file(folder + "/" + downloadFileName);
        file.open(QIODevice::WriteOnly);
        file.write((data));
        file.close();
        QMessageBox::information(this, "Success", "File successfully downloaded.");
    }
}


