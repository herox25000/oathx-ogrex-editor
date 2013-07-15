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
	/// 实体类 GameHistoryScore。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameHistoryScore  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameHistoryScore" ;

		/// <summary>
		/// 比赛标识
		/// </summary>
		public const string _MatchID = "MatchID" ;

		/// <summary>
		/// 比赛场次
		/// </summary>
		public const string _MatchNo = "MatchNo" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 历史积分
		/// </summary>
		public const string _HScore = "HScore" ;

		/// <summary>
		/// 历史赢局
		/// </summary>
		public const string _HWinCount = "HWinCount" ;

		/// <summary>
		/// 历史输局
		/// </summary>
		public const string _HLostCount = "HLostCount" ;

		/// <summary>
		/// 历史和局
		/// </summary>
		public const string _HDrawCount = "HDrawCount" ;

		/// <summary>
		/// 历史逃局
		/// </summary>
		public const string _HFleeCount = "HFleeCount" ;

		/// <summary>
		/// 开始日期
		/// </summary>
		public const string _HBackupTime = "HBackupTime" ;

		/// <summary>
		/// 现在积分
		/// </summary>
		public const string _NScore = "NScore" ;

		/// <summary>
		/// 现在赢局
		/// </summary>
		public const string _NWinCount = "NWinCount" ;

		/// <summary>
		/// 现在输局
		/// </summary>
		public const string _NLostCount = "NLostCount" ;

		/// <summary>
		/// 现在和局
		/// </summary>
		public const string _NDrawCount = "NDrawCount" ;

		/// <summary>
		/// 现在逃局
		/// </summary>
		public const string _NFleeCount = "NFleeCount" ;

		/// <summary>
		/// 结束日期
		/// </summary>
		public const string _NBackupTime = "NBackupTime" ;
		#endregion

		#region 私有变量
		private int m_matchID;					//比赛标识
		private int m_matchNo;					//比赛场次
		private int m_userID;					//用户标识
		private long m_hScore;					//历史积分
		private int m_hWinCount;				//历史赢局
		private int m_hLostCount;				//历史输局
		private int m_hDrawCount;				//历史和局
		private int m_hFleeCount;				//历史逃局
		private DateTime m_hBackupTime;			//开始日期
		private long m_nScore;					//现在积分
		private int m_nWinCount;				//现在赢局
		private int m_nLostCount;				//现在输局
		private int m_nDrawCount;				//现在和局
		private int m_nFleeCount;				//现在逃局
		private DateTime m_nBackupTime;			//结束日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameHistoryScore
		/// </summary>
		public GameHistoryScore()
		{
			m_matchID=0;
			m_matchNo=0;
			m_userID=0;
			m_hScore=0;
			m_hWinCount=0;
			m_hLostCount=0;
			m_hDrawCount=0;
			m_hFleeCount=0;
			m_hBackupTime=DateTime.Now;
			m_nScore=0;
			m_nWinCount=0;
			m_nLostCount=0;
			m_nDrawCount=0;
			m_nFleeCount=0;
			m_nBackupTime=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 比赛标识
		/// </summary>
		public int MatchID
		{
			get { return m_matchID; }
			set { m_matchID = value; }
		}

		/// <summary>
		/// 比赛场次
		/// </summary>
		public int MatchNo
		{
			get { return m_matchNo; }
			set { m_matchNo = value; }
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
		/// 历史积分
		/// </summary>
		public long HScore
		{
			get { return m_hScore; }
			set { m_hScore = value; }
		}

		/// <summary>
		/// 历史赢局
		/// </summary>
		public int HWinCount
		{
			get { return m_hWinCount; }
			set { m_hWinCount = value; }
		}

		/// <summary>
		/// 历史输局
		/// </summary>
		public int HLostCount
		{
			get { return m_hLostCount; }
			set { m_hLostCount = value; }
		}

		/// <summary>
		/// 历史和局
		/// </summary>
		public int HDrawCount
		{
			get { return m_hDrawCount; }
			set { m_hDrawCount = value; }
		}

		/// <summary>
		/// 历史逃局
		/// </summary>
		public int HFleeCount
		{
			get { return m_hFleeCount; }
			set { m_hFleeCount = value; }
		}

		/// <summary>
		/// 开始日期
		/// </summary>
		public DateTime HBackupTime
		{
			get { return m_hBackupTime; }
			set { m_hBackupTime = value; }
		}

		/// <summary>
		/// 现在积分
		/// </summary>
		public long NScore
		{
			get { return m_nScore; }
			set { m_nScore = value; }
		}

		/// <summary>
		/// 现在赢局
		/// </summary>
		public int NWinCount
		{
			get { return m_nWinCount; }
			set { m_nWinCount = value; }
		}

		/// <summary>
		/// 现在输局
		/// </summary>
		public int NLostCount
		{
			get { return m_nLostCount; }
			set { m_nLostCount = value; }
		}

		/// <summary>
		/// 现在和局
		/// </summary>
		public int NDrawCount
		{
			get { return m_nDrawCount; }
			set { m_nDrawCount = value; }
		}

		/// <summary>
		/// 现在逃局
		/// </summary>
		public int NFleeCount
		{
			get { return m_nFleeCount; }
			set { m_nFleeCount = value; }
		}

		/// <summary>
		/// 结束日期
		/// </summary>
		public DateTime NBackupTime
		{
			get { return m_nBackupTime; }
			set { m_nBackupTime = value; }
		}
		#endregion
	}
}
