/*
 * 版本：4.0
 * 时间：2011-8-1
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.Record
{
	/// <summary>
	/// 实体类 RecordEncashPresent。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordEncashPresent  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordEncashPresent" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 当前金币数目
		/// </summary>
		public const string _CurGold = "CurGold" ;

		/// <summary>
		/// 当前礼物数目
		/// </summary>
		public const string _CurPresent = "CurPresent" ;

		/// <summary>
		/// 兑换金币数目
		/// </summary>
		public const string _EncashGold = "EncashGold" ;

		/// <summary>
		/// 兑换礼物数目
		/// </summary>
		public const string _EncashPresent = "EncashPresent" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 玩家IP
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 兑换时间
		/// </summary>
		public const string _EncashTime = "EncashTime" ;
		#endregion

		#region 私有变量
		private int m_userID;				//用户标识
		private long m_curGold;				//当前金币数目
		private int m_curPresent;			//当前礼物数目
		private int m_encashGold;			//兑换金币数目
		private int m_encashPresent;		//兑换礼物数目
		private int m_kindID;				//类型标识
		private int m_serverID;				//房间标识
		private string m_clientIP;			//玩家IP
		private DateTime m_encashTime;		//兑换时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordEncashPresent
		/// </summary>
		public RecordEncashPresent()
		{
			m_userID=0;
			m_curGold=0;
			m_curPresent=0;
			m_encashGold=0;
			m_encashPresent=0;
			m_kindID=0;
			m_serverID=0;
			m_clientIP="";
			m_encashTime=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 当前金币数目
		/// </summary>
		public long CurGold
		{
			get { return m_curGold; }
			set { m_curGold = value; }
		}

		/// <summary>
		/// 当前礼物数目
		/// </summary>
		public int CurPresent
		{
			get { return m_curPresent; }
			set { m_curPresent = value; }
		}

		/// <summary>
		/// 兑换金币数目
		/// </summary>
		public int EncashGold
		{
			get { return m_encashGold; }
			set { m_encashGold = value; }
		}

		/// <summary>
		/// 兑换礼物数目
		/// </summary>
		public int EncashPresent
		{
			get { return m_encashPresent; }
			set { m_encashPresent = value; }
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
		/// 玩家IP
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 兑换时间
		/// </summary>
		public DateTime EncashTime
		{
			get { return m_encashTime; }
			set { m_encashTime = value; }
		}
		#endregion
	}
}
