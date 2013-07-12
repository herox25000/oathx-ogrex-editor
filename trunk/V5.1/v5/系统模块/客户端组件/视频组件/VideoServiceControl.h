#ifndef VIDEO_SERVICE_CONTROL_HEAD_FILE
#define VIDEO_SERVICE_CONTROL_HEAD_FILE

#pragma once

#include "VideoServiceModule.h"
#include "DlgVideoClone.h"


//////////////////////////////////////////////////////////////////////////

//��Ƶ����
class VIDEO_SERVICE_CLASS CVideoServiceControl : public CWnd
{
	//��Ԫ����
	friend class CVideoServiceManager;

	//�ں˱���
private:
	bool							m_bInitVideo;						//���ñ�־
	bool							m_bShowVideo;						//��ʾ��Ƶ

	//�û���Ϣ
private:
	DWORD							m_dwUserID;							//�û���ʶ
	TCHAR							m_szAccounts[LEN_NICKNAME];				//�û��ʺ�

	//״̬����
private:
	float							m_fVolumePercent;					//��������
	CRect							m_rcPaintVolume;					//��������

	//�ͻ�����
private:
	DWORD							m_dwTargerUserID;					//Ŀ�����

	//�˵�����
private:
	tagUserInfo						*m_pUserData;						//�����Ϣ

	//���Ʊ���
private:
	bool							m_bSmallMode;						//С��ģʽ
	bool							m_bLocalMode;						//���ر�־
	bool							m_bEnableVideo;						//�Ƿ���Ƶ
	bool							m_bEnableAudio;						//�Ƿ���Ƶ

	//��ť�ؼ�
private:
	CSkinButton						m_btMore;							//���ఴť
	CSkinButton						m_btVideo;							//��Ƶ��ť
	CSkinButton						m_btAudio;							//��Ƶ��ť
	CSkinButton						m_btClone;							//��¡��ť
	CSkinButton						m_btFlower;							//�ͻ���ť
	CDlgVideoClone					m_DlgVideoClone;					//��¡�Ի���

	//�ؼ�����
protected:
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�

	//ͼƬ��Դ
private:
	CBitImage						m_ImageSmallPhoto;					//��Сͷ��
	CBitImage						m_ImageLargePhoto;					//�Ŵ�ͷ��
	CBitImage						m_ImageSmallFrame;					//��С���
	CBitImage						m_ImageLargeFrame;					//�Ŵ���
	CBitImage						m_ImageLargeVolume;					//�Ŵ���
	CBitImage						m_ImageLargeVolumeEx;				//�Ŵ���
	CBitImage						m_ImageSmallVolumeEx;				//�Ŵ���
	CBitImage						m_ImageSmallVolume;					//�Ŵ���

	//��������
public:
	//���캯��
	CVideoServiceControl();
	//��������
	virtual ~CVideoServiceControl();

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//��Сģʽ
public:
	//��Сģʽ
	bool SetSmallMode(bool bSmallMode);
	//��Сģʽ
	bool IsSamllMode() { return m_bSmallMode; }
	//��ȡ��С
	void GetVideoSize(CRect &rcVideo);

	//Զ���û�
public:
	//Զ���û�
	DWORD GetVideoUserID() { return m_dwUserID; }
	//Զ���û�
	bool SetVideoUserInfo(DWORD dwUserID, LPCTSTR pszAccounts);

	//���ƺ���
public:
	//������Ƶ
	bool InitVideoService(bool bLocalMode, bool bSmallMode);
	//��������
	void SetVolume(DWORD dwCurrentVolume);

	//��Ƶ����
public:		
	//������Ƶ
	void DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader);
	//�����ı�
	void OnWaveInVolumeChange(DWORD dwVolume);
	//�����ı�
	void OnWaveOutVolumeChange(DWORD dwVolume);

	//�ڲ�����
protected:
	//��������
	VOID RectifyControl();	

	//��Ϣӳ��
protected:
	//�ػ�����
	VOID OnPaint();
	//��������
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//���غ���
protected:
	//�˵�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//�¼�����
protected:
	//�����¼�
	bool OnEventUserEnter();
	//�뿪�¼�
	bool OnEventUserLeave();
	//�����¼�
	bool OnEventReset();
	//����ͷ�¼�
	void OnEventCameraState(BYTE cbState);

	//��ť��Ϣ
protected:
	//���ఴť
	VOID OnBnClickedMore();
	//��Ƶ��ť
	VOID OnBnClickedVideo();
	//��Ƶ��ť
	VOID OnBnClickedAudio();
	//��¡��ť
	VOID OnBnClickedClone();
	//�ͻ���ť
	VOID OnBnClickedFlower();
    
	//��Ϣ��
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
interface IClientKernel;
//��Ƶ����
class VIDEO_SERVICE_CLASS CVideoServiceManager : public CWnd
{
	//��Ԫ����
	friend class CVideoServiceControl;

	//��Ƶ��Ϣ
protected:
	WORD							m_wVideoPort;						//��Ƶ�˿�
	DWORD							m_dwVideoServer;					//��Ƶ��ַ
	DWORD							m_dwLocalUserID;					//�����û�
	DWORD							m_dwUserID[MAX_CHAIR];				//�û���ʶ
	DWORD							m_dwVideoRoomID;					//�����ʶ

	//��Դ����
protected:
	static HINSTANCE				m_hResInstance;						//��Դ���
	//static tagVideoFrameImage		m_VideoFrameImage;					//��Ƶ��Դ
	//static tagPropertyMenuImage		m_PropertyMenuImage;				//�˵���Դ

	//�������
protected:
	IClientKernel *					m_pIClientKernel;					//�ں˽ӿ�
	IStringMessage *				m_pIMessageProxy;					//��Ϣ����
	CVideoServiceControl *			m_VideoServiceControl[MAX_CHAIR];	//��Ƶ����

	//��̬����
protected:
	static CVideoServiceManager *	m_pVideoServiceManager;				//�������

	//��������
public:
	//���캯��
	CVideoServiceManager();
	//��������
	virtual ~CVideoServiceManager();

	//���ú���
public:
	//���ýӿ�
	bool SetClientKernel(IUnknownEx * pIUnknownEx);
	//��ȡ�ӿ�
	IClientKernel *GetClientKernel() {return m_pIClientKernel;}
	//���ýӿ�
	bool SetMessageProxy(IUnknownEx * pIUnknownEx);
	//������Ϣ
	bool SetVideoServiceInfo(DWORD dwLoaclUserID, DWORD dwVideoServer, WORD wVideoPort);
	//���ö���
	bool SetVideoServiceControl(WORD wVideoIndex, CVideoServiceControl * pVideoServiceControl);
	//��ȡ����
	CVideoServiceControl *GetVideoServiceControl(WORD wVideoIndex);
	//��½��Ƶ
	void LoginVideoSystem();
	//�ǳ�ϵͳ
	void LogoutVideoSystem();
	//������Դ
	static void SetSkinResource(HINSTANCE hResInstance/*,tagVideoFrameImage *pVideoFrameImage,tagPropertyMenuImage *pPropertyMenuImage*/);

	//�¼��ӿ�
public:
	//������Ƶ
	bool OnEventGameReset();

	//��������
public:
	//��ʾ��־
	void AppendLogString(CString strLog);
	//��ȡ����
	WORD GetVideoIndex(DWORD dwUserID);
	//��ȡ����
	WORD GetVideoIndex(tagUserInfo const*pagUserData);

	//��Ƶ�¼�
public:
	//�����¼�
	afx_msg LRESULT OnGVClientConnect(WPARAM wParam, LPARAM lParam);
	//��½�¼�
	afx_msg LRESULT OnGVClientLogin(WPARAM wParam, LPARAM lParam);
	//�����¼�
	afx_msg LRESULT OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam);
	//�б��¼�
	afx_msg LRESULT OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam);
	//�����¼�
	afx_msg LRESULT OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam);
	//�����¼�
	afx_msg LRESULT OnGVClientLinkClose(WPARAM wParam, LPARAM lParam);
	//����ͷ�¼�
	afx_msg LRESULT OnGVClientCameraState(WPARAM wParam, LPARAM lParam);

	//��̬����
public:
	//��ȡʵ��
	static CVideoServiceManager * GetInstance() { return m_pVideoServiceManager; }

	//��Ϣ��
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif
