#include "qsyssethelper.h"

#include <QMessageBox>

QSysSetHelper::QSysSetHelper(QObject *parent)
    :LCustomHelper(parent)
{

}

QSysSetHelper::~QSysSetHelper()
{

}

void QSysSetHelper::showMessage(const QString &title, const QString &info)
{
    QMessageBox::information(NULL, title, info);
}

