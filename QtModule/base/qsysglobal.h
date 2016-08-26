#ifndef QSYSGLOBAL_H
#define QSYSGLOBAL_H
/**
 * @brief LOG_LEVEL enum
 *
 * 日志级别，LOG_ERROR等级最高
 * @author wzguo
 * @date 2015-09-24
 */

/* ***************************************** /
/* 枚举日志级别，在天池项目中也有同样的文件
/* 如果修改了这个文件请一并修改天池项目中的文件
/* ******************************************/
enum SYS_LOG_LEVEL
{
    LOG_ERROR  =  0,
    LOG_WARNING,
    LOG_TRACK,
    LOG_INFO,
    LOG_DEBUG
};

#endif // QSYSGLOBAL_H

