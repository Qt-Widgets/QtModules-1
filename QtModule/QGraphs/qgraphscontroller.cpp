#include "qgraphscontroller.h"

#include "../base/qplugins.h"
#include "../base/objectfactory.h"
#include "../tianchi/tianchi.h"

#include "qgraphs.h"

QLModuleController *LGetModuleController()  //DLL入口函数
{
    QGraphsController *graphsController = new QGraphsController();

    qDebug() << "LGetModuleController == " << graphsController;
    return graphsController;
}

QGraphsController::QGraphsController(QObject *parent)
    :QLModuleController(parent)
{
    // 每个项目中都要设置日志产生路径和级别，不然程序不会记录日志
    tlog.setAppFile(qApp->applicationFilePath());
    tlog.setLogLevel(LOG_DEBUG);
}

QGraphsController::~QGraphsController()
{

}

void QGraphsController::initPluginFactory(QLModuleController *mdlController)
{
    ObjectFactory::registerObject<QGraphs >();  //注册这个DLL的基础类，Qt的放射机制
    new LPluginFactory(mdlController, createPlugin, QString("QGraphs"), QString("Graphs Drawing Library"));
}

