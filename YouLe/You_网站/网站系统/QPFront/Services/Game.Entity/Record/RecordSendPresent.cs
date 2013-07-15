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
	/// 实体类 RecordSendPresent。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordSendPresent  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordSendPresent" ;

		/// <summary>
		/// 礼物标识
		/// </summary>
		public const string _PresentID = "PresentID" ;

		/// <summary>
		/// 玩家标识
		/// </summary>
		public const string _RcvUserID = "RcvUserID" ;

		/// <summary>
		/// 玩家标识
		/// </summary>
		public const string _SendUserID = "SendUserID" ;

		/// <summary>
		/// 魅力数目
		/// </summary>
		public const string _LovelinessRcv = "LovelinessRcv" ;

		/// <summary>
		/// 魅力数目
		/// </summary>
		public const string _LovelinessSend = "LovelinessSend" ;

		/// <summary>
		/// 礼物价钱
		/// </summary>
		public const string _PresentPrice = "PresentPrice" ;

		/// <summary>
		/// 礼物数目
		/// </summary>
		public const string _PresentCount = "PresentCount" ;

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
		private byte m_presentID;				//礼物标识
		private int m_rcvUserID;				//玩家标识
		private int m_sendUserID;				//玩家标识
		private int m_lovelinessRcv;			//魅力数目
		private int m_lovelinessSend;			//魅力数目
		private int m_presentPrice;				//礼物价钱
		private int m_presentCount;				//礼物数目
		private int m_kindID;					//类型标识
		private int m_serverID;					//房间标识
		private DateTime m_sendTime;			//赠送时间
		private string m_clientIP;				//玩家地址
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordSendPresent
		/// </summary>
		public RecordSendPresent()
		{
			m_presentID=0;
			m_rcvUserID=0;
			m_sendUserID=0;
			m_lovelinessRcv=0;
			m_lovelinessSend=0;
			m_presentPrice=0;
			m_presentCount=0;
			m_kindID=0;
			m_serverID=0;
			m_sendTime=DateTime.Now;
			m_clientIP="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 礼物标识
		/// </summary>
		public byte PresentID
		{
			get { return m_presentID; }
			set { m_presentID = value; }
		}

		/// <summary>
		/// 玩家标识
		/// </summary>
		public int RcvUserID
		{
			get { return m_rcvUserID; }
			set { m_rcvUserID = value; }
		}

		/// <summary>
		/// 玩家标识
		/// </summary>
		public int SendUserID
		{
			get { return m_sendUserID; }
			set { m_sendUserID = value; }
		}

		/// <summary>
		/// 魅力数目
		/// </summary>
		public int LovelinessRcv
		{
			get { return m_lovelinessRcv; }
			set { m_lovelinessRcv = value; }
		}

		/// <summary>
		/// 魅力数目
		/// </summary>
		public int LovelinessSend
		{
			get { return m_lovelinessSend; }
			set { m_lovelinessSend = value; }
		}

		/// <summary>
		/// 礼物价钱
		/// </summary>
		public int PresentPrice
		{
			get { return m_presentPrice; }
			set { m_presentPrice = value; }
		}

		/// <summary>
		/// 礼物数目
		/// </summary>
		public int PresentCount
		{
			get { return m_presentCount; }
			set { m_presentCount = value; }
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
