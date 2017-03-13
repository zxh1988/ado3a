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

#define MAX_LOG_ROW_SIZE		4096				//һ����־�Ĵ�С
#define MAX_LOG_FILE_SIZE		1*1024*1024		//��־�ļ���С1M

/*++++++++++++++++++log.conf�����ļ�++++++++++++++++++++++++++++++++++++++++++++++
+	FUNCTION������LOG��ӡ��־�ļ����·���ʹ�ӡ����������path��level��ɡ�����pathΪ��			+
+			ӡ��־���·����levelΪ��ӡ��־����������ʾ:							+
+		path=F:\ASID_GZ_build\bin\LOG\LOG.log									+
+		level=INF																+
+	NOTE���������ø�log.conf�����ļ�����LOG.log��ӡ��Ϣ������ڵ�ǰexe��LOGĿ¼��;		+
+			����Ŀ������û��exe����ʱ����ʱ��Ӧ������log.conf�ļ�ָ����ӡ��־���		+
+			·���������Ҳ�����ӡ��־�ļ���											+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static const char *LogCfgFileNameString = "LOG.conf";	//�����ļ�
static const char *LogFileNameString = "ADODll.log";		//��־�ļ�
static const char *LogPathString = "LOG";				//��־Ŀ¼

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
 
//������־����
void SetLogParam(int nLogLevel, int nLogFileSize);
int LOG(unsigned char loglevel,char *fromat,...);



#endif /* LOGC_H_ */