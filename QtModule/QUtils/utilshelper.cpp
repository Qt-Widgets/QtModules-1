#include "utilshelper.h"

#include <QMessageBox>

#include "frmutils.h"
#include "../base/widgetfactory.h"


UtilsHelper::UtilsHelper(QObject *parent)
    :LCustomHelper(parent)
{

}

void UtilsHelper::showMessage(const QString &title, const QString &info)
{
    QMessageBox::information(NULL, title, info);
}

void UtilsHelper::showFrmWindow(QVariant aParam, QVariant aParam1)
{
    QMdiArea *mdiArea = aParam.value<QMdiArea *>();

    FrmUtils *frm = new FrmUtils();
    mdiArea->addSubWindow(frm);
    frm->show();
}


UtilsHelper::~UtilsHelper()
{

}

