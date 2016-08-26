#include "mainwindow.h"
#include <QApplication>

#include "qshell.h"
#include "../base/qsysglobal.h"
#include "../tianchi/tianchi.h"

int main(int argc, char *argv[])
{
    QApplication appc(argc, argv);

    // 初始化资源文件
    Q_INIT_RESOURCE(main);

    // 每个项目中都要设置日志产生路径和级别，不然程序不会记录日志
    // 建议把执行文件名作为参数
    tlog.setAppFile(appc.applicationFilePath());
    tlog.setLogLevel(LOG_DEBUG);
    tlog.debug("开始记录日志", __FILE__, __LINE__);

    //设置插件加载目录
    QString sLoadPath = QString("%1/modules/").arg(appc.applicationDirPath());
    shell.loadPlugin(sLoadPath);

    MainWindow wmin;
    wmin.show();
    return appc.exec();
}
