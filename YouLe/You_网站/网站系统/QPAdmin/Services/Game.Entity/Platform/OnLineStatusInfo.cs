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

namespace Game.Entity.Platform
{
	/// <summary>
	/// 实体类 OnLineStatusInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class OnLineStatusInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "OnLineStatusInfo" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 在线人数
		/// </summary>
		public const string _OnLineCount = "OnLineCount" ;

		/// <summary>
		/// 插入时间
		/// </summary>
		public const string _InsertDateTime = "InsertDateTime" ;

		/// <summary>
		/// 修改时间
		/// </summary>
		public const string _ModifyDateTime = "ModifyDateTime" ;
		#endregion

		#region 私有变量
		private int m_kindID;						//类型标识
		private int m_serverID;						//房间标识
		private int m_onLineCount;					//在线人数
		private DateTime m_insertDateTime;			//插入时间
		private DateTime m_modifyDateTime;			//修改时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化OnLineStatusInfo
		/// </summary>
		public OnLineStatusInfo()
		{
			m_kindID=0;
			m_serverID=0;
			m_onLineCount=0;
			m_insertDateTime=DateTime.Now;
			m_modifyDateTime=DateTime.Now;
		}

		#endregion

		#region 公共属性

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
		/// 在线人数
		/// </summary>
		public int OnLineCount
		{
			get { return m_onLineCount; }
			set { m_onLineCount = value; }
		}

		/// <summary>
		/// 插入时间
		/// </summary>
		public DateTime InsertDateTime
		{
			get { return m_insertDateTime; }
			set { m_insertDateTime = value; }
		}

		/// <summary>
		/// 修改时间
		/// </summary>
		public DateTime ModifyDateTime
		{
			get { return m_modifyDateTime; }
			set { m_modifyDateTime = value; }
		}
		#endregion
	}
}
