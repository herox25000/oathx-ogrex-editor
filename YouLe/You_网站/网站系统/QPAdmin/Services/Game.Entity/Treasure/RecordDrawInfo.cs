/*
 * 版本：4.0
 * 时间：2011-9-28
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.Treasure
{
	/// <summary>
	/// 实体类 RecordDrawInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordDrawInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordDrawInfo" ;

		/// <summary>
		/// 局数标识
		/// </summary>
		public const string _DrawID = "DrawID" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 桌子号码
		/// </summary>
		public const string _TableID = "TableID" ;

		/// <summary>
		/// 用户数目
		/// </summary>
		public const string _UserCount = "UserCount" ;

		/// <summary>
		/// 机器数目
		/// </summary>
		public const string _AndroidCount = "AndroidCount" ;

		/// <summary>
		/// 损耗数目
		/// </summary>
		public const string _Waste = "Waste" ;

		/// <summary>
		/// 税收数目
		/// </summary>
		public const string _Revenue = "Revenue" ;

		/// <summary>
		/// 用户奖牌
		/// </summary>
		public const string _UserMedal = "UserMedal" ;

		/// <summary>
		/// 开始时间
		/// </summary>
		public const string _StartTime = "StartTime" ;

		/// <summary>
		/// 结束时间
		/// </summary>
		public const string _ConcludeTime = "ConcludeTime" ;

		/// <summary>
		/// 插入时间
		/// </summary>
		public const string _InsertTime = "InsertTime" ;

		/// <summary>
		/// 游戏过程
		/// </summary>
		public const string _DrawCourse = "DrawCourse" ;
		#endregion

		#region 私有变量
		private int m_drawID;				//局数标识
		private int m_kindID;				//类型标识
		private int m_serverID;				//房间标识
		private int m_tableID;				//桌子号码
		private int m_userCount;			//用户数目
		private int m_androidCount;			//机器数目
		private long m_waste;				//损耗数目
		private long m_revenue;				//税收数目
		private int m_userMedal;			//用户奖牌
		private DateTime m_startTime;		//开始时间
		private DateTime m_concludeTime;	//结束时间
		private DateTime m_insertTime;		//插入时间
		private System.Byte[] m_drawCourse;	//游戏过程
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordDrawInfo
		/// </summary>
		public RecordDrawInfo()
		{
			m_drawID=0;
			m_kindID=0;
			m_serverID=0;
			m_tableID=0;
			m_userCount=0;
			m_androidCount=0;
			m_waste=0;
			m_revenue=0;
			m_userMedal=0;
			m_startTime=DateTime.Now;
			m_concludeTime=DateTime.Now;
			m_insertTime=DateTime.Now;
			m_drawCourse=null;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 局数标识
		/// </summary>
		public int DrawID
		{
			get { return m_drawID; }
			set { m_drawID = value; }
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
		/// 桌子号码
		/// </summary>
		public int TableID
		{
			get { return m_tableID; }
			set { m_tableID = value; }
		}

		/// <summary>
		/// 用户数目
		/// </summary>
		public int UserCount
		{
			get { return m_userCount; }
			set { m_userCount = value; }
		}

		/// <summary>
		/// 机器数目
		/// </summary>
		public int AndroidCount
		{
			get { return m_androidCount; }
			set { m_androidCount = value; }
		}

		/// <summary>
		/// 损耗数目
		/// </summary>
		public long Waste
		{
			get { return m_waste; }
			set { m_waste = value; }
		}

		/// <summary>
		/// 税收数目
		/// </summary>
		public long Revenue
		{
			get { return m_revenue; }
			set { m_revenue = value; }
		}

		/// <summary>
		/// 用户奖牌
		/// </summary>
		public int UserMedal
		{
			get { return m_userMedal; }
			set { m_userMedal = value; }
		}

		/// <summary>
		/// 开始时间
		/// </summary>
		public DateTime StartTime
		{
			get { return m_startTime; }
			set { m_startTime = value; }
		}

		/// <summary>
		/// 结束时间
		/// </summary>
		public DateTime ConcludeTime
		{
			get { return m_concludeTime; }
			set { m_concludeTime = value; }
		}

		/// <summary>
		/// 插入时间
		/// </summary>
		public DateTime InsertTime
		{
			get { return m_insertTime; }
			set { m_insertTime = value; }
		}

		/// <summary>
		/// 游戏过程
		/// </summary>
		public System.Byte[] DrawCourse
		{
			get { return m_drawCourse; }
			set { m_drawCourse = value; }
		}
		#endregion
	}
}
