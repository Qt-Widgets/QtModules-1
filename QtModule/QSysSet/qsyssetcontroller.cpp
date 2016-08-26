#include "qsyssetcontroller.h"

#include "../base/qplugins.h"
#include "../base/objectfactory.h"

#include "qsysset.h"
#include <QDebug>


QLModuleController *LGetModuleController()  //DLL入口函数
{
    QSysSetController *sysSetController = new QSysSetController();

    qDebug() << "LGetModuleController == " << sysSetController;
    return sysSetController;
}

QSysSetController::QSysSetController(QObject *parent)
    :QLModuleController(parent)
{

}

QSysSetController::~QSysSetController()
{

}

void QSysSetController::initPluginFactory(QLModuleController *mdlController)
{
    ObjectFactory::registerObject<QSysSet >();  //注册这个DLL的基础类，Qt的放射机制
    new LPluginFactory(mdlController, createPlugin, QString("QSysSet"), QString("System Setting Library"));

}
