#ifndef CARD_CONTROL_HEAD_FILE
#define CARD_CONTROL_HEAD_FILE

#pragma once

#include "Stdafx.h"


//枚举定义

//数值掩码
#define	CARD_MASK_COLOR				0xF0								//花色掩码
#define	CARD_MASK_VALUE				0x0F								//数值掩码

//X 排列方式
enum enXCollocateMode 
{ 
	enXLeft,						//左对齐
	enXCenter,						//中对齐
	enXRight,						//右对齐
};

//Y 排列方式
enum enYCollocateMode 
{ 
	enYTop,							//上对齐
	enYCenter,						//中对齐
	enYBottom,						//下对齐
};

//////////////////////////////////////////////////////////////////////////

//扑克控件
class CCardControl : public CWnd
{
	//间隔变量
protected:
	DWORD							m_dwCardHSpace;						//横向间隔

	//位置变量
protected:
	CPoint							m_BenchmarkPos;						//基准位置
	enXCollocateMode				m_XCollocateMode;					//显示模式
	enYCollocateMode				m_YCollocateMode;					//显示模式

	//内部数据
protected:
	CRgn							m_CardRegion;						//控件区域
	CArrayTemplate<BYTE,BYTE>		m_CardDataItem;						//扑克数据

	//资源变量
protected:
	static bool						m_bLoad;							//加载标志
	static CSize					m_CardSize;							//扑克大小
	static CSkinImage				m_ImageCard;						//图片资源

	//函数定义
public:
	//构造函数
	CCardControl();
	//析构函数
	virtual ~CCardControl();

	//控件控制
public:
	//设置间距
	void SetCardSpace(DWORD dwCardHSpace);
	//基准位置
	void SetBenchmarkPos(int nXPos, int nYPos, enXCollocateMode XCollocateMode, enYCollocateMode YCollocateMode);
	//基准位置
	void SetBenchmarkPos(const CPoint & BenchmarkPos, enXCollocateMode XCollocateMode, enYCollocateMode YCollocateMode);

	//扑克控制
public:
	//获取数目
	DWORD GetCardCount();
	//设置扑克
	DWORD SetCardData(const BYTE bCardData[], DWORD dwCardCount);
	//获取扑克
	void GetCardData(int nIndex, BYTE &cbCardData);

	//内部函数
private:
	//调整位置
	void RectifyControl();

	//消息函数
protected:
	//重画函数
	afx_msg void OnPaint();
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif