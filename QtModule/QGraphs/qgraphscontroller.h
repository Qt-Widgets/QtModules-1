#ifndef QGRAPHSCONTROLLER_H
#define QGRAPHSCONTROLLER_H

#include "qgraphs_global.h"
#include "../common/qtmodulecontroller.h"

class QGRAPHSSHARED_EXPORT QGraphsController : public QLModuleController
{

public:
    QGraphsController(QObject *parent = 0);
    ~QGraphsController();

    // QLModuleController interface
public:
    void initPluginFactory(QLModuleController *mdlController);
};

extern "C" QGRAPHSSHARED_EXPORT QLModuleController *LGetModuleController();

#endif // QGRAPHSCONTROLLER_H
