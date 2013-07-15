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
	/// 实体类 MatchInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class MatchInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "MatchInfo" ;

		/// <summary>
		/// 比赛标识
		/// </summary>
		public const string _MatchID = "MatchID" ;

		/// <summary>
		/// 比赛名称
		/// </summary>
		public const string _MatchName = "MatchName" ;

		/// <summary>
		/// 比赛描述
		/// </summary>
		public const string _MatchSummary = "MatchSummary" ;

		/// <summary>
		/// 比赛时间
		/// </summary>
		public const string _MatchDate = "MatchDate" ;

		/// <summary>
		/// 比赛说明
		/// </summary>
		public const string _MatchContent = "MatchContent" ;

		/// <summary>
		/// 赛事状态(0:未开始,1:进行中,2:结束)
		/// </summary>
		public const string _MatchStatus = "MatchStatus" ;

		/// <summary>
		/// 禁用状态
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 新增日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_matchID;					//比赛标识
		private string m_matchName;				//比赛名称
		private string m_matchSummary;			//比赛描述
		private string m_matchDate;				//比赛时间
		private string m_matchContent;			//比赛说明
		private int m_matchStatus;				//赛事状态(0:未开始,1:进行中,2:结束)
		private byte m_nullity;					//禁用状态
		private DateTime m_collectDate;			//新增日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化MatchInfo
		/// </summary>
		public MatchInfo()
		{
			m_matchID=0;
			m_matchName="";
			m_matchSummary="";
			m_matchDate="";
			m_matchContent="";
			m_matchStatus=0;
			m_nullity=0;
			m_collectDate=DateTime.Now;
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
		/// 比赛名称
		/// </summary>
		public string MatchName
		{
			get { return m_matchName; }
			set { m_matchName = value; }
		}

		/// <summary>
		/// 比赛描述
		/// </summary>
		public string MatchSummary
		{
			get { return m_matchSummary; }
			set { m_matchSummary = value; }
		}

		/// <summary>
		/// 比赛时间
		/// </summary>
		public string MatchDate
		{
			get { return m_matchDate; }
			set { m_matchDate = value; }
		}

		/// <summary>
		/// 比赛说明
		/// </summary>
		public string MatchContent
		{
			get { return m_matchContent; }
			set { m_matchContent = value; }
		}

		/// <summary>
		/// 赛事状态(0:未开始,1:进行中,2:结束)
		/// </summary>
		public int MatchStatus
		{
			get { return m_matchStatus; }
			set { m_matchStatus = value; }
		}

		/// <summary>
		/// 禁用状态
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 新增日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
