#include "qtpluginfactory.h"
#include "qtmodulecontroller.h"

#include <QDebug>
#include <QMessageBox>

#include "../Base/objectfactory.h"


/*LPluginDescriptor*/
LPluginDescriptor::LPluginDescriptor(QObject *parent )
    :LBaseDescriptor(parent)
{

}

LPluginDescriptor::LPluginDescriptor(const QString &parentObjName, const QString &sName, const QString &aDescription, QObject *parent )
    : LBaseDescriptor(sName, aDescription, parent)
{
    QString sObjectName = parentObjName;
    this->setDescriptPluginType(sObjectName);
}

LPluginDescriptor::LPluginDescriptor(ILPlugin *ilPugin, const QString &aDescription, QObject *parent)
    : LBaseDescriptor(ilPugin->objectName(), aDescription, parent)
{
    QString sObjectName = ilPugin->getParentName();
    this->setDescriptPluginType(sObjectName);
}

void LPluginDescriptor::setDescriptPluginType(const QString &sObjectName)
{
    LPluginType aPluginType = ptUnknown;

    do
    {
        if(sObjectName == "ILTwinVisualPlugin")
        {
            aPluginType = ptTwinVisual;
            break;
        }

        if(sObjectName == "ILOptionPlugin")
        {
            aPluginType = ptOption;
            break;
        }

        if(sObjectName == "ILVisualPlugin")
        {
            aPluginType = ptVisual;
            break;
        }

        if(sObjectName == "ILNonVisualPlugin")
        {
            aPluginType = ptNonVisual;
            break;
        }

    }while (false);

    setPluginType(aPluginType);
}



LPluginDescriptor::~LPluginDescriptor()
{

}

bool LPluginDescriptor::CheckPluginInterface(const QString &AnIID)
{
    return true;
}

LPluginType LPluginDescriptor::getPluginType()
{
    return this->fPluginType;
}

void LPluginDescriptor::setPluginType(LPluginType type)
{
    this->fPluginType = type;
}

/*LBasePluginFactory*/
LBasePluginFactory::LBasePluginFactory(QObject *parent )
    :QObject(parent)
{

}

LPluginDescriptor *LBasePluginFactory::getDescriptor()
{
    return this->fDescriptor;
}

void LBasePluginFactory::setDescriptor(LPluginDescriptor *descriptor)
{
    this->fDescriptor = descriptor;
}

/*LPluginFactory*/
LPluginFactory::LPluginFactory(QObject *parent )
	:LBasePluginFactory(parent)
{

}

LPluginFactory::LPluginFactory(QLModuleController *mdlController,const QString &lpluginName, ILPlugin *iPlugin, const QString &parentObjName, const QString &aDescription, QObject *parent)
    :LBasePluginFactory(parent)
{
    this->instancePlugin =iPlugin;

    LPluginDescriptor *aDescriptior = new LPluginDescriptor(parentObjName, lpluginName, aDescription);
    this->setDescriptor(aDescriptior);

    mdlController->registPluginFactory(this);  // 注册factory
}

LPluginFactory::LPluginFactory(QLModuleController *mdlController, ILPlugin *iPlugin, const QString &aDescription, QObject *parent)
    :LBasePluginFactory(parent)
{
    this->instancePlugin = iPlugin;

    LPluginDescriptor *aDescriptior = new LPluginDescriptor(iPlugin, aDescription);
    this->setDescriptor(aDescriptior);

    mdlController->registPluginFactory(this);  // 注册factory
}

LPluginFactory::LPluginFactory(const QString &lpluginName, qLPluginCreateFunc fPluginFunc, const QString &parentObjName, const QString &aDescription, QObject *parent)
    :LBasePluginFactory(parent)
{
    QLibrary *dllLib = new QLibrary(lpluginName);

    if (!dllLib->load())
    {
        return;
    }

    LPluginDescriptor *aPluginDescriptor = new LPluginDescriptor(parentObjName, lpluginName, aDescription);

    initFactoryInfo(dllLib, fPluginFunc, aPluginDescriptor);
}

LPluginFactory::LPluginFactory(QLibrary *instanceLib, qLPluginCreateFunc fPluginFunc, LPluginDescriptor *aDescriptior, QObject *parent)
    : LBasePluginFactory(parent)
{
    initFactoryInfo(instanceLib, fPluginFunc, aDescriptior);
}

LPluginFactory::LPluginFactory(QLModuleController *mdlController, qLPluginCreateFunc fPluginFunc, const QString &sObjName, const QString &aDescription, QObject *parent)
    : LBasePluginFactory(parent)
{
    this->qPluginFunc = fPluginFunc;

    ILPlugin *objPlugin  = (ILPlugin *)ObjectFactory::createObject(sObjName.toLatin1());

    if(NULL == objPlugin)
    {
        qDebug() << "error happened when createObject,class name:" << sObjName;
        return;
    }

    LPluginDescriptor *aDescriptior = new LPluginDescriptor(objPlugin->getParentName(), objPlugin->objectName(), aDescription);
    this->setDescriptor(aDescriptior);

    delete objPlugin;  //删除无用的实例
    objPlugin = NULL;

    mdlController->registPluginFactory(this);  // 注册factory
}

void LPluginFactory::initFactoryInfo(QLibrary *instanceLib, qLPluginCreateFunc fPluginFunc, LPluginDescriptor *aDescriptior)
{
    this->qPluginFunc = fPluginFunc;
    this->setDescriptor(aDescriptior);

    //取模块控制器函数
    qLModuleControllerFunc fControllerFunc = (qLModuleControllerFunc)instanceLib->resolve("LGetModuleController");//从Dll生成模块控制器

    if (!fControllerFunc)
    {
        return;
    }

    QLModuleController *fModuleController = fControllerFunc();
    qDebug() << "factory fModuleController == " << fModuleController;
    fModuleController->registPluginFactory(this);  // 注册factory
}


 ILPlugin *LPluginFactory::createInstance(ILHost *qHost)
{
     ILPlugin *instPlugin = this->instancePlugin;

    if(NULL != instPlugin)
    {
        instPlugin->setHost(qHost);
    }

    return instPlugin;
}

 ILPlugin *LPluginFactory::createInstance(ILHost *qHost, ILPlugin *instance)
{
    ILPlugin *instancePlugin = qPluginFunc(instance);
    if(NULL != instancePlugin)
    {
        instancePlugin->setHost(qHost);
    }

    return instancePlugin;
}

