#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <dl_dxf.h>
#include <examples/readwrite/test_creationclass.h>
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
//    const QString str(ui->lineEdit->text());
//    dxf.read(str);
    testReading(ui->lineEdit->text().toLocal8Bit().data());
}

void MainWindow::testReading(char* file)
{
    // Load DXF file into memory:
    qWarning() << "Reading file " << file << "...\n";
    Test_CreationClass* creationClass = new Test_CreationClass();
    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in(file, creationClass)) { // if file open failed
        qWarning() << file << " could not be opened.\n";
        return;
    }
    delete dxf;
    delete creationClass;
}
