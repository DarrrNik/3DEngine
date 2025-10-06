#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) 
    : QMainWindow(parent, flags), ui(new Ui::MainWindow), oglWidget(new Scene({ ui->openGLWidget->size().width(), ui->openGLWidget->size().height() }, this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}
