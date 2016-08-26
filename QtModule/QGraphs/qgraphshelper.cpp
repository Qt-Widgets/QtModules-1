#include "qgraphshelper.h"

#include "frmcumentobject.h"

QGraphsHelper::QGraphsHelper(QObject *parent)
    :LCustomHelper(parent)
{

}

QGraphsHelper::~QGraphsHelper()
{

}

QGraphsHelper::showCustomPlot(QVariant aParam, QVariant aParam1)
{
    QMdiArea *mdiArea = aParam.value<QMdiArea *>();

    FrmCumentObject *frm = new FrmCumentObject();
    mdiArea->addSubWindow(frm);
    frm->show();
}


