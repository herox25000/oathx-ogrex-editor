#ifndef GAME_OPTION_ITEM_HEAD_FILE
#define GAME_OPTION_ITEM_HEAD_FILE

#pragma once

#include "GameFrameHead.h"

//////////////////////////////////////////////////////////////////////////

//��������
class GAME_FRAME_CLASS CGameOptionItem : public CDialog, public IGameOptionItem
{
	//��������
protected:
	CSize							m_LogoSize;							//��ͼ��С
	CSize							m_ControlSize;						//�ؼ���С
	CBitImage						m_ImageOptionLogo;					//��ͼ��Դ

	//��������
public:
	//���캯��
	CGameOptionItem();
	//��������
	virtual ~CGameOptionItem();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID  Release() { return; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//���ڽӿ�
public:
	//��ȡ���
	virtual HWND __cdecl GetWindowHwnd() { return m_hWnd; }
	//�����ؼ�
	virtual bool __cdecl CreateOptionItem(CWnd * pParentWnd)=NULL;

	//��չ�ӿ�
public:
	//�����ؼ�
	virtual VOID __cdecl RectifyControl(INT nWidth, INT nHeight);
	//�滭�ؼ�
	virtual VOID __cdecl DrawControlFace(CDC * pDC, INT nWidth, INT nHeight);

	//��Ϣ�ӿ�
public:
	//��������
	virtual bool __cdecl SaveParameter()=NULL;
	//Ĭ�ϲ���
	virtual bool __cdecl DefaultParameter()=NULL;
	//��ȡλ��
	virtual VOID __cdecl GetControlMinSize(CSize & ControlSize) { ControlSize=m_ControlSize; }

	//���غ���
protected:
	//ȷ����Ϣ
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	//��Ϣӳ��
public:
	//�滭��Ϣ
	VOID OnPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//������Ϣ
	BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif