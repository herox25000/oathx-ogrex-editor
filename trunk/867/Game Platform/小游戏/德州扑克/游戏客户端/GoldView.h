#ifndef GOLD_VIEW_HEAD_FILE
#define GOLD_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
//宏定义
#define GOLD_IMAGE_WIDTH		20										//筹码宽
#define GOLD_IMAGE_HEIGHT		19										//筹码高

//////////////////////////////////////////////////////////////////////////

//筹码视图类
class CGoldView
{
	//变量定义
public:
	__int64								m_lGold;						//筹码数目
	__int64								m_lMaxLayer;					//最大层数
	__int64								m_lGoldCount[7];	 			//筹码数目

	//辅助变量
protected:
	static bool							m_bInit;						//初始标志
	static CSkinImage					m_ImageGold;					//筹码图片
	CSkinImage							m_ImageNumber;					//数字图片

	//函数定义
public:
	//构造函数
	CGoldView();
	//析构函数
	virtual ~CGoldView();

	//功能函数
public:
	//设置筹码
	void SetGold(__int64 lGold);
	//获取筹码
	__int64 GetGold() { return m_lGold; };
	//设置层数
	void SetMaxGoldLayer(__int64 lMaxLayer);
	//获取层数
	__int64 GetMaxGoldLayer(){return m_lMaxLayer;}
	//绘画筹码
	void DrawGoldView(CDC * pDC, int nXPos, int nYPos, bool bCount,bool bCenter=false,BYTE bDUser=0);
	//整性变字符
	LPCTSTR GetGlodString(__int64 lGold, TCHAR szString[]);

	//内部函数
private:
	//调整筹码层
	void RectifyGoldLayer();
};

//////////////////////////////////////////////////////////////////////////

#endif