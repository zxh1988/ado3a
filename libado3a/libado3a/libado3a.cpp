// libado3a.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Ado3A.h"




CAdo3A *g_pAdo3a = NULL;
ADORES g_Init = ADO_EXCEPTION;


ADORES AdoInitDb(IN const ADOCHAR *szDbServerIp,IN const ADOCHAR *szDbName,IN const ADOCHAR *szDbUser, IN const ADOCHAR *szDbPasswd)
{
	if (ADO_SUCCESS != g_Init)
	{
		 g_Init = g_pAdo3a->GetInstance()->AdoInitDb(szDbServerIp, szDbName, szDbUser, szDbPasswd);
		 return g_Init;
	}
	return ADO_SUCCESS;	
}

ADORES AdoBeginTransaction()
{
	return g_pAdo3a->GetInstance()->AdoBeginTransaction();
}

ADORES AdoCommitTransaction()
{
	return g_pAdo3a->GetInstance()->AdoCommitTransaction();
}

ADORES AdoRollBackTransaction()
{
	return g_pAdo3a->GetInstance()->AdoRollBackTransaction();
}


//Customer£º
ADORES Ado3AQueryCustomer(OUT CUSTOMER &customer, IN const ADOCHAR *username, IN const ADOCHAR *passwd)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryCustomer(customer,username,passwd);
}

ADORES Ado3AQueryUsers(OUT USERS &user, IN const ADOCHAR *username, IN const ADOCHAR *passwd)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryUsers(user, username, passwd);
}


ADORES Ado3AQueryCustomerProduct(OUT CUSTOMERPRODUCT &customerproduct, IN ADOINT nProductID)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryCustomerProduct(customerproduct,nProductID);
}


ADORES Ado3AUpdateCustomerProduct(IN ADOINT nProductID, IN ADOINT price)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerProduct(nProductID,price);
}

ADORES Ado3AUpdateCustomerProductIsCharge(IN ADOINT nProductID, IN ADOINT nIsCharge)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerProductIsCharge(nProductID, nIsCharge);
}



ADORES Ado3AQueryCustomerProductAndProductDetailsPoint(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN ADOINT AccountID, IN ADOINT ServiceID)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryCustomerProductAndProductDetailsPoint(pp,pNum,AccountID,ServiceID);
}

ADORES Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(OUT PRODUCTANDPRODUCTDETAILS *&pp)
{
	return g_pAdo3a->GetInstance()->Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(pp);
}

ADORES Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN const ADOCHAR *szBeginTime, IN const ADOCHAR *szEndTime)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(pp,pNum,szBeginTime,szEndTime);
}

ADORES Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(IN PRODUCTANDPRODUCTDETAILS *&pp)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(pp);
}




//CustomerProductDetails
ADORES Ado3AQueryCustomerProductDetails(OUT CUSTOMERPRODUCTDETAILS &productdetails, IN ADOINT nProductDetailsID)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryCustomerProductDetails(productdetails,nProductDetailsID);
}

ADORES Ado3AUpdateCustomerProductDetails(IN CUSTOMERPRODUCTDETAILS productdetails, IN ADOINT nProductDetailsID)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerProductDetails(productdetails,nProductDetailsID);
}



ADORES Ado3AUpdateCustomerProductDetailsRemainServiceNum(IN ADOINT nProductDetailsID, IN ADOINT nRemainServiceNum)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerProductDetailsRemainServiceNum(nProductDetailsID,nRemainServiceNum);
}


ADORES Ado3AUpdateCustomerProductDetailsPrice(IN ADOINT nProductDetailsID, IN ADOINT price)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerProductDetailsPrice(nProductDetailsID,price);
}


ADORES Ado3AUpdateCustomerProductDetailExceedPrice(IN ADOINT nProductDetailsID, IN ADOINT exceedprice)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerProductDetailExceedPrice(nProductDetailsID,exceedprice);
}


//Account_Hospital
ADORES Ado3AQueryAccountHospital(IN ACCOUNTHOSTPITAL &accounthospital, IN ADOINT nAccountHospitalID)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryAccountHospital(accounthospital,nAccountHospitalID);
}


ADORES Ado3AQueryAccountHospitalMedicalOrgId(IN ACCOUNTHOSTPITAL &accounthospital, IN const ADOCHAR *szMedicalOrgId)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryAccountHospitalMedicalOrgId(accounthospital,szMedicalOrgId);
}


//CustomerAccount
ADORES Ado3AQueryCustomerAccount(IN CUSTOMERACCOUNT &customeraccount, IN ADOINT AccountID)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryCustomerAccount(customeraccount,AccountID);
}


ADORES Ado3AUpdateCustomerAccountBalance(IN ADOINT AccountID, IN ADOINT balance)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerAccountBalance(AccountID,balance);
}


ADORES Ado3AUpdateCustomerAccountOfferBalance(IN ADOINT AccountID, IN ADOINT offerbalance)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerAccountOfferBalance(AccountID,offerbalance);
}


ADORES Ado3AUpdateCustomerAccountBalanceAndOfferBalance(IN ADOINT AccountID, IN ADOINT balance, IN ADOINT offerbalance)
{
	return g_pAdo3a->GetInstance()->Ado3AUpdateCustomerAccountBalanceAndOfferBalance(AccountID,balance,offerbalance);
}


//ServiceUseRecords
ADORES Ado3AInsertServiceUseRecords(SERVICERECORDS &UseRecord)
{
	return g_pAdo3a->GetInstance()->Ado3AInsertServiceUseRecords(UseRecord);
}

ADORES Ado3AQueryServiceUseLastRecordsID(OUT ADOUINT &nRecordsID)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryServiceUseLastRecordsID(nRecordsID);
}


//BalanceDetails
ADORES Ado3AInsertBalanceDetails(BALANCEDETAILS &BalanceDetail)
{
	return g_pAdo3a->GetInstance()->Ado3AInsertBalanceDetails(BalanceDetail);
}

ADORES Ado3AQueryRechargeRecords(OUT RECHARGERECORDS **pp, OUT ADOINT &pNum, IN ADOINT nAccountID, bool bASC, ADOINT LimitNum)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryRechargeRecords(pp,pNum,nAccountID,bASC,LimitNum);
}

ADORES Ado3AFreeMemoryQueryRechargeRecords(IN RECHARGERECORDS *&pp)
{
	return g_pAdo3a->GetInstance()->Ado3AFreeMemoryQueryRechargeRecords(pp);
}



ADORES Ado3AInsertRechargeRecords(IN RECHARGERECORDS &rechargerecords)
{
	return g_pAdo3a->GetInstance()->Ado3AInsertRechargeRecords(rechargerecords);
}


ADORES Ado3AQueryService(OUT SERVICE &service, IN const ADOCHAR *szServiceCode)
{
	return g_pAdo3a->GetInstance()->Ado3AQueryService(service, szServiceCode);
}


ADORES AdoClose()
{
	// ADORES adores = g_pAdo3a->GetInstance()->AdoClose();
	 delete g_pAdo3a->GetInstance();
	 return ADO_SUCCESS;
}



