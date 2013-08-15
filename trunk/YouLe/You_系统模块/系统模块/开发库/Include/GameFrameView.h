#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameFrame.h"
#include "Irrlicht.h"
//////////////////////////////////////////////////////////////////////////

//�����ṹ
struct tagFlowerEffectInfo
{
	//�ƶ���Ϣ
	WORD							wMoveCount;							//�ƶ�����
	WORD							wMoveIndex;							//�ƶ�����
	CPoint							ptFrom;								//����λ��
	CPoint							ptDest;								//Ŀ��λ��
	CPoint							ptCurPos;							//��ǰλ��

	//������Ϣ
	WORD							wSourceChairID;						//��ʼλ��
	WORD							wTargetChairID;						//����λ��
	UINT							uFlowerID;							//�ʻ���ʶ
	UINT							uFlowerEffectID;					//������ʶ
	bool							bBombEffect;						//��ը��ʶ
};

//�滭ģʽ
enum enImageMode 
{
	enMode_Spread,					//ƽ��ģʽ
	enMode_Centent,					//����ģʽ
	enMode_ElongGate,				//����ģʽ
};

//��˵��
class CClientKernelSink;

//////////////////////////////////////////////////////////////////////////

//��Ϸ��ͼ���
class GAME_FRAME_CLASS CGameFrameView : public CWnd, public IGameFrameView
{
	//��Ԫ����
	friend class CGameFrameDlg;
	friend class CClientKernelSink;

	//λ�ñ���
protected:
	UINT							m_nAnimeStep;						//�ƶ����
	POINT							m_ptName[MAX_CHAIR];				//����λ��
	POINT							m_ptFace[MAX_CHAIR];				//ͷ��λ��
	POINT							m_ptTimer[MAX_CHAIR];				//ʱ��λ��
	POINT							m_ptReady[MAX_CHAIR];				//׼��λ��

protected:
	irr::IrrlichtDevice*			m_pIrrlichtDevice;					//3D�����豸
	irr::video::IVideoDriver*		m_pVideoDriver;						
	//�û�����
private:
	WORD							m_wTimer[MAX_CHAIR];				//�û�ʱ��
	tagUserData*					m_pUserItem[MAX_CHAIR];				//�û���Ϣ

	//���ָ��
private:
	void*							m_pReserve;							//����ָ��
	IUserFaceRes*					m_pIUserFaceRes;					//ͷ��ӿ�

	//ֻ������
public:
	static const int				m_nXFace;							//ͷ��߶�
	static const int				m_nYFace;							//ͷ����
	static const int				m_nXTimer;							//��ʱ����
	static const int				m_nYTimer;							//��ʱ����
	static const int				m_nXBorder;							//��ܿ��
	static const int				m_nYBorder;							//��ܸ߶�

	//��������
public:
	//���캯��
	CGameFrameView();
	//��������
	virtual ~CGameFrameView();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual void __cdecl			Release()
	{ 
		delete this; 
	}
	
	//�ӿڲ�ѯ
	virtual void* __cdecl			QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//��Ϸ����
	virtual bool					DrawAll();
public:
	//��ȡʱ��
	WORD GetUserTimer(WORD wChairID);
	//��ȡ���
	const tagUserData* GetUserInfo(WORD wChairID);

	//�ڲ�����
private:
	//���ý���
	void ResetData();
	//���ýӿ�
	bool SetUserFaceRes(IUnknownEx * pIUnknownEx);
	//����ʱ��
	bool SetUserTimer(WORD wChairID, WORD wTimer);
	//�����û�
	bool SetUserInfo(WORD wChairID, tagUserData * pUserData);

	//��Ϣӳ��
protected:
	//�滭����
	afx_msg void					OnPaint();
	//λ�ñ仯
	afx_msg void					OnSize(UINT nType, int cx, int cy);
	//������Ϣ
	afx_msg int						OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	afx_msg void					OnLButtonDown(UINT nFlags, CPoint point);
	//������Ϣ
	afx_msg void					OnDestroy();
	//ʱ����Ϣ
	afx_msg void					OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif