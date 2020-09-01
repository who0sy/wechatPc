/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Author	: Bruce Liang
 * Website	: https://github.com/ldcsaa
 * Project	: https://github.com/ldcsaa/HP-Socket/HP-Socket
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 44636872, 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

/* HP-Socket �汾�� */
#define HP_VERSION_MAJOR		5	// ���汾��
#define HP_VERSION_MINOR		7	// �Ӱ汾��
#define HP_VERSION_REVISE		1	// �����汾��
#define HP_VERSION_BUILD		7	// �������

//#define _UDP_DISABLED				// ���� UDP
//#define _SSL_DISABLED				// ���� SSL
//#define _HTTP_DISABLED			// ���� HTTP
//#define _ZLIB_DISABLED			// ���� ZLIB

/* �Ƿ����� UDP����������� _UDP_DISABLED ����ã�Ĭ�ϣ����ã� */
#if !defined(_UDP_DISABLED)
	#ifndef _UDP_SUPPORT
		#define _UDP_SUPPORT
	#endif
#endif

/* �Ƿ����� SSL����������� _SSL_DISABLED ����ã�Ĭ�ϣ����ã� */
#if !defined(_SSL_DISABLED)
	#ifndef _SSL_SUPPORT
		#define _SSL_SUPPORT
	#endif
#endif

/* �Ƿ����� HTTP����������� _HTTP_DISABLED ����ã�Ĭ�ϣ����ã� */
#if !defined(_HTTP_DISABLED)
	#ifndef _HTTP_SUPPORT
		#define _HTTP_SUPPORT
	#endif
#endif

/* �Ƿ����� ZLIB����������� _ZLIB_DISABLED ����ã�Ĭ�ϣ����ã� */
#if !defined(_ZLIB_DISABLED)
	#ifndef _ZLIB_SUPPORT
		#define _ZLIB_SUPPORT
	#endif
#endif

/**************************************************/
/********** imports / exports HPSocket4C **********/

#ifdef HPSOCKET_STATIC_LIB
	#define HPSOCKET_API		EXTERN_C
#else
	#ifdef HPSOCKET_EXPORTS
		#define HPSOCKET_API	EXTERN_C __declspec(dllexport)
	#else
		#define HPSOCKET_API	EXTERN_C __declspec(dllimport)
	#endif
#endif

#define __HP_CALL				__stdcall

/*****************************************************************************************************************************************************/
/**************************************************************** Base Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

typedef const BYTE*	LPCBYTE, PCBYTE;

/************************************************************************
���ƣ����� ID ��������
������Ӧ�ó�����԰� CONNID ����Ϊ������Ҫ�����ͣ��磺ULONG / ULONGLONG��
************************************************************************/
typedef ULONG_PTR	CONNID, HP_CONNID;

/************************************************************************
���ƣ�ͨ���������״̬
������Ӧ�ó������ͨ��ͨ������� GetState() ������ȡ�����ǰ����״̬
************************************************************************/
typedef enum EnServiceState
{
	SS_STARTING	= 0,	// ��������
	SS_STARTED	= 1,	// �Ѿ�����
	SS_STOPPING	= 2,	// ����ֹͣ
	SS_STOPPED	= 3,	// �Ѿ�ֹͣ
} En_HP_ServiceState;

/************************************************************************
���ƣ�Socket ��������
������Ӧ�ó���� OnClose() �¼���ͨ���ò�����ʶ�����ֲ������µĴ���
************************************************************************/
typedef enum EnSocketOperation
{
	SO_UNKNOWN	= 0,	// Unknown
	SO_ACCEPT	= 1,	// Acccept
	SO_CONNECT	= 2,	// Connect
	SO_SEND		= 3,	// Send
	SO_RECEIVE	= 4,	// Receive
	SO_CLOSE	= 5,	// Close
} En_HP_SocketOperation;

/************************************************************************
���ƣ��¼��������
�������¼��ķ���ֵ����ͬ�ķ���ֵ��Ӱ��ͨ������ĺ�����Ϊ
************************************************************************/
typedef enum EnHandleResult
{
	HR_OK		= 0,	// �ɹ�
	HR_IGNORE	= 1,	// ����
	HR_ERROR	= 2,	// ����
} En_HP_HandleResult;

/************************************************************************
���ƣ�����ץȡ���
����������ץȡ�����ķ���ֵ
************************************************************************/
typedef enum EnFetchResult
{
	FR_OK				= 0,	// �ɹ�
	FR_LENGTH_TOO_LONG	= 1,	// ץȡ���ȹ���
	FR_DATA_NOT_FOUND	= 2,	// �Ҳ��� ConnID ��Ӧ������
} En_HP_FetchResult;

/************************************************************************
���ƣ����ݷ��Ͳ���
������Server ����� Agent ��������ݷ��Ͳ���

* ������Ͳ��ԣ�Ĭ�ϣ�	�������Ѷ�����Ͳ��������������һ���ͣ����Ӵ���Ч��
* ��ȫ���Ͳ���			�������Ѷ�����Ͳ��������������һ���ͣ������ƴ����ٶȣ����⻺�������
* ֱ�ӷ��Ͳ���			����ÿһ�����Ͳ�����ֱ��Ͷ�ݣ������ڸ��ز��ߵ�Ҫ��ʵʱ�Խϸߵĳ���
************************************************************************/
typedef enum EnSendPolicy
{
	SP_PACK				= 0,	// ���ģʽ��Ĭ�ϣ�
	SP_SAFE				= 1,	// ��ȫģʽ
	SP_DIRECT			= 2,	// ֱ��ģʽ
} En_HP_SendPolicy;

/************************************************************************
���ƣ�OnSend �¼�ͬ������
������Server ����� Agent ����� OnSend �¼�ͬ������

* ��ͬ����Ĭ�ϣ�	����ͬ�� OnSend �¼�������ͬʱ���� OnReceive �� OnClose �¼�
* ͬ�� OnClose	��ֻͬ�� OnClose �¼�������ͬʱ���� OnReceive �¼�
* ͬ�� OnReceive	����ֻ���� TCP �����ͬ�� OnReceive �� OnClose �¼���������ͬʱ���� OnReceive �� OnClose �¼�
************************************************************************/
typedef enum EnOnSendSyncPolicy
{
	OSSP_NONE			= 0,	// ��ͬ����Ĭ�ϣ�
	OSSP_CLOSE			= 1,	// ͬ�� OnClose
	OSSP_RECEIVE		= 2,	// ͬ�� OnReceive��ֻ���� TCP �����	
} En_HP_OnSendSyncPolicy;

/************************************************************************
���ƣ���ַ����ѡ��
������ͨ������ײ� socket �ĵ�ַ����ѡ��
************************************************************************/
typedef enum EnReuseAddressPolicy
{
	RAP_NONE			= 0,	// ������
	RAP_ADDR_ONLY		= 1,	// �����õ�ַ
	RAP_ADDR_AND_PORT	= 2,	// ���õ�ַ�Ͷ˿�
} En_HP_ReuseAddressPolicy;

/************************************************************************
���ƣ������������
��������� Start() / Stop() ����ִ��ʧ��ʱ����ͨ�� GetLastError() ��ȡ�������
************************************************************************/
typedef enum EnSocketError
{
	SE_OK						= NO_ERROR,	// �ɹ�
	SE_ILLEGAL_STATE			= 1,		// ��ǰ״̬����������
	SE_INVALID_PARAM			= 2,		// �Ƿ�����
	SE_SOCKET_CREATE			= 3,		// ���� SOCKET ʧ��
	SE_SOCKET_BIND				= 4,		// �� SOCKET ʧ��
	SE_SOCKET_PREPARE			= 5,		// ���� SOCKET ʧ��
	SE_SOCKET_LISTEN			= 6,		// ���� SOCKET ʧ��
	SE_CP_CREATE				= 7,		// ������ɶ˿�ʧ��
	SE_WORKER_THREAD_CREATE		= 8,		// ���������߳�ʧ��
	SE_DETECT_THREAD_CREATE		= 9,		// ��������߳�ʧ��
	SE_SOCKE_ATTACH_TO_CP		= 10,		// ����ɶ˿�ʧ��
	SE_CONNECT_SERVER			= 11,		// ���ӷ�����ʧ��
	SE_NETWORK					= 12,		// �������
	SE_DATA_PROC				= 13,		// ���ݴ�������
	SE_DATA_SEND				= 14,		// ���ݷ���ʧ��

	/***** SSL Socket ��չ����������� *****/
	SE_SSL_ENV_NOT_READY		= 101,		// SSL ����δ����
} En_HP_SocketError;

/************************************************************************
���ƣ�����ģʽ
������UDP ����Ĳ���ģʽ���鲥��㲥��
************************************************************************/
typedef enum EnCastMode
{
	CM_UNICAST		= -1,	// ����
	CM_MULTICAST	= 0,	// �鲥
	CM_BROADCAST	= 1,	// �㲥
} En_HP_CastMode;

/************************************************************************
���ƣ�IP ��ַ����
������IP ��ַ����ö��ֵ
************************************************************************/
typedef enum EnIPAddrType
{
	IPT_ALL		= 0,		// ����
	IPT_IPV4	= 1,		// IPv4
	IPT_IPV6	= 2,		// IPv6
} En_HP_IPAddrType;

/************************************************************************
���ƣ�IP ��ַ��Ŀ�ṹ��
������IP ��ַ�ĵ�ַ��/��ֵַ�ṹ��
************************************************************************/
typedef struct TIPAddr
{
	EnIPAddrType type;
	LPCTSTR		 address;
} *LPTIPAddr, HP_TIPAddr, *HP_LPTIPAddr;

/************************************************************************
���ƣ��ܾ�����
���������ñ��ܾ���Ĵ�������
************************************************************************/
typedef enum EnRejectedPolicy
{
	TRP_CALL_FAIL	= 0,	// ���̷���ʧ��
	TRP_WAIT_FOR	= 1,	// �ȴ���ֱ���ɹ�����ʱ���̳߳عرյ�ԭ����ʧ�ܣ�
	TRP_CALLER_RUN	= 2,	// �������߳�ֱ��ִ��
} En_HP_RejectedPolicy;

/************************************************************************
���ƣ����񻺳�������
������TSockeTask ���󴴽�������ʱ�����ݲ�ͬ���͵Ļ�������������ͬ�Ĵ���
************************************************************************/
typedef enum EnTaskBufferType
{
	TBT_COPY	= 0,	// ���
	TBT_REFER	= 1,	// ǳ����
	TBT_ATTACH	= 2,	// �����������𴴽������������٣�
} En_HP_TaskBufferType;

/************************************************************************
���ƣ�����������
��������������ں���
������pvArg -- �Զ������
����ֵ�����ޣ�
************************************************************************/
typedef VOID (__HP_CALL *Fn_TaskProc)(PVOID pvArg);
typedef Fn_TaskProc	HP_Fn_TaskProc;

struct TSocketTask;

/************************************************************************
���ƣ�Socket ����������
������Socket ��������ں���
������pTask -- Socket ����ṹ��ָ��
����ֵ�����ޣ�
************************************************************************/
typedef VOID (__HP_CALL *Fn_SocketTaskProc)(TSocketTask* pTask);
typedef Fn_SocketTaskProc	HP_Fn_SocketTaskProc;

/************************************************************************
���ƣ�Socket ����ṹ��
��������װ Socket ����������ݽṹ
************************************************************************/
typedef struct TSocketTask
{
	Fn_SocketTaskProc	fn;			// ����������
	PVOID				sender;		// �������
	CONNID				connID;		// ���� ID
	LPCBYTE				buf;		// ���ݻ�����
	INT					bufLen;		// ���ݻ���������
	EnTaskBufferType	bufType;	// ����������
	WPARAM				wparam;		// �Զ������
	LPARAM				lparam;		// �Զ������
} *LPTSocketTask, HP_TSocketTask, *HP_LPTSocketTask;

/************************************************************************
���ƣ���ȡ HPSocket �汾��
�������汾�ţ�4 ���ֽڷֱ�Ϊ�����汾�ţ��Ӱ汾�ţ������汾�ţ�������ţ�
************************************************************************/
inline DWORD GetHPSocketVersion()
{
	return (HP_VERSION_MAJOR << 24) | (HP_VERSION_MINOR << 16) | (HP_VERSION_REVISE << 8) | HP_VERSION_BUILD;
}

/*****************************************************************************************************************************************************/
/**************************************************************** SSL Type Definitions ***************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _SSL_SUPPORT

/************************************************************************
���ƣ�SSL ����ģʽ
��������ʶ SSL �Ĺ���ģʽ���ͻ���ģʽ������ģʽ
************************************************************************/
typedef enum EnSSLSessionMode
{
	SSL_SM_CLIENT	= 0,	// �ͻ���ģʽ
	SSL_SM_SERVER	= 1,	// �����ģʽ
} En_HP_SSLSessionMode;

/************************************************************************
���ƣ�SSL ��֤ģʽ
������SSL ��֤ģʽѡ�SSL_VM_PEER ���Ժͺ�������ѡ�����һ��
************************************************************************/
typedef enum EnSSLVerifyMode
{
	SSL_VM_NONE					= 0x00,	// SSL_VERIFY_NONE
	SSL_VM_PEER					= 0x01,	// SSL_VERIFY_PEER
	SSL_VM_FAIL_IF_NO_PEER_CERT	= 0x02,	// SSL_VERIFY_FAIL_IF_NO_PEER_CERT
	SSL_VM_CLIENT_ONCE			= 0x04,	// SSL_VERIFY_CLIENT_ONCE
} En_HP_SSLVerifyMode;

/************************************************************************
���ƣ�SSL Session ��Ϣ����
���������� GetSSLSessionInfo()����ʶ����� Session ��Ϣ����
************************************************************************/
typedef enum EnSSLSessionInfo
{
	SSL_SSI_MIN					= 0,	// 
	SSL_SSI_CTX					= 0,	// SSL CTX				��������ͣ�SSL_CTX*��
	SSL_SSI_CTX_METHOD			= 1,	// SSL CTX Mehtod		��������ͣ�SSL_METHOD*��
	SSL_SSI_CTX_CIPHERS			= 2,	// SSL CTX Ciphers		��������ͣ�STACK_OF(SSL_CIPHER)*��
	SSL_SSI_CTX_CERT_STORE		= 3,	// SSL CTX Cert Store	��������ͣ�X509_STORE*��
	SSL_SSI_SERVER_NAME_TYPE	= 4,	// Server Name Type		��������ͣ�int��
	SSL_SSI_SERVER_NAME			= 5,	// Server Name			��������ͣ�LPCSTR��
	SSL_SSI_VERSION				= 6,	// SSL Version			��������ͣ�LPCSTR��
	SSL_SSI_METHOD				= 7,	// SSL Method			��������ͣ�SSL_METHOD*��
	SSL_SSI_CERT				= 8,	// SSL Cert				��������ͣ�X509*��
	SSL_SSI_PKEY				= 9,	// SSL Private Key		��������ͣ�EVP_PKEY*��
	SSL_SSI_CURRENT_CIPHER		= 10,	// SSL Current Cipher	��������ͣ�SSL_CIPHER*��
	SSL_SSI_CIPHERS				= 11,	// SSL Available Ciphers��������ͣ�STACK_OF(SSL_CIPHER)*��
	SSL_SSI_CLIENT_CIPHERS		= 12,	// SSL Client Ciphers	��������ͣ�STACK_OF(SSL_CIPHER)*��
	SSL_SSI_PEER_CERT			= 13,	// SSL Peer Cert		��������ͣ�X509*��
	SSL_SSI_PEER_CERT_CHAIN		= 14,	// SSL Peer Cert Chain	��������ͣ�STACK_OF(X509)*��
	SSL_SSI_VERIFIED_CHAIN		= 15,	// SSL Verified Chain	��������ͣ�STACK_OF(X509)*��
	SSL_SSI_MAX					= 15,	// 
} En_HP_SSLSessionInfo;

/************************************************************************
���ƣ�SNI �������ƻص�����
���������ݷ���������ѡ�� SSL ֤��
������	
		lpszServerName -- ���������ƣ�������

����ֵ��
		0	 -- �ɹ���ʹ��Ĭ�� SSL ֤������
		����	 -- �ɹ���ʹ�÷���ֵ��Ӧ�� SNI ����֤������
		����	 -- ʧ�ܣ��ж� SSL ����

************************************************************************/
typedef int (__HP_CALL *Fn_SNI_ServerNameCallback)(LPCTSTR lpszServerName, PVOID pContext);
typedef Fn_SNI_ServerNameCallback	HP_Fn_SNI_ServerNameCallback;

#endif

/*****************************************************************************************************************************************************/
/**************************************************************** HTTP Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT

/************************************************************************
���ƣ�HTTP �汾
���������ֽڣ����汾�ţ����ֽڣ��ΰ汾��
************************************************************************/

typedef enum EnHttpVersion
{
	HV_1_0	= MAKEWORD(1, 0),	// HTTP/1.0
	HV_1_1	= MAKEWORD(1, 1)	// HTTP/1.1
} En_HP_HttpVersion;

/************************************************************************
���ƣ�URL ��
������HTTP �������� URL ��λ������
************************************************************************/
typedef enum EnHttpUrlField
{ 
	HUF_SCHEMA		= 0,	// Schema
	HUF_HOST		= 1,	// Host
	HUF_PORT		= 2,	// Port
	HUF_PATH		= 3,	// Path
	HUF_QUERY		= 4,	// Query String
	HUF_FRAGMENT	= 5,	// Fragment
	HUF_USERINFO	= 6,	// User Info
	HUF_MAX			= 7,	// (Field Count)
} En_HP_HttpUrlField;

/************************************************************************
���ƣ�HTTP ���������ʶ
������ָʾ HTTP �������Ƿ����ִ�н�������
************************************************************************/
typedef enum EnHttpParseResult
{
	HPR_OK			= 0,	// �����ɹ�
	HPR_SKIP_BODY	= 1,	// ������ǰ���� BODY�������� OnHeadersComplete �¼���
	HPR_UPGRADE		= 2,	// ����Э�飨������ OnHeadersComplete �¼���
	HPR_ERROR		= -1,	// ����������ֹ�������Ͽ�����
} En_HP_HttpParseResult;

/************************************************************************
���ƣ�HTTP Э����������
��������ʶ HTTP ����Ϊ����Э��
************************************************************************/
typedef enum EnHttpUpgradeType
{
	HUT_NONE		= 0,	// û������
	HUT_WEB_SOCKET	= 1,	// WebSocket
	HUT_HTTP_TUNNEL	= 2,	// HTTP ����
	HUT_UNKNOWN		= -1,	// δ֪����
} En_HP_HttpUpgradeType;

/************************************************************************
���ƣ�HTTP ״̬��
������HTTP ��׼״̬��
************************************************************************/
typedef enum EnHttpStatusCode
{ 
	HSC_CONTINUE						= 100,
	HSC_SWITCHING_PROTOCOLS				= 101,
	HSC_PROCESSING						= 102,

	HSC_OK								= 200,
	HSC_CREATED							= 201,
	HSC_ACCEPTED						= 202,
	HSC_NON_AUTHORITATIVE_INFORMATION	= 203,
	HSC_NO_CONTENT						= 204,
	HSC_RESET_CONTENT					= 205,
	HSC_PARTIAL_CONTENT					= 206,
	HSC_MULTI_STATUS					= 207,
	HSC_ALREADY_REPORTED				= 208,
	HSC_IM_USED							= 226,

	HSC_MULTIPLE_CHOICES				= 300,
	HSC_MOVED_PERMANENTLY				= 301,
	HSC_MOVED_TEMPORARILY				= 302,
	HSC_SEE_OTHER						= 303,
	HSC_NOT_MODIFIED					= 304,
	HSC_USE_PROXY						= 305,
	HSC_SWITCH_PROXY					= 306,
	HSC_TEMPORARY_REDIRECT				= 307,
	HSC_PERMANENT_REDIRECT				= 308,

	HSC_BAD_REQUEST						= 400,
	HSC_UNAUTHORIZED					= 401,
	HSC_PAYMENT_REQUIRED				= 402,
	HSC_FORBIDDEN						= 403,
	HSC_NOT_FOUND						= 404,
	HSC_METHOD_NOT_ALLOWED				= 405,
	HSC_NOT_ACCEPTABLE					= 406,
	HSC_PROXY_AUTHENTICATION_REQUIRED	= 407,
	HSC_REQUEST_TIMEOUT					= 408,
	HSC_CONFLICT						= 409,
	HSC_GONE							= 410,
	HSC_LENGTH_REQUIRED					= 411,
	HSC_PRECONDITION_FAILED				= 412,
	HSC_REQUEST_ENTITY_TOO_LARGE		= 413,
	HSC_REQUEST_URI_TOO_LONG			= 414,
	HSC_UNSUPPORTED_MEDIA_TYPE			= 415,
	HSC_REQUESTED_RANGE_NOT_SATISFIABLE	= 416,
	HSC_EXPECTATION_FAILED				= 417,
	HSC_MISDIRECTED_REQUEST				= 421,
	HSC_UNPROCESSABLE_ENTITY			= 422,
	HSC_LOCKED							= 423,
	HSC_FAILED_DEPENDENCY				= 424,
	HSC_UNORDERED_COLLECTION			= 425,
	HSC_UPGRADE_REQUIRED				= 426,
	HSC_PRECONDITION_REQUIRED			= 428,
	HSC_TOO_MANY_REQUESTS				= 429,
	HSC_REQUEST_HEADER_FIELDS_TOO_LARGE	= 431,
	HSC_UNAVAILABLE_FOR_LEGAL_REASONS	= 451,
	HSC_RETRY_WITH						= 449,

	HSC_INTERNAL_SERVER_ERROR			= 500,
	HSC_NOT_IMPLEMENTED					= 501,
	HSC_BAD_GATEWAY						= 502,
	HSC_SERVICE_UNAVAILABLE				= 503,
	HSC_GATEWAY_TIMEOUT					= 504,
	HSC_HTTP_VERSION_NOT_SUPPORTED		= 505,
	HSC_VARIANT_ALSO_NEGOTIATES			= 506,
	HSC_INSUFFICIENT_STORAGE			= 507,
	HSC_LOOP_DETECTED					= 508,
	HSC_BANDWIDTH_LIMIT_EXCEEDED		= 509,
	HSC_NOT_EXTENDED					= 510,
	HSC_NETWORK_AUTHENTICATION_REQUIRED	= 511,

	HSC_UNPARSEABLE_RESPONSE_HEADERS	= 600
} En_HP_HttpStatusCode;

/************************************************************************
���ƣ�Name/Value �ṹ��
�������ַ�����ֵ�Խṹ��
************************************************************************/
typedef struct TNVPair
{ 
	LPCSTR name;
	LPCSTR value;
}	HP_TNVPair,
TParam, HP_TParam, *LPPARAM, *HP_LPPARAM,
THeader, HP_THeader, *LPHEADER, *HP_LPHEADER,
TCookie, HP_TCookie, *LPCOOKIE, *HP_LPCOOKIE;

#endif