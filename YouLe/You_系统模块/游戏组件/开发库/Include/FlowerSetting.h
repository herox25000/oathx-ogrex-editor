#ifndef FLOWER_SETTING_HEAD_FILE
#define FLOWER_SETTING_HEAD_FILE
#pragma once

#include "PropertyModule.h"
#include "GameFrame.h"
///////////////////////////////////////////////////////////////////////////////////

class PROPERTY_MODULE_CLASS CFlowerSetting : public CSkinDialogEx
{
	//变量定义
public:
	int								m_nFlowerCount;						//鲜花数目
	int								m_nFlowerID;						//鲜花ID

	//绑定变量
public:
	CComboBox						m_ComboBoxTargetUser;				//目标玩家
	DWORD							m_dwTargetUserID;					//目标玩家
	CString							m_strDescribe;						//普通价格
	CString							m_strNormalUserPrice;				//普通价格
	CString							m_strMemberUserPrice;				//会员价格
	CString							m_strGoldDescribe;					//金币情况

	//控件变量
protected:
	CSkinButton						m_btOK;								//确定按钮
	CSkinButton						m_btCancel;							//取消按钮

	//组件接口
protected:
	IClientKernel					*m_pIClientKernel;					//框架接口

	//函数定义
public:
	//构造函数
	CFlowerSetting(CWnd* pParent = NULL);
	//析构函数
	virtual ~CFlowerSetting();

	//辅助函数
public:
	//设置ID
	void SetFlowerID(int nFlowerID) { m_nFlowerID = nFlowerID ;}
	//设置接口
	void SetClientKernel(IClientKernel *pIClientKernel) {ASSERT(pIClientKernel!=NULL); m_pIClientKernel = pIClientKernel;}
	//更新界面
	void UpdateView();
	//设置目标
	void SetTargetUserID(DWORD dwTargetUserID){m_dwTargetUserID = dwTargetUserID;}

	//继承函数
protected:
	//绑定函数
	virtual void DoDataExchange(CDataExchange* pDX);

	//消息函数
public:
	//按钮消息
	afx_msg void OnBnClickedOk();
	//初始函数
	virtual BOOL OnInitDialog();
	//设置颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//移动消息
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//消息映射
	DECLARE_MESSAGE_MAP()
};
///////////////////////////////////////////////////////////////////////////////////
#endif
