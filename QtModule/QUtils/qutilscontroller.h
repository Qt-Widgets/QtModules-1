#ifndef QUTILSCONTROLLER_H
#define QUTILSCONTROLLER_H

#include <QObject>

#include "qutils_global.h"
#include "../common/qtmodulecontroller.h"

//QLModuleController *LGetModuleController();

class QUTILSSHARED_EXPORT QUtilsController  : public QLModuleController
{
public:
    QUtilsController(QObject *parent = 0);//禁止构造函数

    ~QUtilsController();

    // QLModuleController interface
    void initPluginFactory(QLModuleController *mdlController) Q_DECL_OVERRIDE;

private:


};


extern "C" QUTILSSHARED_EXPORT QLModuleController *LGetModuleController();

#endif // QUTILSCONTROLLER_H
