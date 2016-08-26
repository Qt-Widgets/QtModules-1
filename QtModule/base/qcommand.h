
/**=================================================
* 系统命令声明单元，系统中所有的命令常量都在此声明
* @author wzguo 2015-09 18
===================================================*/


#ifndef QCOMMAND_H
#define QCOMMAND_H

/*Base Command*/
const     int    SYS_MAIN_WIN_REFRESH           =   00000;          //刷新界面
const     int    SYS_MAIN_GET_MENU              =   00001;          //获取菜单


/**QUtils.dll*/

const     int    SYS_UTILS_SEND_MESSAGE         =  10000;          //基础测试命令
const     int    SYS_UTILS_USER_LOGIN           =  10002;
const     int    SYS_UTILS_CHECK_RIGHT          =  10003;
const     int    SYS_UTILS_RIGHT_DESCRIPT       =  10004;
const     int    SYS_UTILS_USER_GROUPTYPE       =  10005;
const     int    SYS_UTILS_USER_NAME            =  10006;

const     int    SYS_UTILS_USER_PASSWORD        =  10007;
const     int    SYS_UTILS_USER_USERID          =  10008;
const     int    SYS_UTILS_USER_identity        =  10009;
const     int    SYS_UTILS_USER_INFO            =  10010;

const     int    SYS_UTILS_FRMUTILS_WIDGET      =  10011;

/**QSysSet.dll*/
const     int    SYS_SYSSET_SEND_MESSAGE        =  20000;


/**QGraphs.dll*/
const     int    SYS_GRAPHS_SHOW_CUSTOMPLOT     =  30001;


#endif // QCOMMAND_H

