#ifndef QSYSSETCONTROLLER_H
#define QSYSSETCONTROLLER_H

#include "qsysset_global.h"
#include "../common/qtmodulecontroller.h"

class QSYSSETSHARED_EXPORT QSysSetController: public QLModuleController
{

public:
    QSysSetController(QObject *parent = 0);

    ~QSysSetController();

    // QLModuleController interface
public:
    void initPluginFactory(QLModuleController *mdlController) Q_DECL_OVERRIDE;
};


extern "C" QSYSSETSHARED_EXPORT QLModuleController *LGetModuleController();

#endif // QSYSSETCONTROLLER_H
