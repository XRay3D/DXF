#pragma once

#include "dxf/dxf.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(QStringView file ,QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    DxfFile dxf;
    Ui::MainWindow* ui;

    void testReading(const QString& file);
};
