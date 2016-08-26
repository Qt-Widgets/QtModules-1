#include <QMessageBox>

#include "qutils.h"
#include "../common/qtpluginfactory.h"
#include "../base/qcommand.h"
#include "../base/qconsts.h"
#include "../base/qplugins.h"
#include "utilshelper.h"
#include "../tianchi/tianchi.h"

ILPlugin *createPlugin(QObject *obj)
{
    ILPlugin *utils =  new QUtils(obj);

    return utils;
}

/**
 * 注意： ****以下两项必须设置*****
 *
 * 1、设置该模块的DLL的名字，包括后缀，底层通过DLL名字调用对应模块
 * 2、该类实现的基类的名字，暂时没找到获取基类名字的方法，先手动设置
 *
 * @author wzguo 2015-09-24
 */

QUtils::QUtils(QObject *parent)
    :ILVisualPlugin(parent)
{
    this->setObjectName("QUtils.dll");
    this->setParentName("ILVisualPlugin");

    tlog.debug("this->setObjectName(QUtils.dll");
   /*do something ...*/
}

QUtils::~QUtils()
{

}


QVariant QUtils::execCmd(int cmdID, QVariant aParam, QVariant aParam1)
{
    switch (cmdID) {
    case SYS_MAIN_GET_MENU:
    {
        WidgetGUICommond *menuCmd = new WidgetGUICommond();
        menuCmd->displayInfo = QString("信息登记");
        // 菜单栏中的菜单
        menuCmd->widgetType = GUI_WIDGET_QACTION;
        menuCmd->sParentName = QString("信息管理");
        menuCmd->orderId = 0;
        // 表示菜单对应的命令号
        menuCmd->cmdId = QString::number(SYS_UTILS_FRMUTILS_WIDGET);
        menuCmd->moduleName = SYS_MUST_PLUGIN_UTILS;
        // 表示命令对应的图片
        menuCmd->iconPath = QString(":/images/info.png");
        QMap<int, WidgetGUICommond *> mapMenu;
        mapMenu[0] = menuCmd;

        menuCmd = new WidgetGUICommond();
        menuCmd->displayInfo = QString("信息登记");
        // 菜单栏中的菜单
        menuCmd->widgetType = GUI_WIDGET_QACTION;
        menuCmd->sParentName = QString("Help");
        menuCmd->orderId = 0;
        menuCmd->orderName = QString("About");
        // 表示菜单对应的命令号
        menuCmd->cmdId = QString::number(SYS_UTILS_FRMUTILS_WIDGET);
        // 表示命令对应的图片
        menuCmd->iconPath = QString(":images/paste.png");
        mapMenu[1] = menuCmd;

        QVariant varMap;
        varMap.setValue(mapMenu);
        return varMap;

        break;
    }

    case SYS_UTILS_FRMUTILS_WIDGET:
        uitlHelper.showFrmWindow(aParam, aParam1);
        break;

    case SYS_UTILS_SEND_MESSAGE:
        uitlHelper.showMessage(aParam.toString(), aParam1.toString());
        break;

    default:
        break;
    }
}

void QUtils::showMenuItem()
{

}

void QUtils::hide()
{
    return;
}

void QUtils::show()
{
    return;
}

