#ifndef QTMODULEMANAGER_H
#define QTMODULEMANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QStringList>

#include "qtmodulecontroller.h"
#include "qtintf.h"

class QLModule: public QObject
{
    Q_PROPERTY(QString fileName READ fFileName WRITE setFileName)
    Q_PROPERTY(long handle READ fHandle WRITE setHandle)
    Q_PROPERTY(QLModuleController* moduleController READ mLModuleController WRITE setModuleController)
    Q_PROPERTY(bool loadSuccess READ mlbLoadSuccess WRITE setLoadSuccess)

public:
	~QLModule();
	QLModule(QObject *parent = 0);
    QLModule(const QString &sFileName, QObject *parent = 0);

	void setFileName(const QString &sFileName);
	QString getFileName();

    QLModuleController *getModuleController();
	void setModuleController(QLModuleController *mController);

	void setLoadSuccess(bool lbLoad);
	bool getLoadSuccess();

protected:
    void setHandle(long handle);
    long getHandle();

private:
    long fHandle;
    QString fFileName;
    bool mlbLoadSuccess;

    QLModuleController *mLModuleController;
};


class QtModuleManager : public ILHost
{
    Q_PROPERTY(bool autoLoading READ fAutoLoading)

    Q_PROPERTY(LPluginDescriptor *pluginDescriptors READ getPluginDescriptor)
    Q_PROPERTY(int pluginDescriptorCount READ getPluginDescriptorCount)

    Q_PROPERTY(QLModule *module READ getModule)
    Q_PROPERTY(int moduleCount READ getModuleCount)

    Q_PROPERTY(ILPLugin *instances READ getInstances)
    Q_PROPERTY(LInstanceInfo *instanceInfos READ getInstanceInfos)
    Q_PROPERTY(int instanceCount READ getInstanceCount)

    Q_PROPERTY(ILPlugin *options READ getOptions)
    Q_PROPERTY(int optionCount READ getOptionCount)

    Q_PROPERTY(LBasePluginFactory *factories READ getFactories)
    Q_PROPERTY(int factoryCount READ getFactoryCount)

public:
    QtModuleManager(QObject *parent = 0);
    ~QtModuleManager();

	/*Misc. */
    int getModuleFileNames(QList<QString> &aList, const QString &searchPath);
    void setPluginpLoadPath(const QString sloadPath);

	/*Instance creation / release */
    LInstanceInfo *createInstance(const QString &sPluginName, QString sInstanceName = "");
    ILVisualPlugin *createVisualPlugin(const QString &aPluginName, const QString &aInstanceName = "",  QWidget *parent = 0);
    ILNonVisualPlugin *createNonVisualPlugin(const QString &aPluginName, const QString &aInstanceName = "");

	void releaseInstance(const QString &aInstanceName);
    void releaseAllInstances();

	void createAllInstances();

    QObject *createOption(const QString &aPluginName);
	void releaseOption(const QString &aPluginName);

	void createAllOptions();
	void releaseAllOptions();

    
	/**Plugin descriptors */
    LPluginDescriptor *findPluginDescriptor(const QString &aPluginName);
    LPluginDescriptor *pluginDescriptorByName(const QString &aPluginName);

    /**Modules**/
    int  loadModules(const QString &searchPath);
    void loadModules(const QStringList &sfileNameList);
    void loadModules(QMap<int, QString> &mapfileName);
    void loadModules();

    int tryLoadModule(const QString &sfileName);
    int loadModule(const QString &sfileName);

    void unloadModule(const QString &sfileName);
    void unloadModule(int index);
    void unloadModules();

    QLModule *findModule(const QString &sfileName);
    QLModule *moduleByName(const QString &sName);
    QLModule *moduleByFileName(const QString &sfileName);

	/**Plugin Instances**/
    ILPlugin *instanceByName(const QString &sinstanceName);
    LInstanceInfo *instanceInfoByName(const QString &sinstanceName);

protected:
	void load();

	/*ILHost */
    int getInstanceCount() Q_DECL_OVERRIDE;
    ILPlugin *getInstance(int index) Q_DECL_OVERRIDE;
    LInstanceInfo *getInstanceInfos(int index) Q_DECL_OVERRIDE;

    int getOptionCount() Q_DECL_OVERRIDE;
    ILPlugin *getOpetion(int index) Q_DECL_OVERRIDE;
    QWidget *getForm() Q_DECL_OVERRIDE;
    QVariant execCmd(const QString &instanceName, int cmdID, QVariant aParam, QVariant aParam1) Q_DECL_OVERRIDE;

	/* Factories */
    LBasePluginFactory *findFactory(const QString &aPluginName);
    LBasePluginFactory *factoryByName(const QString &aPluginName);

private:
    int getModuleCount();
    QLModule *getModule(int index);
    QStringList getModulesToLoad();
    void setModulesToLoad(const QStringList &mLoadList);
	void setAutoLoad(bool value);

    LBasePluginFactory *getFactories(int index);
	int getFactoryCount();
    LPluginDescriptor *getPluginDescriptor(int index);
	int getPluginDescriptorCount();

    QString getPluginLoadPath();

private:
    QList<QLModule *> mModuleList; //!模块列表

	QList<LBasePluginFactory *> mFactoryList; //!所有加载进来的DLL中插件的生成方法
	QList<LInstanceInfo *> mInstanceList; // 将Instance交给Manager来处理,Instance表示除配置窗口外的其他

    QList<LInstanceInfo *> mInstanceInfoList;
	QStringList modulesLoadList;
    QList<LInstanceInfo *> mOptionInfoList; //专门用来存储配置窗口    配置窗口不常用，等要用的时候再创建

	bool fAutoLoading, fAutoLoad; //!加载后事件

    QString pluginLoadPath;
};

#endif // QTMODULEMANAGER_H
