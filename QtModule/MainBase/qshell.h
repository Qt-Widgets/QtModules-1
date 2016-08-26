#ifndef QSHELL_H
#define QSHELL_H

#include <QObject>
#include <QMdiArea>

#include "../common/qtmodulemanager.h"
#include "../common/qtintf.h"
#include "../base/qsingleton.h"

#include "qshellhelper.h"

/**
  * 模块集中管理类，负责加载各个模块DLL
  *
  * @date 2015-11-02
  */

#define shell Singleton<Shell>::instance()

class Shell : public QObject
{
    //Q_OBJECT

public:
    explicit Shell(QObject *parent = 0);

    ~Shell();

    void loadPlugin(const QString sLoadPath);

    void  setSystemName(const QString &sysName);

    ILHost *getHost();
    void setHost(ILHost *qHost);

    void setPluginpLoadPath(const QString sloadPath);

private:
    QVariant execCMD(int aCmdID, QVariant aParam, QVariant aParam1);

    int  loadBasePlugin();
    int  loadOtherPlugin();

private:
    QtModuleManager *fModuleManager;
    ILHost *fHost;
};


#endif // QSHELL_H
