#pragma once

#include <QWidget>
#include <QMainWindow>

class Ui_MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~MainWindow();
private:
    Ui_MainWindow* ui;
};

