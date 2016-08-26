#ifndef QTMODULECONTROLLER
#define QTMODULECONTROLLER

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QList>

#include "qtintf.h"
#include "qtpluginfactory.h"

QT_BEGIN_NAMESPACE

class QLModuleController;

typedef
    QLModuleController* (*qLModuleControllerFunc)(); //定义函数指针，以备调用


/*------------------------------------------------------------------------------
LModuleDescriptor

模块控制器属性类
记录模块控件器的一些描述信息，暂与基类相同
------------------------------------------------------------------------------ - */
class LModuleDescriptor: public LBaseDescriptor
{
public:
    LModuleDescriptor(QObject *parent = 0);

	virtual ~LModuleDescriptor(){};

private:

};



/*------------------------------------------------------------------------------
LModuleController

模块控制器类
一个插件DLL必须要有一个模块控制器 并且只能有一个
DLL对外的接口就是一个模块控制器，通过模块控制器来实现DLL内各个插件的创建
------------------------------------------------------------------------------ - */
class QLModuleController :public ILModuleController
{
	Q_PROPERTY(LBasePluginFactory *factory READ getFactory)
    Q_PROPERTY(int factoryCount READ getFactoryCount)
    Q_PROPERTY(long hostHwnd READ getHostHwnd WRITE setHostHwnd)
    Q_PROPERTY(LModuleDescriptor *descriptor READ getDescriptor)

public:
	virtual ~QLModuleController(){};

	QLModuleController(QObject *parent = 0);
	QLModuleController(const QString &libName, const QString &aDescription = "", QObject *parent = 0);

    long getDLLInstance();
	void registPluginFactory(LBasePluginFactory *pluginFactory);

    LBasePluginFactory *findFacotory(const QString &pluginName);
    bool findFacotory(LBasePluginFactory *pluginFactory);


    void setHostHwnd(long value) Q_DECL_OVERRIDE;
    long getHostHwnd() Q_DECL_OVERRIDE;


	int getFactoryCount();
    LBasePluginFactory *getFactory(int index);

	LModuleDescriptor *getDescriptor();

    virtual void initPluginFactory(QLModuleController *mdlController) = 0;  // 子类必须实现这个接口

protected:
	virtual void initializeObject();
	

private:
    ILHost *getHost();

private:
    QList<LBasePluginFactory *> factoryList;

	ILHost *mHost;
    long fOldHandle;

	LModuleDescriptor *fDescriptor;

    // ILHostAware interface
public:
    void setHost(ILHost *host);
};

QT_END_NAMESPACE

#endif // QTMODULECONTROLLER

