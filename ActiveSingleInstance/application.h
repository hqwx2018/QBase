#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QObject>

class QLocalServer;
class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int& argc, char** argv, int appFlag = ApplicationFlags);
    ~Application();
    bool setupInstance(QString& msg);
    void removeInstance();

signals:
    void activeInstance();
private:
    QLocalServer* instanceService_ = nullptr;
};

#endif // APPLICATION_H
