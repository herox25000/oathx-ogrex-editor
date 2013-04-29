#ifndef SKIN_AIDE_HEAD_FILE
#define SKIN_AIDE_HEAD_FILE

#pragma once

#include "SkinImage.h"
#include "SkinControls.h"
#include "PngImage.h"
//////////////////////////////////////////////////////////////////////////

//环绕信息
struct tagEncircleInfo
{
	INT								nTBorder;							//上边框高
	INT								nBBorder;							//下边框高
	INT								nLBorder;							//左边框宽
	INT								nRBorder;							//右边框宽
};

//环绕资源
struct tagEncircleResource
{
	LPCTSTR							pszImageTL;							//资源标识
	LPCTSTR							pszImageTM;							//资源标识
	LPCTSTR							pszImageTR;							//资源标识
	LPCTSTR							pszImageML;							//资源标识
	LPCTSTR							pszImageMR;							//资源标识
	LPCTSTR							pszImageBL;							//资源标识
	LPCTSTR							pszImageBM;							//资源标识
	LPCTSTR							pszImageBR;							//资源标识
};

//环绕位图
struct tagEncircleImage
{
	CSkinImage						ImageTL;							//位图对象
	CSkinImage						ImageTM;							//位图对象
	CSkinImage						ImageTR;							//位图对象
	CSkinImage						ImageML;							//位图对象
	CSkinImage						ImageMR;							//位图对象
	CSkinImage						ImageBL;							//位图对象
	CSkinImage						ImageBM;							//位图对象
	CSkinImage						ImageBR;							//位图对象
};

//环绕句柄
struct tagEncircleHandle
{
	CImageHandle					ImageHandleTL;						//位图句柄
	CImageHandle					ImageHandleTM;						//位图句柄
	CImageHandle					ImageHandleTR;						//位图句柄
	CImageHandle					ImageHandleML;						//位图句柄
	CImageHandle					ImageHandleMR;						//位图句柄
	CImageHandle					ImageHandleBL;						//位图句柄
	CImageHandle					ImageHandleBM;						//位图句柄
	CImageHandle					ImageHandleBR;						//位图句柄
};

//环绕位图
struct tagEncirclePNG
{
	CPngImage						ImageTL;							//位图对象
	CPngImage						ImageTM;							//位图对象
	CPngImage						ImageTR;							//位图对象
	CPngImage						ImageML;							//位图对象
	CPngImage						ImageMR;							//位图对象
	CPngImage						ImageBL;							//位图对象
	CPngImage						ImageBM;							//位图对象
	CPngImage						ImageBR;							//位图对象
};


//////////////////////////////////////////////////////////////////////////

//界面助手
class SKIN_CONTROL_CLASS CSkinAide
{
	//函数定义
protected:
	//构造函数
	CSkinAide();
	//析构函数
	virtual ~CSkinAide();

	//环绕辅助
public:
	//环绕信息
	static bool GetEncircleInfo(tagEncircleInfo & EncircleInfo, tagEncircleImage & EncircleImage);
	//资源标识
	static bool SetEncircleResource(tagEncircleImage & EncircleImage, tagEncircleResource & EncircleResource, HINSTANCE hResInstance);

	//环绕绘画
public:
	//绘画环绕
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage);
	//绘画环绕
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle);
	//绘画环绕
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage, COLORREF crTrans);
	//绘画环绕
	static bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle, COLORREF crTrans);

	//环绕计算
public:
	//计算位置
	static bool CaleWindowRect(CRect & rcEncircle, tagEncircleInfo & EncircleInfo, CRect & rcControl);
	//计算位置
	static bool CaleWindowRect(CRect & rcEncircle, tagEncircleImage & EncircleImage, CRect & rcControl);
	//计算位置
	static bool CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo, CRect & rcControl);
	//计算位置
	static bool CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage, CRect & rcControl);

	//环绕调整
public:
	//环绕调整
	static bool SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleInfo & EncircleInfo);
	//环绕调整
	static bool SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleImage & EncircleImage);
	//环绕调整
	static bool SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo);
	//环绕调整
	static bool SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage);

	//环绕调整
public:
	//环绕调整
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleInfo & EncircleInfo);
	//环绕调整
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleImage & EncircleImage);
	//环绕调整
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo);
	//环绕调整
	static bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage);
};


//环绕界面
class SKIN_CONTROL_CLASS CEncirclePNG
{
	//资源信息
protected:
	HINSTANCE						m_hResInstance;						//资源句柄
	tagEncircleInfo					m_EncircleInfo;						//环绕信息
	tagEncircleResource				m_EncircleResource;					//环绕资源

	//函数定义
public:
	//构造函数
	CEncirclePNG();
	//析构函数
	virtual ~CEncirclePNG();

	//重载函数
protected:
	//加载资源
	virtual bool LoadEncircleImage(tagEncirclePNG & EncircleImage);
	//绘画处理
	virtual bool PreDrawEncircleImage(tagEncirclePNG & EncircleImage) { return true; }

	//资源管理
public:
	//默认资源
	bool InitDefaultResource();
	//设置资源
	bool InitEncircleResource(tagEncircleResource & EncircleResource, HINSTANCE hResInstance);

	//环绕绘画
public:
	//绘画环绕
	bool DrawEncircleFrame(CDC * pDC, CRect & rcEncircle);

	//位置函数
public:
	//获取位置
	bool GetEncircleInfo(tagEncircleInfo & EncircleInfo);
	//获取位置
	bool GetEncircleRect(CRect & rcFrameBorad, CRect & rcControl);

	//环绕调整
public:
	//环绕调整
	bool SetWindowPos(CWnd * pWnd, CRect & rcEncircleBorad);
	//环绕调整
	bool DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircleBorad);
};

//////////////////////////////////////////////////////////////////////////

#endif