#include <QApplication>
#include <QLabel>
#include <QShortCut>

#include <memory>

#include "MainWindow.hpp"

int WinMain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>();
    window->setWindowState(Qt::WindowFullScreen);
    window->show();

    QShortcut* exitShortcut = new QShortcut(window.get());
    exitShortcut->setKey(Qt::Key_Escape);
    exitShortcut->setEnabled(true);
    QObject::connect(exitShortcut, QShortcut::activated, window.get(), MainWindow::close);

    return app.exec();
}
