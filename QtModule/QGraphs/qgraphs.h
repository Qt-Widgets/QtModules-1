#ifndef QGRAPHS_H
#define QGRAPHS_H

#include "../common/qtintf.h"
#include "../common/qtmodulecontroller.h"

ILPlugin *createPlugin(QObject *obj);  // 供底层程序调用

class QGraphs : public ILVisualPlugin
{
    Q_OBJECT

public:
    QGraphs(QObject *parent = 0);

    ~QGraphs();

    // ILPlugin interface
public:
    QVariant execCmd(int cmdID, QVariant aParam, QVariant aParam1) Q_DECL_OVERRIDE;


    // ILVisualPlugin interface
public:
    void hide() Q_DECL_OVERRIDE;
    void show() Q_DECL_OVERRIDE;
};

#endif // QGRAPHS_H
