#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "OGLScene.hpp"

#include <QShortcut>
#include <QPushButton>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) 
    : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);       

    auto exitShortcut = new QShortcut(Qt::Key_Escape, this);
    connect(exitShortcut, &QShortcut::activated, this, &MainWindow::close);

    connect(ui->addCubeButton, &QPushButton::clicked, ui->openGLWidget, &OGLScene::OnAddCube);
    connect(ui->addSphereButton, &QPushButton::clicked, ui->openGLWidget, &OGLScene::OnAddSphere);
    connect(ui->addTriangleButton, &QPushButton::clicked, ui->openGLWidget, &OGLScene::OnAddTriangle);
    
    connect(ui->openGLWidget, SIGNAL(ObjectAdded(const QString&)), this, SLOT(OnObjectAdded(const QString&)));
    connect(ui->objectsComboBox, SIGNAL(currentIndexChanged(int)), ui->openGLWidget, SLOT(OnActiveObjectChanged(int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnObjectAdded(const QString& name) {
    ui->objectsComboBox->addItem(name);
}
