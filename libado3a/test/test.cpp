// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "adointerface.h"
#include <windows.h>  
#include <process.h>  
#include <iostream>

#include <vld.h>



//#define CRTDBG_MAP_ALLOC    
//#include <stdlib.h>    
//#include <crtdbg.h>    
//在入口函数中包含 _CrtDumpMemoryLeaks();    
//即可检测到内存泄露  

//定义函数：  
//inline void EnableMemLeakCheck()  
//{  
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  
//}  
//该函数可以放在主函数的任意位置，都能正确的触发内存泄露输出  


void test()
{

	CUSTOMER customer = { 0 };
	//char *username = "admin";
	//char *passwd = "21232f297a57a5a743894a0e4a801fc3";
	char *username = "lbtest";
	char *passwd = "ea18a54be8053ffdf547236c3d6dbec6";
	ADORES adores = Ado3AQueryCustomer(customer, username, passwd);

	USERS user = { 0 };
	adores = Ado3AQueryUsers(user, username, passwd);


	CUSTOMERPRODUCT customerproduct = { 0 };
	int nProductID = 40;
	adores = Ado3AQueryCustomerProduct(customerproduct,nProductID);


	char *productID = "abc";
	adores = Ado3AUpdateCustomerProduct(nProductID,44);

	ADOUINT nIscharge = 1;
	adores = Ado3AUpdateCustomerProductIsCharge(nProductID, nIscharge);

	//PRODUCTANDPRODUCTDETAILSVEC vec;
	//pPRODUCTANDPRODUCTDETAILSVEC vec;
	//vec.clear();
	int nAccountID = 1;
	int nServiceID = 2;
	//adores = Ado3AQueryCustomerProductAndProductDetails(vec,nAccountID,nServiceID);


	PRODUCTANDPRODUCTDETAILS *p = NULL;
	//ADOCHAR **p = NULL;
	ADOUINT nCnt = 0;
	adores = Ado3AQueryCustomerProductAndProductDetailsPoint(&p, nCnt, nAccountID, nServiceID);
	PRODUCTANDPRODUCTDETAILS *pd = p;
	for (int i = 0; i < nCnt; i++)
	{	
		int nProductID = pd->nProductID;
		char szproductCode[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szproductCode),"%s",pd->szproductCode);

		char szProductName[ADO_STRINF_LEN];
		sprintf_s(szProductName,sizeof(pd->szProductName),"%s",pd->szProductName);

		int nChargeMode = pd->nChargeMode;
		int nCustomerID = pd->nCustomerID;
		int nPrice = pd->nPrice;
		int nDeposit = pd->nDeposit;
		int nOrderID = pd->nOrderID;

		char szOrderTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szOrderTime),"%s",pd->szOrderTime);

		char EffectTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->EffectTime),"%s",pd->EffectTime);

		char ExpTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->ExpTime),"%s",pd->ExpTime);

		int nAccountID = pd->nAccountID;


		int nProductDetailsID = pd->nProductDetailsID;

		char szProductDetailsCode[ADO_STRINF_LEN];
		sprintf_s(szProductDetailsCode,sizeof(pd->szProductDetailsCode),"%s",pd->szProductDetailsCode);

		int nExceedPrice = pd->nExceedPrice;

		char szChargeTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szChargeTime),"%s",pd->szChargeTime);

		char szNextChargeTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szNextChargeTime),"%s",pd->szNextChargeTime);

		pd += 1;
	}

	adores = Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(p);



	nCnt = 0;
	char * chBegin = "2006-12-12 16:57:00";
	char * chEnd = "2026-12-12 17:57:00";
	//adores = Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(&p,nCnt,"2016/12/12 16:40:50","2016/12/13 16:40:50");
	adores = Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(&p,nCnt,chBegin,chEnd);
	adores = Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(p);



	CUSTOMERPRODUCTDETAILS productdetails = { 0 };
	int nProductDetailsID = 3;

	adores = AdoBeginTransaction();

	ADORES adores1 = Ado3AQueryCustomerProductDetails(productdetails, nProductDetailsID);
	nProductDetailsID = 1;
	productdetails.nPrice = 1234;
	productdetails.nFreeServiceNum = 333;
	productdetails.nExceedPrice = 5433;
	productdetails.nRemainServiceNum = 77;
	ADORES adores2 = Ado3AUpdateCustomerProductDetails(productdetails,nProductDetailsID);

	BALANCEDETAILS BalanceDetailbbb = { 0 };
	BalanceDetailbbb.nAccountID = 567;
	BalanceDetailbbb.nBalance = 124;
	BalanceDetailbbb.nChangeNum = 98;
	BalanceDetailbbb.nReChargeID = 789;
	BalanceDetailbbb.nRecordsID = 1;
	sprintf_s(BalanceDetailbbb.szOperator,sizeof(BalanceDetailbbb.szOperator),"%s","李四");

	ADORES adores3 = Ado3AInsertBalanceDetails(BalanceDetailbbb);

	if (ADO_SUCCESS == adores1 && ADO_SUCCESS == adores2 && ADO_SUCCESS == adores3)
	{
		adores = AdoCommitTransaction();
	}
	else
	{
		adores = AdoRollBackTransaction();
	}

	nProductDetailsID = 3;
	adores = Ado3AUpdateCustomerProductDetailsRemainServiceNum(nProductDetailsID, 120);
	adores = Ado3AUpdateCustomerProductDetailsPrice(nProductDetailsID, 23);
	adores = Ado3AUpdateCustomerProductDetailExceedPrice(nProductDetailsID, 112);


	ACCOUNTHOSTPITAL accounthospital = { 0 };
	adores = Ado3AQueryAccountHospital(accounthospital, 14);
	ADOCHAR *szMedicalOrgId = "100";
	Ado3AQueryAccountHospitalMedicalOrgId(accounthospital, szMedicalOrgId);

	CUSTOMERACCOUNT customeraccount = { 0 };
	ADOINT AccountID = 1;
	adores = Ado3AQueryCustomerAccount(customeraccount, AccountID);
	ADOINT balance = 66;
	ADOINT offerbalance = 88;
	adores = Ado3AUpdateCustomerAccountBalance(AccountID, balance);
	adores = Ado3AUpdateCustomerAccountOfferBalance(AccountID, offerbalance);

	balance = 120;
	offerbalance = 220;
	adores = Ado3AUpdateCustomerAccountBalanceAndOfferBalance(AccountID, balance, offerbalance);


	SERVICERECORDS UseRecord = {0};
	sprintf_s(UseRecord.szRecordCode,sizeof(UseRecord.szRecordCode),"%s","3xxx");
	//UseRecord.nCustomerID = 1;
	//UseRecord.nAccountID = 1;
	//UseRecord.nProductID = 1;
	//UseRecord.nServiceID = 1;

	UseRecord.nCustomerID = 1;
	UseRecord.nAccountID = 1;
	UseRecord.nProductID = 11;
	UseRecord.nServiceID = 2;
	UseRecord.nCost = 435;
	UseRecord.nUseNum = 99;
	sprintf_s(UseRecord.szApplyId,sizeof(UseRecord.szApplyId),"%s","sb");

	adores = Ado3AInsertServiceUseRecords(UseRecord);

	ADOUINT nRecordsID = 0;
	adores = Ado3AQueryServiceUseLastRecordsID(nRecordsID);


	BALANCEDETAILS BalanceDetail = { 0 };
	BalanceDetail.nAccountID = 1;
	BalanceDetail.nBalance = 124;
	BalanceDetail.nChangeNum = 98;
	BalanceDetail.nReChargeID = 1;
	sprintf_s(BalanceDetail.szOperator,sizeof(BalanceDetail.szOperator),"%s","李四");
	BalanceDetail.nRechargeType = 0;
	BalanceDetail.nRecordsID = 1;


	adores = Ado3AInsertBalanceDetails(BalanceDetail);



	RECHARGERECORDS *ppp = NULL;
	int nNum = 0;
	bool bAsc = true;
	int nLimitNum = 10;
	adores = Ado3AQueryRechargeRecords(&ppp,nNum,AccountID,bAsc,nLimitNum);
	for(int i = 0; i < nNum; i++)
	{
		RECHARGERECORDS *p = ppp;
		int nRechargeID = p->nRechargeID;
		char szRechargeCode[ADO_STRINF_LEN];
		nAccountID = p->nAccountID;
		sprintf_s(szRechargeCode,sizeof(szRechargeCode),"%s",p->szRechargeCode);
	}

	adores = Ado3AFreeMemoryQueryRechargeRecords(ppp);



	RECHARGERECORDS rechargerecords = { 0 };
	sprintf_s(rechargerecords.szRechargeCode,sizeof(rechargerecords.szRechargeCode),"%s","asdd");
	rechargerecords.nAccountID = 1;
	rechargerecords.nRechargeNum = 555;
	sprintf_s(rechargerecords.szRechargeTime,sizeof(rechargerecords.szRechargeTime),"%s","2017-1-26 12:22:24");
	rechargerecords.nStatus = 0;
	sprintf_s(rechargerecords.szComment,sizeof(rechargerecords.szComment),"%s","ffff");
	sprintf_s(rechargerecords.szUserID,sizeof(rechargerecords.szUserID),"%s","zxh");
	rechargerecords.nOperatorID = 1111;

	adores = Ado3AInsertRechargeRecords(rechargerecords);

	SERVICE service = { 0 };
	ADOCHAR *szServiceCode = "HOLTERVIEW1111";


	adores = Ado3AQueryService(service, szServiceCode);
}

static unsigned int WINAPI MemoryLeaksTest(void *arg)
{
	while(1)
	{	
		test();
		Sleep(100);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*char *szDbServerIp = "127.0.0.1";
	char *szDbBase = "EIS";
	char *szDbUser = "sa";
	char *szDbPasswd = "123456";*/

//	EnableMemLeakCheck();  


	char *szDbServerIp = "183.62.224.114";
	//char *szDbServerIp = "192.168.24.33";
	char *szDbBase = "ECGNet";
	char *szDbUser = "sa";
	char *szDbPasswd = "edan@123456";

	
	//char *pTest = new char[1000]; 
	
	ADORES adores = AdoInitDb(szDbServerIp,szDbBase,szDbUser,szDbPasswd);
	//adores = AdoInitDb(szDbServerIp,szDbBase,szDbUser,szDbPasswd);
	if (ADO_SUCCESS != adores)
	{
		getchar();
		return 0;
	}
	//_CrtDumpMemoryLeaks();  


	//unsigned int nThreadID;
	////线程创建
	//HANDLE m_hThreads = (HANDLE)_beginthreadex(NULL, 0, &MemoryLeaksTest, NULL, 0, &nThreadID);

	//while(1)
	//{
	//	Sleep(1000*5);
	//}

///*	
	CUSTOMER customer = { 0 };
	//char *username = "admin";
	//char *passwd = "21232f297a57a5a743894a0e4a801fc3";
	//char *username = "采集医生";
	char *username = "test客户测试";
	char *passwd = "e10adc3949ba59abbe56e057f20f883e";
	//char *passwd = "550a141f12de6341fba65b0ad0433500";
	adores = Ado3AQueryCustomer(customer, username, passwd);

	

	USERS user = { 0 };
	Ado3AQueryUsers(user, username, passwd);
	

	CUSTOMERPRODUCT customerproduct = { 0 };
	int nProductID = 1;
	adores = Ado3AQueryCustomerProduct(customerproduct,nProductID);
	  

	char *productID = "abc";
	adores = Ado3AUpdateCustomerProduct(nProductID,44);

	ADOUINT nIscharge = 1;
	adores = Ado3AUpdateCustomerProductIsCharge(nProductID, nIscharge);

	//PRODUCTANDPRODUCTDETAILSVEC vec;
	//pPRODUCTANDPRODUCTDETAILSVEC vec;
	//vec.clear();
	int nAccountID = 1;
	int nServiceID = 2;
	//adores = Ado3AQueryCustomerProductAndProductDetails(vec,nAccountID,nServiceID);


	PRODUCTANDPRODUCTDETAILS *p = NULL;
	//ADOCHAR **p = NULL;
	ADOUINT nCnt = 0;
	adores = Ado3AQueryCustomerProductAndProductDetailsPoint(&p, nCnt, nAccountID, nServiceID);
	PRODUCTANDPRODUCTDETAILS *pd = p;
	for (int i = 0; i < nCnt; i++)
	{	
		int nProductID = pd->nProductID;
		char szproductCode[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szproductCode),"%s",pd->szproductCode);

		char szProductName[ADO_STRINF_LEN];
		sprintf_s(szProductName,sizeof(pd->szProductName),"%s",pd->szProductName);

		int nChargeMode = pd->nChargeMode;
		int nCustomerID = pd->nCustomerID;
		int nPrice = pd->nPrice;
		int nDeposit = pd->nDeposit;
		int nOrderID = pd->nOrderID;
		
		char szOrderTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szOrderTime),"%s",pd->szOrderTime);

		char EffectTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->EffectTime),"%s",pd->EffectTime);

		char ExpTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->ExpTime),"%s",pd->ExpTime);

		int nAccountID = pd->nAccountID;


		int nProductDetailsID = pd->nProductDetailsID;

		char szProductDetailsCode[ADO_STRINF_LEN];
		sprintf_s(szProductDetailsCode,sizeof(pd->szProductDetailsCode),"%s",pd->szProductDetailsCode);

		int nExceedPrice = pd->nExceedPrice;
		
		char szChargeTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szChargeTime),"%s",pd->szChargeTime);

		char szNextChargeTime[ADO_STRINF_LEN];
		sprintf_s(szproductCode,sizeof(pd->szNextChargeTime),"%s",pd->szNextChargeTime);
		
		pd += 1;
	}

	adores = Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(p);
	


	nCnt = 0;
	char * chBegin = "2006-12-12 16:57:00";
	char * chEnd = "2016-12-12 17:57:00";
	//adores = Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(&p,nCnt,"2016/12/12 16:40:50","2016/12/13 16:40:50");
	adores = Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(&p,nCnt,chBegin,chEnd);
	adores = Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(p);

	

	CUSTOMERPRODUCTDETAILS productdetails = { 0 };
	int nProductDetailsID = 3;
	
	adores = AdoBeginTransaction();

	ADORES adores1 = Ado3AQueryCustomerProductDetails(productdetails, nProductDetailsID);
	nProductDetailsID = 1;
	productdetails.nPrice = 1234;
	productdetails.nFreeServiceNum = 333;
	productdetails.nExceedPrice = 5433;
	productdetails.nRemainServiceNum = 77;
	ADORES adores2 = Ado3AUpdateCustomerProductDetails(productdetails,nProductDetailsID);

	BALANCEDETAILS BalanceDetailbbb = { 0 };
	BalanceDetailbbb.nAccountID = 567;
	BalanceDetailbbb.nBalance = 124;
	BalanceDetailbbb.nChangeNum = 98;
	BalanceDetailbbb.nReChargeID = 789;
	BalanceDetailbbb.nRecordsID = 1;
	sprintf_s(BalanceDetailbbb.szOperator,sizeof(BalanceDetailbbb.szOperator),"%s","李四");

	ADORES adores3 = Ado3AInsertBalanceDetails(BalanceDetailbbb);

	if (ADO_SUCCESS == adores1 && ADO_SUCCESS == adores2 && ADO_SUCCESS == adores3)
	{
		adores = AdoCommitTransaction();
	}
	else
	{
		adores = AdoRollBackTransaction();
	}
	
	nProductDetailsID = 3;
	adores = Ado3AUpdateCustomerProductDetailsRemainServiceNum(nProductDetailsID, 120);
	adores = Ado3AUpdateCustomerProductDetailsPrice(nProductDetailsID, 23);
	adores = Ado3AUpdateCustomerProductDetailExceedPrice(nProductDetailsID, 112);


	ACCOUNTHOSTPITAL accounthospital = { 0 };
	adores = Ado3AQueryAccountHospital(accounthospital, 14);
	ADOCHAR *szMedicalOrgId = "100";
	Ado3AQueryAccountHospitalMedicalOrgId(accounthospital, szMedicalOrgId);

	CUSTOMERACCOUNT customeraccount = { 0 };
	ADOINT AccountID = 1;
	adores = Ado3AQueryCustomerAccount(customeraccount, AccountID);
	ADOINT balance = 66;
	ADOINT offerbalance = 88;
	adores = Ado3AUpdateCustomerAccountBalance(AccountID, balance);
	adores = Ado3AUpdateCustomerAccountOfferBalance(AccountID, offerbalance);
	
	balance = 120;
	offerbalance = 220;
	adores = Ado3AUpdateCustomerAccountBalanceAndOfferBalance(AccountID, balance, offerbalance);


	SERVICERECORDS UseRecord = {0};
	sprintf_s(UseRecord.szRecordCode,sizeof(UseRecord.szRecordCode),"%s","3xxx");
	//UseRecord.nCustomerID = 1;
	//UseRecord.nAccountID = 1;
	//UseRecord.nProductID = 1;
	//UseRecord.nServiceID = 1;

	UseRecord.nCustomerID = 1;
	UseRecord.nAccountID = 1;
	UseRecord.nProductID = 11;
	UseRecord.nServiceID = 2;
	UseRecord.nCost = 55555;
	UseRecord.nUseNum = 99;
	sprintf_s(UseRecord.szApplyId,sizeof(UseRecord.szApplyId),"%s","sb");

	adores = Ado3AInsertServiceUseRecords(UseRecord);


	ADOUINT nRecordsID = 0;
	adores = Ado3AQueryServiceUseLastRecordsID(nRecordsID);



	BALANCEDETAILS BalanceDetail = { 0 };
	BalanceDetail.nAccountID = 1;
	BalanceDetail.nBalance = 124;
	BalanceDetail.nChangeNum = 98;
	BalanceDetail.nReChargeID = 1;
	sprintf_s(BalanceDetail.szOperator,sizeof(BalanceDetail.szOperator),"%s","李四");
	BalanceDetail.nRechargeType = 0;
	BalanceDetail.nRecordsID = 1;
	
	
	adores = Ado3AInsertBalanceDetails(BalanceDetail);


	
	RECHARGERECORDS *ppp = NULL;
	int nNum = 0;
	bool bAsc = true;
	int nLimitNum = 10;
	adores = Ado3AQueryRechargeRecords(&ppp,nNum,AccountID,bAsc,nLimitNum);
	for(int i = 0; i < nNum; i++)
	{
		RECHARGERECORDS *p = ppp;
		int nRechargeID = p->nRechargeID;
		char szRechargeCode[ADO_STRINF_LEN];
		nAccountID = p->nAccountID;
		sprintf_s(szRechargeCode,sizeof(szRechargeCode),"%s",p->szRechargeCode);
	}

	adores = Ado3AFreeMemoryQueryRechargeRecords(ppp);
	
	

	RECHARGERECORDS rechargerecords = { 0 };
	sprintf_s(rechargerecords.szRechargeCode,sizeof(rechargerecords.szRechargeCode),"%s","asdd");
	rechargerecords.nAccountID = 1;
	rechargerecords.nRechargeNum = 555;
	sprintf_s(rechargerecords.szRechargeTime,sizeof(rechargerecords.szRechargeTime),"%s","2017-1-26 12:22:24");
	rechargerecords.nStatus = 0;
	sprintf_s(rechargerecords.szComment,sizeof(rechargerecords.szComment),"%s","ffff");
	sprintf_s(rechargerecords.szUserID,sizeof(rechargerecords.szUserID),"%s","zxh");
	rechargerecords.nOperatorID = 1111;

	adores = Ado3AInsertRechargeRecords(rechargerecords);

	SERVICE service = { 0 };
	ADOCHAR *szServiceCode = "HOLTERVIEW1111";
	

	adores = Ado3AQueryService(service, szServiceCode);


	//*/

	adores = AdoClose();
	 _CrtDumpMemoryLeaks();  

	getchar();

	return 0;
}

