#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	QGraphicsDropShadowEffect* shadow = new
	QGraphicsDropShadowEffect();
	shadow->setXOffset(4);
	shadow->setYOffset(4);
	ui->label->setGraphicsEffect(shadow);

	QGraphicsColorizeEffect* colorize = new
	QGraphicsColorizeEffect();
	colorize->setColor(QColor(255, 0, 0));
	ui->butterfly->setGraphicsEffect(colorize);

	QGraphicsBlurEffect* blur = new QGraphicsBlurEffect();
	blur->setBlurRadius(12);
	ui->label2->setGraphicsEffect(blur);

	QGraphicsOpacityEffect* alpha = new QGraphicsOpacityEffect();
	alpha->setOpacity(0.2);
	ui->penguin->setGraphicsEffect(alpha);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QImage image;
	image.load("checker.jpg");

    QImage image2;
    image2.load("tux.png");

    QImage image3;
    image3.load("butterfly.png");

    QPainter painter(this);



}
