#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//主对话框类
class CMakeGUIDDlg : public CDialog
{
	//函数定义
public:
	//构造函数
	CMakeGUIDDlg();

	//对话框数据
	enum { IDD = IDD_MAKEGUID_DIALOG };

	//重载函数
protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual void OnOK();

	//消息函数
public:
	//XOR 按钮
	afx_msg void OnBnClickedXOR();
	//MD5 按钮
	afx_msg void OnBnClickedMD5();
	//拷贝按钮
	afx_msg void OnBnClickedCopy();
	//质数按钮
	afx_msg void OnBnClickedPrime();
	//版本按钮
	afx_msg void OnBnClickedVersion();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
