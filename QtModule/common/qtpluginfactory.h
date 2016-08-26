#ifndef QTPLUGINFACTORY
#define QTPLUGINFACTORY

#include <QLibrary>
#include "qtintf.h"

class QLModuleController;

typedef
    ILPlugin* (* qLPluginCreateFunc)(QObject *); //定义函数指针，以备调用

/**------------------------------------------------------------------------------
LPluginDescriptor

插件属性类
------------------------------------------------------------------------------ - */
class LPluginDescriptor : public LBaseDescriptor
{
    Q_PROPERTY(LPluginType PluginType READ getPluginType)
    Q_PROPERTY(QObject *PluginClass READ fPluginClass)

public:
	LPluginDescriptor(QObject *parent = 0);

    LPluginDescriptor(const QString &parentObjName, const QString &sName, const QString &aDescription, QObject *parent = 0);
    LPluginDescriptor(ILPlugin *ilPugin, const QString &aDescription, QObject *parent = 0);

    ~LPluginDescriptor();

    bool CheckPluginInterface(const QString &AnIID);

	LPluginType getPluginType();

    void setPluginType(LPluginType type);

private:
    void setDescriptPluginType(const QString &sObjectName);

private:
	QObject *fPluginClass;
    LPluginType fPluginType;
};

#define LPluginDescriptor_IID "com.qt.example.Plugin.LPluginDescriptor"
Q_DECLARE_INTERFACE(LPluginDescriptor, LPluginDescriptor_IID)


/**
 * 插件工厂基类
 *
 */
class LBasePluginFactory : public QObject
{
    Q_PROPERTY(LPluginDescriptor *Descriptor READ fDescriptor)

public:
	LBasePluginFactory(QObject *parent = 0);

	virtual ~LBasePluginFactory() {};

    virtual  ILPlugin *createInstance(ILHost* qHost) = 0;
    virtual  ILPlugin *createInstance(ILHost* qHost, ILPlugin *instance) = 0;

	LPluginDescriptor *getDescriptor();

    void setDescriptor(LPluginDescriptor *descriptor);

protected:
	LPluginDescriptor *fDescriptor;

};

#define LBasePluginFactory_IID "com.qt.example.Plugin.LBasePluginFactory"
Q_DECLARE_INTERFACE(LBasePluginFactory, LBasePluginFactory_IID)


/**
 * 插件工厂类
 *
 */

class LPluginFactory :public LBasePluginFactory
{

public:
	LPluginFactory(QObject *parent = 0);
    LPluginFactory(QLModuleController *mdlController,const QString &lpluginName, ILPlugin *iPlugin, const QString &parentObjName, const QString &aDescription = "", QObject *parent = 0);
    LPluginFactory(QLModuleController *mdlController, ILPlugin *iPlugin, const QString &aDescription = "", QObject *parent = 0);

    LPluginFactory(const QString &lpluginName, qLPluginCreateFunc fPluginFunc, const QString &parentObjName, const QString &aDescription = "", QObject *parent = 0);
    LPluginFactory(QLibrary *instanceLib, qLPluginCreateFunc fPluginFunc, LPluginDescriptor *aDescriptior, QObject *parent = 0);

    LPluginFactory(QLModuleController *mdlController, qLPluginCreateFunc fPluginFunc, const QString &sObjName, const QString &aDescription = "", QObject *parent = 0);

    virtual ~LPluginFactory(){};

    ILPlugin *createInstance(ILHost *qHost) Q_DECL_OVERRIDE;
    ILPlugin *createInstance(ILHost *qHost, ILPlugin *instance) Q_DECL_OVERRIDE;

private:
    void initFactoryInfo(QLibrary *instanceLib, qLPluginCreateFunc fPluginFunc, LPluginDescriptor *aDescriptior);

private:
    qLPluginCreateFunc qPluginFunc;

    ILPlugin *instancePlugin;

};


#endif // QTPLUGINFACTORY

