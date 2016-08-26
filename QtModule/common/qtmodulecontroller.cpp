#include <QApplication>

#include "qtmodulecontroller.h"
#include <QDebug>

QLModuleController::QLModuleController(QObject *parent )
    :ILModuleController(parent)
{
    initializeObject();
}

QLModuleController::QLModuleController(const QString &libName, const QString &aDescription, QObject *parent )
	:ILModuleController(parent)
{
	initializeObject();

	this->getDescriptor()->setName(libName);
	this->getDescriptor()->setDescription(aDescription);
}

long QLModuleController::getDLLInstance()
{
	return 0;
}

void QLModuleController::registPluginFactory(LBasePluginFactory *pluginFactory)
{
    if(!findFacotory(pluginFactory))
	{
		factoryList.append(pluginFactory);
	}
}

LBasePluginFactory *QLModuleController::findFacotory(const QString &pluginName)
{
     LBasePluginFactory *basePluginFactory = NULL;

    for (int i = 0; i < factoryList.size(); ++i)
	{
		if (factoryList.at(i)->getDescriptor()->getName() == pluginName)
		{
            basePluginFactory = factoryList[i];
			break;
		}
	}

    return basePluginFactory;
}

bool QLModuleController::findFacotory(LBasePluginFactory *pluginFactory)
{
    bool isExist = false;
    if(factoryList.contains(pluginFactory))
    {
        isExist = true;
    }

    return  isExist;
}

void QLModuleController::setHostHwnd(long value)
{
	if (value != 0)
	{
		fOldHandle = value;
	}
}

long QLModuleController::getHostHwnd()
{
	return fOldHandle;
}

void QLModuleController::initializeObject()
{
	fDescriptor = new LModuleDescriptor();
}


LBasePluginFactory *QLModuleController::getFactory(int index)
{
    return factoryList.at(index);
}

int QLModuleController::getFactoryCount()
{
	return factoryList.count();
}

ILHost *QLModuleController::getHost()
{
    return this->mHost;
}

void QLModuleController::setHost(ILHost *host)
{
    this->mHost = host;
}

LModuleDescriptor *QLModuleController::getDescriptor()
{
	return fDescriptor;
}

LModuleDescriptor::LModuleDescriptor(QObject *parent )
	:LBaseDescriptor(parent)
{

}
