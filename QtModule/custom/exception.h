/**================================================
  * 异常处理类
  *
  * @author:wzguo 2015-09-30
  ================================================*/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <QString>


class Exception : public std::exception
{
public:
    Exception(int code, const QString &msgError);

    virtual ~Exception() throw() {};

    int getCode();
    QString getErrorInfo();

private:
    int exceptCode;
    QString exceptErrorInfo;
};

#endif // EXCEPTION_H
