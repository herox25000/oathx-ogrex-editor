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
	/// 实体类 StreamMatchHistory。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class StreamMatchHistory  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "StreamMatchHistory" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 比赛ID
		/// </summary>
		public const string _MatchID = "MatchID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MatchNo = "MatchNo" ;

		/// <summary>
		/// 比赛名次
		/// </summary>
		public const string _Rank = "Rank" ;

		/// <summary>
		/// 比赛得分
		/// </summary>
		public const string _MatchScore = "MatchScore" ;

		/// <summary>
		/// 奖励经验
		/// </summary>
		public const string _Experience = "Experience" ;

		/// <summary>
		/// 奖励金币
		/// </summary>
		public const string _Gold = "Gold" ;

		/// <summary>
		/// 奖励奖牌
		/// </summary>
		public const string _Medal = "Medal" ;

		/// <summary>
		/// 房间ID
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间ID
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 连接地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _RecordDate = "RecordDate" ;
		#endregion

		#region 私有变量
		private int m_userID;				//
		private int m_matchID;				//比赛ID
		private int m_matchNo;				//
		private int m_rank;					//比赛名次
		private int m_matchScore;			//比赛得分
		private int m_experience;			//奖励经验
		private int m_gold;					//奖励金币
		private int m_medal;				//奖励奖牌
		private int m_kindID;				//房间ID
		private int m_serverID;				//房间ID
		private string m_clientIP;			//连接地址
		private DateTime m_recordDate;		//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化StreamMatchHistory
		/// </summary>
		public StreamMatchHistory()
		{
			m_userID=0;
			m_matchID=0;
			m_matchNo=0;
			m_rank=0;
			m_matchScore=0;
			m_experience=0;
			m_gold=0;
			m_medal=0;
			m_kindID=0;
			m_serverID=0;
			m_clientIP="";
			m_recordDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 比赛ID
		/// </summary>
		public int MatchID
		{
			get { return m_matchID; }
			set { m_matchID = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int MatchNo
		{
			get { return m_matchNo; }
			set { m_matchNo = value; }
		}

		/// <summary>
		/// 比赛名次
		/// </summary>
		public int Rank
		{
			get { return m_rank; }
			set { m_rank = value; }
		}

		/// <summary>
		/// 比赛得分
		/// </summary>
		public int MatchScore
		{
			get { return m_matchScore; }
			set { m_matchScore = value; }
		}

		/// <summary>
		/// 奖励经验
		/// </summary>
		public int Experience
		{
			get { return m_experience; }
			set { m_experience = value; }
		}

		/// <summary>
		/// 奖励金币
		/// </summary>
		public int Gold
		{
			get { return m_gold; }
			set { m_gold = value; }
		}

		/// <summary>
		/// 奖励奖牌
		/// </summary>
		public int Medal
		{
			get { return m_medal; }
			set { m_medal = value; }
		}

		/// <summary>
		/// 房间ID
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 房间ID
		/// </summary>
		public int ServerID
		{
			get { return m_serverID; }
			set { m_serverID = value; }
		}

		/// <summary>
		/// 连接地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public DateTime RecordDate
		{
			get { return m_recordDate; }
			set { m_recordDate = value; }
		}
		#endregion
	}
}
