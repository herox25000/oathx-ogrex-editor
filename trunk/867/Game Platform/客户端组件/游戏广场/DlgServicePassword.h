#ifndef SERVICE_PASSWORD_HEAD_FILE
#define SERVICE_PASSWORD_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"

//////////////////////////////////////////////////////////////////////////////////

//�޸�����
class CDlgServicePassword : public CDlgServiceItem, public ITCPSocketSink
{
	//��������
protected:
	bool							m_bLogonMission;				//�Ƿ�Ϊ�޸ĵ�¼����
	CTCPSocketHelper				m_SocketHelper;					//��������
	//����ǿ��
protected:
	BYTE							m_cbLogonPasswordLevel;				//����ǿ��
	BYTE							m_cbInsurePasswordLevel;			//����ǿ��

	//��������
protected:
	TCHAR							m_szSrcPassword[PASS_LEN];		//�û�����
	TCHAR							m_szDesPassword[PASS_LEN];		//�û�����

	//�ؼ�����
protected:
	CPasswordControl				m_edLogonPassword1;					//�ʺ�����
	CPasswordControl				m_edLogonPassword2;					//�ʺ�����
	CPasswordControl				m_edLogonPassword3;					//�ʺ�����
	CPasswordControl				m_edInsurePassword1;				//��������
	CPasswordControl				m_edInsurePassword2;				//��������
	CPasswordControl				m_edInsurePassword3;				//��������

	//�ؼ�����
protected:
	CSkinButton						m_btLogonPassword;					//�޸İ�ť
	CSkinButton						m_btInsurePassword;					//�޸İ�ť

	//��������
public:
	//���캯��
	CDlgServicePassword();
	//��������
	virtual ~CDlgServicePassword();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//���غ���
public:
	//��ȡ����
	virtual LPCTSTR GetServiceItemName() { return TEXT("�޸�����"); }

	//�����ӿ�
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�����¼�
private:
	//�����¼�
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);

	//�¼�����
protected:
	//��ʼ����
	VOID OnMissionStart();
	//��ֹ����
	VOID OnMissionConclude();

	//���ܺ���
public:
	//����ȼ�
	BYTE GetPasswordLevel(LPCTSTR pszPassword);
	//���ӵ�������
	bool ConnetToServer();
	//��Ϣӳ��
protected:
	//ȡ��
	virtual VOID OnDestroy();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��������
	VOID OnEnChangeLogonPassword();
	//��������
	VOID OnEnChangeInserePassword();
	//�����޸�
	VOID OnBnClickedLogonPassword();
	//�����޸�
	VOID OnBnClickedInsurePassword();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif