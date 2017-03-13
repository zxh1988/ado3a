#pragma once
#include <iostream>



#ifdef _DEBUG
#import "..\..\..\..\bin\\debug\\msado15.dll" \
	no_namespace rename("EOF", "EndOfFile") \
	rename("DataTypeEnum","adoDataTypeEnum") \
	rename("FieldAttributeEnum", "adoFielAttributeEnum") rename("EditModeEnum", "adoEditModeEnum") \
	rename("LockTypeEnum", "adoLockTypeEnum") rename("RecordStatusEnum", "adoRecordStatusEnum") \
	rename("ParameterDirectionEnum", "adoParameterDirectionEnum")
#else
#import "..\..\..\..\bin\\release\\msado15.dll" \
	no_namespace rename("EOF", "EndOfFile") \
	rename("DataTypeEnum","adoDataTypeEnum") \
	rename("FieldAttributeEnum", "adoFielAttributeEnum") rename("EditModeEnum", "adoEditModeEnum") \
	rename("LockTypeEnum", "adoLockTypeEnum") rename("RecordStatusEnum", "adoRecordStatusEnum") \
	rename("ParameterDirectionEnum", "adoParameterDirectionEnum")
#endif



#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>  
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
//#include <conio.h>
#include <log4cplus/helpers/sleep.h>
#include <log4cplus/loggingmacros.h>

#include <iostream>

using namespace log4cplus;
using namespace log4cplus::helpers; 



#include "adointerface.h"





typedef enum TABLEIDIDX
{
	TABLEID_ID = 0
};




namespace Ado
{




class CAdo
{
public:
	CAdo(void);
	virtual ~CAdo(void);

public:
	_ConnectionPtr &GetConnectionPtr() { return m_pConnection; }

	ADORES AdoInitDb(const ADOCHAR *szDbServerIp, const ADOCHAR *szDbName, const ADOCHAR *szDbUser, const ADOCHAR *szDbPasswd);
	ADORES Connect();

	//query
	_RecordsetPtr GetRecordSet(const ADOCHAR *szSQL);
	//execute sql
	ADORES ExcuteSQL(const ADOCHAR *szSQL);
	ADOUINT GetReturnID();
	ADORES Close();
	ADORES Release();

protected:

private:	
	bool m_bInit;
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	_bstr_t m_szConnectStr;

	//HANDLE m_hEventRecordSet;

	Logger m_Logger;
	
};





}; // end namespace
