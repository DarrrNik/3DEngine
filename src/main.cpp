#include <QApplication>
#include <QLabel>

#include <memory>

#include "MainWindow.hpp"

extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


int WinMain(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>();
    window->setWindowState(Qt::WindowFullScreen);
    window->show();

    return app.exec();
}
