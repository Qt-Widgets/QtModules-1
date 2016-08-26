#include "qgraphs.h"


#include "../base/qcommand.h"
#include "../base/qconsts.h"
#include "../base/qplugins.h"

#include "qgraphshelper.h"

ILPlugin *createPlugin(QObject *obj)
{
    ILPlugin *graphs =  new QGraphs(obj);
    return graphs;
}

QGraphs::QGraphs(QObject *parent)
    :ILVisualPlugin(parent)
{
    this->setObjectName("QGraphs.dll");
    this->setParentName("ILVisualPlugin");
}

QGraphs::~QGraphs()
{

}

QVariant QGraphs::execCmd(int cmdID, QVariant aParam, QVariant aParam1)
{
    switch (cmdID) {
    case SYS_MAIN_GET_MENU:
    {
        WidgetGUICommond *menuCmd = new WidgetGUICommond();
        menuCmd->displayInfo = QString("曲线图");
        // 菜单栏中的菜单
        menuCmd->widgetType = GUI_WIDGET_QACTION;
        menuCmd->sParentName = QString("信息管理");
        menuCmd->orderId = 0;
        // 表示对应的模块
        menuCmd->moduleName = SYS_MUST_PLUGIN_GRAPHS;
        // 表示菜单对应的命令号
        menuCmd->cmdId = QString::number(SYS_GRAPHS_SHOW_CUSTOMPLOT);
        // 表示命令对应的图片
        menuCmd->iconPath = QString(":/images/print.png");
        QMap<int, WidgetGUICommond *> mapMenu;
        mapMenu[0] = menuCmd;

        QVariant varMap;
        varMap.setValue(mapMenu);
        return varMap;

        break;
    }

    case SYS_GRAPHS_SHOW_CUSTOMPLOT:
        graphHelper.showCustomPlot(aParam, aParam1);
        break;

    default:
        break;
    }
}

void QGraphs::hide()
{

}

void QGraphs::show()
{

}

