#ifndef QTINTF
#define QTINTF

#include <QObject>
#include <QString>
#include <QVariant>
#include <QWidget>
#include <QMdiArea>

QT_BEGIN_NAMESPACE

/**------------------------------------------------------------------------------
*TLBaseDescriptor
*
*属性基类
*主要记录名称、描述等属性，用于模块、插件等的属性字段
------------------------------------------------------------------------------ - */
enum LPluginType 
{
    ptNonVisual   = 0,
    ptVisual      = 1,
    ptTwinVisual  = 2,
    ptOption      = 3,
    ptUnknown     = 4
};

class LBaseDescriptor : public QObject
{

    Q_PROPERTY(QString caption READ fCaption)
    Q_PROPERTY(QString Name READ fName)
    Q_PROPERTY(QString description READ fDescription)

public:
    LBaseDescriptor(QObject *parent = 0);
    LBaseDescriptor(const QString &aName, const QString &aDescription, QObject *parent = 0);

    virtual ~LBaseDescriptor() {};


    void setName(const QString &sName);
    void setCaption(const QString &sCaption);
    void setDescription(const QString &sDescription);

    QString getName();

private:
    QString fName;
    QString fCaption;
    QString fDescription;
};

#define LBaseDescriptor_IID "com.qt.example.Plugin.LBaseDescriptor/1.0"
Q_DECLARE_INTERFACE(LBaseDescriptor, LBaseDescriptor_IID)



/*------------------------------------------------------------------------------
*LInstanceInfo
*
*接口实例信息类
*记录已创建好的实例信息
------------------------------------------------------------------------------ - */
class ILPlugin;
class LInstanceInfo : public QObject
{

    Q_PROPERTY(QString instanceName READ getInstanceName)
    Q_PROPERTY(ILPlugin *instance READ getInstane)
    Q_PROPERTY(LPluginType pluginType READ getPluginType)

public:
    LInstanceInfo(QObject *parent = 0);
    LInstanceInfo(const QString &aInstanceName, QObject *parent = 0);
    ~LInstanceInfo();


    QString getInstanceName();
    void setInstance(ILPlugin *instance);

    void setPluginType(LPluginType pluginType);
    LPluginType getPluginType();

    ILPlugin* getInstane();

private:
    QString fInstanceName; //实例名
    ILPlugin *fInstance; //实例接口
    LPluginType fPluginType; //类型

};

#define LInstanceInfo_IID "com.qt.example.Plugin.LInstanceInfo/1.0"
Q_DECLARE_INTERFACE(LInstanceInfo, LInstanceInfo_IID)

/**------------------------------------------------------------------------------
ILHostAware

------------------------------------------------------------------------------ - */
class ILHost;
class ILHostAware :public QObject
{
    Q_PROPERTY(ILHost host READ getHost WRITE setHost)

public:
    ILHostAware(QObject *parent = 0);

    virtual ~ILHostAware() {};

    void setHost(ILHost *host);
    ILHost *getHost();

private:
    ILHost *fHost;

};

#define ILHostAware_IID "com.qt.example.Plugin.ILHostAware/1.0"
Q_DECLARE_INTERFACE(ILHostAware, ILHostAware_IID)



/**------------------------------------------------------------------------------
ILPlugin

插件接口基类
任何类型的插件都要实现这个接口定义的函数
------------------------------------------------------------------------------ - */
class ILPlugin :public ILHostAware
{

public:
    ILPlugin(QObject *parent = 0);

    virtual ~ILPlugin() {};


    virtual QVariant execCmd(int cmdID, QVariant aParam, QVariant aParam1) = 0;

    QString getParentName();

    void setParentName(const QString &sParent);

private:
    QString parentName;
};

#define ILPlugin_IID "com.qt.example.Plugin.ILPlugin/1.0"
Q_DECLARE_INTERFACE(ILPlugin, ILPlugin_IID)


/**------------------------------------------------------------------------------
*ILHost  宿主接口
*宿主接口定义
*一般由ModuleManager实现这个接口
------------------------------------------------------------------------------ -*/

class ILHost :public QObject
{
    Q_PROPERTY(ILPlugin *instance READ getInstance)
    Q_PROPERTY(int instanceCount READ getInstanceCount)
    Q_PROPERTY(QWidget *form READ getForm)

public:
    ILHost(QObject *parent = 0);

    ~ILHost();

    virtual int getInstanceCount() = 0;
    virtual ILPlugin *getInstance(int index) = 0;

    virtual LInstanceInfo *getInstanceInfos(int index) = 0;
    virtual int getOptionCount() = 0;
    virtual ILPlugin *getOpetion(int index) = 0;

    virtual QWidget *getForm() = 0;

    virtual QVariant execCmd(const QString &instanceName, int cmdID, QVariant aParam, QVariant aParam1) = 0;

private:

};

#define ILHost_IID "com.qt.example.Plugin.ILHost/1.0"
Q_DECLARE_INTERFACE(ILHost, ILHost_IID)


/**------------------------------------------------------------------------------
ILModuleController

模块控制器接口
一个DLL包含一个模块控制器，用来管理DLL内的多个插件
------------------------------------------------------------------------------ - */

class ILModuleController :public ILHostAware
{

    Q_PROPERTY(long hostHwnd READ getHostHwnd WRITE setHostHwnd)

public:
    ILModuleController(QObject *parent = 0);

    virtual ~ILModuleController() {};

    virtual void setHostHwnd(long value) = 0;
    virtual long getHostHwnd() = 0;

private:

};

#define ILModuleController_IID "com.qt.example.Plugin.ILModuleController/1.0"
Q_DECLARE_INTERFACE(ILModuleController, ILModuleController_IID)



/*------------------------------------------------------------------------------
ILVisualPlugin

可视单嵌入窗口接口
------------------------------------------------------------------------------ - */
class ILVisualPlugin : public ILPlugin
{
    Q_PROPERTY(bool visible READ getVisible WRITE setVisible)
    Q_PROPERTY(QString caption READ getCaption)
    Q_PROPERTY(QString Name READ getName)

public:
    ILVisualPlugin(QObject *parent = 0);

    virtual ~ILVisualPlugin() {};

    bool getVisible();
    void setVisible(bool value);

    QString getCaption();
    void setCaption(const QString &caption);

    QString getName();
    void setName(const QString &sName);

    virtual void hide() = 0;
    virtual void show() = 0;

private:
    QString fName;
    QString fCaption;
    bool fVisible;

};

#define ILVisualPlugin_IID "com.qt.example.Plugin.ILVisualPlugin/1.0"
Q_DECLARE_INTERFACE(ILVisualPlugin, ILVisualPlugin_IID)




/**------------------------------------------------------------------------------
ILTwinVisualPlugin

带双窗口的可视插件接口
由于类似Outlook的界面要用两个窗口显示在主界面
------------------------------------------------------------------------------ - */
class ILTwinVisualPlugin : public ILVisualPlugin
{

public:
    ILTwinVisualPlugin(QObject *parent = 0);

    virtual ~ILTwinVisualPlugin() {};

    virtual void ShowParentedEx(QWidget *aParent1, QWidget *aParamt2) = 0;

private:

};

#define ILTwinVisualPlugin_IID "com.qt.example.Plugin.ILTwinVisualPlugin/1.0"
Q_DECLARE_INTERFACE(ILTwinVisualPlugin, ILTwinVisualPlugin_IID)



/*------------------------------------------------------------------------------
ILOptionPlugin
属性插件接口 属性插件是特殊的可视插件 ，集中在主程序的属性设置窗口显示
------------------------------------------------------------------------------ - */
class  ILOptionPlugin: public ILVisualPlugin
{
public:
    ILOptionPlugin(QObject *parent = 0);

    virtual ~ILOptionPlugin() {};

    virtual bool saveOption() = 0;

private:

};

#define ILOptionPlugin_IID "com.qt.example.Plugin.ILOptionPlugin/1.0"
Q_DECLARE_INTERFACE(ILOptionPlugin, ILOptionPlugin_IID)




/*------------------------------------------------------------------------------
ILNonVisualPlugin

不可视插件接口
不可插件不会嵌入到主窗体，但可以有弹出窗口
------------------------------------------------------------------------------ - */
class ILNonVisualPlugin: public ILPlugin
{

public:
    ILNonVisualPlugin(QObject *parent = 0);

    virtual ~ILNonVisualPlugin() {};

    virtual void showMenuItem() = 0;

private:

};

#define ILNonVisualPlugin_IID "com.qt.example.Plugin.ILNonVisualPlugin/1.0"
Q_DECLARE_INTERFACE(ILNonVisualPlugin, ILNonVisualPlugin_IID)


QT_END_NAMESPACE

#endif // QTINTF

