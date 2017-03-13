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
/// @brief		[初始化数据库]
///
/// @param [in] szDbServerIp [数据库IP地址]
/// @param [in] szDbName     [数据库名称]
/// @param [in] szDbUser     [数据库登录用户名]
/// @param [in] szDbPasswd   [数据库登录密码]
/// @return					 [ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoInitDb(IN const ADOCHAR *szDbServerIp,IN const ADOCHAR *szDbName,IN const ADOCHAR *szDbUser, IN const ADOCHAR *szDbPasswd);



//////////////////////////////////////////////////////////////////////////
/// @function		[AdoBeginTransaction]
/// @brief			[开始事物]
///
/// @return			[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoBeginTransaction();



//////////////////////////////////////////////////////////////////////////
/// @function		[AdoCommitTransaction]
/// @brief			[提交事物]
///
/// @return			[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoCommitTransaction();



//////////////////////////////////////////////////////////////////////////
/// @function		[AdoRollBackTransaction]
/// @brief			[回滚事物]
///
/// @return			[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoRollBackTransaction();


//Customer：
//////////////////////////////////////////////////////////////////////////
/// @function		[Ado3AQueryCustomer]
/// @brief			[查询用户名和密码]
///
/// @param [in] username    [用户名]
/// @param [in] passwd      [密码]
/// @param [OUT] customer   [客户结构体]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomer(OUT CUSTOMER &customer, IN const ADOCHAR *username, IN const ADOCHAR *passwd);



//Users
//////////////////////////////////////////////////////////////////////////
/// @function		[Ado3AQueryUsers]
/// @brief			[查询用户名和密码]
///
/// @param [in] username [用户名]
/// @param [in] passwd   [密码]
/// @param [OUT] user    [结构体]
/// @return			     [ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryUsers(OUT USERS &user, IN const ADOCHAR *username, IN const ADOCHAR *passwd);


//CustomerProduct
//////////////////////////////////////////////////////////////////////////
/// @function		[Ado3AQueryCustomerProduct]
/// @brief			[查询客户产品]
///
/// @param [in] nProductID			[产品ID]
/// @param [OUT] customerproduct    [客户产品]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProduct(OUT CUSTOMERPRODUCT &customerproduct, IN ADOINT nProductID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AUpdateCustomerProduct]
/// @brief		[修改产品价格]
///
/// @param [in] nProductID	[产品ID]
/// @param [in] price		[价格]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProduct(IN ADOINT nProductID, IN ADOINT price);


//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AUpdateCustomerProduct]
/// @brief		[修改是否已经扣费]
///
/// @param [in] nProductID	[产品ID]
/// @param [in] nIsCharge	[是否已经扣费]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductIsCharge(IN ADOINT nProductID, IN ADOINT nIsCharge);


//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerProductAndProductDetailsPoint]
/// @brief		[按时间查询服务模式记录数]
///
/// @param [in] AccountID	[帐户ID]
/// @param [in] ServiceID   [服务ID]
/// @param [OUT] pp         [产品和产品明细结构体指针]
/// @param [OUT] pNum       [结构体的个数]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProductAndProductDetailsPoint(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN ADOINT AccountID, IN ADOINT ServiceID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint]
/// @brief		[释放内存]
///
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AFreeMemoryQueryCustomerProductAndProductDetailsPoint(IN PRODUCTANDPRODUCTDETAILS *&pp);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerProductAndProductDetailsNextChargeTime]
/// @brief		[按时间查询服务模式记录数]
///
/// @param [in] szBeginTime [起始时间]
/// @param [in] szEndTime   [结束时间]
/// @param [OUT] pp         [产品和产品明细结构体指针]
/// @param [OUT] pNum       [结构体的个数]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProductAndProductDetailsNextChargeTime(OUT PRODUCTANDPRODUCTDETAILS **pp, OUT ADOUINT &pNum, IN const ADOCHAR *szBeginTime, IN const ADOCHAR *szEndTime);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime]
/// @brief [释放内存]
///
/// @param [OUT] pp         [指针]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryFreeMemoryCustomerProductAndProductDetailsNextChargeTime(IN PRODUCTANDPRODUCTDETAILS *&pp);


//CustomerProductDetails
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerProductDetails]
/// @brief		[查询产品明细表]
///
/// @param [OUT] productdetails		[产品详细]
/// @param [in] nProductDetailsID	[起始时间]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerProductDetails(OUT CUSTOMERPRODUCTDETAILS &productdetails, IN ADOINT nProductDetailsID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AUpdateCustomerProductDetails]
/// @brief		[修改产品明细表记录]
///
/// @param [in] productdetails		[产品详细]
/// @param [in] nProductDetailsID	[起始时间]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetails(IN CUSTOMERPRODUCTDETAILS productdetails, IN ADOINT nProductDetailsID);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerProductDetailsRemainServiceNum]
/// @brief [修改产品明细表剩余次数]
///
/// @param [in] nProductDetailsID	[产品明细ID]
/// @param [in] nRemainServiceNum   [剩余次数]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetailsRemainServiceNum(IN ADOINT nProductDetailsID, IN ADOINT nRemainServiceNum);


//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerProductDetailsPrice]
/// @brief [修改产品明细价格]
///
/// @param [in] nProductDetailsID	[产品明细ID]
/// @param [in] price				[产品价格]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetailsPrice(IN ADOINT nProductDetailsID, IN ADOINT price);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerProductDetailExceedPrice]
/// @brief [修改产品明细表溢价]
///
/// @param [in] nProductDetailsID	[产品明细ID]
/// @param [in] exceedprice			[溢价]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerProductDetailExceedPrice(IN ADOINT nProductDetailsID, IN ADOINT exceedprice);



//Account_Hospital
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryAccountHospital]
/// @brief		[查询帐户医院]
///
/// @param [in] nAccountHospitalID	[帐户医院ID]
/// @param [OUT] accounthospital	[帐户医院结构体]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryAccountHospital(OUT ACCOUNTHOSTPITAL &accounthospital, IN ADOINT nAccountHospitalID);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryAccountHospitalMedicalOrgId]
/// @brief		[查询帐户医院机构ID]
///
/// @param [in] szMedicalOrgId   [机构ID]
/// @param [OUT] accounthospital [帐户医院]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryAccountHospitalMedicalOrgId(OUT ACCOUNTHOSTPITAL &accounthospital, IN const ADOCHAR *szMedicalOrgId);



//CustomerAccount
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryCustomerAccount]
/// @brief		[查询客户帐户]
///
/// @param [in] AccountID			[帐户ID]
/// @param [OUT] customeraccount    [客户帐户]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryCustomerAccount(IN CUSTOMERACCOUNT &customeraccount, IN ADOINT AccountID);

//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerAccountBalance]
/// @brief [修改客户帐户资金]
///
/// @param [in] AccountID	[帐户ID]
/// @param [in] balance		[资金]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerAccountBalance(IN ADOINT AccountID, IN ADOINT balance);

//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerAccountOfferBalance]
/// @brief [更新客户帐户赠送余额]
///
/// @param [in] AccountID		[帐户ID]
/// @param [in] offerbalance	[赠送余额]
/// @return						[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerAccountOfferBalance(IN ADOINT AccountID, IN ADOINT offerbalance);



//////////////////////////////////////////////////////////////////////////
/// @function [Ado3AUpdateCustomerAccountBalanceAndOfferBalance]
/// @brief [按时间查询服务模式记录数]
///
/// @param [in] AccountID			[帐户ID]
/// @param [in] balance				[金额]
/// @param [in] offerbalance		[赠送余额]
/// @return							[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AUpdateCustomerAccountBalanceAndOfferBalance(IN ADOINT AccountID, IN ADOINT balance, IN ADOINT offerbalance);


//ServiceUseRecords
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AInsertServiceUseRecords]
/// @brief		[插入使用记录]
///
/// @param [in] UseRecord	[使用记录结构体]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AInsertServiceUseRecords(IN SERVICERECORDS &UseRecord);


//ServiceUseRecords
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryServiceUseLastRecordsID]
/// @brief		[查询最大使用记录值]
///
/// @param [OUT] UseRecord	[最大使用记录值]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryServiceUseLastRecordsID(OUT ADOUINT &nRecordsID);


//BalanceDetails
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AInsertBalanceDetails]
/// @brief		[插入金额明细]
///
/// @param [in] BalanceDetail	[金额明细]
/// @return						[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AInsertBalanceDetails(IN BALANCEDETAILS &BalanceDetail);



//RechargeRecords
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryRechargeRecords]
/// @brief		[查询充值记录次数]
///
/// @param [in] nAccountID	[帐户ID]
/// @param [in] bASC		[升序/降序 true/false]
/// @param [in] LimitNum	[查询最大数]
/// @param [OUT] pp         [充值记录数结构体指针]
/// @param [OUT] pNum       [充值记录数结构体的个数]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryRechargeRecords(OUT RECHARGERECORDS **pp, OUT ADOINT &pNum, IN ADOINT nAccountID, bool bASC, ADOINT LimitNum);


//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AFreeMemoryQueryRechargeRecords]
/// @brief		[释放内存]
///
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AFreeMemoryQueryRechargeRecords(IN RECHARGERECORDS *&pp);



//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AInsertRechargeRecords]
/// @brief		[插入充值记录]
///
/// @param [in] rechargerecords [充值记录结构体]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AInsertRechargeRecords(IN RECHARGERECORDS &rechargerecords);

//Service
//////////////////////////////////////////////////////////////////////////
/// @function	[Ado3AQueryService]
/// @brief		[查询服务记录]
///
/// @param [in] service		[服务结构体]
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES Ado3AQueryService(OUT SERVICE &service, IN const ADOCHAR *szServiceCode);



//////////////////////////////////////////////////////////////////////////
/// @function	[AdoClose]
/// @brief		[释放资源]
///
/// @return					[ADORES枚举结果]
//////////////////////////////////////////////////////////////////////////
ADOEXPORT ADORES AdoClose();






#endif
