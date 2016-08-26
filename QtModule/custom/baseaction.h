#ifndef BASEACTION_H
#define BASEACTION_H

/**
  * 自定义Action类，用于存储命令号
  *
  * @author wzguo 2015-10-28
  */

#include <QAction>

class BaseAction : public QAction
{
    Q_OBJECT

    Q_PROPERTY(QString cmdInfo READ getCmdInfo WRITE setCmdInfo)

public:
    BaseAction(QObject *parent = 0);
    BaseAction(const QString &text, QObject *parent = 0);
    BaseAction(const QString &text, const QString &sCmd, QObject *parent = 0);
    BaseAction(const QIcon &icon, const QString &text, QObject* parent = 0);
    BaseAction(const QIcon &icon, const QString &text, const QString &sCmd, QObject* parent = 0);

    ~BaseAction();

    QString getCmdInfo();
    void setCmdInfo(const QString &sCmd);

    QString getModuleName();
    void setModuleName(const QString &sName);
private:
    void initAction();

private:
    QString sCommond;
    QString sModuleName;
};

#endif // BASEACTION_H
