#ifndef QGRAPHSHELPER_H
#define QGRAPHSHELPER_H

#include "../common/qcusstomhelper.h"
#include "../base/qsingleton.h"

#define graphHelper Singleton<QGraphsHelper>::instance()

class QGraphsHelper : public LCustomHelper
{
     Q_OBJECT

public:
    QGraphsHelper(QObject *parent = 0);

    ~QGraphsHelper();

    showCustomPlot(QVariant aParam, QVariant aParam1);
};

#endif // QGRAPHSHELPER_H
