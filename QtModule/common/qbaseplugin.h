#ifndef QBASEPLUGIN
#define QBASEPLUGIN

#include <QObject>
#include <QString>
#include <QtPlugin>
#include <QWidget>
#include <QVariant>

/**
 * 插件基础接口，所有DLL必须实现这个接口
 *
 */
class QBasePlugin: public QObject
{

public:
	QBasePlugin(QObject *parent = 0);

    virtual ~QBasePlugin() {};

    virtual QVariant ExecCmd(const QString instanceName, int cmdID, QVariant param) = 0;

    virtual QWidget *createWidget(QWidget *parent) = 0;
};

QT_BEGIN_NAMESPACE

#define QBasePlugin_IID "com.qt.example.Plugin.QBasePlugin/1.0"

Q_DECLARE_INTERFACE(QBasePlugin, QBasePlugin_IID)

QT_END_NAMESPACE

#endif // QBASEPLUGIN

