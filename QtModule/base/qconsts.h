/**=================================================
* 系统常量声明单元，系统中所有的常量都在此声明
* @wzguo 2015-09 18
===================================================*/

#ifndef QCONSTS_H
#define QCONSTS_H

#include <QString>

// 定义在主界面中显示的命令类型
const     int    GUI_WIDGET_QMENUBAR               =   1;          //QMenuBar
const     int    GUI_WIDGET_QMENU                  =   2;
const     int    GUI_WIDGET_QPUSHBUTTON            =   3;          //QPushButton
const     int    GUI_WIDGET_QTOOLBAR               =   4;
const     int    GUI_WIDGET_QACTION                =   5;
const     int    GUI_WIDGET_QDOCKWIDGET            =   6;
const     int    GUI_WIDGET_QSTATUSBAR             =   7;
const     int    GUI_WIDGET_QWIDGET                =   8;

/**
 * @brief WidgetGUICommond
 *
 * @ 表示显示在主界面的命令的结构体
 *
 * @author wzguo  2015-11-02
 */

struct WidgetGUICommond
{
    int         parentId;      // 表示命令的父菜单的ID
    QString     sParentName;   // 父级菜单显示的名字

    int         orderId;       // 表示本菜单父菜单中的序号
    QString     orderName;     // 表示这个命令位于哪个命令的后面
    int         widgetType;    // 表示命令的类型，对应上面的ID
    QString     displayInfo;   // 表示要 显示的信息
    QString     tipInfo;       // 表示要显示的Tip信息

    QString     moduleName;      // 对应模块
    QString     cmdId;         // 对应的命令号
    QString     iconPath;      // ICON路径

    WidgetGUICommond()
    {
        parentId = 0;
        sParentName = "";

        orderId  = 0;
        orderName = "";
        widgetType = 0;

        displayInfo = "";
        tipInfo = "";

        cmdId = "0";
        iconPath = "";
    }
};

// 必须注册类型，否则报错：invalid application...
Q_DECLARE_METATYPE(WidgetGUICommond *);

#endif // QCONSTS_H
