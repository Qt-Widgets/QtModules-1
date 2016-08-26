#include "qtmodulemanager.h"
#include "qtmodulecontroller.h"

#include <QLibrary>
#include <QApplication>
#include <QMessageBox>
#include <QStringList>
#include <QDir>
#include <QDebug>

/**QLModule*/
QLModule::~QLModule()
{

}

QLModule::QLModule(QObject *parent)
	:QObject(parent)
{

}

QLModule::QLModule(const QString &sDllName, QObject *parent)
	: QObject(parent)
{
    qLModuleControllerFunc qmoduleCtrFunc;

    mlbLoadSuccess = false;

    QLibrary dllLib(sDllName); // 路径+DLL名字

    if (!dllLib.load())
    {
        qDebug() <<"Error : " << QString("动态库加载失败：%1").arg(sDllName);
        return;
    }

    qmoduleCtrFunc = (qLModuleControllerFunc)dllLib.resolve("LGetModuleController");

    if (!qmoduleCtrFunc)
    {
        return;
    }

    QLModuleController *moduleController = qmoduleCtrFunc();

    this->setModuleController(moduleController);

    qDebug()<< "modlemanager moduleController == " << moduleController;

    this->getModuleController()->initPluginFactory(moduleController);

    fFileName = sDllName;
    mlbLoadSuccess = true;
}

void QLModule::setFileName(const QString &sFileName)
{
	this->fFileName = sFileName;
}

QString QLModule::getFileName()
{
	return this->fFileName;
}

void QLModule::setHandle(long handle)
{
    this->fHandle = handle;
}

long QLModule::getHandle()
{
    return this->fHandle;
}

QLModuleController *QLModule::getModuleController()
{
    return this->mLModuleController;
}

void QLModule::setModuleController(QLModuleController *mController)
{
    this->mLModuleController = mController;
}

void QLModule::setLoadSuccess(bool lbLoad)
{
    this->mlbLoadSuccess = lbLoad;
}

bool QLModule::getLoadSuccess()
{
    return this->mlbLoadSuccess;
}


/**QtModuleManager*/

QtModuleManager::QtModuleManager(QObject *parent)
	:ILHost(parent)
{
    mModuleList.clear();
    mFactoryList.clear();
    mInstanceList.clear();
}

QtModuleManager::~QtModuleManager()
{
    this->releaseAllOptions();
    this->releaseAllInstances();

    this->unloadModules();
}

LInstanceInfo *QtModuleManager::createInstance(const QString &sPluginName,  QString sInstanceName)
{
    if(sInstanceName.trimmed() == "")
    {
		sInstanceName = sPluginName;
    }

    for(int i = 0; i < mInstanceList.count(); i++) // 判断是否已经存在同名的Instacne
    {
     //   LInstanceInfo *instanceInfo = qobject_cast<LInstanceInfo *>(mInstanceList.at(i));
        LInstanceInfo *instanceInfo = (LInstanceInfo *)mInstanceList.at(i);
        qDebug()<<" instanceInfo == " << instanceInfo;

        qDebug()<<"instanceInfo->getInstanceName() ==" << instanceInfo->getInstanceName() << "sInstanceName == "<< sInstanceName;
        if (instanceInfo->getInstanceName() == sInstanceName)
        {
            return instanceInfo;
        }
    }

    // 待完善
	LInstanceInfo *qInstanceInfo = new LInstanceInfo(sInstanceName);

    LBasePluginFactory *qBasePluginFactory = factoryByName(sPluginName);
    qDebug() << "qBasePluginFactory == " <<qBasePluginFactory;

    ILPlugin *instancePlugin = qBasePluginFactory->createInstance(this, NULL);

    qInstanceInfo->setInstance(instancePlugin);
	qInstanceInfo->setPluginType(qBasePluginFactory->getDescriptor()->getPluginType());

    if(NULL != qInstanceInfo->getInstane())
    {
        mInstanceList.append(qInstanceInfo);
    }

    qDebug()<< "mInstanceList count == " << mInstanceList.count() <<"mInstanceList == "<<mInstanceList;
    return qInstanceInfo;
}

ILVisualPlugin *QtModuleManager::createVisualPlugin(const QString &aPluginName, const QString &aInstanceName, QWidget *parent)
{
    return NULL;
}

ILNonVisualPlugin *QtModuleManager::createNonVisualPlugin(const QString &aPluginName, const QString &aInstanceName)
{
    return NULL;
}

void QtModuleManager::releaseInstance(const QString &sInstanceName)
{
    for(int i=0; i<mInstanceList.count(); i++)
    {
        LInstanceInfo *instanceInfo = mInstanceList.at(i);
        if(instanceInfo->getInstanceName() == sInstanceName)
        {
            delete instanceInfo;
            instanceInfo = NULL;
            mInstanceList.removeAt(i);
            break;
        }
    }
}

void QtModuleManager::releaseAllInstances()
{
    for(int i=0; i<mInstanceList.count(); i++)
    {
        LInstanceInfo *instanceInfo = mInstanceList.at(i);

        delete instanceInfo;
        instanceInfo = NULL;
        mInstanceList.removeAt(i);
        break;
    }
}

void QtModuleManager::createAllInstances()
{
    QLModuleController *moduleController;
    LPluginDescriptor *aPluginDescriptor;

    for(int i=0; i< this->getModuleCount(); i++)
    {
        moduleController = this->getModule(i)->getModuleController();

        qDebug() << "moduleController == " << moduleController;

        for(int j=0; j < moduleController->getFactoryCount(); j++)
        {
            aPluginDescriptor = moduleController->getFactory(j)->getDescriptor();

            LPluginType dscptPluginType = aPluginDescriptor->getPluginType();

            qDebug() << "aPluginDescriptor.name == " << aPluginDescriptor->getName();

            if(dscptPluginType == ptVisual || dscptPluginType == ptTwinVisual || dscptPluginType == ptNonVisual)
            {
                this->createInstance(aPluginDescriptor->getName(), "");
            }
        }
    }
}

QObject *QtModuleManager::createOption(const QString &aPluginName)
{
    QString sPluginName = aPluginName;
    LInstanceInfo *instanceInfo = new LInstanceInfo(sPluginName);
    LBasePluginFactory *factory = this->factoryByName(sPluginName);

    ILPlugin *lPugin = factory->createInstance(this, NULL);

    instanceInfo->setInstance(lPugin);
    instanceInfo->setPluginType(factory->getDescriptor()->getPluginType());

    if(NULL != instanceInfo->getInstane())
    {
        mOptionInfoList.append(instanceInfo);
    }
    else
    {
        delete instanceInfo;
        instanceInfo = NULL;
    }

    return instanceInfo;
}

void QtModuleManager::releaseOption(const QString &aPluginName)
{
    for(int i=0; i< mOptionInfoList.count(); i++)
    {
        LInstanceInfo *instanceInfo = mOptionInfoList.at(i);
        if(instanceInfo->getInstanceName() == aPluginName)
        {
            delete instanceInfo;
            instanceInfo = NULL;
            mOptionInfoList.removeAt(i);
            break;
        }
    }
}

void QtModuleManager::createAllOptions()
{
    for(int i=0; i <this->getModuleCount(); i++)
    {
        QLModuleController *moduleController = this->getModule(i)->getModuleController();
        for(int j=0; j< moduleController->getFactoryCount(); j++)
        {
            LBasePluginFactory *baseFactory = moduleController->getFactory(j);
            if(baseFactory->getDescriptor()->getPluginType() == ptOption)
            {
                this->createOption(baseFactory->getDescriptor()->getName());
            }
        }
    }
}

void QtModuleManager::releaseAllOptions()
{
    for(int i=0; i < mOptionInfoList.count(); i++)
    {
         LInstanceInfo *instanceInfo = mOptionInfoList.at(i);
         delete instanceInfo;
         instanceInfo = NULL;
         mOptionInfoList.removeAt(i);
    }
}

LPluginDescriptor *QtModuleManager::findPluginDescriptor(const QString &aPluginName)
{
    LPluginDescriptor *pluginDescriptor = NULL;
    LBasePluginFactory *baseFactory = this->findFactory(aPluginName);
    if(NULL != baseFactory)
    {
        pluginDescriptor = baseFactory->getDescriptor();
    }

    return pluginDescriptor;
}

LPluginDescriptor *QtModuleManager::pluginDescriptorByName(const QString &aPluginName)
{
    return this->findPluginDescriptor(aPluginName);
}

int QtModuleManager::getModuleFileNames(QList<QString> &aList, const QString &searchPath)
{
   // QDir pluginsDir(qApp->applicationDirPath());
    QDir pluginsDir(searchPath);
    pluginsDir.cd("Plugins");

    int moduleCount = 0;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        if(fileName.trimmed().toLower().right(4) == ".dll")
        {
            moduleCount++;
            aList.append(fileName);
        }
    }

    return moduleCount;
}

void QtModuleManager::setPluginpLoadPath(const QString sloadPath)
{
    this->pluginLoadPath = sloadPath;
}

int QtModuleManager::loadModules(const QString &searchPath)
{
    int mt = 0;
    QStringList qstrList;

	if (getModuleFileNames(qstrList, searchPath)> 0)
    {
        int mcount =this->getModuleCount();
        for(int i = 0; i< mModuleList.count(); i++)
        {
			loadModule(mModuleList.at(i)->getFileName());
            if(this->getModuleCount() > mcount)
            {
                mt++;
            }
        }
    }

    return mt;
}

void QtModuleManager::loadModules(const QStringList &sfileNameList)
{
     for(int i = 0; i < sfileNameList.size(); ++i)
     {
         loadModule(sfileNameList.at(i));
     }
}

void QtModuleManager::loadModules(QMap<int, QString> &mapfileName)
{
    QMap<int, QString>::iterator iter, iterEnd;
    iter = mapfileName.begin();
    iterEnd = mapfileName.end();

    for(; iter != iterEnd; iter++)
    {
        loadModule(iter.value());
    }
}

void QtModuleManager::loadModules()
{
    loadModules(modulesLoadList);
}

int QtModuleManager::tryLoadModule(const QString &sfileName)
{
    try
    {
       return loadModule(sfileName);
    }
    catch(QString &str)
    {
        qDebug()<< "---Error --info: " << str;
        return 0;
    }
}

int QtModuleManager::loadModule(const QString &sfileName)
{
    QLModule *qmodule;
    QLModuleController *qmController;

    qmodule = findModule(sfileName);
    if (qmodule != NULL)
    {
        qDebug() <<"Error : " <<QString("模块已经加载：%1").arg(sfileName);
        return -1;
    }

    QString fileName = this->getPluginLoadPath().trimmed() +sfileName.trimmed();  // 获取路径

    qmodule = new QLModule(fileName);
    if (qmodule->getLoadSuccess())
    {
        mModuleList.append(qmodule);

        qmController = qmodule->getModuleController();
        qmController->setHostHwnd(0);

        ILHost *ihost = qobject_cast<ILHost *>(this);
        qmController->setHost(ihost);

		for (int i = 0; i < qmController->getFactoryCount(); i++)
        {
			mFactoryList.append(qmController->getFactory(i));
        }
    }

	return mModuleList.count();
}

void QtModuleManager::unloadModule(const QString &sfileName)
{
    for(int i=0; i < mModuleList.count(); i++)
    {
        QLModule *module = mModuleList.at(i);
        if(module->getFileName() == sfileName)
        {
            unloadModule(i);
        }
    }
}

void QtModuleManager::unloadModule(int index)
{
    QLModuleController *controller = mModuleList.at(index)->getModuleController();

    for(int i= 0; i< controller->getFactoryCount(); i++)
    {
        int pluginIndex = mFactoryList.indexOf(controller->getFactory(i));

        if(pluginIndex > 0)
        {
            LBasePluginFactory *pluginFactory = mFactoryList.at(pluginIndex);
            delete pluginFactory;
            pluginFactory = NULL;
            mFactoryList.removeAt(pluginIndex);
        }
    }

    delete controller;
    controller = NULL;
    mModuleList.removeAt(index);

}

void QtModuleManager::unloadModules()
{
    for(int i=0; i < mModuleList.count(); i++)
    {
        unloadModule(i);
    }
}

QLModule *QtModuleManager::findModule(const QString &sfileName)
{
    for(int i = 0; i < mModuleList.count(); i++)
    {
		QLModule* qmodule = mModuleList.at(i);
        if (qmodule->getFileName() == sfileName.trimmed())
        {
            return qmodule;
            break;
        }
    }

    return NULL;
}

QLModule *QtModuleManager::moduleByName(const QString &sName)
{
    for(int i = 0; i < mModuleList.count(); i++)
    {
        if(mModuleList.at(i)->getModuleController()->getDescriptor()->getName() == sName)
        {
            return mModuleList.at(i);
            break;
        }
    }

    return NULL;
}

QLModule *QtModuleManager::moduleByFileName(const QString &sfileName)
{
    return findModule(sfileName);

}

ILPlugin *QtModuleManager::instanceByName(const QString &sinstanceName)
{
    ILPlugin *plugin = NULL;
    qDebug()<< "mInstanceList count == " << mInstanceList.count() <<"mInstanceList == "<<mInstanceList;

    for(int i=0; i< this->getInstanceCount(); i++)
    {
        LInstanceInfo *instanceInfo = mInstanceList.at(i);
        qDebug()<<"sinstanceName =="<< sinstanceName << "instanceInfo.name  == " << instanceInfo->getInstanceName();
        if(instanceInfo->getInstanceName() == sinstanceName)
        {
            plugin = instanceInfo->getInstane();
            break;
        }
    }

    return plugin;
}

LInstanceInfo *QtModuleManager::instanceInfoByName(const QString &sinstanceName)
{
    LInstanceInfo *instanceInfo = NULL;
    for(int i=0; i< mInstanceInfoList.count(); i++)
    {
        if(mInstanceInfoList.at(i)->getInstanceName() == sinstanceName)
        {
            instanceInfo = mInstanceInfoList.at(i);
            break;
        }
    }

    return instanceInfo;
}

void QtModuleManager::load()
{
    if(fAutoLoad)
    {
        try
        {
            fAutoLoading = true;
            loadModules();
        }
        catch(QString &strError)
        {

            qDebug() << "error: -- " <<strError;
        }
        fAutoLoading = false;
    }
}

int QtModuleManager::getModuleCount()
{
    return mModuleList.count();
}

QLModule* QtModuleManager::getModule(int index)
{
    return mModuleList.at(index);
}

QStringList QtModuleManager::getModulesToLoad()
{
    return modulesLoadList;
}

void QtModuleManager::setModulesToLoad(const QStringList &mLoadList)
{
    modulesLoadList = mLoadList;
}

void QtModuleManager::setAutoLoad(bool value)
{
    fAutoLoad = value;
}

LBasePluginFactory *QtModuleManager::getFactories(int index)
{
    return mFactoryList.at(index);
}

LBasePluginFactory *QtModuleManager::factoryByName(const QString &spluginName)
{
    return findFactory(spluginName);
}

LBasePluginFactory *QtModuleManager::findFactory(const QString &spluginName)
{
    LBasePluginFactory *basePluginFactory = NULL;

    for(int i = 0; i < this->mFactoryList.count(); i++)
    {
		LBasePluginFactory *qbasePlugin = mFactoryList.at(i);
		if (qbasePlugin->getDescriptor()->getName() == spluginName.trimmed())
        {
            basePluginFactory = qbasePlugin;
            break;
        }
    }

    qDebug() << "basePluginFactory == " <<basePluginFactory;
    return basePluginFactory;
}

int QtModuleManager::getFactoryCount()
{
    return mFactoryList.count();
}

LPluginDescriptor *QtModuleManager::getPluginDescriptor(int index)
{
    return mFactoryList.at(index)->getDescriptor();
}

int QtModuleManager::getPluginDescriptorCount()
{
    return mFactoryList.count();
}

QString QtModuleManager::getPluginLoadPath()
{
    return this->pluginLoadPath;
}

int QtModuleManager::getInstanceCount()
{
    return mInstanceList.count();
}

ILPlugin *QtModuleManager::getInstance(int index)
{
    LInstanceInfo *instanceInfo = qobject_cast<LInstanceInfo *>(mInstanceList.at(index));

    return instanceInfo->getInstane();
}

LInstanceInfo *QtModuleManager::getInstanceInfos(int index)
{
    return mInstanceList.at(index);
}

int QtModuleManager::getOptionCount()
{
    return mOptionInfoList.count();
}

ILPlugin *QtModuleManager::getOpetion(int index)
{
    return mOptionInfoList.at(index)->getInstane();
}

QWidget *QtModuleManager::getForm()
{
    QWidget *frmWidget = qobject_cast<QWidget *>(this->parent());
    return frmWidget;
}

//所有命令都在这里处理
QVariant QtModuleManager::execCmd(const QString &instanceName, int cmdID, QVariant aParam, QVariant aParam1)
{
    if (instanceName.trimmed() == "")
    {
        return 0;
    }

    ILPlugin *qlPlugin = this->instanceByName(instanceName);

    if(qlPlugin != NULL)
    {
        return qlPlugin->execCmd(cmdID, aParam, aParam1);
    }
    else
    {
        qDebug() << "Error -- "<< QString("未找到插件: %1").arg(instanceName);
        return 0;
    }
}
