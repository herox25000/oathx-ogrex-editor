#pragma once

#include <vector>

//类说明
class CTimerEngine;
class CGameBase;
//////////////////////////////////////////////////////////////////////////

//定时器线程
class CTimerThread : public CServiceThread
{
	//变量定义
protected:
	DWORD								m_dwTimerSpace;					//时间间隔
	CTimerEngine						* m_pTimerEngine;				//定时器引擎

	//函数定义
public:
	//构造函数
	CTimerThread(void);
	//析构函数
	virtual ~CTimerThread(void);

	//功能函数
public:
	//配置函数
	bool InitThread(CTimerEngine * pTimerEngine, DWORD dwTimerSpace);

	//重载函数
private:
	////运行函数
	//virtual bool RepetitionRun();
	//运行函数
	virtual bool OnEventThreadRun();
};

//定时器子项
struct tagTimerItem
{
	WORD								wTimerID;						//定时器 ID
	DWORD								dwElapse;						//定时时间
	DWORD								dwTimeLeave;					//倒计时间
	DWORD								dwRepeatTimes;					//重复次数
	CGameBase							*pGame;							//游戏指针
};

typedef std::vector<tagTimerItem*> CTimerItemPtr;

class CTimerEngine
{
	friend class CTimerThread;

	//配置定义
protected:
	DWORD								m_dwTimerSpace;					//时间间隔

	//状态变量
protected:
	bool								m_bService;						//运行标志
	DWORD								m_dwTimePass;					//经过时间
	DWORD								m_dwTimeLeave;					//倒计时间
	CTimerItemPtr						m_TimerItemFree;				//空闲数组
	CTimerItemPtr						m_TimerItemActive;				//活动数组

	//组件变量
protected:
	CTimerThread						m_TimerThread;					//定时器线程
	CCriticalSection					m_CriticalSection; //	//线程锁
public:
	CTimerEngine(void);
	~CTimerEngine(void);

	//接口函数
public:
	//设置定时器
	virtual bool SetTimer(CGameBase *pGame, WORD wTimerID, DWORD dwElapse, DWORD dwRepeat);
	//删除定时器
	virtual bool KillTimer(CGameBase *pGame, WORD wTimerID);
	//删除定时器
	virtual bool KillAllTimer();

	//开始服务
	virtual bool BeginService();
	//停止服务
	virtual bool EndService();

	//内部函数
private:
	//定时器通知
	void OnTimerThreadSink();
};
