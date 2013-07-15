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
	/// 实体类 RecordSendProperty。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordSendProperty  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordSendProperty" ;

		/// <summary>
		/// 道具标识
		/// </summary>
		public const string _PropID = "PropID" ;

		/// <summary>
		/// 玩家标识
		/// </summary>
		public const string _SourceUserID = "SourceUserID" ;

		/// <summary>
		/// 玩家标识
		/// </summary>
		public const string _TargetUserID = "TargetUserID" ;

		/// <summary>
		/// 道具价格
		/// </summary>
		public const string _PropPrice = "PropPrice" ;

		/// <summary>
		/// 道具数目
		/// </summary>
		public const string _PropCount = "PropCount" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 赠送时间
		/// </summary>
		public const string _SendTime = "SendTime" ;

		/// <summary>
		/// 玩家地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;
		#endregion

		#region 私有变量
		private byte m_propID;				//道具标识
		private int m_sourceUserID;			//玩家标识
		private int m_targetUserID;			//玩家标识
		private int m_propPrice;			//道具价格
		private int m_propCount;			//道具数目
		private int m_kindID;				//类型标识
		private int m_serverID;				//房间标识
		private DateTime m_sendTime;		//赠送时间
		private string m_clientIP;			//玩家地址
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordSendProperty
		/// </summary>
		public RecordSendProperty()
		{
			m_propID=0;
			m_sourceUserID=0;
			m_targetUserID=0;
			m_propPrice=0;
			m_propCount=0;
			m_kindID=0;
			m_serverID=0;
			m_sendTime=DateTime.Now;
			m_clientIP="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 道具标识
		/// </summary>
		public byte PropID
		{
			get { return m_propID; }
			set { m_propID = value; }
		}

		/// <summary>
		/// 玩家标识
		/// </summary>
		public int SourceUserID
		{
			get { return m_sourceUserID; }
			set { m_sourceUserID = value; }
		}

		/// <summary>
		/// 玩家标识
		/// </summary>
		public int TargetUserID
		{
			get { return m_targetUserID; }
			set { m_targetUserID = value; }
		}

		/// <summary>
		/// 道具价格
		/// </summary>
		public int PropPrice
		{
			get { return m_propPrice; }
			set { m_propPrice = value; }
		}

		/// <summary>
		/// 道具数目
		/// </summary>
		public int PropCount
		{
			get { return m_propCount; }
			set { m_propCount = value; }
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
		/// 赠送时间
		/// </summary>
		public DateTime SendTime
		{
			get { return m_sendTime; }
			set { m_sendTime = value; }
		}

		/// <summary>
		/// 玩家地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}
		#endregion
	}
}
