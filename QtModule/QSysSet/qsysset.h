#ifndef QSYSSET_H
#define QSYSSET_H

#include <QObject>
#include "../common/qtintf.h"
#include "../common/qtmodulecontroller.h"

ILPlugin *createPlugin(QObject *obj);  // 供底层程序调用

class QSysSet: public ILNonVisualPlugin
{
  Q_OBJECT

public:
    QSysSet(QObject *parent = 0);

    ~QSysSet();

    // ILPlugin interface
public:
    QVariant execCmd(int cmdID, QVariant aParam, QVariant aParam1) Q_DECL_OVERRIDE;

    // ILNonVisualPlugin interface
public:
    void showMenuItem() Q_DECL_OVERRIDE;
};

#endif // QSYSSET_H
