#include "qtintf.h"

/************************************************************************/
/* ??????????                                                           */
/************************************************************************/


/*LBaseDescriptor*/
LBaseDescriptor::LBaseDescriptor(QObject *parent )
	:QObject(parent)
{

}

LBaseDescriptor::LBaseDescriptor(const QString &aName, const QString &aDescription, QObject *parent )
	: QObject(parent)
{
	this->fName = aName;
	this->fDescription = aDescription;
}

void LBaseDescriptor::setName(const QString &sName)
{
	this->fName = sName;
}

void LBaseDescriptor::setCaption(const QString &sCaption)
{
	this->fCaption = sCaption;
}

void LBaseDescriptor::setDescription(const QString &sDescription)
{
	this->fDescription = sDescription;
}

QString LBaseDescriptor::getName()
{
    return this->fName;
}

/*LInstanceInfo*/
LInstanceInfo::LInstanceInfo(QObject *parent )
	:QObject(parent)
{

}

LInstanceInfo::LInstanceInfo(const QString &aInstanceName, QObject *parent )
	: QObject(parent)
{
    this->fInstanceName = aInstanceName;
}

LInstanceInfo::~LInstanceInfo()
{

}

QString LInstanceInfo::getInstanceName()
{
    return this->fInstanceName;
}

ILPlugin *LInstanceInfo::getInstane()
{
    return fInstance;
}

void LInstanceInfo::setInstance(ILPlugin *instance)
{
    fInstance = instance;
}

void LInstanceInfo::setPluginType(LPluginType pluginType)
{
    fPluginType = pluginType;
}

LPluginType LInstanceInfo::getPluginType()
{
    return this->fPluginType;
}


/*ILHost*/
ILHost::ILHost(QObject *parent )
	:QObject(parent)
{

}

ILHost::~ILHost()
{

}



/*ILPlugin*/
ILPlugin::ILPlugin(QObject *parent )
	: ILHostAware(parent)
{

}

QString ILPlugin::getParentName()
{
    return this->parentName;
}

void ILPlugin::setParentName(const QString &sParent)
{
    this->parentName = sParent;
}



/*ILHostAware*/
ILHostAware::ILHostAware(QObject *parent )
	: QObject(parent)
{

}

void ILHostAware::setHost(ILHost *host)
{
    this->fHost = host;
}

ILHost *ILHostAware::getHost()
{
    return this->fHost;
}



/*ILModuleController*/
ILModuleController::ILModuleController(QObject *parent )
	:ILHostAware(parent)
{

}



/*ILVisualPlugin*/
ILVisualPlugin::ILVisualPlugin(QObject *parent )
	:ILPlugin(parent)
{

}

bool ILVisualPlugin::getVisible()
{
    return this->fVisible;
}

void ILVisualPlugin::setVisible(bool value)
{
    this->fVisible = value;
}

QString ILVisualPlugin::getCaption()
{
    return this->fCaption;
}

void ILVisualPlugin::setCaption(const QString &caption)
{
    this->fCaption = caption;
}

QString ILVisualPlugin::getName()
{
    return this->fName;
}

void ILVisualPlugin::setName(const QString &sName)
{
    this->fName = sName;
}


/*ILTwinVisualPlugin*/
ILTwinVisualPlugin::ILTwinVisualPlugin(QObject *parent )
	:ILVisualPlugin(parent)
{

}



/*ILOptionPlugin*/
ILOptionPlugin::ILOptionPlugin(QObject *parent )
	: ILVisualPlugin(parent)
{

}



/*ILNonVisualPlugin*/
ILNonVisualPlugin::ILNonVisualPlugin(QObject *parent )
	:ILPlugin(parent)
{
    this->setObjectName("ILNonVisualPlugin");
}
