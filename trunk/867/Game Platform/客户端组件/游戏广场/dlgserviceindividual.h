#ifndef SERVICE_INDIVIDUAL_HEAD_FILE
#define SERVICE_INDIVIDUAL_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"

//////////////////////////////////////////////////////////////////////////////////

//�޸�����
class CDlgServiceIndividual : public CDlgServiceItem, public ITCPSocketSink
{
	//��Ԫ����
	friend class CDlgService;

	//��������
protected:
	bool							m_bQueryMission;						//��ѯ����
	bool							m_bModifyMission;						//�޸�����

	//����ӿ�
protected:
	CTCPSocketHelper                m_SocketHelper;
	//�ʺ�����
protected:
	BYTE							m_cbGender;								//�û��Ա�
	int								m_cbFaceID;								//ͷ��ID
	TCHAR							m_szAccounts[NICKNAME_LEN];				//�û���
	TCHAR							m_szPassword[PASS_LEN];					//�û�����
	TCHAR							m_szUnderWrite[UNDER_WRITE_LEN];		//����ǩ��

	//��ϸ����
protected:
	TCHAR							m_szQQ[QQ_LEN];							//Q Q ����
	TCHAR							m_szEMail[EMAIL_LEN];					//�����ʼ�
	TCHAR							m_szUserNote[USER_NOTE_LEN];			//�û�˵��
	TCHAR							m_szSFZ[IDCARD_LEN];					//���֤
	TCHAR							m_szMobilePhone[MOBILE_PHONE_LEN];		//�ƶ��绰
	TCHAR							m_szCompellation[COMPELLATION_LEN];		//��ʵ����
	TCHAR							m_szDwellingPlace[DWELLING_PLACE_LEN];	//��ϵ��ַ

	//�ؼ�����
protected:
	CSkinEdit						m_edGameID;								//��ϷID
	CSkinEdit						m_edAccounts;							//�û���
	CSkinEdit						m_edPassword;							//�޸�����
	CSkinEdit						m_edUnderWrite;							//����ǩ��

	//�ؼ�����
protected:
	CSkinEdit						m_edQQ;									//Q Q ����
	CSkinEdit						m_edEMail;								//�����ʼ�
	CSkinEdit						m_edUserNote;							//�û�˵��
	CSkinEdit						m_edSFZ	;								//���֤
	CSkinEdit						m_edMobilePhone;						//�ƶ��绰
	CSkinEdit						m_edCompellation;						//��ʵ����
	CSkinEdit						m_edDwellingPlace;						//��ϵ��ַ

	//�ؼ�����
protected:
	CSkinButton						m_btOk;									//�޸İ�ť
	//ͷ��ؼ�
	CImageList							m_ImageList;
	CComboBoxEx							m_FaceSelect;

	//��������
public:
	//���캯��
	CDlgServiceIndividual();
	//��������
	virtual ~CDlgServiceIndividual();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnDestroy();

	//���غ���
public:
	//��ȡ����
	virtual LPCTSTR GetServiceItemName() { return TEXT("�û�����"); }

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
private:
	//���ӵ�������
	bool ConnetToServer();
	//������Ϣ��ѯ��Ϣ
	void SendQueryIndividualInfoMsg();
	//�����޸���Ϣ��Ϣ
	void SendModifyIndividualInfoMsg();
	//���غ���
protected:
	//�ʺ���Ϣ
	VOID LoadAccountsInfo();
	//��ѯ����
	VOID QueryIndividualInfo();
	//��������
	VOID UpdateIndividualInfo();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif