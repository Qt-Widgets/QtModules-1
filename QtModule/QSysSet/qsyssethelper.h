#ifndef QSYSSETHELPER_H
#define QSYSSETHELPER_H

#include <QObject>

#include "../common/qcusstomhelper.h"
#include "../base/qsingleton.h"

#define sysSetHelper Singleton<QSysSetHelper>::instance()

class QSysSetHelper : public LCustomHelper
{
     Q_OBJECT

public:
    QSysSetHelper(QObject *parent = 0);

    ~QSysSetHelper();

    void showMessage(const QString &title, const QString &info);

};

#endif // QSYSSETHELPER_H
