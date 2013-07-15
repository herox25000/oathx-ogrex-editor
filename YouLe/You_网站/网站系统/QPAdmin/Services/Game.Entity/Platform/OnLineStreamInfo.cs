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
	/// 实体类 OnLineStreamInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class OnLineStreamInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "OnLineStreamInfo" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ID = "ID" ;

		/// <summary>
		/// 机器标识
		/// </summary>
		public const string _MachineID = "MachineID" ;

		/// <summary>
		/// 机器名字
		/// </summary>
		public const string _MachineServer = "MachineServer" ;

		/// <summary>
		/// 插入时间
		/// </summary>
		public const string _InsertDateTime = "InsertDateTime" ;

		/// <summary>
		/// 用户数目
		/// </summary>
		public const string _OnLineCountSum = "OnLineCountSum" ;

		/// <summary>
		/// 在线信息
		/// </summary>
		public const string _OnLineCountKind = "OnLineCountKind" ;
		#endregion

		#region 私有变量
		private int m_iD;							//房间标识
		private string m_machineID;					//机器标识
		private string m_machineServer;				//机器名字
		private DateTime m_insertDateTime;			//插入时间
		private int m_onLineCountSum;				//用户数目
		private string m_onLineCountKind;			//在线信息
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化OnLineStreamInfo
		/// </summary>
		public OnLineStreamInfo()
		{
			m_iD=0;
			m_machineID="";
			m_machineServer="";
			m_insertDateTime=DateTime.Now;
			m_onLineCountSum=0;
			m_onLineCountKind="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 房间标识
		/// </summary>
		public int ID
		{
			get { return m_iD; }
			set { m_iD = value; }
		}

		/// <summary>
		/// 机器标识
		/// </summary>
		public string MachineID
		{
			get { return m_machineID; }
			set { m_machineID = value; }
		}

		/// <summary>
		/// 机器名字
		/// </summary>
		public string MachineServer
		{
			get { return m_machineServer; }
			set { m_machineServer = value; }
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
		/// 用户数目
		/// </summary>
		public int OnLineCountSum
		{
			get { return m_onLineCountSum; }
			set { m_onLineCountSum = value; }
		}

		/// <summary>
		/// 在线信息
		/// </summary>
		public string OnLineCountKind
		{
			get { return m_onLineCountKind; }
			set { m_onLineCountKind = value; }
		}
		#endregion
	}
}
