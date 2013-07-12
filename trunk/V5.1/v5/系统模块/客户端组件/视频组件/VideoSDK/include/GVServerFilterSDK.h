
#if !defined(_GVSERVER_FILTER_SDK__INCLUDED_)
#define _GVSERVER_FILTER_SDK__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 *	��ȡSDK����汾��Ϣ
 *	@param lpVersion ���ز���İ汾��Ϣ
 *	@param dwVSLen �汾��Ϣ����������
 */
#define BRGS_FUNCNAME_GETVERSION	"BRGS_GetVersion"
typedef void (_cdecl * BRGS_GetVersion_PROC)(OUT LPTSTR lpVersion, 
											 IN DWORD dwVSLen);
/**
 *	��ʼ��SDK Filter
 *	�����ڸ÷����ж�ȡ��ص����ò������������ݿ����ӵȳ�ʼ������
 *	@return ��ʼ���ɹ�����TRUE�����򷵻�FALSE
 */
#define BRGS_FUNCNAME_INITFILTER	"BRGS_InitFilter"
typedef BOOL (_cdecl * BRGS_InitFilter_PROC)(void);

/**
 *	��֤�û����
 *	@param lpUserName �����û���
 *	@param lpPassword �����û�����
 *	@param lpUserID ������û���ID�ţ�ע�⣺��ID�ű���Ψһ�������ظ���
 *	@param lpUserLevel ������û��ļ���
 *	@param lpNickName ������û����ǳ�
 *	@param dwNCLen �����û��ǳƻ������ĳ���
 *	@return ���س����룬�ɹ����� GV_ERR_SUCCESS�����򷵻ض�Ӧ�Ĵ������
 */
#define BRGS_FUNCNAME_VERIFYUSER	"BRGS_VerifyUser"
typedef DWORD (_cdecl * BRGS_VerifyUser_PROC)(IN LPCTSTR lpUserName, 
											  IN LPCTSTR lpPassword, 
											  OUT LPDWORD lpUserID, 
											  OUT LPDWORD lpUserLevel, 
											  OUT LPTSTR lpNickName,
											  IN DWORD dwNCLen);


/**
 *	�ͷ�SDK Filter��Դ
 *	�ڷ������˳�ʱ����
 */
#define BRGS_FUNCNAME_RELEASE		"BRGS_ReleaseFilter"
typedef BOOL (_cdecl * BRGS_ReleaseFilter_PROC)(void);

#endif //_GVSERVER_FILTER_SDK__INCLUDED_