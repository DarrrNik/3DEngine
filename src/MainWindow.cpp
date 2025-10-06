#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "Scene.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) 
    : QMainWindow(parent, flags), ui(new Ui::MainWindow), oglWidget(new Scene({ ui->openGLWidget->size().width(), ui->openGLWidget->size().height() }, this))
{
    delete ui->openGLWidget;
    ui->openGLWidget = oglWidget;
    ui->openGLWidget->setObjectName("openGLWidget");

    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
}
