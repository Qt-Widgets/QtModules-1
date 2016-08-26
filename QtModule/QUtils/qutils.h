#ifndef QUTILS_H
#define QUTILS_H

#include "../common/qtintf.h"
#include "../common/qtmodulecontroller.h"
#include "../base/qsingleton.h"

ILPlugin *createPlugin(QObject *obj);  // 供底层程序调用

class QUtils : public ILVisualPlugin
{
  Q_OBJECT

public:
    QUtils(QObject *parent = 0);

    ~QUtils();


    // ILPlugin interface
public:
    QVariant execCmd(int cmdID, QVariant aParam, QVariant aParam1) Q_DECL_OVERRIDE;

    // ILNonVisualPlugin interface
protected:
    void showMenuItem() Q_DECL_OVERRIDE;


    // ILVisualPlugin interface
public:
    void hide() Q_DECL_OVERRIDE;
    void show() Q_DECL_OVERRIDE;
};

#endif // QUTILS_H
