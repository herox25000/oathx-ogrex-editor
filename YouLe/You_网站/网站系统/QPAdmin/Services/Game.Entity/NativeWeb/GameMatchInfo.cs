/*
 * 版本：4.0
 * 时间：2011-9-30
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.NativeWeb
{
	/// <summary>
	/// 实体类 GameMatchInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameMatchInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameMatchInfo" ;

		/// <summary>
		/// 比赛标识
		/// </summary>
		public const string _MatchID = "MatchID" ;

		/// <summary>
		/// 比赛标题
		/// </summary>
		public const string _MatchTitle = "MatchTitle" ;

		/// <summary>
		/// 比赛摘要
		/// </summary>
		public const string _MatchSummary = "MatchSummary" ;

		/// <summary>
		/// 比赛内容
		/// </summary>
		public const string _MatchContent = "MatchContent" ;

		/// <summary>
		/// 报名开始时间
		/// </summary>
		public const string _ApplyBeginDate = "ApplyBeginDate" ;

		/// <summary>
		/// 报名截止时间
		/// </summary>
		public const string _ApplyEndDate = "ApplyEndDate" ;

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

		/// <summary>
		/// 修改日期
		/// </summary>
		public const string _ModifyDate = "ModifyDate" ;
		#endregion

		#region 私有变量
		private int m_matchID;						//比赛标识
		private string m_matchTitle;				//比赛标题
		private string m_matchSummary;				//比赛摘要
		private string m_matchContent;				//比赛内容
		private DateTime m_applyBeginDate;			//报名开始时间
		private DateTime m_applyEndDate;			//报名截止时间
		private int m_matchStatus;					//赛事状态(0:未开始,1:进行中,2:结束)
		private byte m_nullity;						//禁用状态
		private DateTime m_collectDate;				//新增日期
		private DateTime m_modifyDate;				//修改日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameMatchInfo
		/// </summary>
		public GameMatchInfo()
		{
			m_matchID=0;
			m_matchTitle="";
			m_matchSummary="";
			m_matchContent="";
			m_applyBeginDate=DateTime.Now;
			m_applyEndDate=DateTime.Now;
			m_matchStatus=0;
			m_nullity=0;
			m_collectDate=DateTime.Now;
			m_modifyDate=DateTime.Now;
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
		/// 比赛标题
		/// </summary>
		public string MatchTitle
		{
			get { return m_matchTitle; }
			set { m_matchTitle = value; }
		}

		/// <summary>
		/// 比赛摘要
		/// </summary>
		public string MatchSummary
		{
			get { return m_matchSummary; }
			set { m_matchSummary = value; }
		}

		/// <summary>
		/// 比赛内容
		/// </summary>
		public string MatchContent
		{
			get { return m_matchContent; }
			set { m_matchContent = value; }
		}

		/// <summary>
		/// 报名开始时间
		/// </summary>
		public DateTime ApplyBeginDate
		{
			get { return m_applyBeginDate; }
			set { m_applyBeginDate = value; }
		}

		/// <summary>
		/// 报名截止时间
		/// </summary>
		public DateTime ApplyEndDate
		{
			get { return m_applyEndDate; }
			set { m_applyEndDate = value; }
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

		/// <summary>
		/// 修改日期
		/// </summary>
		public DateTime ModifyDate
		{
			get { return m_modifyDate; }
			set { m_modifyDate = value; }
		}
		#endregion
	}
}
