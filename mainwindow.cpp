#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <tables/layermodel.h>
//#include <dl_dxf.h>
//#include <examples/readwrite/test_creationclass.h>
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

    connect(ui->graphicsView, &GraphicsView::fileDroped, [](QStringView file) {
        auto w = new MainWindow(file);
        w->show();
    } /* this, &MainWindow::testReading*/);

    {
        QSettings s("dxf.ini", QSettings::IniFormat);
        restoreState(s.value("State").toByteArray());
        restoreGeometry(s.value("Geometry").toByteArray());
        ui->splitter->restoreState(s.value("Splitter").toByteArray());
        ui->lineEdit->setText(s.value("lineEdit").toString());
    }

    on_pushButton_clicked();
}

MainWindow::MainWindow(QStringView file, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene = new QGraphicsScene(ui->graphicsView));
    ui->graphicsView->scene()->setObjectName("scene");
    //    connect(ui->graphicsView, &GraphicsView::fileDroped, this, &MainWindow::testReading);
    connect(ui->graphicsView, &GraphicsView::fileDroped, [](QStringView file) {
        auto w = new MainWindow(file);
        w->show();
    } /* this, &MainWindow::testReading*/);

    {
        QSettings s("dxf.ini", QSettings::IniFormat);
        restoreState(s.value("State").toByteArray());
        restoreGeometry(s.value("Geometry").toByteArray());
        ui->splitter->restoreState(s.value("Splitter").toByteArray());
        ui->lineEdit->setText(s.value("lineEdit").toString());
    }

    ui->lineEdit->setText(file.toString());

    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    {
        QSettings s("dxf.ini", QSettings::IniFormat);
        s.setValue("State", saveState());
        s.setValue("Geometry", saveGeometry());
        s.setValue("Splitter", ui->splitter->saveState());
        s.setValue("lineEdit", ui->lineEdit->text());
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->lineEdit->text();
    if (ui->tableView->model())
        delete ui->tableView->model();
    ui->tableView->setModel(new LayerModel({}));
    scene->clear();
    const QString str(ui->lineEdit->text());
    if (dxf.read(str)) {
        ui->tableView->setModel(new LayerModel(dxf.layers));
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void MainWindow::testReading(const QString& file)
{
    qDebug() << file;
    ui->tableView->setEnabled(false);
    ui->lineEdit->setText(file);
    on_pushButton_clicked();
    ui->tableView->setEnabled(true);
}
