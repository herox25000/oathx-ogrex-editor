#ifndef RECORD_GAME_LIST_HEAD_FILE
#define RECORD_GAME_LIST_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//游戏记录
struct tagGameRecord
{
	//游戏信息
	WORD							wDrawCount;							//游戏局数	
	BYTE							cbWinerSide;						//胜利玩家
	BYTE							cbPlayerPoint;						//闲家牌点
	BYTE							cbBankerPoint;						//庄家牌点	

	//我的信息
	__int64							lGameScore;							//游戏成绩	
	__int64							lMyAddGold;							//游戏下注	

	//下注总量
	__int64							lDrawBigTigerScore;					//买大老虎总注
	__int64							lDrawSmlTigerScore;					//买小老虎总注
	__int64							lDrawBigBogScore;					//买大狗总注
	__int64							lDrawSmlBogScore;					//买大狗总注
	__int64							lDrawBigHorseScore;					//买大马总注
	__int64							lDrawSmlHorseScore;					//买小马总注
	__int64							lDrawBigSnakeScore;					//买大蛇总注
	__int64							lDrawSmlSnakeScore;					//买小蛇总注
};

//////////////////////////////////////////////////////////////////////////

//游戏记录
class CGameRecord : public CSkinDialogEx
{
	//控件变量
public:
	CSkinListCtrl					m_RecordGameList;					//游戏列表

	//函数定义
public:
	//构造函数
	CGameRecord();
	//析构函数
	virtual ~CGameRecord();

	//重载函数
protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();
	//确定消息
	virtual void OnOK() { return; }
	//取消消息
	virtual void OnCancel() { return; }

	//功能函数
public:
	//插入列表
	void FillGameRecourd(tagGameRecord & GameRecord);

	//消息映射
protected:
	//位置变化
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif