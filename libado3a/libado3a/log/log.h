/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ log.cpp													+
+ Function:print											+
+ Created on: Feb 20, 2016									+
+ Author: Xianhui Zhang										+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
#ifndef LOGC_H_
#define LOGC_H_

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////
// platform
///////////////////////////////////////////////////////////////
#ifndef _XianHUi_PLATFORM_DEFINED_
	#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
		#define _XianHUi_WIN32_
	#else
		#define _XianHUi_POSIX_
	#endif
	#define _XianHUi_PLATFORM_DEFINED_
#endif

#ifdef _XianHUi_WIN32_
#include <windows.h>
#include <tchar.h>
#include <io.h> 
#include <process.h> 
#else
#include <pthread.h>
#include "unistd.h"
#include "stdarg.h"
#endif

#define MAXLEN			2048
#define MAXFILEPATH		512
#define MAXFILENAME		256
#define LENGTH			512
#define LEN				512

#define MAX_LOG_ROW_SIZE		4096				//一行日志的大小
#define MAX_LOG_FILE_SIZE		1*1024*1024		//日志文件大小1M

/*++++++++++++++++++log.conf配置文件++++++++++++++++++++++++++++++++++++++++++++++
+	FUNCTION：设置LOG打印日志文件存放路径和打印级别，内容由path和level组成。其中path为打			+
+			印日志存放路径；level为打印日志级别。如下所示:							+
+		path=F:\ASID_GZ_build\bin\LOG\LOG.log									+
+		level=INF																+
+	NOTE：若不配置该log.conf配置文件，则LOG.log打印信息将存放在当前exe的LOG目录下;		+
+			当项目工程里没有exe程序时，此时就应该配置log.conf文件指定打印日志存放		+
+			路径，否则将找不到打印日志文件。											+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static const char *LogCfgFileNameString = "LOG.conf";	//配置文件
static const char *LogFileNameString = "ADODll.log";		//日志文件
static const char *LogPathString = "LOG";				//日志目录

typedef enum E_ERROR
{
    ERROR_1 = -1,
    ERROR_2 = -2,
    ERROR_3 = -3
};
 
typedef enum E_LOGLEVEL
{
    NONE = 0,
    INF = 1,
    DEBUGG = 2,
    ERRORR = 4,
    ALL = 255
}LOGLEVEL;
 
typedef struct tag_LOGSETINFO
{
	char logtime[LENGTH];
    char filepath[MAXFILEPATH];
    FILE *logfile;
}LOGSETINFO;
 
typedef struct tagLOGSETING
{
    char filepath[MAXFILEPATH];
    unsigned int maxfilelen;
    unsigned char loglevel;
}LOGSET;
 
//设置日志参数
void SetLogParam(int nLogLevel, int nLogFileSize);
int LOG(unsigned char loglevel,char *fromat,...);



#endif /* LOGC_H_ */