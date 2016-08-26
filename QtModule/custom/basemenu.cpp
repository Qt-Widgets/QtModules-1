#include "basemenu.h"

BaseMenu::BaseMenu(QWidget *parent)
    :QMenu(parent)
{
    mmenu = new QMenu(parent);
    initMenu();
}

BaseMenu::BaseMenu(const QString &title, QWidget *parent)
    :QMenu(title, parent)
{
    mmenu = new QMenu(title, parent);
    initMenu();
}

BaseMenu::BaseMenu(QMenu *menu, QWidget *parent)
    :QMenu(menu->title(), parent)
    ,mmenu(menu)
{
    initMenu();
}

BaseMenu::~BaseMenu()
{

}

void BaseMenu::initMenu()
{
    // do something...
}


QAction *BaseMenu::addAction(const QString &text)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QAction *action = mmenu->addAction(text);
    mapAction[mapAction.count()] = action;

    return action;
}

QAction *BaseMenu::addAction(const QIcon &icon, const QString &text)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QAction *action = mmenu->addAction(icon, text);
    mapAction[mapAction.count()] = action;

    return action;
}

QAction *BaseMenu::addAction(const QString &text, const QObject *receiver, const char *member, const QKeySequence &shortcut)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QAction *action = mmenu->addAction(text, receiver, member, shortcut);
    mapAction[mapAction.count()] = action;

    return action;
}

QAction *BaseMenu::addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char *member, const QKeySequence &shortcut)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QAction *action = mmenu->addAction(icon, text, receiver, member, shortcut);
    mapAction[mapAction.count()] = action;

    return action;
}

void BaseMenu::addAction(QAction *action)
{
    if(NULL == mmenu)
    {
        return;
    }

    mmenu->addAction(action);
    mapAction[mapAction.count()] = action;

    return;
}

QAction *BaseMenu::addMenu(QMenu *menu)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QAction *action = mmenu->addMenu(menu);
    mapAction[mapAction.count()] = action;

    return action;
}

QAction *BaseMenu::addSection(const QString &text)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QString title = text.trimmed();
    if(!title.contains('&'))
    {
        title = QString("&%1").arg(title);
    }

    QAction *action = mmenu->addSection(title);
    mapAction[mapAction.count()] = action;

    return action;
}

QAction *BaseMenu::addSection(const QIcon &icon, const QString &text)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    QString title = text.trimmed();
    if(!title.contains('&'))
    {
        title = QString("&%1").arg(title);
    }

    QAction *action = mmenu->addSection(icon, title);
    mapAction[mapAction.count()] = action;

    return action;
}

QAction *BaseMenu::addAction(const QString &beforeTitle, const QString &text)
{
    QString title = text.trimmed();
    if(!title.contains('&'))
    {
        title = QString("&%1").arg(title);
    }

   return addAction(beforeTitle, new QAction(title, this));
}

QAction *BaseMenu::addAction(const QString &beforeTitle, QAction *action)
{
    QString text = beforeTitle.trimmed();
    if(!text.contains('&'))
    {
        text = QString("&%1").arg(text);
    }

    QMap<int, QAction *>::iterator mapBegin, mapEnd;
    mapBegin = mapAction.begin();
    mapEnd = mapAction.end();

    int index = -1;

    for(; mapBegin != mapEnd; mapBegin++)
    {
         if(mapBegin.value()->text().trimmed() == text)
         {
             index = mapBegin.key();
             break;
         }
    }

    if(index == -1)
    {
        return NULL;
    }

    return addAction(index, action);
}

QAction *BaseMenu::addAction(int index, const QString &text)
{
    QString title = text.trimmed();
    if(!title.contains('&'))
    {
        title = QString("&%1").arg(title);
    }

    QAction *action = new QAction(title, this);
    return addAction(index, action);
}

QAction *BaseMenu::addAction(int index, QAction *action)
{
    if(NULL == mmenu)
    {
        return NULL;
    }

    mapAction.insert(index, action);

    QMap<int, QAction *>::iterator mapBegin, mapEnd;
    mapBegin = mapAction.begin();
    mapEnd = mapAction.end();

    for(; mapBegin != mapEnd; mapBegin++)
    {
        mmenu->removeAction(mapBegin.value());
        mmenu->addAction(mapBegin.value());
    }

    return action;
}

QAction *BaseMenu::findAction(QAction *action)
{
    QMap<int, QAction *>::iterator mapBegin, mapEnd;
    mapBegin = mapAction.begin();
    mapEnd = mapAction.end();

    for(; mapBegin != mapEnd; mapBegin++)
    {
         if(mapBegin.value()->text().trimmed() == action->text().trimmed())
         {
             return mapBegin.value();
             break;
         }
    }

    return NULL;
}

QAction *BaseMenu::findAction(const QString &text)
{
    QString actionTitle = text.trimmed();
    if(!actionTitle.contains('&'))
    {
        actionTitle = QString("&%1").arg(actionTitle);
    }

    QMap<int, QAction *>::iterator mapBegin, mapEnd;
    mapBegin = mapAction.begin();
    mapEnd = mapAction.end();

    for(; mapBegin != mapEnd; mapBegin++)
    {
         if(mapBegin.value()->text().trimmed() == actionTitle)
         {
             return mapBegin.value();
             break;
         }
    }

    return NULL;
}

