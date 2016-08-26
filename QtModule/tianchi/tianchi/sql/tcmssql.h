// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：SQL Server 相关应用
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.18   XChinux     建立
// 2013.06.04   XChinux     增加ODBCDSN()函数
//
// ==========================================================================
/// @file MSSQL.h SQL Server 相关应用
#ifndef TIANCHI_TCMSSQL_H
#define TIANCHI_TCMSSQL_H

#include <tianchi/tcglobal.h>
#include <QStringList>

/// @brief 读取 ODBC 驱动和版本信息
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcMSSQL
{
public:
    /// @brief 读取 ODBC 驱动和版本信息
    /// @date 2013-04-18
    /// @return  以 / 分隔版本号和驱动名称:<br>
    ///     10.00/SQL Server Native Client 10.0<br>
    ///     09.00/SQL Native Client<br>
    ///     03.50/SQL Server<br>
    static QStringList availableODBCDrivers();
    /// @brief  构造ODBC DSN字符串
    /// @date 2013-06-04
    /// @param  driver  可用ODBC驱动名称
    /// @param  server  host\instancename 格式,如果为默认实例，则直接为host
    /// @param  dbname  数据库名
    /// @param  user    连接用户名
    /// @param  pass    连接密码
    /// @return 返回DSN字符串
    static QString ODBCDSN(const QString &driver,
            const QString &server,
            const QString &dbname,
            const QString &user = QString(),
            const QString &pass = QString());
};

#endif
