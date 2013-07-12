#ifndef GLOBAL_UNITES_HEAD_FILE
#define GLOBAL_UNITES_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgDownLoad.h"

//////////////////////////////////////////////////////////////////////////////////

//全局单元
class CGlobalUnits
{
	//版本信息
protected:
	DWORD							m_dwPlazaVersion;					//大厅版本
	DWORD							m_dwFrameVersion;					//框架版本

	//组件指针
protected:
	CDlgDownLoad *					m_pDlgDownLoad;						//下载组件

	//字符变量
protected:
	TCHAR                           m_szValidateParam[255];             //验证参数 

	//静态变量
protected:
	static CGlobalUnits *			m_pGlobalUnits;						//对象指针

	//函数定义
public:
	//构造函数
	CGlobalUnits();
	//析构函数
	virtual ~CGlobalUnits();

	//版本信息
public:
	//大厅版本
	virtual DWORD GetPlazaVersion() { return m_dwPlazaVersion; }
	//框架版本
	virtual DWORD GetFrameVersion() { return m_dwFrameVersion; }

	//甜饼信息
public:
	//记录甜饼
	bool WriteUserCookie();
	//删除甜饼
	bool DeleteUserCookie();

	//功能函数
public:
	//下载游戏
	bool DownLoadClient(LPCTSTR pszClientName, WORD wKindID, WORD wServerID);
	//文件判断
	bool LocalFileExist(LPCTSTR pszFileName);
	//设置参数
	void SetValidateParam(DWORD dwUserID,LPCTSTR szPassword);
	//获取参数
	LPCTSTR GetValidateParamAsString();

	//声音函数
public:
	//播放声音
	bool PlayPlazaSound(LPCTSTR pszSoundName);
	//播放声音
	bool PlayPlazaSound(HINSTANCE hInstance, LPCTSTR pszSoundName);

	//静态函数
public:
	//获取对象
	static CGlobalUnits * GetInstance() { return m_pGlobalUnits; }
};

//////////////////////////////////////////////////////////////////////////////////

#endif