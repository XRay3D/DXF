#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //dxf.read("D:/ЛИТЕРАТУРА/DXF/HC-01_16_МКЛВ_V1.DXF");
    dxf.read("D:/MAN2/МАН2_SCH_PCB/V2/МАН2_МСИС_V2_.dxf");
}
