#ifndef GAME_FRAME_VIEW_GDI_HEAD_FILE
#define GAME_FRAME_VIEW_GDI_HEAD_FILE

#pragma once

#include "GameFrameView.h"
#include "GameFrameHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��ͼ���
class GAME_FRAME_CLASS CGameFrameViewGDI : public CGameFrameView
{
	//�������
private:
	CSize							m_SizeBackSurface;					//�����С
	CRect							m_RectDirtySurface;					//�ػ�����
	CImage							m_ImageBackSurface;					//�������
	CSkinButton						m_btCloseAwards;					//�رհ�ť

	//��ϷԪ��
protected:
	CPngImageEx						m_ImageUserReadyEx;					//�û�׼��
	CPngImageEx                     m_ImageClockItemEx;
	CPngImageEx                     m_ImageClockBackEx;

	//��������
public:
	//���캯��
	CGameFrameViewGDI();
	//��������
	virtual ~CGameFrameViewGDI();

	//���غ���
private:
	//�滭����
	virtual VOID DrawGameView(CDC * pDC, INT nWidth, INT nHeight)=NULL;

	//���غ���
public:
	//���ý���
	virtual VOID ResetGameView();
	//�����ؼ�
	virtual VOID RectifyControl(INT nWidth, INT nHeight);
	//�������
	virtual VOID InvalidGameView(INT nXPos, INT nYPos, INT nWidth, INT nHeight);
	//������Ϣ
	virtual void AddGameTableMessage(LPCTSTR pszMessage,WORD wLen,WORD wType);

	//��ϷԪ��
public:
	//�滭׼��
	VOID DrawUserReady(CDC * pDC, INT nXPos, INT nYPos);
	//�滭ʱ��
	VOID DrawUserClock(CDC * pDC, INT nXPos, INT nYPos, WORD wUserClock);
	//�滭ͷ��
	VOID DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, IClientUserItem * pIClientUserItem);
	//�滭ͷ��
	VOID DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, IClientUserItem * pIClientUserItem);

	//��ͼ����
public:
	//�滭����
	VOID DrawViewImage(CDC * pDC, CBitImage & BitImage, BYTE cbDrawMode);
	//�滭�ַ�
	VOID DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, CRect rcRect,CDFontEx *pFontEx=NULL);
	//�滭�ַ�
	VOID DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, INT nXPos, INT nYPos,CDFontEx *pFontEx=NULL);
	//�滭����
	VOID DrawNumberString(CDC * pDC, CPngImage &PngNumber, LONG lNumber, INT nXPos, INT nYPos,BYTE cbAlign=TA_LEFT);
	//������Ϣ
	VOID DrawMatchInfo(CDC * pDC);

	//��Ϣӳ��
protected:
	//�滭����
	VOID OnPaint();
	//�رս�״
	VOID OnBnClickedCloseAwards();

	DECLARE_MESSAGE_MAP()

	//��Ϣӳ��
public:
	afx_msg void OnTimer(UINT nIDEvent);

	//WIN7֧��
public:
	//�Ƿ��������
	virtual bool RealizeWIN7() { return false; }
	//�滭����
	VOID DrawViewImage(CDC * pDC, CBitImageEx & BitImage, BYTE cbDrawMode);
	//�滭����
	VOID DrawNumberString(CDC * pDC, CPngImageEx &PngNumber, LONG lNumber, INT nXPos, INT nYPos,BYTE cbAlign=TA_LEFT);
	//д�ַ�
	VOID DrawText(CDC * pDC, LPCTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat, CDFontEx* pFontEx = NULL);
	//д�ַ�
	VOID DrawText(CDC * pDC, const CString& str, LPRECT lpRect, UINT nFormat, CDFontEx* pFontEx = NULL);
	//д�ַ�
	VOID TextOut(CDC * pDC, int x, int y, LPCTSTR lpszString, int nCount, CDFontEx* pFontEx = NULL);
	//д�ַ�
	VOID TextOut(CDC * pDC, int x, int y, const CString& str, CDFontEx* pFontEx = NULL);
};

//////////////////////////////////////////////////////////////////////////////////

#endif