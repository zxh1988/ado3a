/*************************************************
  Copyright (C), 2015-2020, 理邦精密仪器股份有限公司
  @File name:	
  @Author:   	xianhui zhang
  @Date:     	2016-09-02
  @Description:  
*************************************************/
#ifndef ADOINTERFACE_H
#define ADOINTERFACE_H

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
typedef unsigned int UINT;



typedef enum ADORES
{
	ADO_SUCCESS,				//operation success	
	ADO_EXCEPTION,				//operation exception
	ADO_FAIL,					//fail		
	ADO_NOT_FOUND,				//not find	
	ADO_PARAM_ERROR,            //param error
	ADO_NOT_CONNECT,            //not connect
	ADO_KEYEXISIT,              //key exist
	ADO_NOPRIVALEGE,            //no access
	ADO_USEREXISIT,             //user exist
	ADO_LOGINFAILED             //user login fail

};




#endif
