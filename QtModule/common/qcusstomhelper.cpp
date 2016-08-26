#include "qcusstomhelper.h"
#include <QDebug>

LCustomHelper::LCustomHelper(QObject *parent)
    : QObject(parent)
{
    initPage();
}

LCustomHelper::~LCustomHelper()
{

}

QVariant LCustomHelper::execCommand(const QString &sInstanceName, int cmdID, QVariant aParam, QVariant aParam1)
{
    qDebug() << "qCusstomHelper::execCommand -- " <<"Begin";
    if(NULL != fHost)
    {
        fHost->execCmd(sInstanceName, cmdID, aParam, aParam1);
    }

    qDebug() << "qCusstomHelper::execCommand -- " <<"End";
}

ILHost *LCustomHelper::getHost()
{
    return this->fHost;
}

void LCustomHelper::setHost(ILHost *fHost)
{
    this->fHost= fHost;
}

QString LCustomHelper::getSysUserName()
{

}

QString LCustomHelper::getSysUserId()
{

}

QString LCustomHelper::getSysUserPwd()
{

}

QString LCustomHelper::setSysUserGroup()
{

}

bool LCustomHelper::checkRight(int moduleID, int rightID, bool isShowMessage)
{

}

void LCustomHelper::initPage()
{

}

