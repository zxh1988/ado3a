#include "stdafx.h"
#include "Ado.h"
//#include "log.h"

#include <tchar.h>
//#include <vld.h>




namespace Ado
{



CAdo::CAdo(void):m_pConnection(NULL),
	m_pRecordset(NULL)
{	
	//m_hEventRecordSet = CreateEvent(NULL, TRUE, TRUE, NULL);	
	m_bInit = false;
}

CAdo::~CAdo(void)
{
	// release COM
	//::CoUninitialize();
	//Close();
}


ADORES CAdo::AdoInitDb(IN const ADOCHAR *szDbServerIp, \
						IN const ADOCHAR *szDbName, \
						IN const ADOCHAR *szDbUser, \
						IN const char *szDbPasswd)
{ 
	/*SharedAppenderPtr pFileAppender(new FileAppender(_T("ADO3ADll.log"), \
		std::ios::app | std::ios::in, \
		true, true)); */
	SharedAppenderPtr  pFileAppender(new  RollingFileAppender(_T("ADO3ADll.log"), 10*1024*1024, 1, true, true));
	pFileAppender->setName(_T("filelibado3a"));
	std::auto_ptr<Layout> pPatternLayout(new PatternLayout(_T("%D{%Y-%m-%d %H:%M:%S}    - %m [%l]%n")));   
	pFileAppender->setLayout(pPatternLayout);   
	m_Logger = Logger::getInstance(_T("LoggerName"));   	
	m_Logger.addAppender(pFileAppender);  
	

	// 初始化OLE/COM库环境
	::CoInitialize(NULL);
	try
	{
		if (NULL == m_pConnection)
		{
			// 创建Connection对象
			m_pConnection.CreateInstance(__uuidof(Connection));
		}
		//设置连接字符串，必须是BSTR型或者_bstr_t类型
		m_pConnection->ConnectionString = (_bstr_t)("Provider = SQLOLEDB;Server=") \
			+ szDbServerIp \
			+(_bstr_t)(";Database=") + szDbName \
			+ (_bstr_t)(";uid=") +  szDbUser \
			+ (_bstr_t)(";pwd=") + szDbPasswd; 

		m_szConnectStr = m_pConnection->ConnectionString;
		m_pConnection->CommandTimeout = 10;
		m_pConnection->ConnectionTimeout = 5;
		HRESULT res = m_pConnection->Open("", "", "", adModeUnknown);
		m_bInit = true;
	}
	catch(_com_error &e)
	{
		std::cerr<<e.Description() << std::endl;
		std::cout <<"CAdo::AdoInitDb "<<e.Description()<< std::endl;	
		//LOG(ERRORR,"CAdo::AdoInitDb exception=%s",e.Description());
		LOG4CPLUS_ERROR(m_Logger,"CAdo::AdoInitDb exception=" << e.Description());
		return ADO_EXCEPTION;
	}
	//LOG(INF,"CAdo::AdoInitDb success szDbUser=%s szDbPasswd=%s szDbServer=%s szDbBase=%s",szDbUser,szDbPasswd,szDbServer,szDbBase);
	LOG4CPLUS_INFO(m_Logger, "CAdo::AdoInitDb success" \
		<<" szDbUser:"<<szDbUser \
		<<" szDbPasswd:" << szDbPasswd \
		<<" szDbServerIp:"<< szDbServerIp \
		<<" szDbBase:"<<szDbName); 

	return ADO_SUCCESS;
}

ADORES CAdo::Connect()
{
	try
	{
		// 创建Connection对象
		m_pConnection.CreateInstance(__uuidof(Connection));
		HRESULT res = m_pConnection->Open(m_szConnectStr, "", "", adModeUnknown);
	}
	catch(_com_error &e)
	{
		std::cerr<<e.Description() << std::endl;
		std::cout <<"CAdo::Connect "<<e.Description()<< std::endl;
		//LOG(ERRORR,"CAdo::Connect exception=%s",e.Description());
		LOG4CPLUS_ERROR(m_Logger,"CAdo::Connect exception="<<e.Description());
		return ADO_EXCEPTION;
	}
	//LOG(INF,"CAdo::Connect success ConnectString=%s",m_szConnectStr);
	LOG4CPLUS_INFO(m_Logger,"CAdo::Connect success ConnectString="<<m_szConnectStr);
	return ADO_SUCCESS;
}

_RecordsetPtr CAdo::GetRecordSet(const ADOCHAR *szSQL)
{
	_RecordsetPtr pRecordset = NULL;
	try
	{
		if (!m_bInit)
		{
			if (ADO_SUCCESS != Connect()) return pRecordset;
		}
		
		// 创建记录集对象
		pRecordset.CreateInstance(__uuidof(Recordset));		
		// 取得表中的记录
		pRecordset->Open((_bstr_t)szSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		
	}
	catch(_com_error &e)
	{
		m_bInit = false;
		std::cerr<<e.Description() << std::endl;
		std::cout <<"CAdo::GetRecordSet "<<e.Description()<< std::endl;
		//LOG(ERRORR,"CAdo::GetRecordSet exception=%s SQL=%s",e.Description(),szSQL);
		LOG4CPLUS_ERROR(m_Logger,"CAdo::GetRecordSet exception="<<e.Description()<<"SQL="<<szSQL);
		pRecordset = NULL;
		return pRecordset;
	}
	//LOG(INF,"CAdo::GetRecordSet success SQL=%s",szSQL);
	LOG4CPLUS_INFO(m_Logger,"CAdo::GetRecordSet success SQL="<<szSQL);
	//SetEvent(m_hEventRecordSet);
	return pRecordset;
}

ADORES CAdo::ExcuteSQL(const ADOCHAR *szSQL)
{
	try
	{	
		//m_pConnection->BeginTrans();
		m_pConnection->Execute(szSQL, NULL, adCmdText);	//执行SQL语句	
		//m_pConnection->CommitTrans();
	}
	catch(_com_error &e)
	{
		//m_pConnection->RollbackTrans();
		std::cerr<<e.Description() << std::endl;
		std::cout <<"CAdo::ExcuteSQL "<<e.Description()<< std::endl;
		//LOG(ERRORR,"CAdo::ExcuteSQL exception=%s SQL=%s",e.Description(),szSQL);
		LOG4CPLUS_ERROR(m_Logger,"CAdo::ExcuteSQL exception="<<e.Description() <<"SQL="<<szSQL);

		return ADO_EXCEPTION;
	}
	//LOG(INF,"CAdo::ExcuteSQL success SQL=%s",szSQL);
	LOG4CPLUS_INFO(m_Logger,"CAdo::ExcuteSQL success SQL="<<szSQL);
	return ADO_SUCCESS;
}

ADOUINT CAdo::GetReturnID()
{
	_variant_t vVal;				
	std::string szVal;	
	ADOINT nId = -1;

	//EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = GetRecordSet("SELECT @@IDENTITY");
	//LeaveCriticalSection(&m_csMutex);
	//if (NULL == sqlres) return ADO_NOT_FOUND;

	while(!sqlres->EndOfFile)
	{	
		int num = sqlres->GetFields()->GetCount();		
		for (int i = 0; i < num; i++)
		{		
			switch(i)
			{
			case TABLEID_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));		
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				nId = atoi(szVal.c_str());
				break;
			default:
				break;
			}
		}
		sqlres->MoveNext();
	}
	sqlres->Close();
	return nId;
}

ADORES CAdo::Close()
{
	try
	{		
		if(m_pConnection->State != adStateClosed)
		{
			m_pConnection->Close(); 
		}
		if (NULL != m_pConnection)
		{		
			m_pConnection.Release();
			m_pConnection = NULL;
		} 

		if (m_pRecordset->GetState() == adStateOpen)
		{
			m_pRecordset->Close();
		}
		if (NULL != m_pRecordset)
		{
			m_pRecordset.Release();
			m_pRecordset = NULL;
		}
	}
	catch(_com_error &e)
	{
		LOG4CPLUS_ERROR(m_Logger,"CAdo::Close exception="<<e.Description());
		return ADO_EXCEPTION;
	}

	// 释放环境
	::CoUninitialize();	
	return ADO_SUCCESS;
}

ADORES CAdo::Release()
{
	m_pConnection->Release();
	return ADO_SUCCESS;
}





} // end namespace