#pragma once

#include "Stdafx.h"
#include "AfxTempl.h"

//////////////////////////////////////////////////////////////////////////

//对话框类
class CSDKBuilderDlg : public CDialog
{
	//变量定义
protected:
	CString								m_strSourcePath;				//原路径
	CString								m_strTargetPath;				//目标路径
	CArray<CString>						m_strConversion;				//转化字符

	//控件变量
protected:
	CSkinRichEdit						m_SDKFileList;					//头文件列表
	CSkinRichEdit						m_LIBFileList;					//头文件列表

	//函数定义
public:
	//构造函数
	CSDKBuilderDlg();

	//重载函数
protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();

	//功能函数
protected:
	//加载头文件
	void LoadSDKFileList();
	//加载链接库
	void LoadLIBFileList();
	//加载转化字符
	void LoadConversionList();
	//创建目录
	void CreateDirectory(LPCTSTR pszDirectory);
	//转换文件
	bool ConversionSDKFile(LPCTSTR pszSDKFile);
	//拷贝文件
	bool CopyBinaryFile(LPCTSTR pszSourceFile, LPCTSTR pszTargetPath);

	//消息映射
public:
	//生成命令
	afx_msg void OnBnClickedBulid();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
