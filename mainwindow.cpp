#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QSettings>
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

    {
        QSettings s("dxf.ini", QSettings::IniFormat);
        restoreState(s.value("State").toByteArray());
        restoreGeometry(s.value("Geometry").toByteArray());
        ui->lineEdit->setText(s.value("lineEdit").toString());
    }

    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    {
        QSettings s("dxf.ini", QSettings::IniFormat);
        s.setValue("State", saveState());
        s.setValue("Geometry", saveGeometry());
        s.setValue("lineEdit", ui->lineEdit->text());
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    scene->clear();
    const QString str(ui->lineEdit->text());
    dxf.read(str);
}
