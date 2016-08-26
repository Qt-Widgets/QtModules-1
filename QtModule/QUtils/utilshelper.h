/**==================================================
 * 模块中所有方法都从这个类调取，由uitls调用这个单元中的方法
 *
 ====================================================*/


#ifndef UTILSHELPER_H
#define UTILSHELPER_H

#include <QObject>

#include "../common/qcusstomhelper.h"
#include "../base/qsingleton.h"

#define uitlHelper Singleton<UtilsHelper>::instance()

class UtilsHelper : public LCustomHelper
{
    Q_OBJECT

public:
    explicit UtilsHelper(QObject *parent = 0);
    ~UtilsHelper();

    void showMessage(const QString &title, const QString &info);
    void showFrmWindow(QVariant aParam, QVariant aParam1);
};

#endif // UTILSHELPER_H
