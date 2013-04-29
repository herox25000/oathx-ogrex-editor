#pragma once

#ifndef SKIN_DIALOG_HEAD_FILE
#define SKIN_DIALOG_HEAD_FILE

#include "SkinControls.h"
#include "SkinWndObject.h"
#include "PngImage.h"
#include "SkinAide.h"


//////////////////////////////////////////////////////////////////////////

//对话框类
class SKIN_CONTROL_CLASS CSkinDialog : public CDialog, public CSkinWndObject
{
	//函数定义
public:
	//构造函数
	CSkinDialog(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//析构函数
	virtual ~CSkinDialog();

	//重载函数
public:
	//初始化消息
	virtual BOOL OnInitDialog();

	//消息映射
protected:
	//激活消息
	afx_msg void OnActivate(UINT nState, CWnd * pWndOther, BOOL bMinimized);
	//激活消息
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	//鼠标消息
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//绘画消息
	afx_msg void OnPaint();
	//改变消息
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//绘画背景
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//位置改变
	afx_msg void OnWindowPosChanged(WINDOWPOS * lpwndpos);
	//控件颜色
	afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	//标题消息
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinDialog)
};

//////////////////////////////////////////////////////////////////////////

//对话框类
class SKIN_CONTROL_CLASS CSkinDialogEx : public CSkinDialog
{
	//函数定义
public:
	//构造函数
	CSkinDialogEx(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//析构函数
	virtual ~CSkinDialogEx();

	//绘画函数
protected:
	//绘画边框
	void DrawBorder(CDC * pDC);
	//绘画标题
	void DrawCaption(CDC * pDC);
	//绘画背景
	void DrawBackGround(CDC * pDC);

	//消息函数
protected:
	//重画消息
	afx_msg void OnPaint();
	//位置消息
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinDialogEx)
};

//////////////////////////////////////////////////////////////////////////

//区域对话框类
class SKIN_CONTROL_CLASS CRgnDialog : public CDialog
{
	//变量定义
protected:
	CRgn							m_DialogRgn;						//窗口区域
	CSkinImage						m_ImageBack;						//背景位图

	//函数定义
public:
	//构造函数
	CRgnDialog(UINT uTemplate, CWnd * pParent=NULL);
	//析构函数
	virtual ~CRgnDialog();
	//初始化函数
	virtual BOOL OnInitDialog();

	//功能函数
public:
	//加载位图
	bool LoadRgnImage(LPCTSTR pszFileName, COLORREF crTrans);
	//加载位图
	bool LoadRgnImage(HINSTANCE hInstance, UINT uBitmapID, COLORREF crTrans);

	//内部函数 
private:
	//创建区域
	bool CreateControlRgn(COLORREF crTrans);

	//消息函数
public:
	//重画函数
	afx_msg void OnPaint();
	//鼠标右键按下消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//背景消息
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CRgnDialog)
};

//////////////////////////////////////////////////////////////////////////

//分层窗口
class SKIN_CONTROL_CLASS CSkinLayered : public CWnd
{
	//变量定义
protected:
	CWnd *							m_pWndControl;						//控件窗口

	//函数定义
public:
	//构造函数
	CSkinLayered();
	//析构函数
	virtual ~CSkinLayered();

	//功能函数
public:
	//创建窗口
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//设置区域
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//设置区域
	VOID InitLayeredArea(CPngImage & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//消息映射
protected:
	//关闭消息
	VOID OnClose();
	//焦点消息
	VOID OnSetFocus(CWnd * pOldWnd);

	//静态函数
protected:
	//枚举函数
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};




//带有资源的对话框

//窗口资源
class SKIN_CONTROL_CLASS CSkinDialogAttribute
{
	//颜色定义
public:
	COLORREF						m_crTitleText;						//标题颜色
	COLORREF						m_crTitleFrame;						//标题颜色
	COLORREF						m_crBackGround;						//背景颜色
	COLORREF						m_crControlText;					//控制颜色

	//资源变量
public:
	CSize							m_SizeButton;						//按钮大小
	CBrush							m_brBackGround;						//背景画刷
	CEncirclePNG					m_PNGEncircleFrame;					//框架资源

	//位置变量
public:
	tagEncircleInfo					m_EncircleInfoView;					//视图环绕
	tagEncircleInfo					m_EncircleInfoFrame;				//框架环绕

	//函数定义
public:
	//构造函数
	CSkinDialogAttribute();
	//析构函数
	virtual ~CSkinDialogAttribute();

	//管理函数
public:
	//配置资源
	bool Initialization(CSkinRenderManager * pSkinRenderManager);
};


//////////////////////////////////////////////////////////////////////////////////

//对话框类
class SKIN_CONTROL_CLASS CSkinPngDialog : public CDialog
{
	//按钮状态
private:
	BYTE							m_cbNowHotIndex;					//现在焦点
	BYTE							m_cbNowHitIndex;					//按下按钮
	BYTE							m_cbButtonState[3];					//按钮状态

	//过渡状态
private:
	bool							m_bTransition;						//过渡状态
	WORD							m_wImageIndex[3];					//过渡索引

	//窗口变量
private:
	CRect							m_rcButton[3];						//按钮位置
	CSkinLayered					m_SkinLayered;						//分层窗口

	//资源变量
public:
	static CSkinDialogAttribute		m_SkinAttribute;					//资源变量

	//函数定义
public:
	//构造函数
	CSkinPngDialog(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//析构函数
	virtual ~CSkinPngDialog();

	//重载函数
public:
	//配置消息
	virtual BOOL OnInitDialog();
	//绘画消息
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//辅助函数
private:
	//按键测试
	UINT ControlHitTest(CPoint Point);
	//调整资源
	VOID RectifyResource(INT nWidth, INT nHeight);
	//调整按钮
	VOID CaleTitleButton(INT nWidth, INT nHeight);

	//绘画函数
private:
	//绘画控件
	VOID DrawControlView(CDC * pDC, INT nWdith, INT nHeight);
	//绘画标题
	VOID DrawSystemTitle(CDC * pDC, INT nWdith, INT nHeight);
	//绘画按钮
	VOID DrawSystemButton(CDC * pDC, INT nWdith, INT nHeight);

	//消息映射
protected:
	//鼠标消息
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);

	//消息映射
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//时间消息
	VOID OnTimer(UINT_PTR nIDEvent);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//控件颜色
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	//自定消息
protected:
	//标题消息
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinPngDialog)
};


#endif