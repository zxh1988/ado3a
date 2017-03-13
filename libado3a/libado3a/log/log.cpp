/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ logc.cpp													+
+ Function:print											+
+ Created on: Feb 20, 2016									+
+ Author: Xianhui Zhang										+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "stdafx.h"
#include "log.h"

#define MAXLEVELNUM (3)

/*
WriteLog: 写日志函数---如果日志文件超过指定大小 则从0开始
*/

int g_nLogLevel = DEBUGG;
int g_nLogFileSize = MAX_LOG_FILE_SIZE;
bool g_bInit = false;

#ifdef _XianHUi_WIN32_
	CRITICAL_SECTION g_lock;
#else
	pthread_mutex_t g_lock;
#endif


 
LOGSET g_LogSetting;
LOGSETINFO g_Loging;
 
const static char LogLevelText[4][10] = {"INF","DEBUG","ERROR","ERROR"};
 
static char * getdate(char *date);
 
static unsigned char getcode(char *path)
{
	unsigned char code = ALL;
    if(0 == strcmp("INF",path))			code = INF;	
    else if(0 == strcmp("DEBUG",path))	code = DEBUGG;	
    else if(0 == strcmp("ERROR",path))	code = ERRORR;	
    else if(0 == strcmp("NONE",path))	code = NONE;
    return code;
}
 
static string GetLogPath()
{
	char szFilePath[LEN];
	memset(szFilePath,0,LEN);
	GetModuleFileNameA(NULL,szFilePath,LEN);
	string szFileFullPath = szFilePath;

	int iPos = -1;
	iPos = szFileFullPath.size() - 1;
	while(szFileFullPath[iPos] != '\\' && iPos >= 0)
	{
		szFileFullPath.erase(iPos,1);
		iPos--;
	}
	return szFileFullPath;
}

static unsigned char ReadLogConfig(const char *path)
{
	char value[LENGTH] = {0};
	char data[LENGTH] = {0};

    FILE *fpath = fopen(path,"r");
    if(NULL == fpath) 
	{
		return -1;
	}
    fscanf(fpath,"path = %s\n",value);
    if(0 != strcmp(value,g_LogSetting.filepath))
	{
        memcpy(g_LogSetting.filepath,value,strlen(value));
	}
    memset(value,0,sizeof(value));
 
    fscanf(fpath,"level = %s\n",value);
    g_LogSetting.loglevel = getcode(value);
    fclose(fpath);
    return 0;
}

//将TCHAR转为char   
#ifdef _XianHUi_WIN32_
static char *UnicodeToANSI(const wchar_t *spBuf)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, spBuf, -1, NULL, 0, NULL, NULL);
	char* chpBuf = new char[nLen+1];
	memset(chpBuf,0,nLen+1);
	WideCharToMultiByte(CP_ACP, 0, spBuf, -1, chpBuf, nLen, NULL, NULL);
	return chpBuf;
}
#endif

//同上   
#ifdef _XianHUi_WIN32_
static wchar_t *ANSItoUnicode(const char *chpBuf)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0, chpBuf, strlen(chpBuf) + 1, NULL, 0);
	wchar_t *spBuf = new wchar_t[nLen+1];
	memset(spBuf,0,nLen+1);
	MultiByteToWideChar(CP_ACP, 0, chpBuf, strlen(chpBuf) + 1, spBuf, nLen);
	return spBuf;
}
#endif

#ifdef _XianHUi_WIN32_
static string UnicodeToString(const wchar_t *spBuf)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, spBuf, -1, NULL, 0, NULL, NULL);
	char* chpBuf = new char[nLen+1];
	memset(chpBuf,0,nLen+1);
	WideCharToMultiByte(CP_ACP, 0, spBuf, -1, chpBuf, nLen, NULL, NULL);
	std::string szBuf(chpBuf);
	delete[] chpBuf;
	chpBuf = NULL;
	return szBuf;
}
#endif

/*
 *日志设置信息
函数说明：getcwd()会将当前的工作目录绝对路径复制到参数buf 所指的内存空间，参数size 为buf 的空间大小。
函数说明：access()会检查是否可以读/写某一已存在的文件。附加说明：使用access()作用户认证方面的判断要特别小心，例如在access()后再做open()的空文件可能会造成系统安全上的问题。
 * */
static LOGSET *getlogset()
{   
#ifdef _XianHUi_WIN32_
	string szPath = GetLogPath();	//得到当前工作路径
	szPath += LogPathString;
	wchar_t *wStrDir = ANSItoUnicode(szPath.c_str());
	CreateDirectory(wStrDir,NULL);
	//CreateDirectory(szPath.c_str(), NULL);
	delete[] wStrDir; 
	szPath += "\\";
	szPath += LogCfgFileNameString;
	
	if (0 == access(szPath.c_str(), 0))		///log.conf文件是否存在
	{
		if (0 != ReadLogConfig((char*)szPath.c_str()))
		{
			g_LogSetting.loglevel = INF;
			g_LogSetting.maxfilelen = MAX_LOG_ROW_SIZE;
		}
	}
	else
	{
		g_LogSetting.loglevel = INF;
		g_LogSetting.maxfilelen = MAX_LOG_ROW_SIZE;
	}

#else	
	char path[LEN] = {0};
	getcwd(path,sizeof(path));
	sprintf(path,"%s/%s","/",LogCfgFileNameString);
    if(0 == access(path,F_OK))		//表示文件存在
	{
        if(ReadLogConfig(path) != 0)		
		{
            g_LogSetting.loglevel = INF;
			g_LogSetting.maxfilelen = MAX_LOG_ROW_SIZE;
        }
    }
	else
	{
        g_LogSetting.loglevel = INF;
		g_LogSetting.maxfilelen = MAX_LOG_ROW_SIZE;
    }
#endif
    return &g_LogSetting;
}
 
/*
 *获取日期
 * */
static char * getdate(char *date)
{
    time_t timer = time(NULL);
	strftime(date, LEN, "%Y-%m-%d", localtime(&timer));
    return date;
}
 
/*
 *获取时间
 * */
static void settime()
{
    time_t timer = time(NULL);
	strftime(g_Loging.logtime, LEN, "%Y-%m-%d %H:%M:%S", localtime(&timer));
}
 
/*
 *不定参打印
 * */
static void PrintfLOG(char * fromat,va_list args)
{
#ifdef _XianHUi_WIN32_
	EnterCriticalSection(&g_lock);
#else
	pthread_mutex_lock(&g_lock);
#endif
	//限制大小
	fseek(g_Loging.logfile, 0, SEEK_END);
	int nwFileSize = ftell(g_Loging.logfile);
	if (nwFileSize > g_nLogFileSize)
	{
		fclose(g_Loging.logfile);
		g_Loging.logfile = NULL;
		fopen(g_Loging.filepath, "w");
		nwFileSize = 0;
		if (g_Loging.logfile == NULL)
		{
			goto END_LOG;
		}
	}
	//处理参数
	vfprintf(g_Loging.logfile, fromat, args);
	fprintf(g_Loging.logfile, "%s", "]\n");

END_LOG:
#ifdef _XianHUi_WIN32_
	LeaveCriticalSection(&g_lock);
#else
	pthread_mutex_unlock(&g_lock);
#endif
}
 
 /*
 函数说明：char *getenv(const char *name)用来取得参数name 环境变量的内容. 参数name 为环境变量的名称, 
			如果该变量存在则会返回指向该内容的指针. 环境变量的格式为name＝value.
 */
 
static int InitLOG(unsigned char nLogLevel)
{
#ifdef _XianHUi_WIN32_
		InitializeCriticalSection(&g_lock);
#else
		pthread_mutex_init(&g_lock, NULL);
#endif	

	g_bInit = true;
	char strdate[LEN] = {0};
	LOGSET *g_LogSetting;
	//获取日志配置信息
    if(NULL == (g_LogSetting = getlogset()))
	{
        perror("Get Log Set Fail!");
        return -1;
    }

    if(nLogLevel != (nLogLevel & (g_LogSetting->loglevel)))
        return -1;
    memset(&g_Loging,0,sizeof(LOGSETINFO));
    //获取日志时间
    settime();

#ifdef _XianHUi_WIN32_
	if (0 == strlen(g_LogSetting->filepath))
	{
		string szPath = GetLogPath();	//得到当前工作路径
		szPath += LogPathString;
		//按固定文件名命名
		sprintf_s(g_LogSetting->filepath, "%s/%s", szPath.c_str(), LogFileNameString);
	}
#else	
    if(0 == strlen(g_LogSetting->filepath))
	{
        char *path = getenv("HOME");
        memcpy(g_LogSetting->filepath,path,strlen(path));
        getdate(strdate);
        strcat(strdate,".log");
        strcat(g_LogSetting->filepath,"/");
        strcat(g_LogSetting->filepath,strdate);
    }
#endif
    memcpy(g_Loging.filepath,g_LogSetting->filepath,MAXFILEPATH);
    return 0;
}
 
void SetLogParam(int nLogLevel, int nLogFileSize)
{
	g_nLogLevel = nLogLevel;
	g_nLogFileSize = nLogFileSize;
}

/*
 *日志写入
 * */
int LOG(unsigned char nLogLevel,char *fromat,...)
{
    va_list args;
    //初始化日志
	if (!g_bInit) InitLOG(nLogLevel);
	//打开日志文件
	if (NULL == g_Loging.logfile)
	{
		g_Loging.logfile = fopen(g_Loging.filepath, "a+");
	}

	if (NULL == g_Loging.logfile)
	{
		g_bInit = false;
		perror("Open Log File Fail!");
		return -1;
	}	
	//获取日志时间
	settime();
	//写入日志级别，日志时间
	fprintf(g_Loging.logfile, "[%s] [%s]:[", LogLevelText[nLogLevel-1], g_Loging.logtime);

    //打印日志信息
    va_start(args,fromat);
    PrintfLOG(fromat,args);
    va_end(args);
    //文件刷出
    fflush(g_Loging.logfile);
    //日志关闭
    if(NULL != g_Loging.logfile)
	{
        fclose(g_Loging.logfile);
	}
    g_Loging.logfile=NULL;
    return 0;
}