#pragma once

#include "GdipButton.h"

// CFrameSet 对话框

class CFrameSet : public CDialog
{
	DECLARE_DYNAMIC(CFrameSet)

public:
	CFrameSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFrameSet();

// 对话框数据
	enum { IDD = IDD_FRAMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);

	//图片资源
protected:
	CPngImage			m_ImageBack;			//背景图

	//按钮控件
protected:
	CGdipButton			m_btClose;
	CGdipButton			m_btConfirn;
	CGdipButton			m_btCancel;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
