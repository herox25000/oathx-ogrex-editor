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
	/// 实体类 RecordUserInout。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordUserInout  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordUserInout" ;

		/// <summary>
		/// 索引标识
		/// </summary>
		public const string _ID = "ID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 进入时间
		/// </summary>
		public const string _EnterTime = "EnterTime" ;

		/// <summary>
		/// 进入积分
		/// </summary>
		public const string _EnterScore = "EnterScore" ;

		/// <summary>
		/// 进入银行
		/// </summary>
		public const string _EnterInsure = "EnterInsure" ;

		/// <summary>
		/// 进入奖牌
		/// </summary>
		public const string _EnterUserMedal = "EnterUserMedal" ;

		/// <summary>
		/// 进入魅力
		/// </summary>
		public const string _EnterLoveliness = "EnterLoveliness" ;

		/// <summary>
		/// 进入机器
		/// </summary>
		public const string _EnterMachine = "EnterMachine" ;

		/// <summary>
		/// 登录地址
		/// </summary>
		public const string _EnterClientIP = "EnterClientIP" ;

		/// <summary>
		/// 离开时间
		/// </summary>
		public const string _LeaveTime = "LeaveTime" ;

		/// <summary>
		/// 离开原因
		/// </summary>
		public const string _LeaveReason = "LeaveReason" ;

		/// <summary>
		/// 进入机器
		/// </summary>
		public const string _LeaveMachine = "LeaveMachine" ;

		/// <summary>
		/// 登录地址
		/// </summary>
		public const string _LeaveClientIP = "LeaveClientIP" ;

		/// <summary>
		/// 变更积分
		/// </summary>
		public const string _Score = "Score" ;

		/// <summary>
		/// 银行变更
		/// </summary>
		public const string _Insure = "Insure" ;

		/// <summary>
		/// 变更税收
		/// </summary>
		public const string _Revenue = "Revenue" ;

		/// <summary>
		/// 胜局变更
		/// </summary>
		public const string _WinCount = "WinCount" ;

		/// <summary>
		/// 输局变更
		/// </summary>
		public const string _LostCount = "LostCount" ;

		/// <summary>
		/// 和局变更
		/// </summary>
		public const string _DrawCount = "DrawCount" ;

		/// <summary>
		/// 逃局变更
		/// </summary>
		public const string _FleeCount = "FleeCount" ;

		/// <summary>
		/// 奖牌数目
		/// </summary>
		public const string _UserMedal = "UserMedal" ;

		/// <summary>
		/// 魅力变更
		/// </summary>
		public const string _LoveLiness = "LoveLiness" ;

		/// <summary>
		/// 经验变更
		/// </summary>
		public const string _Experience = "Experience" ;

		/// <summary>
		/// 游戏时间
		/// </summary>
		public const string _PlayTimeCount = "PlayTimeCount" ;

		/// <summary>
		/// 在线时间
		/// </summary>
		public const string _OnLineTimeCount = "OnLineTimeCount" ;
		#endregion

		#region 私有变量
		private int m_iD;						//索引标识
		private int m_userID;					//用户标识
		private int m_kindID;					//类型标识
		private int m_serverID;					//房间标识
		private DateTime m_enterTime;			//进入时间
		private long m_enterScore;				//进入积分
		private long m_enterInsure;				//进入银行
		private int m_enterUserMedal;			//进入奖牌
		private int m_enterLoveliness;			//进入魅力
		private string m_enterMachine;			//进入机器
		private string m_enterClientIP;			//登录地址
		private DateTime m_leaveTime;			//离开时间
		private int m_leaveReason;				//离开原因
		private string m_leaveMachine;			//进入机器
		private string m_leaveClientIP;			//登录地址
		private long m_score;					//变更积分
		private long m_insure;					//银行变更
		private long m_revenue;					//变更税收
		private int m_winCount;					//胜局变更
		private int m_lostCount;				//输局变更
		private int m_drawCount;				//和局变更
		private int m_fleeCount;				//逃局变更
		private int m_userMedal;				//奖牌数目
		private int m_loveLiness;				//魅力变更
		private int m_experience;				//经验变更
		private int m_playTimeCount;			//游戏时间
		private int m_onLineTimeCount;			//在线时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordUserInout
		/// </summary>
		public RecordUserInout()
		{
			m_iD=0;
			m_userID=0;
			m_kindID=0;
			m_serverID=0;
			m_enterTime=DateTime.Now;
			m_enterScore=0;
			m_enterInsure=0;
			m_enterUserMedal=0;
			m_enterLoveliness=0;
			m_enterMachine="";
			m_enterClientIP="";
			m_leaveTime=DateTime.Now;
			m_leaveReason=0;
			m_leaveMachine="";
			m_leaveClientIP="";
			m_score=0;
			m_insure=0;
			m_revenue=0;
			m_winCount=0;
			m_lostCount=0;
			m_drawCount=0;
			m_fleeCount=0;
			m_userMedal=0;
			m_loveLiness=0;
			m_experience=0;
			m_playTimeCount=0;
			m_onLineTimeCount=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 索引标识
		/// </summary>
		public int ID
		{
			get { return m_iD; }
			set { m_iD = value; }
		}

		/// <summary>
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 类型标识
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 房间标识
		/// </summary>
		public int ServerID
		{
			get { return m_serverID; }
			set { m_serverID = value; }
		}

		/// <summary>
		/// 进入时间
		/// </summary>
		public DateTime EnterTime
		{
			get { return m_enterTime; }
			set { m_enterTime = value; }
		}

		/// <summary>
		/// 进入积分
		/// </summary>
		public long EnterScore
		{
			get { return m_enterScore; }
			set { m_enterScore = value; }
		}

		/// <summary>
		/// 进入银行
		/// </summary>
		public long EnterInsure
		{
			get { return m_enterInsure; }
			set { m_enterInsure = value; }
		}

		/// <summary>
		/// 进入奖牌
		/// </summary>
		public int EnterUserMedal
		{
			get { return m_enterUserMedal; }
			set { m_enterUserMedal = value; }
		}

		/// <summary>
		/// 进入魅力
		/// </summary>
		public int EnterLoveliness
		{
			get { return m_enterLoveliness; }
			set { m_enterLoveliness = value; }
		}

		/// <summary>
		/// 进入机器
		/// </summary>
		public string EnterMachine
		{
			get { return m_enterMachine; }
			set { m_enterMachine = value; }
		}

		/// <summary>
		/// 登录地址
		/// </summary>
		public string EnterClientIP
		{
			get { return m_enterClientIP; }
			set { m_enterClientIP = value; }
		}

		/// <summary>
		/// 离开时间
		/// </summary>
		public DateTime LeaveTime
		{
			get { return m_leaveTime; }
			set { m_leaveTime = value; }
		}

		/// <summary>
		/// 离开原因
		/// </summary>
		public int LeaveReason
		{
			get { return m_leaveReason; }
			set { m_leaveReason = value; }
		}

		/// <summary>
		/// 进入机器
		/// </summary>
		public string LeaveMachine
		{
			get { return m_leaveMachine; }
			set { m_leaveMachine = value; }
		}

		/// <summary>
		/// 登录地址
		/// </summary>
		public string LeaveClientIP
		{
			get { return m_leaveClientIP; }
			set { m_leaveClientIP = value; }
		}

		/// <summary>
		/// 变更积分
		/// </summary>
		public long Score
		{
			get { return m_score; }
			set { m_score = value; }
		}

		/// <summary>
		/// 银行变更
		/// </summary>
		public long Insure
		{
			get { return m_insure; }
			set { m_insure = value; }
		}

		/// <summary>
		/// 变更税收
		/// </summary>
		public long Revenue
		{
			get { return m_revenue; }
			set { m_revenue = value; }
		}

		/// <summary>
		/// 胜局变更
		/// </summary>
		public int WinCount
		{
			get { return m_winCount; }
			set { m_winCount = value; }
		}

		/// <summary>
		/// 输局变更
		/// </summary>
		public int LostCount
		{
			get { return m_lostCount; }
			set { m_lostCount = value; }
		}

		/// <summary>
		/// 和局变更
		/// </summary>
		public int DrawCount
		{
			get { return m_drawCount; }
			set { m_drawCount = value; }
		}

		/// <summary>
		/// 逃局变更
		/// </summary>
		public int FleeCount
		{
			get { return m_fleeCount; }
			set { m_fleeCount = value; }
		}

		/// <summary>
		/// 奖牌数目
		/// </summary>
		public int UserMedal
		{
			get { return m_userMedal; }
			set { m_userMedal = value; }
		}

		/// <summary>
		/// 魅力变更
		/// </summary>
		public int LoveLiness
		{
			get { return m_loveLiness; }
			set { m_loveLiness = value; }
		}

		/// <summary>
		/// 经验变更
		/// </summary>
		public int Experience
		{
			get { return m_experience; }
			set { m_experience = value; }
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
		#endregion
	}
}
