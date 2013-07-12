#pragma once
#ifndef D_FONT_EX_HEAD_FILE
#define D_FONT_EX_HEAD_FILE

#pragma once

#include "WHImageHead.h"

class WH_IMAGE_CLASS CDFontEx
{

	//��������
public:
	CWnd*								m_pWnd;
	CFont								m_GDIFont;
	void*								m_pD2DFont;
	int									m_nWidth;


public:
	CDFontEx(void);
	~CDFontEx(void);

public:
	//��������
	void CreateFont(CWnd* pWnd, LPCTSTR strInfo, int nWidth, int nWeight);
	//��ȡ�ַ�����
	static int GetCharLength(TCHAR chInfo, int nWidth);

public:
	//�滭����
	void DrawText(CDC* pDC, LPCTSTR str, LPRECT lpRect, COLORREF colorref, UINT nFormat);
	//�滭����
	void DrawText(CDC* pDC, LPCTSTR str, int XPos, int YPos, COLORREF colorref, UINT nFormat);

public:
	//�滭����
	static void DrawText(CWnd* pWnd, CDC* pDC, int nWidth, int nWeight, LPCTSTR str, LPRECT lpRect, COLORREF colorref, UINT nFormat);
	//�滭����
	static void DrawText(CWnd* pWnd, CDC* pDC, int nWidth, int nWeight, LPCTSTR str, int XPos, int YPos, COLORREF colorref, UINT nFormat);

public:
	//ɾ������
	void DeleteFont();
};
#endif