#include "stdafx.h"
#include <iostream>
#include "Ado3A.h"

#include <ATLComTime.h>

//#include <vld.h>


CAdo3A *CAdo3A::m_gpCAdo3A = NULL;


CAdo3A::CAdo3A(void)
{	
	InitializeCriticalSection(&m_csMutex);
}

CAdo3A::~CAdo3A(void)
{
	AdoClose();
	DeleteCriticalSection(&m_csMutex);
}

CAdo3A *CAdo3A::GetInstance()
{
	if (!m_gpCAdo3A)
	{
		m_gpCAdo3A = new CAdo3A();
	}
	return m_gpCAdo3A;
}

ADORES CAdo3A::AdoInitDb(IN const ADOCHAR *szDbServerIp, \
						IN const ADOCHAR *szDbName, \
						IN const char *szDbUser, \
						IN const ADOCHAR *szDbPasswd)
{
	return ado.AdoInitDb(szDbServerIp,szDbName,szDbUser,szDbPasswd);
}

ADORES CAdo3A::AdoBeginTransaction()
{
	return ado.ExcuteSQL("BEGIN TRANSACTION");
}

ADORES CAdo3A::AdoCommitTransaction()
{
	return ado.ExcuteSQL("COMMIT TRANSACTION");
}

ADORES CAdo3A::AdoRollBackTransaction()
{
	return ado.ExcuteSQL("ROLLBACK TRANSACTION");
}


ADORES CAdo3A::Ado3AQueryCustomer(IN CUSTOMER &customer, \
								IN const ADOCHAR *username, \
								IN const ADOCHAR *passwd) 
{

	if (NULL == username || NULL == passwd) return ADO_PARAM_ERROR;
	
	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
					WHERE  \"LoginName\" = '%s' AND \"Password\" = '%s';", \
					CUSTOMER_3A_TAB_CFG,username,passwd);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);

	if (NULL == sqlres) return ADO_LOGINFAILED;
	
	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
		memset(szTime, 0 ,sizeof(szTime));

		memset(&customer, 0 ,sizeof(customer));
		vVal = sqlres->GetCollect(_variant_t("CustomerID"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customer.nCustomerID = atoi(szVal.c_str());		

		vVal = sqlres->GetCollect(_variant_t("LoginName"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szLoginName,sizeof(customer.szLoginName),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("CustomerCode"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szCustomerCode,sizeof(customer.szCustomerCode),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Password"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szPassWd,sizeof(customer.szPassWd),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Corporation"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szCorporation,sizeof(customer.szCorporation),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("CorporationIDCard"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szCorporationIDCard,sizeof(customer.szCorporationIDCard),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Company"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szCompany,sizeof(customer.szCompany),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Email"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szEmail,sizeof(customer.szEmail),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Address"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szAddr,sizeof(customer.szAddr),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("AgentID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customer.nAgentID = atoi(szVal.c_str());

		vVal = sqlres->GetCollect(_variant_t("Description"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szDescription,sizeof(customer.szDescription),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("QQNum"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szQQNum,sizeof(customer.szQQNum),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("OperatorMobile"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szOperatorMobile,sizeof(customer.szOperatorMobile),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("OperatorFaxNum"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szOperatorTelPhone,sizeof(customer.szOperatorTelPhone),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("CustomerTypeID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customer.nCustomerTypeID = atoi(szVal.c_str());

		vVal = sqlres->GetCollect(_variant_t("CustomerAreaID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customer.nCustomerAreaID = atoi(szVal.c_str());

		vVal = sqlres->GetCollect(_variant_t("CreateTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
		nYear = odatetime.GetYear();
		nMon = odatetime.GetMonth();
		nDay = odatetime.GetDay();
		nHour = odatetime.GetHour();
		nMin = odatetime.GetMinute();
		nSec = odatetime.GetSecond();
		sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		sprintf_s(customer.szCreateTime,sizeof(customer.szCreateTime),"%s",szTime);	

		vVal = sqlres->GetCollect(_variant_t("UpdateTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;	
		if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
		{
			memset(szTime, 0, sizeof(szTime));
		}
		else
		{
			nYear = odatetime.GetYear();
			nMon = odatetime.GetMonth();
			nDay = odatetime.GetDay();
			nHour = odatetime.GetHour();
			nMin = odatetime.GetMinute();
			nSec = odatetime.GetSecond();
			sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		}		
		
		sprintf_s(customer.szUpdateTime,sizeof(customer.szUpdateTime),"%s",szTime);	
	
		vVal = sqlres->GetCollect(_variant_t("Operator"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customer.szOperator,sizeof(customer.szOperator),"%s",szVal.c_str());	

		bFound = true;
		sqlres->MoveNext();					//move next row
	}	
	sqlres->Close();
	return (!bFound) ? ADO_LOGINFAILED: ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AQueryUsers(OUT USERS &user, IN const ADOCHAR *username, IN const ADOCHAR *passwd)
{
	if (NULL == username || NULL == passwd) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"UserName\" = '%s' AND \"Password\" = '%s';", \
										USERS_3A_TAB_CFG,username,passwd);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);

	if (NULL == sqlres) return ADO_LOGINFAILED;

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		memset(&user, 0 ,sizeof(user));
		vVal = sqlres->GetCollect(_variant_t("UserId"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szUserId,sizeof(user.szUserId),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("UserName"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szUserName,sizeof(user.szUserName),"%s",szVal.c_str());	
		
		vVal = sqlres->GetCollect(_variant_t("RealName"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szRealName,sizeof(user.szRealName),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Password"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szPasswd,sizeof(user.szPasswd),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Position"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szPosition,sizeof(user.szPosition),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Qualification"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szQualification,sizeof(user.szQualification),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Call"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szCall,sizeof(user.szCall),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("MedicaLOrgId"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szMedicalOrgId,sizeof(user.szMedicalOrgId),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("DepartmentId"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szDepartmentId,sizeof(user.szDepartmentId),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("HandPhone"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szHandPhone,sizeof(user.szHandPhone),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Email"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szEmail,sizeof(user.szEmail),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("IsValid"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		szVal = (szVal == "-1") ? "1" : "0";
		user.nIsValid = atoi(szVal.c_str());

		vVal = sqlres->GetCollect(_variant_t("SignImg"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		//sprintf_s(user.szSignImg,sizeof(user.szSignImg),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("UserImg"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		//sprintf_s(user.szUserImg,sizeof(user.szUserImg),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("UserIntroduction"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(user.szUserIntroduction,sizeof(user.szUserIntroduction),"%s",szVal.c_str());	
		
		
		bFound = true;
		sqlres->MoveNext();					//move next row
	}	
	sqlres->Close();
	return (!bFound) ? ADO_LOGINFAILED: ADO_SUCCESS;
}


ADORES CAdo3A::Ado3AQueryCustomerProduct(OUT CUSTOMERPRODUCT &customerproduct, \
									IN ADOINT nProductID)
{
	if (nProductID < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"ProductID\" = %d;", \
										CUSTOMER_PRODUCT_3A_TAB_CFG,nProductID);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);
	if (NULL == sqlres) return ADO_EXCEPTION;

	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
		memset(szTime, 0 ,sizeof(szTime));

		memset(&customerproduct, 0 ,sizeof(customerproduct));

		vVal = sqlres->GetCollect(_variant_t("ProductID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nProductID = atoi(szVal.c_str());
				
		vVal = sqlres->GetCollect(_variant_t("ProductCode"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customerproduct.szproductCode,sizeof(customerproduct.szproductCode),"%s",szVal.c_str());	
			
		vVal = sqlres->GetCollect(_variant_t("ProductName"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(customerproduct.szProductName,sizeof(customerproduct.szProductName),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("ChargeMode"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nChargeMode = atoi(szVal.c_str());
		
		vVal = sqlres->GetCollect(_variant_t("CustomerID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nCustomerID = atoi(szVal.c_str());
		
		vVal = sqlres->GetCollect(_variant_t("Price"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nPrice = atoi(szVal.c_str());
		
		vVal = sqlres->GetCollect(_variant_t("Deposit"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nDeposit = atoi(szVal.c_str());
					
		vVal = sqlres->GetCollect(_variant_t("OrderID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nOrderID = atoi(szVal.c_str());
								
		vVal = sqlres->GetCollect(_variant_t("OrderTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
		nYear = odatetime.GetYear();
		nMon = odatetime.GetMonth();
		nDay = odatetime.GetDay();
		nHour = odatetime.GetHour();
		nMin = odatetime.GetMinute();
		nSec = odatetime.GetSecond();
		sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		sprintf_s(customerproduct.szOrderTime,sizeof(customerproduct.szOrderTime),"%s",szTime);	

					
		vVal = sqlres->GetCollect(_variant_t("EffectTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
		nYear = odatetime.GetYear();
		nMon = odatetime.GetMonth();
		nDay = odatetime.GetDay();
		nHour = odatetime.GetHour();
		nMin = odatetime.GetMinute();
		nSec = odatetime.GetSecond();
		sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		sprintf_s(customerproduct.EffectTime,sizeof(customerproduct.EffectTime),"%s",szTime);	
		

		vVal = sqlres->GetCollect(_variant_t("ExpTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
		nYear = odatetime.GetYear();
		nMon = odatetime.GetMonth();
		nDay = odatetime.GetDay();
		nHour = odatetime.GetHour();
		nMin = odatetime.GetMinute();
		nSec = odatetime.GetSecond();
		sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		sprintf_s(customerproduct.ExpTime,sizeof(customerproduct.ExpTime),"%s",szTime);	
			

		vVal = sqlres->GetCollect(_variant_t("AccountID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nAccountID = atoi(szVal.c_str());

		vVal = sqlres->GetCollect(_variant_t("IsValid"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nIsValid = atoi(szVal.c_str());

		vVal = sqlres->GetCollect(_variant_t("UpdateTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;	
		if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
		{
			memset(szTime, 0, sizeof(szTime));
		}
		else
		{
			nYear = odatetime.GetYear();
			nMon = odatetime.GetMonth();
			nDay = odatetime.GetDay();
			nHour = odatetime.GetHour();
			nMin = odatetime.GetMinute();
			nSec = odatetime.GetSecond();
			sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		}

		sprintf_s(customerproduct.szUpdateTime,sizeof(customerproduct.szUpdateTime),"%s",szTime);	

		vVal = sqlres->GetCollect(_variant_t("IsCharge"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		customerproduct.nIsCharge = atoi(szVal.c_str());

		bFound = true;
		sqlres->MoveNext();	
	}
	sqlres->Close();
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AUpdateCustomerProduct(IN ADOINT nProductID, IN ADOINT price)
{
	if (nProductID < 0 || price < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"Price\" = %d  \
				where \"ProductID\" = %d;", \
				CUSTOMER_PRODUCT_3A_TAB_CFG,price,nProductID);
	
	ADORES adores = ado.ExcuteSQL(szSql);

	return adores;
}

ADORES CAdo3A::Ado3AUpdateCustomerProductIsCharge(IN ADOINT nProductID, IN ADOINT nIsCharge)
{
	if (nProductID < 0 || nIsCharge < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"IsCharge\" = %d  \
										where \"ProductID\" = %d;", \
										CUSTOMER_PRODUCT_3A_TAB_CFG,nIsCharge,nProductID);

	ADORES adores = ado.ExcuteSQL(szSql);

	return adores;
}



ADORES CAdo3A::Ado3AQueryCustomerProductAndProductDetailsPoint(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN ADOINT AccountID, IN ADOINT ServiceID)
{
	if (AccountID < 0 || ServiceID < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	//sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT p.ProductID, p.ProductCode, \
	//									p.ProductName, p.ChargeMode, \
	//									p.CustomerID, p.Price, \
	//									p.Deposit, p.OrderID, \
	//									p.OrderTime, p.EffectTime, \
	//									p.ExpTime, p.AccountID, \
	//									pd.ProductDetailsID, pd.ProductDetailsCode, \
	//									pd.ProductID, pd.ServiceID, \
	//									pd.ChargeType, pd.Price, \
	//									pd.FreeServiceNum, pd.ExceedPrice, \
	//									pd.SaleDeviceTypeID, pd.SaleDeviceNum, \
	//									pd.ChargeTime, pd.NextChargeTime, \
	//									pd.RemainServiceNum \
	//									FROM %s AS p, %s AS pd \
	//									WHERE  \"AccountID\" = %d AND \
	//									\"ServiceID\" = %d \
	//									ORDER BY ExpTime ASC, EffectTime  ASC;", \
	//									CUSTOMER_PRODUCT_3A_TAB_CFG, \
	//									CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG, \
	//									AccountID, ServiceID);


	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										RIGHT JOIN %s \
										ON CustomerProduct.ProductID = \
										CustomerProductDetails.ProductID \
										WHERE \"AccountID\" = %d AND \
										\"ServiceID\" = %d \
										AND IsValid <> 0 \
										ORDER BY ExpTime ASC, EffectTime  ASC;",\
										CUSTOMER_PRODUCT_3A_TAB_CFG, \
										CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG, \
										AccountID, ServiceID);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);
	if (NULL == sqlres) return ADO_EXCEPTION;


	_variant_t vVal;				
	std::string szVal;
	bool bFound = false;
	pNum = 0;


	long nRows = sqlres->GetRecordCount();
	// 如果ado不支持此属性，则手工计算记录数目 
	if (nRows < 0)
	{
		nRows = 0;
		//sqlres->MoveFirst();
		while(!sqlres->EndOfFile)
		{
			nRows++;
			sqlres->MoveNext();
		}		
	}

	if(nRows <= 0) return ADO_SUCCESS;

	sqlres->MoveFirst();
	
	int nLen = sizeof(PRODUCTANDPRODUCTDETAILS);
	*pp = (PRODUCTANDPRODUCTDETAILS*)new ADOCHAR[nRows * nLen];
	pNum = nRows;

	memset(*pp, 0 ,sizeof(nRows * nLen));


	PRODUCTANDPRODUCTDETAILS *productanddetails;
	productanddetails = (PRODUCTANDPRODUCTDETAILS *)(*pp);

	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	while(!sqlres->EndOfFile)
	{	
		int num = sqlres->GetFields()->GetCount();	
		memset(productanddetails, 0, sizeof(PRODUCTANDPRODUCTDETAILS));
		for (int i = 0; i < num; i++)
		{		
			nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
			memset(szTime, 0 ,sizeof(szTime));

			switch(i)
			{
			case TABCUSTOMERPRODUCTANDDETAILS_PRODUCT_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductID = atoi(szVal.c_str());			
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_PRODUCT_CODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(productanddetails->szproductCode,sizeof(productanddetails->szproductCode),"%s",szVal.c_str());	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_PRODUCT_NAME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(productanddetails->szProductName,sizeof(productanddetails->szProductName),"%s",szVal.c_str());	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_CHARGEMODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nChargeMode = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_CUSTOMER_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nCustomerID = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_PRICE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nPrice = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_DEPOSIT:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nDeposit = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_ORDER_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nOrderID = atoi(szVal.c_str());
				break;													
			case TABCUSTOMERPRODUCTANDDETAILS_ORDER_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szOrderTime,sizeof(productanddetails->szOrderTime),"%s",szTime);		
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_EFFECT_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->EffectTime,sizeof(productanddetails->EffectTime),"%s",szTime);	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_EXP_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->ExpTime,sizeof(productanddetails->ExpTime),"%s",szTime);	
				break;		
			case TABCUSTOMERPRODUCTANDDETAILS_ACCOUNT_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nAccountID = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_IS_VALID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nIsValid = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_UPDATE_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szUpdateTime,sizeof(productanddetails->szUpdateTime),"%s",szTime);	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_IsCharge:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nIsCharge = atoi(szVal.c_str());
				break;

			case TABPRODUCTDETAILSANDDETAILS_DETAILS_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductDetailsID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_DETAILS_CODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(productanddetails->szProductDetailsCode,sizeof(productanddetails->szProductDetailsCode),"%s",szVal.c_str());	
				break;
			case TABPRODUCTDETAILSANDDETAILS_PRODUCTDETAILS_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductDetailsProductID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_SERVICE_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nServiceID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_CHARGE_TYPE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nChargeType = atoi(szVal.c_str());
				break;			
			case TABPRODUCTDETAILSANDDETAILS_PRODUCTANDDETAILS_PRICE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductDetailsPrice = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_FREE_SERVICE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nFreeServiceNum = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_EXCEED_PRICE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nExceedPrice = atoi(szVal.c_str());
				break;		
			case TABPRODUCTDETAILSANDDETAILS_SALE_DEVICE_TYPE_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nSaleDeviceTypeID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_SALE_DEVICE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nSaleDeviceNum = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_CHARGE_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szChargeTime,sizeof(productanddetails->szChargeTime),"%s",szTime);	
				break;
			case TABPRODUCTDETAILSANDDETAILS_NEXT_CHARGE_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szNextChargeTime,sizeof(productanddetails->szNextChargeTime),"%s",szTime);	
				break;
			case TABPRODUCTDETAILSANDDETAILS_REMAIN_SERVICE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nRemainServiceNum = atoi(szVal.c_str());		
			case TABPRODUCTDETAILSANDDETAILS_CHARGE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nChageNum = atoi(szVal.c_str());	
				break;
			default:
				break;
			}
			bFound = true;
		}
		productanddetails += 1;
		bFound = true;
		sqlres->MoveNext();	
	}
	sqlres->Close();
	productanddetails = NULL;
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(PRODUCTANDPRODUCTDETAILS *&pp)
{
	if (NULL != pp)
	{
		delete[] pp;
		pp = NULL;
	}
	return ADO_SUCCESS;
}


ADORES CAdo3A::Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN const ADOCHAR *szBeginTime, IN const ADOCHAR *szEndTime)
{
	if (NULL == szBeginTime || NULL == szEndTime) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	/*sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT p.ProductID, p.ProductCode, \
										p.ProductName, p.ChargeMode, \
										p.CustomerID, p.Price, \
										p.Deposit, p.OrderID, \
										p.OrderTime, p.EffectTime, \
										p.ExpTime, p.AccountID, \
										pd.ProductDetailsID, pd.ProductDetailsCode, \
										pd.ProductID, pd.ServiceID, \
										pd.ChargeType, pd.Price, \
										pd.FreeServiceNum, pd.ExceedPrice, \
										pd.SaleDeviceTypeID, pd.SaleDeviceNum, \
										pd.ChargeTime, pd.NextChargeTime, \
										pd.RemainServiceNum \
										FROM %s AS pd , %s AS p \
										WHERE  \"NextChargeTime\" >= '%s' AND \
										\"NextChargeTime\" <= '%s' \
										ORDER BY NextChargeTime ASC;", \
										CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG, \
										CUSTOMER_PRODUCT_3A_TAB_CFG, \
										szBeginTime, szEndTime);*/


	
	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
											 RIGHT JOIN %s \
											 ON CustomerProduct.ProductID = \
											 CustomerProductDetails.ProductID \
											 WHERE ChargeMode = 2 AND \"NextChargeTime\" >= '%s' AND \
											 \"NextChargeTime\" <= '%s' \
											 AND ChargeType <> 0 AND IsValid <> 0 \
											 ORDER BY NextChargeTime ASC;",\
		CUSTOMER_PRODUCT_3A_TAB_CFG, \
		CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG,
		szBeginTime, szEndTime);
	/**ChargeType <> 0表示查询按时间计费的记录**/


	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);
	if (NULL == sqlres) return ADO_EXCEPTION;


	_variant_t vVal;				
	std::string szVal;
	bool bFound = false;
	pNum = 0;


	long nRows = sqlres->GetRecordCount();
	// 如果ado不支持此属性，则手工计算记录数目 
	if (nRows < 0)
	{
		nRows = 0;
		//sqlres->MoveFirst();
		while(!sqlres->EndOfFile)
		{
			nRows++;
			sqlres->MoveNext();			
		}	
	}

	if(nRows <= 0) return ADO_SUCCESS;

	sqlres->MoveFirst();

	int nLen = sizeof(PRODUCTANDPRODUCTDETAILS);
	*pp = (PRODUCTANDPRODUCTDETAILS*)new ADOCHAR[nRows * nLen];
	pNum = nRows;

	memset(*pp, 0 ,sizeof(nRows * nLen));


	PRODUCTANDPRODUCTDETAILS *productanddetails;
	productanddetails = (PRODUCTANDPRODUCTDETAILS *)(*pp);

	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	while(!sqlres->EndOfFile)
	{	
		int num = sqlres->GetFields()->GetCount();	
		memset(productanddetails, 0, sizeof(PRODUCTANDPRODUCTDETAILS));
		for (int i = 0; i < num; i++)
		{		
			nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
			memset(szTime, 0 ,sizeof(szTime));
			switch(i)
			{
			case TABCUSTOMERPRODUCTANDDETAILS_PRODUCT_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductID = atoi(szVal.c_str());			
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_PRODUCT_CODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(productanddetails->szproductCode,sizeof(productanddetails->szproductCode),"%s",szVal.c_str());	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_PRODUCT_NAME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(productanddetails->szProductName,sizeof(productanddetails->szProductName),"%s",szVal.c_str());	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_CHARGEMODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nChargeMode = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_CUSTOMER_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nCustomerID = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_PRICE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nPrice = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_DEPOSIT:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nDeposit = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_ORDER_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nOrderID = atoi(szVal.c_str());
				break;													
			case TABCUSTOMERPRODUCTANDDETAILS_ORDER_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szOrderTime,sizeof(productanddetails->szOrderTime),"%s",szTime);		
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_EFFECT_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->EffectTime,sizeof(productanddetails->EffectTime),"%s",szTime);	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_EXP_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->ExpTime,sizeof(productanddetails->ExpTime),"%s",szTime);	
				break;		
			case TABCUSTOMERPRODUCTANDDETAILS_ACCOUNT_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nAccountID = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_IS_VALID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nIsValid = atoi(szVal.c_str());
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_UPDATE_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szUpdateTime,sizeof(productanddetails->szUpdateTime),"%s",szTime);	
				break;
			case TABCUSTOMERPRODUCTANDDETAILS_IsCharge:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nIsCharge = atoi(szVal.c_str());
				break;


			case TABPRODUCTDETAILSANDDETAILS_DETAILS_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductDetailsID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_DETAILS_CODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(productanddetails->szProductDetailsCode,sizeof(productanddetails->szProductDetailsCode),"%s",szVal.c_str());	
				break;
			case TABPRODUCTDETAILSANDDETAILS_PRODUCTDETAILS_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_SERVICE_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nServiceID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_CHARGE_TYPE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nChargeType = atoi(szVal.c_str());
				break;			
			case TABPRODUCTDETAILSANDDETAILS_PRODUCTANDDETAILS_PRICE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nProductDetailsPrice = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_FREE_SERVICE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nFreeServiceNum = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_EXCEED_PRICE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nExceedPrice = atoi(szVal.c_str());
				break;		
			case TABPRODUCTDETAILSANDDETAILS_SALE_DEVICE_TYPE_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nSaleDeviceTypeID = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_SALE_DEVICE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nSaleDeviceNum = atoi(szVal.c_str());
				break;
			case TABPRODUCTDETAILSANDDETAILS_CHARGE_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szChargeTime,sizeof(productanddetails->szChargeTime),"%s",szTime);	
				break;
			case TABPRODUCTDETAILSANDDETAILS_NEXT_CHARGE_TIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));		
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(productanddetails->szNextChargeTime,sizeof(productanddetails->szNextChargeTime),"%s",szTime);	
				break;
			case TABPRODUCTDETAILSANDDETAILS_REMAIN_SERVICE_NUM:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				productanddetails->nRemainServiceNum = atoi(szVal.c_str());
				break;
			default:
				break;
			}
			bFound = true;
		}
		productanddetails += 1;
		bFound = true;
		sqlres->MoveNext();	
	}
	sqlres->Close();
	productanddetails = NULL;
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(IN PRODUCTANDPRODUCTDETAILS *&pp)
{
	if (NULL != pp)
	{
		delete[] pp;
		pp = NULL;
	}
	return ADO_SUCCESS;
}


ADORES CAdo3A::Ado3AQueryCustomerProductDetails( \
							OUT CUSTOMERPRODUCTDETAILS &productdetails, \
							IN ADOINT nProductDetailsID)
{
	if (nProductDetailsID < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"ProductDetailsID\" = %d;", \
										CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG,nProductDetailsID);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);
	if (NULL == sqlres) return ADO_EXCEPTION;

	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		memset(&productdetails, 0 ,sizeof(productdetails));
		int num = sqlres->GetFields()->GetCount();		
		for (int i = 0; i < num; i++)
		{		
			nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
			memset(szTime, 0 ,sizeof(szTime));
			switch(i)
			{
				case TABPRODUCTDETAILS_DETAILS_ID:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nProductDetailsID = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_DETAILS_CODE:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					sprintf_s(productdetails.szProductDetailsCode,sizeof(productdetails.szProductDetailsCode),"%s",szVal.c_str());	
					break;
				case TABPRODUCTDETAILS_PRODUCT_ID:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nProductID = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_SERVICE_ID:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nServiceID = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_CHARGE_TYPE:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nChargeType = atoi(szVal.c_str());
					break;				
				case TABPRODUCTDETAILS_PRICE:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nPrice = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_FREE_SERVICE_NUM:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nFreeServiceNum = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_EXCEED_PRICE:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nExceedPrice = atoi(szVal.c_str());
					break;	
				case TABPRODUCTDETAILS_SALE_DEVICE_TYPE_ID:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nSaleDeviceTypeID = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_SALE_DEVICE_NUM:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nSaleDeviceNum = atoi(szVal.c_str());
					break;
				case TABPRODUCTDETAILS_CHARGE_TIME:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
					if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
					{
						memset(szTime, 0, sizeof(szTime));
					}
					else
					{
						nYear = odatetime.GetYear();
						nMon = odatetime.GetMonth();
						nDay = odatetime.GetDay();
						nHour = odatetime.GetHour();
						nMin = odatetime.GetMinute();
						nSec = odatetime.GetSecond();
						sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
					}
					sprintf_s(productdetails.szChargeTime,sizeof(productdetails.szChargeTime),"%s",szTime);	
					break;
				case TABPRODUCTDETAILS_NEXT_CHARGE_TIME:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
					if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
					{
						memset(szTime, 0, sizeof(szTime));
					}
					else
					{
						nYear = odatetime.GetYear();
						nMon = odatetime.GetMonth();
						nDay = odatetime.GetDay();
						nHour = odatetime.GetHour();
						nMin = odatetime.GetMinute();
						nSec = odatetime.GetSecond();
						sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
					}
					sprintf_s(productdetails.szNextChargeTime,sizeof(productdetails.szNextChargeTime),"%s",szTime);	
					break;
				case TABPRODUCTDETAILS_REMAIN_SERVICE_NUM:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nRemainServiceNum = atoi(szVal.c_str());
				case TABPRODUCTDETAILS_CHARGE_NUM:
					vVal = sqlres->GetCollect(_variant_t((long)i));							
					szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
					productdetails.nChageNum = atoi(szVal.c_str());
					break;
				default:
					break;
			}
			bFound = true;
		}	
		sqlres->MoveNext();	
	}
	sqlres->Close();
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AUpdateCustomerProductDetails(IN CUSTOMERPRODUCTDETAILS productdetails, IN ADOINT nProductDetailsID)
{
	if (nProductDetailsID < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"ProductDetailsCode\" = '%s', \
										\"ProductID\" = %d, \
										\"ServiceID\" = %d, \
										\"ChargeType\" = %d,\
										\"Price\" = %d, \
										\"FreeServiceNum\" = %d, \
										\"ExceedPrice\" = %d, \
										\"SaleDeviceTypeID\" = %d, \
										\"SaleDeviceNum\" = %d, \
										\"ChargeTime\" = '%s', \
										\"NextChargeTime\" =  '%s', \
										\"RemainServiceNum\" = %d \
										WHERE \"ProductDetailsID\" = %d;", \
										CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG, \
										productdetails.szProductDetailsCode, \
										productdetails.nProductID, \
										productdetails.nServiceID, \
										productdetails.nChargeType, \
										productdetails.nPrice, \
										productdetails.nFreeServiceNum, \
										productdetails.nExceedPrice, \
										productdetails.nSaleDeviceTypeID, \
										productdetails.nSaleDeviceNum, \
										productdetails.szChargeTime, \
										productdetails.szNextChargeTime, \
										productdetails.nRemainServiceNum, \
										nProductDetailsID);


	ADORES adores = ado.ExcuteSQL(szSql);

	return adores;
}



ADORES CAdo3A::Ado3AUpdateCustomerProductDetailsRemainServiceNum( \
									IN ADOINT nProductDetailsID, \
									IN ADOINT nFreeServicetNum)
{
	if (nProductDetailsID < 0 || nFreeServicetNum < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"RemainServiceNum\" = %d  \
										WHERE \"ProductDetailsID\" = %d;", \
					CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG,nFreeServicetNum,nProductDetailsID);

	ADORES adores = ado.ExcuteSQL(szSql);

	return adores;

}

ADORES CAdo3A::Ado3AUpdateCustomerProductDetailsPrice( \
						IN ADOINT nProductDetailsID, \
						IN ADOINT price)
{
	if (nProductDetailsID < 0 || price < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"Price\" = %d  \
										WHERE \"ProductDetailsID\" = %d;", \
					CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG,price,nProductDetailsID);

	ADORES adores = ado.ExcuteSQL(szSql);

	return adores;
}

ADORES CAdo3A::Ado3AUpdateCustomerProductDetailExceedPrice( \
					IN ADOINT nProductDetailsID, \
					IN ADOINT exceedprice)
{
	if (nProductDetailsID < 0 || exceedprice < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"ExceedPrice\" = %d  \
										WHERE \"ProductDetailsID\" = %d;", \
					CUSTOMER_PRODUCT_DETAILS_3A_TAB_CFG,exceedprice,nProductDetailsID);

	ADORES adores = ado.ExcuteSQL(szSql);

	return adores;

}

ADORES CAdo3A::Ado3AQueryAccountHospital( \
							OUT ACCOUNTHOSTPITAL &accounthospital, \
							IN ADOINT nAccountHospitalID)
{
	if (nAccountHospitalID < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"AccountHospitalID\" = %d;", \
										ACCOUNT_HOSPITAL_3A_TAB_CFG,nAccountHospitalID);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);

	if (NULL == sqlres) return ADO_EXCEPTION;


	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		memset(&accounthospital, 0 ,sizeof(accounthospital));
		int num = sqlres->GetFields()->GetCount();		
		for (int i = 0; i < num; i++)
		{		
			switch(i)
			{
			case TABACCOUNTHOSPITAL_ACCOUNT_HOSPITAL_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				accounthospital.nAccountHospitalID = atoi(szVal.c_str());
				break;
			case TABACCOUNTHOSPITAL_ACCOUNT_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				accounthospital.nAccountID = atoi(szVal.c_str());
				break;
			case TABACCOUNTHOSPITAL_MEDICALORG_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(accounthospital.szMedicalOrgId,sizeof(accounthospital.szMedicalOrgId),"%s",szVal.c_str());
				break;
			}
			bFound = true;
		}
		sqlres->MoveNext();	
	}
	sqlres->Close();
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AQueryAccountHospitalMedicalOrgId( \
							OUT ACCOUNTHOSTPITAL &accounthospital, \
							IN const ADOCHAR *szMedicalOrgId)
{
	if (NULL == szMedicalOrgId) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"MedicalOrgId\" = '%s'", \
										ACCOUNT_HOSPITAL_3A_TAB_CFG,szMedicalOrgId);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);

	if (NULL == sqlres) return ADO_EXCEPTION;


	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		memset(&accounthospital, 0 ,sizeof(accounthospital));
		int num = sqlres->GetFields()->GetCount();		
		for (int i = 0; i < num; i++)
		{		
			switch(i)
			{
			case TABACCOUNTHOSPITAL_ACCOUNT_HOSPITAL_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				accounthospital.nAccountHospitalID = atoi(szVal.c_str());
				break;
			case TABACCOUNTHOSPITAL_ACCOUNT_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				accounthospital.nAccountID = atoi(szVal.c_str());
				break;
			case TABACCOUNTHOSPITAL_MEDICALORG_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(accounthospital.szMedicalOrgId,sizeof(accounthospital.szMedicalOrgId),"%s",szVal.c_str());
				break;
			default:
				break;
			}
			bFound = true;
		}
		sqlres->MoveNext();	
	}
	sqlres->Close();
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}


ADORES CAdo3A::Ado3AQueryCustomerAccount( \
							IN CUSTOMERACCOUNT &customeraccount, \
							IN ADOINT AccountID)
{
	if (AccountID < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"AccountID\" = %d;", \
										CUSTOMER_ACCOUNT_3A_TAB_CFG,AccountID);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);

	if (NULL == sqlres) return ADO_EXCEPTION;

	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		memset(&customeraccount, 0 ,sizeof(customeraccount));
		int num = sqlres->GetFields()->GetCount();		
		for (int i = 0; i < num; i++)
		{	
			nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
			memset(szTime, 0 ,sizeof(szTime));
			switch(i)
			{
			case TABCUSTOMERACCOUNT_ACCOUNTID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				customeraccount.nAccountID = atoi(szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_ACCOUNT_CODE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(customeraccount.szAccountCode,sizeof(customeraccount.szAccountCode),"%s",szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_BALANCE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				customeraccount.nBalance = atoi(szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_OFFERBALANCE:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				customeraccount.nOfferBalance = atoi(szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_USERID:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				customeraccount.nCustomerID = atoi(szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_TRANSACTION_PASSWD:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				sprintf_s(customeraccount.szTransactionPasswd,sizeof(customeraccount.szTransactionPasswd),"%s",szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_DEPOSIT:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				customeraccount.nDeposit = atoi(szVal.c_str());
				break;
			case TABCUSTOMERACCOUNT_CREATETIME:
				vVal = sqlres->GetCollect(_variant_t((long)i));							
				//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
				if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
				{
					memset(szTime, 0, sizeof(szTime));
				}
				else
				{
					nYear = odatetime.GetYear();
					nMon = odatetime.GetMonth();
					nDay = odatetime.GetDay();
					nHour = odatetime.GetHour();
					nMin = odatetime.GetMinute();
					nSec = odatetime.GetSecond();
					sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
				}
				sprintf_s(customeraccount.szCreateTime,sizeof(customeraccount.szCreateTime),"%s",szTime);
				break;
			default:
				break;
			}
			bFound = true;
		}
		sqlres->MoveNext();	
	}
	sqlres->Close();
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AUpdateCustomerAccountBalance(IN ADOINT AccountID, IN ADOINT balance)
{
	if (balance < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"Balance\" = %d  \
										WHERE \"AccountID\" = %d;", \
										CUSTOMER_ACCOUNT_3A_TAB_CFG, \
										balance,AccountID);

	ADORES adores = ado.ExcuteSQL(szSql);
	return adores;
}

ADORES CAdo3A::Ado3AUpdateCustomerAccountOfferBalance( \
							IN ADOINT AccountID, \
							IN ADOINT offerbalance)
{
	if (offerbalance < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"OfferBalance\" = %d  \
										WHERE \"AccountID\" = %d;", \
										CUSTOMER_ACCOUNT_3A_TAB_CFG, \
										offerbalance,AccountID);

	ADORES adores = ado.ExcuteSQL(szSql);
	return adores;
}

ADORES CAdo3A::Ado3AUpdateCustomerAccountBalanceAndOfferBalance( \
						IN ADOINT AccountID,  \
						IN ADOINT balance,  \
						IN ADOINT offerbalance)
{
	if (offerbalance < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"UPDATE %s SET \"Balance\" = %d, \
										\"OfferBalance\" = %d \
										WHERE \"AccountID\" = %d ", \
										CUSTOMER_ACCOUNT_3A_TAB_CFG, \
										balance,offerbalance,AccountID);

	ADORES adores = ado.ExcuteSQL(szSql);
	return adores;
}


ADORES CAdo3A::Ado3AInsertServiceUseRecords(SERVICERECORDS &UseRecord)
{
	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"INSERT INTO %s ( \
		\"RecordsCode\", \
		\"CustomerID\",\"AccountID\", \
		\"ProductID\",\"ServiceID\", \
		\"UserId\",\"LoginIP\", \
		\"UseNum\",\"Cost\", \
		\"MedicalOrgId\", \"CostTime\", \
		\"AppliId\") OUTPUT INSERTED.RecordsID \
		VALUES (\
			'%s', \
			%d, %d, \
			%d, %d, \
			'%s', '%s', \
			'%d',  %d, \
			'%s', '%s',	\
			'%s');", \
		SERVICE_USER_RECORDS_3A_TAB_CFG, \
		UseRecord.szRecordCode, \
		UseRecord.nCustomerID, UseRecord.nAccountID, \
		UseRecord.nProductID, UseRecord.nServiceID, \
		UseRecord.szUserID, UseRecord.szLoginIP, \
		UseRecord.nUseNum, UseRecord.nCost, \
		UseRecord.szMedicalOrgId, UseRecord.szCostTime, \
		UseRecord.szApplyId);


	ADORES adores = ado.ExcuteSQL(szSql);
	if (ADO_SUCCESS != adores) return adores;

	UseRecord.nRecordID = ado.GetReturnID();

	return ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AQueryServiceUseLastRecordsID(OUT ADOUINT &nRecordsID)
{
	//select MAX(RecordsID) from ServiceUseRecords;//test_zxh;
	//Select IDENT_CURRENT('ServiceUseRecords') 
	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql, MAX_ADO_SQL_STR_LEN,"%s", "SELECT IDENT_CURRENT('ServiceUseRecords')");

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);
	if (NULL == sqlres) return ADO_EXCEPTION;

	nRecordsID = 0;

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		int num = sqlres->GetFields()->GetCount();		
		for (int i = 0; i < num; i++)
		{	
			switch(i)
			{
			case TABSERVICEUSERECORDS_ID:
				vVal = sqlres->GetCollect(_variant_t((long)i));
				szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
				nRecordsID = atoi(szVal.c_str());	
				break;
			}
		}
		
		bFound = true;
		sqlres->MoveNext();		
	}	
	sqlres->Close();
	return (!bFound) ? ADO_LOGINFAILED: ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AInsertBalanceDetails(BALANCEDETAILS &BalanceDetail)
{
	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"INSERT INTO %s ( \
				\"AccountID\", \"Balance\", \
				\"ChangeNum\",\"ChangeTime\", \
				\"Comment\", \"RechargeID\", \
				\"Operator\", \"ChangeType\", \
				\"RecordsID\", \"RechargeType\") OUTPUT INSERTED.BalanceDetailsID  \
				VALUES (\
				%d, %d, \
				%d, '%s',\
				'%s', %d,\
				'%s', %d,\
				%d, %d);", 
			BALANCE_DETAILS_3A_TAB_CFG, \
			BalanceDetail.nAccountID, \
			BalanceDetail.nBalance, BalanceDetail.nChangeNum, \
		    BalanceDetail.szChangeTime, BalanceDetail.szComment,\
			BalanceDetail.nReChargeID, \
			BalanceDetail.szOperator, BalanceDetail.nChangType, \
			BalanceDetail.nRecordsID, BalanceDetail.nRechargeType);

	ADORES adores = ado.ExcuteSQL(szSql);
	if (ADO_SUCCESS != adores) return adores;

	BalanceDetail.nBanlanceDetailsID = ado.GetReturnID();

	return adores;
}

ADORES CAdo3A::Ado3AQueryRechargeRecords(OUT RECHARGERECORDS **pp, OUT ADOINT &nNum, IN ADOINT nAccountID, bool bASC, ADOINT LimitNum)
{
	if (nAccountID < 0 || LimitNum < 0) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT TOP %d * FROM %s \
										WHERE  \"AccountID\" = %d \
										ORDER BY RechargeTime %s;", \
										LimitNum, \
										RECHARGE_RECORDS_3A_TAB_CFG, \
										nAccountID, \
										(bASC == true) ? "ASC" : "DESC");

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);
	if (NULL == sqlres) return ADO_EXCEPTION;


	_variant_t vVal;				
	std::string szVal;
	bool bFound = false;
	nNum = 0;

	long nRows = sqlres->GetRecordCount();
	// 如果ado不支持此属性，则手工计算记录数目 
	if (nRows < 0)
	{
		nRows = 0;
		//sqlres->MoveFirst();
		while(!sqlres->EndOfFile)
		{
			nRows++;
			sqlres->MoveNext();
		}	
	}

	if(nRows <= 0) return ADO_SUCCESS;

	sqlres->MoveFirst();

	int nLen = sizeof(RECHARGERECORDS);
	*pp = (RECHARGERECORDS *)new ADOCHAR[nRows * nLen];
	nNum = nRows;

	memset(*pp, 0 ,sizeof(nRows * nLen));

	RECHARGERECORDS *rechargerecords;
	rechargerecords = (RECHARGERECORDS *)(*pp);

	COleDateTime  odatetime;
	int nYear,nMon,nDay,nHour,nMin,nSec;
	ADOCHAR szTime[ADO_STRINF_LEN];

	while(!sqlres->EndOfFile)
	{			
		nYear = 0; nMon = 0; nDay = 0; nHour = 0; nMin = 0; nSec = 0;
		memset(szTime, 0 ,sizeof(szTime));

		memset(rechargerecords, 0, sizeof(RECHARGERECORDS));
	
		vVal = sqlres->GetCollect(_variant_t("RechargeID"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		rechargerecords->nRechargeID = atoi(szVal.c_str());		

		vVal = sqlres->GetCollect(_variant_t("RechargeCode"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(rechargerecords->szRechargeCode,sizeof(rechargerecords->szRechargeCode),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("AccountID"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		rechargerecords->nAccountID = atoi(szVal.c_str());		

		vVal = sqlres->GetCollect(_variant_t("RechargeNum"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		rechargerecords->nRechargeNum = atoi(szVal.c_str());		

		vVal = sqlres->GetCollect(_variant_t("RechargeTime"));							
		//szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		odatetime = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? 0 : vVal.date;			
		if (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt)
		{
			memset(szTime, 0, sizeof(szTime));
		}
		else
		{
			nYear = odatetime.GetYear();
			nMon = odatetime.GetMonth();
			nDay = odatetime.GetDay();
			nHour = odatetime.GetHour();
			nMin = odatetime.GetMinute();
			nSec = odatetime.GetSecond();
			sprintf_s(szTime, ADO_STRINF_LEN, "%04d-%02d-%02d %02d:%02d:%02d", nYear,nMon,nDay,nHour,nMin,nSec);
		}
		sprintf_s(rechargerecords->szRechargeTime,sizeof(rechargerecords->szRechargeTime),"%s",szTime);	


		vVal = sqlres->GetCollect(_variant_t("Status"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		rechargerecords->nStatus = atoi(szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Comment"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(rechargerecords->szComment,sizeof(rechargerecords->szComment),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("UserID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(rechargerecords->szUserID,sizeof(rechargerecords->szUserID),"%s",szVal.c_str());	


		vVal = sqlres->GetCollect(_variant_t("OperatorID"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		rechargerecords->nOperatorID = atoi(szVal.c_str());
	
		rechargerecords += 1;
		bFound = true;
		sqlres->MoveNext();	
	}

	sqlres->Close();
	rechargerecords = NULL;
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;
}

ADORES CAdo3A::Ado3AFreeMemoryQueryRechargeRecords(IN RECHARGERECORDS *&pp)
{
	if (NULL != pp)
	{
		delete[] pp;
		pp = NULL;
	}
	return ADO_SUCCESS;
}


ADORES CAdo3A::Ado3AInsertRechargeRecords(IN RECHARGERECORDS &rechargerecords)
{
	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"INSERT INTO %s ( \
				\"RechargeCode\", \
				\"AccountID\",\"RechargeNum\", \
				\"RechargeTime\", \"Status\", \
				\"Comment\", \"UserID\", \
				\"OperatorID\") OUTPUT INSERTED.RechargeID \
				VALUES (\
				'%s', \
				%d, %d, \
				'%s', %d, \
				'%s', '%s', \
				%d);", 
				RECHARGE_RECORDS_3A_TAB_CFG, \
				rechargerecords.szRechargeCode, rechargerecords.nAccountID, \
				rechargerecords.nRechargeNum, rechargerecords.szRechargeTime,\
				rechargerecords.nStatus, rechargerecords.szComment, \
				rechargerecords.szUserID,rechargerecords.nOperatorID);

	ADORES adores = ado.ExcuteSQL(szSql);
	if (ADO_SUCCESS != adores) return adores;

	rechargerecords.nRechargeID = ado.GetReturnID();
	return adores;
}

ADORES CAdo3A::Ado3AQueryService(SERVICE &service, const ADOCHAR *szServiceCode)
{
	if (NULL == szServiceCode) return ADO_PARAM_ERROR;

	char szSql[MAX_ADO_SQL_STR_LEN] = { 0 };

	sprintf_s(szSql,MAX_ADO_SQL_STR_LEN,"SELECT * FROM %s \
										WHERE  \"ServiceCode\" = '%s';", \
										SERVICE_3A_TAB_CFG,szServiceCode);

	EnterCriticalSection(&m_csMutex);
	_RecordsetPtr sqlres = ado.GetRecordSet(szSql);
	LeaveCriticalSection(&m_csMutex);

	if (NULL == sqlres) return ADO_EXCEPTION;

	_variant_t vVal;				
	std::string szVal;	
	bool bFound = false;
	while(!sqlres->EndOfFile)
	{
		memset(&service, 0 ,sizeof(service));
		vVal = sqlres->GetCollect(_variant_t("ServiceID"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		service.nServiceID = atoi(szVal.c_str());		

		vVal = sqlres->GetCollect(_variant_t("ServiceCode"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(service.szServiceCode,sizeof(service.szServiceCode),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("Name"));							
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		sprintf_s(service.szName,sizeof(service.szName),"%s",szVal.c_str());	

		vVal = sqlres->GetCollect(_variant_t("TypeID"));
		szVal = (VT_NULL == vVal.vt || VT_EMPTY == vVal.vt) ? "" : (ADOCHAR*)(_bstr_t)vVal;	
		service.nTypeID = atoi(szVal.c_str());	

		bFound = true;
		sqlres->MoveNext();					//move next row
	}	
	sqlres->Close();
	return (!bFound) ? ADO_EXCEPTION : ADO_SUCCESS;

}

ADORES CAdo3A::AdoClose()
{
	return ado.Close();
}










