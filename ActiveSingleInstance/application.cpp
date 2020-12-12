#include "application.h"

#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <QProcess>
#include <QDebug>

Application::Application(int& argc, char** argv, int appFlag)
    : QApplication(argc, argv, appFlag)
{
}

bool Application::setupInstance(QString& msg)
{
    const QString serverName = QString("{%1-%2-3E2A779B-CE01-46e2-B80F-B9DE65DB232D}")
                               .arg(organizationName()).arg(applicationName());

    // 尝试连接服务: 如果连接成功，表示已有实例在运行；如果连接失败，则认为未有实例在运行
    {
        const int kTimeOut = 500;   //500 ms
        QLocalSocket socket;
        socket.connectToServer(serverName);
        if(socket.waitForConnected(kTimeOut)) {
            qWarning() << "exists a instance running!";
            return false; // 已有实例在运行
        }
    }
    // 连接失败时马上创建服务
    instanceService_ = new QLocalServer(this);
    connect(instanceService_, &QLocalServer::newConnection, this, [this](){
        qInfo() << "active instance!";
        emit activeInstance();
    });
    if(!instanceService_ ->listen(serverName)) {
        qWarning() << "instance serivce listen error: " << instanceService_->errorString()
                   << ", try to relisten...";
        QLocalServer::removeServer(serverName);
        if(!instanceService_ ->listen(serverName)){
            qWarning() << "instance serivce listen error again: " << instanceService_->errorString();
            msg = instanceService_->errorString();
            // 再次尝试失败
            return false;
        }
    }
    return true;
}

void Application::removeInstance()
{
    if(instanceService_){
        instanceService_->deleteLater();
        instanceService_ = nullptr;
    }
}

Application::~Application()
{
    removeInstance();
}
