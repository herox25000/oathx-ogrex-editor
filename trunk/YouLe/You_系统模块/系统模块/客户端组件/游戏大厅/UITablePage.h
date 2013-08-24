#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	///////////////////////////////////////////////////////////////////
	//桌子资源
	//////////////////////////////////////////////////////////////////
	class CTableResource
	{
		//桌子属性
	public:
		CSize							m_SizeChair;						//椅子尺寸
		CSize							m_SizeTable;						//桌子尺寸
		CSize							m_SizeEnter;						//进入尺寸

		//属性变量
	public:
		bool							m_bShowUser;						//显示用户
		bool							m_bShowEnter;						//显示进入
		bool							m_bShowChair;						//显示椅子
		bool							m_bShowTable;						//显示桌子
		bool							m_bShowFocus;						//显示焦点
		bool							m_bCustomUser;						//自定用户
		bool							m_bShowTableID;						//显示桌号
		bool							m_bRenderImage;						//渲染标志

		//数目变量
	public:
		WORD							m_wTableItemCount;					//子项数目
		WORD							m_wChairItemCount;					//子项数目

		//类型数目
	public:
		WORD							m_wUserGenreCount;					//类型数目
		WORD							m_wTableGenreCount;					//类型数目
		WORD							m_wChairGenreCount;					//类型数目

		//位置属性
	public:
		CPoint							m_ptLock;							//桌锁位置
		CPoint							m_ptEnter;							//进入位置
		CPoint							m_ptTableID;						//桌号位置
		CPoint							m_ptReadyArray[MAX_CHAIR];			//准备位置

		//框架位置
	public:
		CRect							m_rcNameArray[MAX_CHAIR];			//名字位置
		CRect							m_rcChairArray[MAX_CHAIR];			//椅子位置

		//颜色属性
	public:
		COLORREF						m_crName;							//名字颜色
		COLORREF						m_crMember;							//会员颜色
		COLORREF						m_crMaster;							//管理颜色

		//辅助变量
	public:
		INT								m_nDrawStyle[MAX_CHAIR];			//输出格式
		TCHAR							m_szDirectory[MAX_PATH];			//资源路径

		//资源变量
	public:
		CSize							m_SizeBackSurface;					//表面大小
		CImage							m_ImageBackSurface;					//缓冲表面

		//外部资源
	public:
		CPngImage                       m_ImageChair;						//椅子位图 
		CPngImage						m_ImageEnter;						//进入位图
		CPngImage                       m_ImageTable;						//桌子位图
		//CBitImage						m_ImageGround;						//背景位图
		CPngImage						m_ImageGround;	
		CPngImage						m_ImageCustomUser;					//自定位图

		//内部资源
	public:
		CPngImage						m_ImageReady;						//准备位图
		CPngImage						m_ImageLocker;						//桌锁位图
		CPngImage						m_ImageNumberNB;					//号码位图
		CPngImage						m_ImageNumberBK;					//号码背景
		//CBitImage						m_ImageUserFace;					//用户头像
		CPngImage						m_ImageUserFace;					//用户头像
		//函数定义
	public:
		//构造函数
		CTableResource();
		//析构函数
		virtual ~CTableResource();

		//功能函数
	public:
		//释放资源
		VOID DestroyResource();
		//加载资源
		bool LoadResource(LPCTSTR szGameName, WORD wChairCount, bool bAvertCheatMode);
		//更新资源
		//bool UpdateResource(CSkinRenderManager * pSkinRenderManager);
		//加载图片
		bool LoadResourceImages();

		//辅助函数
	protected:
		//读取数值
		LONG ReadStringValue(LPCTSTR & pszSring);
		//读取矩形
		bool ReadRect(RECT & ValueRect, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile);
		//读取坐标
		bool ReadPoint(POINT & ValuePoint, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile);
		//读取颜色
		bool ReadColor(COLORREF & ValueColor, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile);
	};

	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子构造
	//////////////////////////////////////////////////////////////////////////
	class UITableItem : public UIWidget, public UIProcess
	{
	public:
		UITableItem(void);

		virtual ~UITableItem(void);

		// UIWidget 继承
	public:
		// 创建控件
		virtual	BOOL		Create(INT nID, INT nDestX, INT nDestY,
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		// 绘制
		virtual BOOL		Draw(CDC* pDC);
		// 鼠标移动
		virtual BOOL		OnMouseMove(const CPoint& cPt);
		// 鼠标离开
		virtual BOOL		OnMouseLeave(const CPoint& cPt);
		// 鼠标进入
		virtual BOOL		OnMouseEnter(const CPoint& cPt);
		// 左键按下
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		// 左键弹起
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	//	// UIProcess继承
	//public:
	//	// 左键按下
	//	virtual BOOL		OnLeftDown(UIWidget* pWidget,const CPoint& cPt);
	//	// 左键弹起
	//	virtual BOOL		OnLeftUp(UIWidget* pWidget,const CPoint& cPt);

		// 功能函数
	public:
		// 绘制桌子
		void				DrawTableView(CDC * pDC,INT nXTablePos,INT nYTablePos);
		// 绘制所有用户信息
		void				DrawAllUserInfo(CDC* pDC,INT nXTablePos,INT nYTablePos);
		// 绘制名字
		void				DrawUserName(CDC * pDC, WORD wChairID, LPCTSTR pszNickName);		
		// 绘制头像
		void				DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos,tagUserData* pUserData);
		// 查询椅子
		WORD				SwitchChairID(POINT MousePoint);

	protected:
		CPngImage			m_PngBill;
	

	public:
		TableInfo*			m_pTableInfo;	//桌子信息
		CTableResource*		m_pTableRes;	//桌子资源信息	
		CPngImage			m_UserHead;
		CFont				m_DrawFont;	
		WORD				m_wHoverChairID;
		bool				m_bMouseDown;
		bool				m_bFocus;		// 是否是焦点
	};


	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子视图构造
	//////////////////////////////////////////////////////////////////////////
	class UITablePage : public UIWidget, public UIProcess
	{
	public:
		UITablePage(void);

		virtual ~UITablePage(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
		
		// 绘制
		virtual BOOL		Draw(CDC* pDC);

		// 继承函数
	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// 显示时响应函数
		virtual void		VisibleTrigger();
		// 不可见时触发函数
		virtual void		InvisibleTrigger();	
		// 功能函数
	public:
		// 响应上一页
		void				OnClickLastPage();
		// 响应下一页
		void				OnClickNextPage();
		// 所有Item是否显示
		void				VisibleAllTableItem(bool bVisible);				
		// 枚举GameItem
		bool				EnumTableItem();
		// 显示首页
		void				ShowFirstTablePage();
		// 快速加入
		bool				OnFastJoin();
		// 设置房间信息
		void				SetRoomInfo();
		// 读取房间资源
		void				LoadTableRes();
		// 读取防作弊图片
		void				LoadNoCheatImage();	
		// 根据桌子的大小创建桌子
		bool				CreateTable();
	public:
		// 防作弊图片
		CPngImage			m_NoCheatImage;
		// 桌子容器 
		std::vector<UITableItem*>		m_TableItemVector;
		// 字体
		CFont				m_DrawFont;
		// 桌子资源
		CTableResource		m_TableResource;					
		// 枚举序列
		int					m_EnumIndex;
		// 返回按钮
		UIPngButton*		m_pBtBack;
		// 标题
		CPngImage			m_TilteImage;
		// 
		CListServer*		m_pListServer;
		//
		WORD				m_wTableCount;
		//
		WORD				m_wChairCount;
		// X上能创建的桌子张数
		INT					m_nXTableCount;
		// Y上能创建桌子的张数
		INT					m_nYTableCount;
	};
}