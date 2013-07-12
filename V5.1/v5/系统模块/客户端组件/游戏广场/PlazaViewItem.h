#ifndef PLAZA_VIEW_ITEM_HEAD_FILE
#define PLAZA_VIEW_ITEM_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerListData.h"

//////////////////////////////////////////////////////////////////////////////////

//常量定义
#define VIEW_MODE_NONE				0									//无效模式
#define VIEW_MODE_KIND				1									//类型模式
#define VIEW_MODE_SERVER			2									//房间模式

//按钮标识
#define BT_VIEW_RULE				1									//查看规则
#define BT_ENTER_KIND				2									//进入类型
#define BT_ENTER_SERVER				3									//进入房间

//////////////////////////////////////////////////////////////////////////////////

//类型定义
struct tagGameKindInfo
{
	WORD							wSortID;							//排序标识
	CPngImage						ImageKindItem;						//类型图片
	CGameKindItem *					pGameKindItem;						//类型对象
};

//房间定义
struct tagGameServerInfo
{
	WORD							wSortID;							//排序标识
	WORD							wServerID;							//房间标识
	CGameServerItem *				pGameServerItem;					//房间对象
};

//数组定义
typedef CWHArray<tagGameKindInfo *>	CGameKindInfoArray;					//类型数组
typedef CWHArray<tagGameServerInfo *> CGameServerInfoArray;				//房间数组

//////////////////////////////////////////////////////////////////////////////////

//游戏广场
class CPlazaViewItem : public CDialog, public IUnknownEx
{
	//状态变量
protected:
	bool							m_bHovering;						//盘旋标志
	bool							m_bCreateFlag;						//创建标志
	BYTE							m_cbShowItemMode;					//显示模式

	//移动位置
protected:
	BYTE							m_cbButtonDown;						//按钮掩码
	BYTE							m_cbButtonHover;					//按钮掩码
	WORD							m_wViewItemDown;					//点击子项
	WORD							m_wViewItemHover;					//盘旋子项

	//位置变量
protected:
	WORD							m_wKindXCount;						//类型列数
	WORD							m_wKindYCount;						//类型行数
	WORD							m_wKindExcursion;					//类型偏移
	WORD							m_wKindPageCount;					//类型页数
	WORD							m_wKindPageCurrent;					//当前页数
	WORD                            m_wKindTypeCurrentID;               //当前类型

	//位置变量
protected:
	WORD							m_wServerXCount;					//房间列数
	WORD							m_wServerYCount;					//房间行数
	WORD							m_wServerExcursion;					//房间偏移
	WORD							m_wServerPageCount;					//房间页数
	WORD							m_wServerPageCurrent;				//当前页数

	//资源变量
protected:
	CPngImage						m_ImageTitle;						//房间图片
	CPngImage						m_ImageServer;						//房间图片

	//按钮变量
protected:
	CSkinButton						m_btLastKind;						//上页按钮
	CSkinButton						m_btNextKind;						//下页按钮
	CSkinButton                     m_btReturnHall;                     //返回按钮
	CSkinButton						m_btLastServer;						//上页按钮
	CSkinButton						m_btNextServer;						//下页按钮

	//变量定义
protected:
	CGameKindInfoArray				m_GameKindInfoActive;				//类型数组
	CGameKindInfoArray				m_GameKindInfoBuffer;				//类型数组
	CGameServerInfoArray			m_GameServerInfoActive;				//房间数组
	CGameServerInfoArray			m_GameServerInfoBuffer;				//房间数组

	//控件指针
protected:
	static CPlazaViewItem *			m_pPlazaViewItem;					//广场指针

	//函数定义
public:
	//构造函数
	CPlazaViewItem();
	//析构函数
	virtual ~CPlazaViewItem();

	//基础接口
public:
	//释放对象
	virtual VOID Release() { delete this; }
	//接口查询
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//重载函数
protected:
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK() { return; };
	//取消函数
	virtual VOID OnCancel() { return; };

	//功能函数
public:
	//显示类型
	VOID ShowKindItemView(WORD wTypeID,BOOL bResetPageIndex=TRUE);
	//显示房间
	VOID ShowServerItemView(WORD wKindID,BOOL bResetPageIndex=FALSE);
	//界面更新
	VOID InValidateWndView(BYTE cbViewType);

	//功能函数
public:
	//获取实例
	static CPlazaViewItem * GetInstance() { return m_pPlazaViewItem; }	

	//绘画函数
private:
	//绘画类型
	VOID DrawKindItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameKindInfo * pGameKindInfo);
	//绘画房间
	VOID DrawServerItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameServerInfo * pGameServerInfo);

	//内部函数
protected:
	//调整控件
	VOID RectifyControl(INT nWidth, INT nHeight);
	//资源目录
	VOID GetGameDirectory(TCHAR szDirectory[], WORD wBufferCount, tagGameKind & GameKind);

	//位置测试
protected:
	//对象索引
	WORD GetHoverIndex(CPoint MousePoint);
	//按钮测试
	BYTE GetHoverButton(WORD wViewIndex, CPoint MousePoint);

	//按钮消息
protected:
	//查看规则
	VOID OnButtonViewRule(WORD wKindID);
	//进入类型
	VOID OnButtonEnterKind(WORD wKindID);
	//进入房间
	VOID OnButtonEnterServer(WORD wServerID);

	//按钮消息
protected:
	//上页按钮
	VOID OnBnClickedLastKind();
	//下页按钮
	VOID OnBnClickedNextKind();
	//返回按钮
	VOID OnBnClickedReturnHall();
	//上页按钮
	VOID OnBnClickedLastServer();
	//下页按钮
	VOID OnBnClickedNextServer();	

	//消息函数
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//鼠标移动
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标离开
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif