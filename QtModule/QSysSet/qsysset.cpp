#include "qsysset.h"
#include "qsyssethelper.h"

#include "../common/qtpluginfactory.h"
#include "../base/qcommand.h"
#include "../tianchi/tianchi.h"

ILPlugin *createPlugin(QObject *obj)
{
    ILPlugin *sysset =  new QSysSet(obj);
    return sysset;
}

QSysSet::QSysSet(QObject *parent)
    :ILNonVisualPlugin(parent)
{
    this->setObjectName("QSysSet.dll");
    this->setParentName("ILNonVisualPlugin");
}

QSysSet::~QSysSet()
{

}

QVariant QSysSet::execCmd(int cmdID, QVariant aParam, QVariant aParam1)
{
    switch (cmdID) {

    case SYS_SYSSET_SEND_MESSAGE:
        sysSetHelper.showMessage(aParam.toString(), aParam1.toString());
        break;

    default:
        break;
    }
}

void QSysSet::showMenuItem()
{

}

