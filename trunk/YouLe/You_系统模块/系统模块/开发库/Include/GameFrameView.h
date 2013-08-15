#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameFrame.h"
#include "Irrlicht.h"
//////////////////////////////////////////////////////////////////////////

//动画结构
struct tagFlowerEffectInfo
{
	//移动信息
	WORD							wMoveCount;							//移动次数
	WORD							wMoveIndex;							//移动索引
	CPoint							ptFrom;								//出发位置
	CPoint							ptDest;								//目的位置
	CPoint							ptCurPos;							//当前位置

	//属性信息
	WORD							wSourceChairID;						//起始位置
	WORD							wTargetChairID;						//结束位置
	UINT							uFlowerID;							//鲜花标识
	UINT							uFlowerEffectID;					//动画标识
	bool							bBombEffect;						//爆炸标识
};

//绘画模式
enum enImageMode 
{
	enMode_Spread,					//平铺模式
	enMode_Centent,					//居中模式
	enMode_ElongGate,				//拉伸模式
};

//类说明
class CClientKernelSink;

//////////////////////////////////////////////////////////////////////////

//游戏视图框架
class GAME_FRAME_CLASS CGameFrameView : public CWnd, public IGameFrameView
{
	//友元定义
	friend class CGameFrameDlg;
	friend class CClientKernelSink;

	//位置变量
protected:
	UINT							m_nAnimeStep;						//移动间距
	POINT							m_ptName[MAX_CHAIR];				//名字位置
	POINT							m_ptFace[MAX_CHAIR];				//头像位置
	POINT							m_ptTimer[MAX_CHAIR];				//时间位置
	POINT							m_ptReady[MAX_CHAIR];				//准备位置

protected:
	irr::IrrlichtDevice*			m_pIrrlichtDevice;					//3D引擎设备
	irr::video::IVideoDriver*		m_pVideoDriver;						
	//用户变量
private:
	WORD							m_wTimer[MAX_CHAIR];				//用户时间
	tagUserData*					m_pUserItem[MAX_CHAIR];				//用户信息

	//组件指针
private:
	void*							m_pReserve;							//保留指针
	IUserFaceRes*					m_pIUserFaceRes;					//头像接口

	//只读变量
public:
	static const int				m_nXFace;							//头像高度
	static const int				m_nYFace;							//头像宽度
	static const int				m_nXTimer;							//定时器宽
	static const int				m_nYTimer;							//定时器高
	static const int				m_nXBorder;							//框架宽度
	static const int				m_nYBorder;							//框架高度

	//函数定义
public:
	//构造函数
	CGameFrameView();
	//析构函数
	virtual ~CGameFrameView();

	//基础接口
public:
	//释放对象
	virtual void __cdecl			Release()
	{ 
		delete this; 
	}
	
	//接口查询
	virtual void* __cdecl			QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//游戏惠子
	virtual bool					DrawAll();
public:
	//获取时间
	WORD GetUserTimer(WORD wChairID);
	//获取玩家
	const tagUserData* GetUserInfo(WORD wChairID);

	//内部函数
private:
	//重置界面
	void ResetData();
	//设置接口
	bool SetUserFaceRes(IUnknownEx * pIUnknownEx);
	//设置时间
	bool SetUserTimer(WORD wChairID, WORD wTimer);
	//设置用户
	bool SetUserInfo(WORD wChairID, tagUserData * pUserData);

	//消息映射
protected:
	//绘画函数
	afx_msg void					OnPaint();
	//位置变化
	afx_msg void					OnSize(UINT nType, int cx, int cy);
	//创建消息
	afx_msg int						OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标消息
	afx_msg void					OnLButtonDown(UINT nFlags, CPoint point);
	//销毁消息
	afx_msg void					OnDestroy();
	//时间消息
	afx_msg void					OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif