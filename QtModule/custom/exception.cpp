#include "exception.h"

Exception::Exception(int code, const QString &msgError)
    :exceptErrorInfo(msgError)
    ,exceptCode(code)
{

}

int Exception::getCode()
{
    return this->exceptCode;
}

QString Exception::getErrorInfo()
{
    return this->exceptErrorInfo;
}
