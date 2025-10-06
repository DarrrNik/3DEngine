#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QOpenGLWidget>

class Scene;

namespace Ui { class MainWindow; };

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~MainWindow();
private:
    Ui::MainWindow* ui;

    Scene* oglWidget;
};

