#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
//#include <libdxfrw/src/libdxfrw.h>
//#include <libdxfrw/src/mydrwinterface.h>

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
    //const QString str("D:/PRO/VBA/Новая папка/1.dxf");
    const QString str("D:/MAN2/МАН2_SCH_PCB/V2/МАН2_МСИС_V2_.dxf");
    dxf.read(str);

    //    dxfRW dxf(str.toLocal8Bit().data());
    //    MyDRWInterface ifs;
    //    qDebug() << "dxf.read" << dxf.read(&ifs, true);
}
