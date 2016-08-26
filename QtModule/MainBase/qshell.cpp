#include "qshell.h"

#include <QApplication>
#include <QDebug>

#include "../../Base/qconsts.h"
#include "../tianchi/tianchi.h"

Shell::Shell(QObject *parent)
    : QObject(parent)
{
    fModuleManager = new QtModuleManager(parent);
    fHost = fModuleManager;

    shellHelper.setHost(fModuleManager);
}

Shell::~Shell()
{
    if(fModuleManager != NULL)
    {
        delete fModuleManager;
        fModuleManager = NULL;
        fHost = NULL;
    }
}

int Shell::loadBasePlugin()
{
    qDebug() << "QUtils loadBasePlugin Begin";

    try
    {
        qDebug() << "QUtils loadModule Begin";
        fModuleManager->loadModule("QUtils.dll");
        qDebug() << "loadModule end";

        qDebug() << "QUtils createAllInstances Begin";
        fModuleManager->createAllInstances();
        qDebug() << "QUtils createAllInstances end";
    }
    catch(QString &strError)
    {
        qDebug() <<"QUtils load error: " << strError;
    }

    return 1;
    qDebug() << "QUtils loadBasePlugin End";
}

int Shell::loadOtherPlugin()
{
    qDebug() << "Shell loadOtherPlugin Begin";

    QDir pluginsDir(qApp->applicationDirPath());
   #if defined(Q_OS_WIN)
       if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
       {
           pluginsDir.cdUp();
       }
   #elif defined(Q_OS_MAC)
       if (pluginsDir.dirName() == "MacOS")
       {
           pluginsDir.cdUp();
           pluginsDir.cdUp();
           pluginsDir.cdUp();
       }
   #endif

    pluginsDir.cd("modules");
    int nloadCount = 0;
    try
    {
        foreach (QString fileName, pluginsDir.entryList(QDir::Files))
        {
            QString file = fileName.trimmed();
            // 过滤其他文件
            if (file.toLower().contains("dll"))
            {
                fModuleManager->loadModule(file);
                nloadCount += 1;
            }
        }

        // 动态库加载完成后再初始化
        fModuleManager->createAllInstances();
    }
    catch(QString &strError)
    {
       qDebug() <<"Shell loadOtherPlugin error: " << strError;
    }

    return nloadCount;
    qDebug() << "Shell loadOtherPlugin End";
}

void Shell::loadPlugin(const QString sLoadPath)
{
    shell.setPluginpLoadPath(sLoadPath);

    tlog.debug("------loadBasePlugin begin------", __FILE__, __LINE__);
    shell.loadBasePlugin();
    tlog.debug("------loadBasePlugin end------", __FILE__, __LINE__);

    tlog.debug("------loadOtherPlugin begin------", __FILE__, __LINE__);
    shell.loadOtherPlugin();
    tlog.debug("------loadOtherPlugin end------", __FILE__, __LINE__);
}

void Shell::setSystemName(const QString &sysName)
{
    return;
}

ILHost *Shell::getHost()
{
    return this->fHost;
}

void Shell::setHost(ILHost *qHost)
{
    this->fHost = qHost;
}

void Shell::setPluginpLoadPath(const QString sloadPath)
{
    fModuleManager->setPluginpLoadPath(sloadPath);
}

//主程序中的命令，在这里中转
QVariant Shell::execCMD(int aCmdID, QVariant aParam, QVariant aParam1)
{
    qDebug() << "execCMD Begin " << "aCmdID = " << aCmdID;

    switch(aCmdID)
    {
    case 0:

        break;
    case 1:

        break;
    default:
        qDebug()<<"Error: aCmdID is undefind";
        break;
    }

    qDebug()<<"execCMD End ";
}

