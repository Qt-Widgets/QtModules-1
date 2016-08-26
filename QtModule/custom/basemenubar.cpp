#include "basemenubar.h"

#include <QDebug>

#include "basemenu.h"

BaseMenuBar::BaseMenuBar(QWidget *parent)
    :QMenuBar(parent)
{
    initMenuBar();
}

BaseMenuBar::~BaseMenuBar()
{

}

void BaseMenuBar::initMenuBar()
{
   // do something...
}

QAction *BaseMenuBar::addMenu(BaseMenu *menu)
{
    QAction *action = QMenuBar::addMenu((QMenu *)menu);
    menuList.append(menu);

    return action;
}

BaseMenu *BaseMenuBar::addMenu(const QString &title)
{
    QString menuTitle = title.trimmed();

    if(!menuTitle.contains('&'))
    {
        menuTitle = QString("&%1").arg(menuTitle);
    }

    QMenu *menu = QMenuBar::addMenu(menuTitle);

    BaseMenu *baseMenu = new BaseMenu(menu);
    menuList.append(baseMenu);

    return baseMenu;
}

BaseMenu *BaseMenuBar::addMenu(const QIcon &icon, const QString &title)
{
    QString menuTitle = title.trimmed();

    if(!menuTitle.contains('&'))
    {
        menuTitle = QString("&%1").arg(menuTitle);
    }

    QMenu *menu = QMenuBar::addMenu(icon, menuTitle);
    BaseMenu *baseMenu = new BaseMenu(menu);
    menuList.append(baseMenu);

    return baseMenu;
}

BaseMenu *BaseMenuBar::findMenu(BaseMenu *menu)
{
    if (!menuList.contains(menu))
    {
        return NULL;
    }

    return menu;
}

BaseMenu *BaseMenuBar::findMenu(const QString &title)
{
    QString menuTitle = title.trimmed();

    if(menuTitle == "")
    {
         return NULL;
    }

    if(!menuTitle.contains('&'))
    {
        menuTitle = QString("&%1").arg(menuTitle);
    }

    for (int i = 0; i < menuList.size(); ++i)
    {
        if (menuList.at(i)->title() == menuTitle)
        {
            return menuList.at(i);
            break;
        }
    }

    return NULL;
}



