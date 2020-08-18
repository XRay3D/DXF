#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

QGraphicsScene* scene;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene = new QGraphicsScene(ui->graphicsView));
    ui->graphicsView->scene()->setObjectName("scene");
    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //dxf.read("D:/ЛИТЕРАТУРА/DXF/HC-01_16_МКЛВ_V1.DXF");
    dxf.read("D:/PRO/VBA/Новая папка/1.dxf");
}
