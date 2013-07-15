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
	/// 实体类 SystemStreamInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class SystemStreamInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "SystemStreamInfo" ;

		/// <summary>
		/// 日期标识
		/// </summary>
		public const string _DateID = "DateID" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 进入数目
		/// </summary>
		public const string _LogonCount = "LogonCount" ;

		/// <summary>
		/// 注册数目
		/// </summary>
		public const string _RegisterCount = "RegisterCount" ;

		/// <summary>
		/// 录入时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_dateID;				//日期标识
		private int m_kindID;				//类型标识
		private int m_serverID;				//房间标识
		private int m_logonCount;			//进入数目
		private int m_registerCount;		//注册数目
		private DateTime m_collectDate;		//录入时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化SystemStreamInfo
		/// </summary>
		public SystemStreamInfo()
		{
			m_dateID=0;
			m_kindID=0;
			m_serverID=0;
			m_logonCount=0;
			m_registerCount=0;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 日期标识
		/// </summary>
		public int DateID
		{
			get { return m_dateID; }
			set { m_dateID = value; }
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
		/// 进入数目
		/// </summary>
		public int LogonCount
		{
			get { return m_logonCount; }
			set { m_logonCount = value; }
		}

		/// <summary>
		/// 注册数目
		/// </summary>
		public int RegisterCount
		{
			get { return m_registerCount; }
			set { m_registerCount = value; }
		}

		/// <summary>
		/// 录入时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
