#include "qutilscontroller.h"
#include "qutils.h"
#include "../base/qplugins.h"
#include "../base/objectfactory.h"

#include "../tianchi/tianchi.h"

#include <QDebug>

//DLL入口函数
QLModuleController *LGetModuleController()
{
    QUtilsController *utilController = new QUtilsController();

    qDebug() << "LGetModuleController == " << utilController;

    return utilController;
}

QUtilsController::QUtilsController(QObject *parent)
    :QLModuleController(parent)
{
    // 每个项目中都要设置日志产生路径和级别，不然程序不会记录日志
    tlog.setAppFile(qApp->applicationFilePath());
    tlog.setLogLevel(LOG_DEBUG);
}

QUtilsController::~QUtilsController()
{

}

void QUtilsController::initPluginFactory(QLModuleController *mdlController)
{
    //注册这个DLL的基础类，Qt的反射机制
    ObjectFactory::registerObject<QUtils >();

    /* createPlugin是供底层调用的函数，之所以这么做，是为了可以将主程序的参数传过来
     * QUtils 即DLL的基础类
     */
    new LPluginFactory(mdlController, createPlugin, QString("QUtils"), QString("Base Library"));
}



