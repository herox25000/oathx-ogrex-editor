#pragma once

class ID2DInterface
{
	//��������
public:
	//������Դ
	virtual LPCTSTR LaodImage( IN CWnd* pWnd, IN LPCTSTR strPath, OUT TCHAR* szOutInfo ) = NULL;
	//������Դ
	virtual LPCTSTR LaodImage( IN CWnd* pWnd, IN HINSTANCE hinstance, IN LPCTSTR strNmae,  IN LPCTSTR strType, OUT TCHAR* szOutInfo ) = NULL;
	//������Դ
	virtual LPCTSTR LaodImage( IN CWnd* pWnd, IN HINSTANCE hinstance, IN UINT uResID, OUT TCHAR* szOutInfo ) = NULL;
	//������Դ
	virtual LPCTSTR LaodImage( IN CWnd* pWnd, IN HINSTANCE hinstance, IN LPCTSTR strResID, OUT TCHAR* szOutInfo ) = NULL;

	//���庯��
public:
	//��ʼ�滭
	virtual void BeginDraw( IN CWnd* pWnd ) = NULL;
	//�����滭
	virtual void EndDraw( IN CWnd* pWnd ) = NULL;

	//��������
public:
	//�ͷŽӿ�
	virtual void Release() = NULL;
	//ɾ����Դ
	virtual void DeleteImage( IN CWnd* pWnd, IN LPCTSTR strInfo) = NULL;
	//��ȡ���
	virtual UINT GetWidth( IN CWnd* pWnd, IN LPCTSTR strInfo ) = NULL;
	//��ȡ�߶�
	virtual UINT GetHeight( IN CWnd* pWnd, IN LPCTSTR strInfo ) = NULL;

	//�滭����
public:
	//�滭����
	virtual bool DrawImage( IN CWnd* pWnd, IN LPCTSTR strInfo, IN INT nXDest, IN INT nYDest, IN BYTE cbAlpha) = NULL;
	//�滭����
	virtual bool DrawImage( IN CWnd* pWnd, IN LPCTSTR strInfo, IN INT nXDest, IN INT nYDest, IN INT nDestWidth, INT nDestHeight, IN INT nXScr, IN INT nYSrc, IN BYTE cbAlpha) = NULL;
	//�滭����
	virtual bool DrawImage( IN CWnd* pWnd, IN LPCTSTR strInfo, IN INT nXDest, IN INT nYDest, IN INT nDestWidth, IN INT nDestHeight, IN INT nXScr, IN INT nYSrc, IN INT nSrcWidth, IN INT nSrcHeight, IN BYTE cbAlpha ) = NULL;
	//�滭����
	virtual bool DrawImage( IN CWnd* pWnd, IN LPCTSTR strInfo, IN INT nXDest, IN INT nYDest, IN INT nDestWidth, IN INT nDestHeight, IN INT nXScr, IN INT nYSrc, IN INT nSrcWidth, IN INT nSrcHeight, COLORREF colorTransparent, IN BYTE cbAlpha ) = NULL;

	//���ֺ���
public:
	//��������
	virtual void* CreateFont( IN LPCTSTR strInfo, IN int nWidth, IN int nWeight) = NULL;
	//�滭����
	virtual bool DrawText( IN CWnd* pWnd, IN void* pFont, IN LPCTSTR strInfo, IN PRECT rect, IN COLORREF colorref, IN UINT uFormat) = NULL;
	//�滭����
	virtual bool DrawText( IN CWnd* pWnd, IN void* pFont, IN LPCTSTR strInfo, IN int nXPos, IN int nYPos, IN COLORREF colorref, IN UINT uFormat) = NULL;
	//�滭����
	virtual bool DrawText( IN CWnd* pWnd, IN int nWidth, IN int nWeight, IN LPCTSTR strInfo, IN PRECT rect, IN COLORREF colorref, IN UINT uFormat) = NULL;
	//�滭����
	virtual bool DrawText( IN CWnd* pWnd, IN int nWidth, IN int nWeight, IN LPCTSTR strInfo, IN int nXPos, int nYPos, IN COLORREF colorref, IN UINT uFormat) = NULL;
	//ɾ������
	virtual bool DeleteFont( IN void* pVoid) = NULL;

	//�滭����
public:	
	//�Զ���滭����
	virtual bool DrawCustomImage( IN CWnd* pWnd, IN INT nXDest, IN INT nYDest, IN INT nDestWidth, IN INT nDestHeight, IN DWORD* pImageData, IN INT nImageWidth, IN INT nImageHeight, IN BYTE cbAlpha ) = NULL;

};