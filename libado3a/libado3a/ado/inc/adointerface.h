//////////////////////////////////////////////////////////////////////////
/// @par edan co. All Rights Reserved, Copyright (C) 2016-2020.
/// @brief   [ado sql interface]
///
/// @file    adointerface.h
/// @author  zhangxianhui
/// @date    2016-12-9
/// @version V1.0
/// @note author date modify
/// @note zhangxianhui 2016-12-9 create
/// @note zhangxianhui 2016-12-14 modify
//////////////////////////////////////////////////////////////////////////


#ifndef ADO3AINTERFACE_H
#define ADO3AINTERFACE_H
#include <iostream>
//#include <vector>



#ifdef LIBADOEXPORT                                                 
#define ADOEXPORT extern "C" __declspec(dllexport)
#else
#define ADOEXPORT extern "C" __declspec(dllimport)
#endif


#define INOUT                    
#define IN                       
#define OUT    


//sql max length
#define MAX_ADO_SQL_STR_LEN					20480
//sql timeout ms
#define MAX_ADO_WAIT_TIME_OUT				10000
//string length
#define ADO_STRINF_LEN						128
//string max length
#define MAX_ADO_STRINF_LEN					256
//text max length
#define MAX_ADO_TEXT_LEN					512
//content max length
#define MAX_ADO_CONTENT_LEN					1024
//path max length
#define MAX_ADO_PATH_LEN					512


typedef bool ADOBOOL;
typedef unsigned char ADOBYTE;
typedef unsigned int ADOUINT;
typedef int  ADOINT;
typedef char  ADOCHAR;
typedef float  ADOFLOAT;
typedef double   ADODOUBLE;
typedef unsigned short ADOWORD;
typedef unsigned int ADOUINT;



typedef enum ADORES
{
	ADO_SUCCESS,				//operation success	
	ADO_EXCEPTION,				//operation exception
	ADO_FAIL,					//fail		
	//ADO_NOT_FOUND,			//not find	
	ADO_PARAM_ERROR,            //param error
	ADO_NOT_CONNECT,            //not connect
	ADO_KEYEXISIT,              //key exist
	ADO_NOPRIVALEGE,            //no access
	ADO_USEREXISIT,             //user exist
	ADO_LOGINFAILED             //user login fail

};


#pragma pack(push,1)

//customer
typedef struct tag_CUSTOMER
{
	ADOINT nCustomerID;
	ADOCHAR szLoginName[ADO_STRINF_LEN];
	ADOCHAR szCustomerCode[ADO_STRINF_LEN];
	ADOCHAR szPassWd[ADO_STRINF_LEN];
	ADOCHAR szCorporation[ADO_STRINF_LEN];
	ADOCHAR szCorporationIDCard[ADO_STRINF_LEN];
	ADOCHAR szCompany[ADO_STRINF_LEN];
	ADOCHAR szEmail[ADO_STRINF_LEN];
	ADOCHAR szAddr[ADO_STRINF_LEN];
	ADOINT nAgentID;
	ADOCHAR szDescription[ADO_STRINF_LEN];
	ADOCHAR szOperator[ADO_STRINF_LEN];
	ADOCHAR szQQNum[ADO_STRINF_LEN];	
	ADOCHAR szOperatorMobile[ADO_STRINF_LEN];
	ADOCHAR szOperatorTelPhone[ADO_STRINF_LEN];
	ADOCHAR szOperatorFaxNum[ADO_STRINF_LEN];
	ADOINT nCustomerTypeID;
	ADOINT nCustomerAreaID;	
	ADOCHAR szCreateTime[ADO_STRINF_LEN];
	ADOCHAR szUpdateTime[ADO_STRINF_LEN];
	
}CUSTOMER, *pCUSTOMER;

typedef struct tag_USERS
{
	ADOCHAR szUserId[ADO_STRINF_LEN];
	ADOCHAR szUserName[ADO_STRINF_LEN];
	ADOCHAR szRealName[ADO_STRINF_LEN];
	ADOCHAR szPasswd[ADO_STRINF_LEN];
	ADOCHAR szPosition[ADO_STRINF_LEN];
	ADOCHAR szQualification[ADO_STRINF_LEN];
	ADOCHAR szCall[ADO_STRINF_LEN];
	ADOCHAR szMedicalOrgId[ADO_STRINF_LEN];
	ADOCHAR szDepartmentId[ADO_STRINF_LEN];
	ADOCHAR szHandPhone[ADO_STRINF_LEN];
	ADOCHAR szEmail[ADO_STRINF_LEN];
	ADOBYTE nIsValid;
	ADOCHAR szSignImg[ADO_STRINF_LEN];
	ADOCHAR szUserImg[ADO_STRINF_LEN];
	ADOCHAR szUserIntroduction[ADO_STRINF_LEN];

}USERS, *pUSERS;


//CustomerProduct
typedef struct tag_CUSTOMERPRODUCT
{
	ADOINT nProductID;
	ADOCHAR szproductCode[ADO_STRINF_LEN];
	ADOCHAR szProductName[ADO_STRINF_LEN];
	ADOINT nChargeMode;
	ADOINT nCustomerID;
	ADOINT nPrice;
	ADOINT nDeposit;
	ADOINT nOrderID;	
	ADOCHAR szOrderTime[ADO_STRINF_LEN];
	ADOCHAR EffectTime[ADO_STRINF_LEN];
	ADOCHAR ExpTime[ADO_STRINF_LEN];
	ADOINT nAccountID;
	ADOINT nIsValid;
	ADOCHAR szUpdateTime[ADO_STRINF_LEN];
	ADOINT nIsCharge;
	
}CUSTOMERPRODUCT, *pCUSTOMERPRODUCT;

//CustomerProductDetails
typedef struct tag_CUSTOMERPRODUCTDETAILS
{
	ADOINT nProductDetailsID;
	ADOCHAR szProductDetailsCode[ADO_STRINF_LEN];
	ADOINT nProductID;
	ADOINT nServiceID;
	ADOINT nChargeType;
	ADOINT nPrice;
	ADOINT nFreeServiceNum;
	ADOINT nExceedPrice;
	ADOINT nSaleDeviceTypeID;
	ADOINT nSaleDeviceNum;
	ADOCHAR szChargeTime[ADO_STRINF_LEN];
	ADOCHAR szNextChargeTime[ADO_STRINF_LEN];
	ADOINT nRemainServiceNum;
	ADOINT nChageNum;

}CUSTOMERPRODUCTDETAILS, *pCUSTOMERPRODUCTDETAILS;


typedef struct tag_PRODUCTANDPRODUCTDETAILS
{
	ADOINT nProductID;
	ADOCHAR szproductCode[ADO_STRINF_LEN];
	ADOCHAR szProductName[ADO_STRINF_LEN];
	ADOINT nChargeMode;
	ADOINT nCustomerID;
	ADOINT nPrice;
	ADOINT nDeposit;
	ADOINT nOrderID;	
	ADOCHAR szOrderTime[ADO_STRINF_LEN];
	ADOCHAR EffectTime[ADO_STRINF_LEN];
	ADOCHAR ExpTime[ADO_STRINF_LEN];
	ADOINT nAccountID;
	ADOINT nIsValid;
	ADOCHAR szUpdateTime[ADO_STRINF_LEN];
	ADOINT nIsCharge;

	ADOINT nProductDetailsID;
	ADOCHAR szProductDetailsCode[ADO_STRINF_LEN];
	ADOINT nProductDetailsProductID;
	ADOINT nServiceID;
	ADOINT nChargeType;
	ADOINT nProductDetailsPrice;
	ADOINT nFreeServiceNum;
	ADOINT nExceedPrice;
	ADOINT nSaleDeviceTypeID;
	ADOINT nSaleDeviceNum;
	ADOCHAR szChargeTime[ADO_STRINF_LEN];
	ADOCHAR szNextChargeTime[ADO_STRINF_LEN];
	ADOINT nRemainServiceNum;
	ADOINT nChageNum;

}PRODUCTANDPRODUCTDETAILS, *pPRODUCTANDPRODUCTDETAILS;
//typedef std::vector<PRODUCTANDPRODUCTDETAILS> PRODUCTANDPRODUCTDETAILSVEC;
//typedef std::vector<PRODUCTANDPRODUCTDETAILS*> pPRODUCTANDPRODUCTDETAILSVEC;


//Account_Hospital
typedef struct tag_ACCOUNTHOSTPITAL
{
	ADOINT nAccountHospitalID;
	ADOINT nAccountID;
	ADOCHAR szMedicalOrgId[MAX_ADO_STRINF_LEN];

}ACCOUNTHOSTPITAL, *pACCOUNTHOSTPITAL;

//CustomerAccount
typedef struct tag_CUSTOMERACCOUNT
{
	ADOINT nAccountID;
	ADOCHAR szAccountCode[ADO_STRINF_LEN];
	ADOINT nBalance;
	ADOINT nOfferBalance;
	ADOINT nCustomerID;
	ADOCHAR szTransactionPasswd[ADO_STRINF_LEN];
	ADOINT nDeposit;
	ADOCHAR szCreateTime[ADO_STRINF_LEN];

}CUSTOMERACCOUNT, *pCUSTOMERACCOUNT;


//ServiceUseRecords
typedef struct tag_SERVICERECORDS
{
	ADOINT nRecordID;
	ADOCHAR szRecordCode[ADO_STRINF_LEN];
	ADOINT nCustomerID;
	ADOINT nAccountID;
	ADOINT nProductID;
	ADOINT nServiceID;
	ADOCHAR szUserID[ADO_STRINF_LEN];
	ADOCHAR szLoginIP[ADO_STRINF_LEN];
	ADOINT nUseNum;
	ADOINT nCost;
	ADOCHAR szMedicalOrgId[ADO_STRINF_LEN];	
	ADOCHAR szCostTime[ADO_STRINF_LEN];
	ADOCHAR szApplyId[ADO_STRINF_LEN];

}SERVICERECORDS, *pSERVICERECORDS;

//BalanceDetails
typedef struct tag_BALANCEDETAILS
{
	ADOINT nBanlanceDetailsID;
	ADOINT nAccountID;
	ADOINT nBalance;
	ADOINT nChangeNum;
	ADOCHAR szChangeTime[ADO_STRINF_LEN];
	ADOCHAR szComment[MAX_ADO_TEXT_LEN];
	ADOINT nReChargeID;
	ADOCHAR szOperator[ADO_STRINF_LEN];
	ADOINT nChangType;
	ADOINT nRecordsID;
	ADOINT nRechargeType;

}BALANCEDETAILS, *pBALANCEDETAILS;


typedef struct tag_RECHARGERECORDS
{
	ADOINT nRechargeID;
	ADOCHAR szRechargeCode[ADO_STRINF_LEN];
	ADOINT nAccountID;
	ADOINT nRechargeNum;
	ADOCHAR szRechargeTime[ADO_STRINF_LEN];
	ADOINT nStatus;
	ADOCHAR szComment[MAX_ADO_TEXT_LEN];
	ADOCHAR szUserID[ADO_STRINF_LEN];
	ADOINT nOperatorID;

}RECHARGERECORDS, *pRECHARGERECORDS;


typedef struct tag_SERVICE
{
	ADOINT nServiceID;
	ADOCHAR szServiceCode[ADO_STRINF_LEN];
	ADOCHAR szName[ADO_STRINF_LEN];
	ADOINT nTypeID;

}SERVICE, *pSERVICE;


#pragma pack(pop,1)




//////////////////////////////////////////////////////////////////////////
/// @function	[AdoInitDb]
/// @brief		[��ʼ�����ݿ�]
///
/// @param [in] szDbServerIp [���ݿ�IP��ַ]
/// @param [in] szDbName     [���ݿ�����]
/// @param [in] szDbUser     [���ݿ��¼�û���]
/// @param [in] szDbPasswd   [���ݿ��¼����]
/// @return					 [ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoInitDb(IN const ADOCHAR *szDbServerIp,IN const ADOCHAR *szDbName,IN const ADOCHAR *szDbUser, IN const ADOCHAR *szDbPasswd);



//////////////////////////////////////////////////////////////////////////
/// @function		[AdoBeginTransaction]
/// @brief			[��ʼ����]
///
/// @return			[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoBeginTransaction();



//////////////////////////////////////////////////////////////////////////
/// @function		[AdoCommitTransaction]
/// @brief			[�ύ����]
///
/// @return			[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoCommitTransaction();



//////////////////////////////////////////////////////////////////////////
/// @function		[AdoRollBackTransaction]
/// @brief			[�ع�����]
///
/// @return			[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoRollBackTransaction();


//Customer��
//////////////////////////////////////////////////////////////////////////
/// @function		[Ado3AQueryCustomer]
/// @brief			[��ѯ�û���������]
///
/// @param [in] username    [�û���]
/// @param [in] passwd      [����]
/// @param [OUT] customer   [�ͻ��ṹ��]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomer(OUT CUSTOMER &customer, IN const ADOCHAR *username, IN const ADOCHAR *passwd);



//Users
//////////////////////////////////////////////////////////////////////////
/// @function		[Ado3AQueryUsers]
/// @brief			[��ѯ�û���������]
///
/// @param [in] username [�û���]
/// @param [in] passwd   [����]
/// @param [OUT] user    [�ṹ��]
/// @return			     [ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryUsers(OUT USERS &user, IN const ADOCHAR *username, IN const ADOCHAR *passwd);


//CustomerProduct
//////////////////////////////////////////////////////////////////////////
/// @function		[Ado3AQueryCustomerProduct]
/// @brief			[��ѯ�ͻ���Ʒ]
///
/// @param [in] nProductID			[��ƷID]
/// @param [OUT] customerproduct    [�ͻ���Ʒ]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProduct(OUT CUSTOMERPRODUCT &customerproduct, IN ADOINT nProductID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AUpdateCustomerProduct]
/// @brief		[�޸Ĳ�Ʒ�۸�]
///
/// @param [in] nProductID	[��ƷID]
/// @param [in] price		[�۸�]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProduct(IN ADOINT nProductID, IN ADOINT price);


//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AUpdateCustomerProduct]
/// @brief		[�޸��Ƿ��Ѿ��۷�]
///
/// @param [in] nProductID	[��ƷID]
/// @param [in] nIsCharge	[�Ƿ��Ѿ��۷�]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductIsCharge(IN ADOINT nProductID, IN ADOINT nIsCharge);


//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerProductAndProductDetailsPoint]
/// @brief		[��ʱ���ѯ����ģʽ��¼��]
///
/// @param [in] AccountID	[�ʻ�ID]
/// @param [in] ServiceID   [����ID]
/// @param [OUT] pp         [��Ʒ�Ͳ�Ʒ��ϸ�ṹ��ָ��]
/// @param [OUT] pNum       [�ṹ��ĸ���]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProductAndProductDetailsPoint(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN ADOINT AccountID, IN ADOINT ServiceID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint]
/// @brief		[�ͷ��ڴ�]
///
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(IN PRODUCTANDPRODUCTDETAILS *&pp);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerProductAndProductDetailsNextChargeTime]
/// @brief		[��ʱ���ѯ����ģʽ��¼��]
///
/// @param [in] szBeginTime [��ʼʱ��]
/// @param [in] szEndTime   [����ʱ��]
/// @param [OUT] pp         [��Ʒ�Ͳ�Ʒ��ϸ�ṹ��ָ��]
/// @param [OUT] pNum       [�ṹ��ĸ���]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN const ADOCHAR *szBeginTime, IN const ADOCHAR *szEndTime);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime]
/// @brief [�ͷ��ڴ�]
///
/// @param [OUT] pp         [ָ��]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(IN PRODUCTANDPRODUCTDETAILS *&pp);


//CustomerProductDetails
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerProductDetails]
/// @brief		[��ѯ��Ʒ��ϸ��]
///
/// @param [OUT] productdetails		[��Ʒ��ϸ]
/// @param [in] nProductDetailsID	[��ʼʱ��]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProductDetails(OUT CUSTOMERPRODUCTDETAILS &productdetails, IN ADOINT nProductDetailsID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AUpdateCustomerProductDetails]
/// @brief		[�޸Ĳ�Ʒ��ϸ���¼]
///
/// @param [in] productdetails		[��Ʒ��ϸ]
/// @param [in] nProductDetailsID	[��ʼʱ��]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetails(IN CUSTOMERPRODUCTDETAILS productdetails, IN ADOINT nProductDetailsID);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerProductDetailsRemainServiceNum]
/// @brief [�޸Ĳ�Ʒ��ϸ��ʣ�����]
///
/// @param [in] nProductDetailsID	[��Ʒ��ϸID]
/// @param [in] nRemainServiceNum   [ʣ�����]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetailsRemainServiceNum(IN ADOINT nProductDetailsID, IN ADOINT nRemainServiceNum);


//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerProductDetailsPrice]
/// @brief [�޸Ĳ�Ʒ��ϸ�۸�]
///
/// @param [in] nProductDetailsID	[��Ʒ��ϸID]
/// @param [in] price				[��Ʒ�۸�]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetailsPrice(IN ADOINT nProductDetailsID, IN ADOINT price);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerProductDetailExceedPrice]
/// @brief [�޸Ĳ�Ʒ��ϸ�����]
///
/// @param [in] nProductDetailsID	[��Ʒ��ϸID]
/// @param [in] exceedprice			[���]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetailExceedPrice(IN ADOINT nProductDetailsID, IN ADOINT exceedprice);



//Account_Hospital
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryAccountHospital]
/// @brief		[��ѯ�ʻ�ҽԺ]
///
/// @param [in] nAccountHospitalID	[�ʻ�ҽԺID]
/// @param [OUT] accounthospital	[�ʻ�ҽԺ�ṹ��]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryAccountHospital(OUT ACCOUNTHOSTPITAL &accounthospital, IN ADOINT nAccountHospitalID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryAccountHospitalMedicalOrgId]
/// @brief		[��ѯ�ʻ�ҽԺ����ID]
///
/// @param [in] szMedicalOrgId   [����ID]
/// @param [OUT] accounthospital [�ʻ�ҽԺ]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryAccountHospitalMedicalOrgId(OUT ACCOUNTHOSTPITAL &accounthospital, IN const ADOCHAR *szMedicalOrgId);



//CustomerAccount
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerAccount]
/// @brief		[��ѯ�ͻ��ʻ�]
///
/// @param [in] AccountID			[�ʻ�ID]
/// @param [OUT] customeraccount    [�ͻ��ʻ�]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerAccount(IN CUSTOMERACCOUNT &customeraccount, IN ADOINT AccountID);

//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerAccountBalance]
/// @brief [�޸Ŀͻ��ʻ��ʽ�]
///
/// @param [in] AccountID	[�ʻ�ID]
/// @param [in] balance		[�ʽ�]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerAccountBalance(IN ADOINT AccountID, IN ADOINT balance);

//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerAccountOfferBalance]
/// @brief [���¿ͻ��ʻ��������]
///
/// @param [in] AccountID		[�ʻ�ID]
/// @param [in] offerbalance	[�������]
/// @return						[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerAccountOfferBalance(IN ADOINT AccountID, IN ADOINT offerbalance);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerAccountBalanceAndOfferBalance]
/// @brief [��ʱ���ѯ����ģʽ��¼��]
///
/// @param [in] AccountID			[�ʻ�ID]
/// @param [in] balance				[���]
/// @param [in] offerbalance		[�������]
/// @return							[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerAccountBalanceAndOfferBalance(IN ADOINT AccountID, IN ADOINT balance, IN ADOINT offerbalance);


//ServiceUseRecords
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AInsertServiceUseRecords]
/// @brief		[����ʹ�ü�¼]
///
/// @param [in] UseRecord	[ʹ�ü�¼�ṹ��]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AInsertServiceUseRecords(IN SERVICERECORDS &UseRecord);


//ServiceUseRecords
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryServiceUseLastRecordsID]
/// @brief		[��ѯ���ʹ�ü�¼ֵ]
///
/// @param [OUT] UseRecord	[���ʹ�ü�¼ֵ]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryServiceUseLastRecordsID(OUT ADOUINT &nRecordsID);


//BalanceDetails
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AInsertBalanceDetails]
/// @brief		[��������ϸ]
///
/// @param [in] BalanceDetail	[�����ϸ]
/// @return						[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AInsertBalanceDetails(IN BALANCEDETAILS &BalanceDetail);



//RechargeRecords
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryRechargeRecords]
/// @brief		[��ѯ��ֵ��¼����]
///
/// @param [in] nAccountID	[�ʻ�ID]
/// @param [in] bASC		[����/���� true/false]
/// @param [in] LimitNum	[��ѯ�����]
/// @param [OUT] pp         [��ֵ��¼���ṹ��ָ��]
/// @param [OUT] pNum       [��ֵ��¼���ṹ��ĸ���]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryRechargeRecords(OUT RECHARGERECORDS **pp, OUT ADOINT &pNum, IN ADOINT nAccountID, bool bASC, ADOINT LimitNum);


//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AFreeMemoryQueryRechargeRecords]
/// @brief		[�ͷ��ڴ�]
///
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AFreeMemoryQueryRechargeRecords(IN RECHARGERECORDS *&pp);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AInsertRechargeRecords]
/// @brief		[�����ֵ��¼]
///
/// @param [in] rechargerecords [��ֵ��¼�ṹ��]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AInsertRechargeRecords(IN RECHARGERECORDS &rechargerecords);

//Service
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryService]
/// @brief		[��ѯ�����¼]
///
/// @param [in] service		[����ṹ��]
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryService(OUT SERVICE &service, IN const ADOCHAR *szServiceCode);



//////////////////////////////////////////////////////////////////////////
/// @function	[AdoClose]
/// @brief		[�ͷ���Դ]
///
/// @return					[ADORESö�ٽ��]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoClose();






#endif
