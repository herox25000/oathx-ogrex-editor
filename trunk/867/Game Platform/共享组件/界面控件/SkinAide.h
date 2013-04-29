#ifndef SKIN_AIDE_HEAD_FILE
#define SKIN_AIDE_HEAD_FILE

#pragma once

#include "SkinImage.h"
#include "SkinControls.h"
#include "PngImage.h"
//////////////////////////////////////////////////////////////////////////

//������Ϣ
struct tagEncircleInfo
{
	INT								nTBorder;							//�ϱ߿��
	INT								nBBorder;							//�±߿��
	INT								nLBorder;							//��߿��
	INT								nRBorder;							//�ұ߿��
};

//������Դ
struct tagEncircleResource
{
	LPCTSTR							pszImageTL;							//��Դ��ʶ
	LPCTSTR							pszImageTM;							//��Դ��ʶ
	LPCTSTR							pszImageTR;							//��Դ��ʶ
	LPCTSTR							pszImageML;							//��Դ��ʶ
	LPCTSTR							pszImageMR;							//��Դ��ʶ
	LPCTSTR							pszImageBL;							//��Դ��ʶ
	LPCTSTR							pszImageBM;							//��Դ��ʶ
	LPCTSTR							pszImageBR;							//��Դ��ʶ
};

//����λͼ
struct tagEncircleImage
{
	CSkinImage						ImageTL;							//λͼ����
	CSkinImage						ImageTM;							//λͼ����
	CSkinImage						ImageTR;							//λͼ����
	CSkinImage						ImageML;							//λͼ����
	CSkinImage						ImageMR;							//λͼ����
	CSkinImage						ImageBL;							//λͼ����
	CSkinImage						ImageBM;							//λͼ����
	CSkinImage						ImageBR;							//λͼ����
};

//���ƾ��
struct tagEncircleHandle
{
	CImageHandle					ImageHandleTL;						//λͼ���
	CImageHandle					ImageHandleTM;						//λͼ���
	CImageHandle					ImageHandleTR;						//λͼ���
	CImageHandle					ImageHandleML;						//λͼ���
	CImageHandle					ImageHandleMR;						//λͼ���
	CImageHandle					ImageHandleBL;						//λͼ���
	CImageHandle					ImageHandleBM;						//λͼ���
	CImageHandle					ImageHandleBR;						//λͼ���
};

//����λͼ
struct tagEncirclePNG
{
	CPngImage						ImageTL;							//λͼ����
	CPngImage						ImageTM;							//λͼ����
	CPngImage						ImageTR;							//λͼ����
	CPngImage						ImageML;							//λͼ����
	CPngImage						ImageMR;							//λͼ����
	CPngImage						ImageBL;							//λͼ����
	CPngImage						ImageBM;							//λͼ����
	CPngImage						ImageBR;							//λͼ����
};


//////////////////////////////////////////////////////////////////////////

//��������
class SKIN_CONTROL_CLASS CSkinAide
{
	//��������
protected:
	//���캯��
	CSkinAide();
	//��������
	virtual ~CSkinAide();

	//���Ƹ���
public:
	//������Ϣ
	static bool GetEncircleInfo(tagEncircleInfo & EncircleInfo, tagEncircleImage & EncircleImage);
	//��Դ��ʶ
	static bool SetEncircleResource(tagEncircleImage & EncircleImage, tagEncircleResource & EncircleResource, HINSTANCE hResInstance);

	//���ƻ滭
public:
	//�滭����
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage);
	//�滭����
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle);
	//�滭����
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage, COLORREF crTrans);
	//�滭����
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle, COLORREF crTrans);

	//���Ƽ���
public:
	//����λ��
	static bool CaleWindowRect(CRect & rcEncircle, tagEncircleInfo & EncircleInfo, CRect & rcControl);
	//����λ��
	static bool CaleWindowRect(CRect & rcEncircle, tagEncircleImage & EncircleImage, CRect & rcControl);
	//����λ��
	static bool CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo, CRect & rcControl);
	//����λ��
	static bool CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage, CRect & rcControl);

	//���Ƶ���
public:
	//���Ƶ���
	static bool SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleInfo & EncircleInfo);
	//���Ƶ���
	static bool SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleImage & EncircleImage);
	//���Ƶ���
	static bool SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo);
	//���Ƶ���
	static bool SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage);

	//���Ƶ���
public:
	//���Ƶ���
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleInfo & EncircleInfo);
	//���Ƶ���
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleImage & EncircleImage);
	//���Ƶ���
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo);
	//���Ƶ���
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage);
};


//���ƽ���
class SKIN_CONTROL_CLASS CEncirclePNG
{
	//��Դ��Ϣ
protected:
	HINSTANCE						m_hResInstance;						//��Դ���
	tagEncircleInfo					m_EncircleInfo;						//������Ϣ
	tagEncircleResource				m_EncircleResource;					//������Դ

	//��������
public:
	//���캯��
	CEncirclePNG();
	//��������
	virtual ~CEncirclePNG();

	//���غ���
protected:
	//������Դ
	virtual bool LoadEncircleImage(tagEncirclePNG & EncircleImage);
	//�滭����
	virtual bool PreDrawEncircleImage(tagEncirclePNG & EncircleImage) { return true; }

	//��Դ����
public:
	//Ĭ����Դ
	bool InitDefaultResource();
	//������Դ
	bool InitEncircleResource(tagEncircleResource & EncircleResource, HINSTANCE hResInstance);

	//���ƻ滭
public:
	//�滭����
	bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle);

	//λ�ú���
public:
	//��ȡλ��
	bool GetEncircleInfo(tagEncircleInfo & EncircleInfo);
	//��ȡλ��
	bool GetEncircleRect(CRect & rcFrameBorad, CRect & rcControl);

	//���Ƶ���
public:
	//���Ƶ���
	bool SetWindowPos(CWnd * pWnd, CRect & rcEncircleBorad);
	//���Ƶ���
	bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircleBorad);
};

//////////////////////////////////////////////////////////////////////////

#endif