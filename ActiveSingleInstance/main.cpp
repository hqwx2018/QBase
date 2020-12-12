#include "mainwindow.h"

#include "application.h"
int main(int argc, char *argv[])
{
    Application a(argc, argv);
    QString errMsg;
    if(!a.setupInstance(errMsg)){
        return 0;
    }

    MainWindow w;

    QObject::connect(&a, &Application::activeInstance, [&w](){
        w.setWindowState(w.windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
        w.show();
        w.activateWindow();
    });
    w.show();

    int ret = a.exec();
    a.removeInstance();
    return ret;
}
