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
	/// 实体类 StreamMatchFeeInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class StreamMatchFeeInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "StreamMatchFeeInfo" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 比赛标识
		/// </summary>
		public const string _MatchID = "MatchID" ;

		/// <summary>
		/// 比赛序号
		/// </summary>
		public const string _MatchNo = "MatchNo" ;

		/// <summary>
		/// 报名费
		/// </summary>
		public const string _Fee = "Fee" ;

		/// <summary>
		/// 收录时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_recordID;					//记录标识
		private int m_userID;					//用户标识
		private int m_serverID;					//房间标识
		private int m_matchID;					//比赛标识
		private int m_matchNo;					//比赛序号
		private int m_fee;						//报名费
		private DateTime m_collectDate;			//收录时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化StreamMatchFeeInfo
		/// </summary>
		public StreamMatchFeeInfo()
		{
			m_recordID=0;
			m_userID=0;
			m_serverID=0;
			m_matchID=0;
			m_matchNo=0;
			m_fee=0;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 记录标识
		/// </summary>
		public int RecordID
		{
			get { return m_recordID; }
			set { m_recordID = value; }
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
		/// 房间标识
		/// </summary>
		public int ServerID
		{
			get { return m_serverID; }
			set { m_serverID = value; }
		}

		/// <summary>
		/// 比赛标识
		/// </summary>
		public int MatchID
		{
			get { return m_matchID; }
			set { m_matchID = value; }
		}

		/// <summary>
		/// 比赛序号
		/// </summary>
		public int MatchNo
		{
			get { return m_matchNo; }
			set { m_matchNo = value; }
		}

		/// <summary>
		/// 报名费
		/// </summary>
		public int Fee
		{
			get { return m_fee; }
			set { m_fee = value; }
		}

		/// <summary>
		/// 收录时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
