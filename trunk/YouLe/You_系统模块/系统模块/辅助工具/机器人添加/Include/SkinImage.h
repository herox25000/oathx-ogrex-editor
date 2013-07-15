#ifndef SKIN_IMAGE_HEAD_FILE
#define SKIN_IMAGE_HEAD_FILE

#pragma once

#include "SkinControls.h"

//////////////////////////////////////////////////////////////////////////

//GDI ��Դ�ӿ�
interface IGDIResource
{
	//��������
	virtual int LockResource()=NULL;
	//��������
	virtual int UnLockResource()=NULL;
	//��ȡ���ü���
	virtual int GetReferenceCount()=NULL;
};

//��Դ����ӿ�
interface IGDIResourceHandle
{
	//�Ƿ��
	virtual bool IsAttached()=NULL;
	//�Ƿ���Ч
	virtual bool IsResourceValid()=NULL;
	//�����
	virtual bool DetchResource()=NULL;
	//����Դ
	virtual bool AttachResource(IGDIResource * pGDIObject)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//����λͼ�ṹ
struct tagImageLoadInfo
{
	//��������
	UINT								uResourceID;						//��Դ ID
	CString								strFileName;						//�ļ�����
	HINSTANCE							hResourceDLL;						//��Դ���

	//��������
	tagImageLoadInfo()
	{
		uResourceID=0;
		hResourceDLL=NULL;
	}
};

//λͼ������
class SKIN_CONTROL_CLASS CSkinImage : public CImage, public IGDIResource
{
	friend class CImageHandle;

	//�ڲ�����
private:
	int									m_nRefCount;						//���ü���
	bool								m_bLoadAlways;						//�Ƿ���
	tagImageLoadInfo					m_LoadInfo;							//���ز���

	//��������
public:
	//���캯��
	CSkinImage(void);
	//��������
	virtual ~CSkinImage(void);

	//�ӿں���
protected:
	//��������
	virtual int LockResource();
	//��������
	virtual int UnLockResource();
	//��ȡ���ü���
	virtual int GetReferenceCount() { return m_nRefCount; }

	//���ܺ���
public:
	//�Ƿ����ü�����Ϣ
	bool IsSetLoadInfo();
	//������ز���
	bool RemoveLoadInfo();
	//��ȡ���ز���
	bool GetLoadInfo(tagImageLoadInfo & LoadInfo);
	//���ü��ز���
	bool SetLoadInfo(LPCTSTR pszFileName, bool bLoadAlways=false);
	//���ü��ز���
	bool SetLoadInfo(UINT uResourceID, HINSTANCE hResourceDLL=NULL, bool bLoadAlways=false);

	//���غ���
public:
	//λͼָ��
	operator CBitmap * () { return CBitmap::FromHandle((HBITMAP)(*this)); }

	//��ͼ����
public:
	//��������
	HRGN CreateImageRegion(COLORREF cTranColor);
	//͸���滭
	bool AlphaDrawImage(CDC * pDestDC, int xDest, int yDest, COLORREF crTrans);
	//͸���滭
	bool AlphaDrawImage(CDC * pDestDC, int xDest, int yDest, int cxDest, int cyDest, int xSrc, int ySrc, COLORREF crTrans);
	//͸���滭
	bool AlphaDrawImageEx(CDC * pDestDC, int xDest, int yDest, COLORREF crTrans);
	//͸���滭
	bool AlphaDrawImageEx(CDC * pDestDC, int xDest, int yDest, int cxDest, int cyDest, int xSrc, int ySrc, COLORREF crTrans);
};

//////////////////////////////////////////////////////////////////////////

//λͼ��Դ���
class SKIN_CONTROL_CLASS CImageHandle : public IGDIResourceHandle
{
	//��������
protected:
	CSkinImage							* m_pImage;							//λͼָ��
	
	//��������
public:
	//���캯��
	CImageHandle(CSkinImage * pImageObject=NULL);
	//��������
	virtual ~CImageHandle();
	
	//�ӿں���
public:
	//�Ƿ��
	virtual bool IsAttached();
	//�Ƿ���Ч
	virtual bool IsResourceValid();
	//�����
	virtual bool DetchResource();
	//����Դ
	virtual bool AttachResource(IGDIResource * pImageObject);

	//��������
public:
	//��ȡ���
	HBITMAP GetBitmapHandle();
	//��ȡ����
	CSkinImage * GetImageObject() { return m_pImage; };
	//ָ������
	CSkinImage * operator->() { return GetImageObject(); }
};

//////////////////////////////////////////////////////////////////////////

#endif