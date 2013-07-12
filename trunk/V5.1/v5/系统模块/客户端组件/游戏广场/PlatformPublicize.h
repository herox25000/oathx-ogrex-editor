#ifndef PLATFORM_PUBLICIZE_HEAD_FILE
#define PLATFORM_PUBLICIZE_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//��ܹ��
class CPlatformPublicize : public CWebPublicize
{
	//��������
protected:
	COLORREF						m_crBackColor;						//������ɫ
	COLORREF						m_crBoradColor;						//�߿���ɫ
	TCHAR							m_szSpareURL[MAX_PATH];				//������ַ

	//��������
public:
	//���캯��
	CPlatformPublicize();
	//��������
	virtual ~CPlatformPublicize();

	//���ú���
protected:
	//״̬֪ͨ
	virtual VOID OnBrowserStatus(BYTE cbStatus);
	//λ�ú���
	virtual VOID GetWebBrowserRect(CRect & rcWebBrowser);
	//�滭����
	virtual VOID DrawPublicizeView(CDC * pDC, INT nWidth, INT nHeight, BYTE cbStatus);

	//���ܺ���
public:
	//���ñ���
	VOID SetBackColor(COLORREF crBackColor);
	//���ñ߿�
	VOID SetBoradColor(COLORREF crBoradColor);
	//������ַ
	VOID SetSpareURL(LPCTSTR pszURL);
};

//////////////////////////////////////////////////////////////////////////////////

#endif