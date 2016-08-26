#ifndef QSHELLHELPER_H
#define QSHELLHELPER_H

#include <QObject>
#include "../common/qcusstomhelper.h"

/**
 * 主程序辅助类，调用其他动态库的指令从这里发出
 * @author wzguo
 *
 * @date 2015-11-02
 *
 */

#define shellHelper Singleton<ShellHelper>::instance()

class ShellHelper : public LCustomHelper
{
    Q_OBJECT

public:
    explicit ShellHelper(QObject *parent = 0);

    ~ShellHelper();

    // 获取个人任务
    bool getPersonalTask(const QString &userId);

    // 检查版本更新
    int checkUpdate();
};

#endif // QSHELLHELPER_H
