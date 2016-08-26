#ifndef QCUSSTOMHELPER_H
#define QCUSSTOMHELPER_H

#include <QObject>

#include "qtintf.h"

/**
 * 辅助基类，每个模块都有一个辅助基类
 * 各种基础功能都在这个类中实现，如权限检查，获取系统参数，获取当前用户名，密码等等
 *
 * @date 2015-11-02
 */


class LCustomHelper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ILHost* fHost READ getHost)

public:
    explicit LCustomHelper(QObject *parent = 0);
    ~LCustomHelper();

    QVariant execCommand(const QString &sInstanceName, int cmdID, QVariant aParam, QVariant aParam1);

    ILHost* getHost();
    void setHost(ILHost *fHost);

    // 获取登陆账户相关信息
    QString getSysUserName();
    QString getSysUserId();
    QString getSysUserPwd();
    QString setSysUserGroup();

    //检查权限
    bool checkRight(int moduleID, int rightID, bool isShowMessage = true);

    // ...

private:
    void initPage();

private:
    ILHost* fHost;

};

#endif // QCUSSTOMHELPER_H
