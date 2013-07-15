/*
 * 版本：4.0
 * 时间：2012-2-28
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.GameMatch
{
	/// <summary>
	/// 实体类 GameScoreInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameScoreInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameScoreInfo" ;

		/// <summary>
		/// 用户 ID
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 用户积分（货币）
		/// </summary>
		public const string _Score = "Score" ;

		/// <summary>
		/// 胜局数目
		/// </summary>
		public const string _WinCount = "WinCount" ;

		/// <summary>
		/// 输局数目
		/// </summary>
		public const string _LostCount = "LostCount" ;

		/// <summary>
		/// 和局数目
		/// </summary>
		public const string _DrawCount = "DrawCount" ;

		/// <summary>
		/// 逃局数目
		/// </summary>
		public const string _FleeCount = "FleeCount" ;

		/// <summary>
		/// 用户权限
		/// </summary>
		public const string _UserRight = "UserRight" ;

		/// <summary>
		/// 管理权限
		/// </summary>
		public const string _MasterRight = "MasterRight" ;

		/// <summary>
		/// 管理等级
		/// </summary>
		public const string _MasterOrder = "MasterOrder" ;

		/// <summary>
		/// 总登陆次数
		/// </summary>
		public const string _AllLogonTimes = "AllLogonTimes" ;

		/// <summary>
		/// 游戏时间
		/// </summary>
		public const string _PlayTimeCount = "PlayTimeCount" ;

		/// <summary>
		/// 在线时间
		/// </summary>
		public const string _OnLineTimeCount = "OnLineTimeCount" ;

		/// <summary>
		/// 上次登陆 IP
		/// </summary>
		public const string _LastLogonIP = "LastLogonIP" ;

		/// <summary>
		/// 上次登陆时间
		/// </summary>
		public const string _LastLogonDate = "LastLogonDate" ;

		/// <summary>
		/// 登录机器
		/// </summary>
		public const string _LastLogonMachine = "LastLogonMachine" ;

		/// <summary>
		/// 注册 IP
		/// </summary>
		public const string _RegisterIP = "RegisterIP" ;

		/// <summary>
		/// 注册时间
		/// </summary>
		public const string _RegisterDate = "RegisterDate" ;

		/// <summary>
		/// 注册机器
		/// </summary>
		public const string _RegisterMachine = "RegisterMachine" ;
		#endregion

		#region 私有变量
		private int m_userID;						//用户 ID
		private long m_score;						//用户积分（货币）
		private int m_winCount;						//胜局数目
		private int m_lostCount;					//输局数目
		private int m_drawCount;					//和局数目
		private int m_fleeCount;					//逃局数目
		private int m_userRight;					//用户权限
		private int m_masterRight;					//管理权限
		private byte m_masterOrder;					//管理等级
		private int m_allLogonTimes;				//总登陆次数
		private int m_playTimeCount;				//游戏时间
		private int m_onLineTimeCount;				//在线时间
		private string m_lastLogonIP;				//上次登陆 IP
		private DateTime m_lastLogonDate;			//上次登陆时间
		private string m_lastLogonMachine;			//登录机器
		private string m_registerIP;				//注册 IP
		private DateTime m_registerDate;			//注册时间
		private string m_registerMachine;			//注册机器
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameScoreInfo
		/// </summary>
		public GameScoreInfo()
		{
			m_userID=0;
			m_score=0;
			m_winCount=0;
			m_lostCount=0;
			m_drawCount=0;
			m_fleeCount=0;
			m_userRight=0;
			m_masterRight=0;
			m_masterOrder=0;
			m_allLogonTimes=0;
			m_playTimeCount=0;
			m_onLineTimeCount=0;
			m_lastLogonIP="";
			m_lastLogonDate=DateTime.Now;
			m_lastLogonMachine="";
			m_registerIP="";
			m_registerDate=DateTime.Now;
			m_registerMachine="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 用户 ID
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 用户积分（货币）
		/// </summary>
		public long Score
		{
			get { return m_score; }
			set { m_score = value; }
		}

		/// <summary>
		/// 胜局数目
		/// </summary>
		public int WinCount
		{
			get { return m_winCount; }
			set { m_winCount = value; }
		}

		/// <summary>
		/// 输局数目
		/// </summary>
		public int LostCount
		{
			get { return m_lostCount; }
			set { m_lostCount = value; }
		}

		/// <summary>
		/// 和局数目
		/// </summary>
		public int DrawCount
		{
			get { return m_drawCount; }
			set { m_drawCount = value; }
		}

		/// <summary>
		/// 逃局数目
		/// </summary>
		public int FleeCount
		{
			get { return m_fleeCount; }
			set { m_fleeCount = value; }
		}

		/// <summary>
		/// 用户权限
		/// </summary>
		public int UserRight
		{
			get { return m_userRight; }
			set { m_userRight = value; }
		}

		/// <summary>
		/// 管理权限
		/// </summary>
		public int MasterRight
		{
			get { return m_masterRight; }
			set { m_masterRight = value; }
		}

		/// <summary>
		/// 管理等级
		/// </summary>
		public byte MasterOrder
		{
			get { return m_masterOrder; }
			set { m_masterOrder = value; }
		}

		/// <summary>
		/// 总登陆次数
		/// </summary>
		public int AllLogonTimes
		{
			get { return m_allLogonTimes; }
			set { m_allLogonTimes = value; }
		}

		/// <summary>
		/// 游戏时间
		/// </summary>
		public int PlayTimeCount
		{
			get { return m_playTimeCount; }
			set { m_playTimeCount = value; }
		}

		/// <summary>
		/// 在线时间
		/// </summary>
		public int OnLineTimeCount
		{
			get { return m_onLineTimeCount; }
			set { m_onLineTimeCount = value; }
		}

		/// <summary>
		/// 上次登陆 IP
		/// </summary>
		public string LastLogonIP
		{
			get { return m_lastLogonIP; }
			set { m_lastLogonIP = value; }
		}

		/// <summary>
		/// 上次登陆时间
		/// </summary>
		public DateTime LastLogonDate
		{
			get { return m_lastLogonDate; }
			set { m_lastLogonDate = value; }
		}

		/// <summary>
		/// 登录机器
		/// </summary>
		public string LastLogonMachine
		{
			get { return m_lastLogonMachine; }
			set { m_lastLogonMachine = value; }
		}

		/// <summary>
		/// 注册 IP
		/// </summary>
		public string RegisterIP
		{
			get { return m_registerIP; }
			set { m_registerIP = value; }
		}

		/// <summary>
		/// 注册时间
		/// </summary>
		public DateTime RegisterDate
		{
			get { return m_registerDate; }
			set { m_registerDate = value; }
		}

		/// <summary>
		/// 注册机器
		/// </summary>
		public string RegisterMachine
		{
			get { return m_registerMachine; }
			set { m_registerMachine = value; }
		}
		#endregion
	}
}
