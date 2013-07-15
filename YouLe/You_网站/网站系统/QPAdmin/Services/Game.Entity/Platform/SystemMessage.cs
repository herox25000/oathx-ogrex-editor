/*
 * 版本：4.0
 * 时间：2012-2-23
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
	/// 实体类 SystemMessage。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class SystemMessage  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "SystemMessage" ;

		/// <summary>
		/// 索引标识
		/// </summary>
		public const string _ID = "ID" ;

		/// <summary>
		/// 消息范围(1:游戏,2:房间,3:全部)
		/// </summary>
		public const string _MessageType = "MessageType" ;

		/// <summary>
		/// 房间范围(0:所有房间)
		/// </summary>
		public const string _ServerRange = "ServerRange" ;

		/// <summary>
		/// 消息内容
		/// </summary>
		public const string _MessageString = "MessageString" ;

		/// <summary>
		/// 开始时间
		/// </summary>
		public const string _StartTime = "StartTime" ;

		/// <summary>
		/// 结束时间
		/// </summary>
		public const string _ConcludeTime = "ConcludeTime" ;

		/// <summary>
		/// 时间频率(多长时间发送一次)
		/// </summary>
		public const string _TimeRate = "TimeRate" ;

		/// <summary>
		/// 禁止标志
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 创建时间
		/// </summary>
		public const string _CreateDate = "CreateDate" ;

		/// <summary>
		/// 创建管理员ID
		/// </summary>
		public const string _CreateMasterID = "CreateMasterID" ;

		/// <summary>
		/// 最后更新时间
		/// </summary>
		public const string _UpdateDate = "UpdateDate" ;

		/// <summary>
		/// 修改管理员ID
		/// </summary>
		public const string _UpdateMasterID = "UpdateMasterID" ;

		/// <summary>
		/// 修改次数
		/// </summary>
		public const string _UpdateCount = "UpdateCount" ;

		/// <summary>
		/// 备注
		/// </summary>
		public const string _CollectNote = "CollectNote" ;
		#endregion

		#region 私有变量
		private int m_iD;						//索引标识
		private int m_messageType;				//消息范围(1:游戏,2:房间,3:全部)
		private string m_serverRange;			//房间范围(0:所有房间)
		private string m_messageString;			//消息内容
		private DateTime m_startTime;			//开始时间
		private DateTime m_concludeTime;		//结束时间
		private int m_timeRate;					//时间频率(多长时间发送一次)
		private byte m_nullity;					//禁止标志
		private DateTime m_createDate;			//创建时间
		private int m_createMasterID;			//创建管理员ID
		private DateTime m_updateDate;			//最后更新时间
		private int m_updateMasterID;			//修改管理员ID
		private int m_updateCount;				//修改次数
		private string m_collectNote;			//备注
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化SystemMessage
		/// </summary>
		public SystemMessage()
		{
			m_iD=0;
			m_messageType=0;
			m_serverRange="";
			m_messageString="";
			m_startTime=DateTime.Now;
			m_concludeTime=DateTime.Now;
			m_timeRate=0;
			m_nullity=0;
			m_createDate=DateTime.Now;
			m_createMasterID=0;
			m_updateDate=DateTime.Now;
			m_updateMasterID=0;
			m_updateCount=0;
			m_collectNote="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 索引标识
		/// </summary>
		public int ID
		{
			get { return m_iD; }
			set { m_iD = value; }
		}

		/// <summary>
		/// 消息范围(1:游戏,2:房间,3:全部)
		/// </summary>
		public int MessageType
		{
			get { return m_messageType; }
			set { m_messageType = value; }
		}

		/// <summary>
		/// 房间范围(0:所有房间)
		/// </summary>
		public string ServerRange
		{
			get { return m_serverRange; }
			set { m_serverRange = value; }
		}

		/// <summary>
		/// 消息内容
		/// </summary>
		public string MessageString
		{
			get { return m_messageString; }
			set { m_messageString = value; }
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
		/// 时间频率(多长时间发送一次)
		/// </summary>
		public int TimeRate
		{
			get { return m_timeRate; }
			set { m_timeRate = value; }
		}

		/// <summary>
		/// 禁止标志
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 创建时间
		/// </summary>
		public DateTime CreateDate
		{
			get { return m_createDate; }
			set { m_createDate = value; }
		}

		/// <summary>
		/// 创建管理员ID
		/// </summary>
		public int CreateMasterID
		{
			get { return m_createMasterID; }
			set { m_createMasterID = value; }
		}

		/// <summary>
		/// 最后更新时间
		/// </summary>
		public DateTime UpdateDate
		{
			get { return m_updateDate; }
			set { m_updateDate = value; }
		}

		/// <summary>
		/// 修改管理员ID
		/// </summary>
		public int UpdateMasterID
		{
			get { return m_updateMasterID; }
			set { m_updateMasterID = value; }
		}

		/// <summary>
		/// 修改次数
		/// </summary>
		public int UpdateCount
		{
			get { return m_updateCount; }
			set { m_updateCount = value; }
		}

		/// <summary>
		/// 备注
		/// </summary>
		public string CollectNote
		{
			get { return m_collectNote; }
			set { m_collectNote = value; }
		}
		#endregion
	}
}
