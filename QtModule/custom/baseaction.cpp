#include "baseaction.h"

BaseAction::BaseAction(QObject *parent)
    :QAction(parent)
{
    initAction();
}

BaseAction::BaseAction(const QString &text, QObject *parent)
    :QAction(text, parent)
{
    initAction();
}

BaseAction::BaseAction(const QString &text, const QString &sCmd, QObject *parent)
    :QAction(text, parent)
{
    this->sCommond = sCmd;
    initAction();
}

BaseAction::BaseAction(const QIcon &icon, const QString &text, QObject *parent)
    :QAction(icon, text, parent)
{
    initAction();
}

BaseAction::BaseAction(const QIcon &icon, const QString &text, const QString &sCmd, QObject *parent)
    :QAction(icon, text, parent)
{
    this->sCommond = sCmd;
    initAction();
}

BaseAction::~BaseAction()
{

}

QString BaseAction::getCmdInfo()
{
    return this->sCommond;
}

void BaseAction::setCmdInfo(const QString &sCmd)
{
    this->sCommond = sCmd;
}

QString BaseAction::getModuleName()
{
    return this->sModuleName;
}

void BaseAction::setModuleName(const QString &sName)
{
    this->sModuleName = sName;
}

void BaseAction::initAction()
{
    //do something...
}
