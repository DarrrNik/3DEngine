#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QMainWindow>
#include <QOpenGLWidget>

class QShortcut;
class OGLScene;

namespace Ui { class MainWindow; };

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~MainWindow();
public slots:
    void OnObjectAdded(const QString& name);
private:
    Ui::MainWindow* ui;

    QShortcut* exitShortcut;
};

#endif
