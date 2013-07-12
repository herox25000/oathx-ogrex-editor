#ifndef GAME_FRAME_ENGINE_HEAD_FILE
#define GAME_FRAME_ENGINE_HEAD_FILE

#pragma once

#include "GameFrameHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_FRAME_CLASS CGameFrameEngine : public CWnd, public IGameFrameEngine
{
	//��Ԫ����
	friend class CGameFrameService;

	//����ӿ�
protected:
	IClientKernel *					m_pIClientKernel;					//�ں˽ӿ�
	IStringMessage *				m_pIStringMessage;					//��Ϣ�ӿ�

	//��̬����
protected:
	static CGameFrameEngine *		m_pGameFrameEngine;					//����ӿ�

	//��������
public:
	//���캯��
	CGameFrameEngine();
	//��������
	virtual ~CGameFrameEngine();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//ϵͳ�¼�
public:
	//��������
	virtual bool OnInitGameEngine()=NULL;
	//���ú���
	virtual bool OnResetGameEngine()=NULL;

	//ʱ���¼�
public:
	//ʱ��ɾ��
	virtual bool OnEventGameClockKill(WORD wChairID)=NULL;
	//ʱ����Ϣ
	virtual bool OnEventGameClockInfo(WORD wChairID, UINT nElapse, WORD wClockID)=NULL;

	//��Ϸ�¼�
public:
	//�Թ���Ϣ
	virtual bool OnEventLookonMode(VOID * pData, WORD wDataSize)=NULL;
	//��Ϸ��Ϣ
	virtual bool OnEventGameMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize)=NULL;
	//������Ϣ
	virtual bool OnEventSceneMessage(BYTE cbGameStatus, bool bLookonUser, VOID * pData, WORD wDataSize)=NULL;
	//������Ϣ
	virtual bool OnEventInsureMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize);

	//�û��¼�
public:
	//�û�����
	virtual VOID OnEventUserEnter(IClientUserItem * pIClientUserItem, bool bLookonUser){}
	//�û��뿪
	virtual VOID OnEventUserLeave(IClientUserItem * pIClientUserItem, bool bLookonUser){}
	//�û�����
	virtual VOID OnEventUserScore(IClientUserItem * pIClientUserItem, bool bLookonUser){}
	//�û�״̬
	virtual VOID OnEventUserStatus(IClientUserItem * pIClientUserItem, bool bLookonUser){}

	//ģʽ����
public:
	//����ģʽ
	bool IsSingleMode();
	//�Թ��û�
	bool IsLookonMode();
	//�����Թ�
	bool IsAllowLookon();

	//״̬����
public:
	//��ȡ״̬
	BYTE GetGameStatus();
	//����״̬
	VOID SetGameStatus(BYTE cbGameStatus);

	//���ܺ���
public:
	//��ȡ�Լ�
	WORD GetMeChairID();
	//��ȡ�Լ�
	IClientUserItem * GetMeUserItem();
	//��Ϸ�û�
	IClientUserItem * GetTableUserItem(WORD wChariID);
	//��Ϸ�û�
	IClientUserItem * SearchTableUserItem(DWORD dwUserID);

	//���нӿ�
public:
	//������Ϸ��
	bool PerformSaveScore(SCORE lScore);
	//��ȡ��Ϸ��
	bool PerformTakeScore(SCORE lScore, TCHAR *pszInsurePass);

	//���ͺ���
public:
	//���ͺ���
	bool SendSocketData(WORD wSubCmdID);
	//���ͺ���
	bool SendSocketData(WORD wSubCmdID, VOID * pData, WORD wDataSize);

	//���ܽӿ�
public:
	//����׼��
	bool SendUserReady(VOID * pData, WORD wDataSize);
	//���ͱ���
	bool SendUserExpression(DWORD dwTargetUserID, WORD wItemIndex);
	//��������
	bool SendUserChatMessage(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor);

	//ʱ�亯��
public:
	//ʱ�ӱ�ʶ
	UINT GetClockID();
	//ʱ��λ��
	WORD GetClockChairID();
	//ɾ��ʱ��
	VOID KillGameClock(WORD wClockID);
	//����ʱ��
	VOID SetGameClock(WORD wChairID, WORD wClockID, UINT nElapse);

	//��������
public:
	//������
	VOID ActiveGameFrame();
	//�л�����
	WORD SwitchViewChairID(WORD wChairID);

	//��������
public:
	//��������
	bool PlayGameSound(LPCTSTR pszSoundName);
	//��������
	bool PlayGameSound(HINSTANCE hInstance, LPCTSTR pszSoundName);
	//��������
	bool PlayBackGroundSound(LPCTSTR pszSoundName);
	//��������
	bool PlayBackGroundSound(HINSTANCE hInstance, LPCTSTR pszSoundName);
	//ֹͣ����
	bool StopSound();

	//�ڲ�����
private:
	//��������
	bool ResetGameFrameEngine();
	//��������
	bool CreateGameFrameEngine();

	//���ܺ���
public:
	//��ʾ��Ϣ
	INT ShowMessageBox(LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0);
	//��ʾ��Ϣ
	INT ShowMessageBox(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0);

	//��̬����
public:
	//��ȡʵ��
	static CGameFrameEngine * GetInstance() { return m_pGameFrameEngine; }

	DECLARE_MESSAGE_MAP()

	//�����¼�
public:
	//�����¼�
	virtual bool OnGameOptionChange();
	//��������
	virtual bool AllowBackGroundSound(bool bAllowSound){return true;}
};

//////////////////////////////////////////////////////////////////////////////////

#endif