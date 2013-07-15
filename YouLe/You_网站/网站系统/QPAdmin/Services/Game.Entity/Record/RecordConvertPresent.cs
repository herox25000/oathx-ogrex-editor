/*
 * 版本：4.0
 * 时间：2011-9-27
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
	/// 实体类 RecordConvertPresent。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordConvertPresent  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordConvertPresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 兑换前银行
		/// </summary>
		public const string _CurInsureScore = "CurInsureScore" ;

		/// <summary>
		/// 兑换前魅力点
		/// </summary>
		public const string _CurPresent = "CurPresent" ;

		/// <summary>
		/// 兑换点数
		/// </summary>
		public const string _ConvertPresent = "ConvertPresent" ;

		/// <summary>
		/// 兑换比例
		/// </summary>
		public const string _ConvertRate = "ConvertRate" ;

		/// <summary>
		/// 兑换场所(0:大厅,1:网页)
		/// </summary>
		public const string _IsGamePlaza = "IsGamePlaza" ;

		/// <summary>
		/// 兑换地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 兑换日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_recordID;					//
		private int m_userID;					//用户标识
		private int m_kindID;					//游戏标识
		private int m_serverID;					//房间标识
		private long m_curInsureScore;			//兑换前银行
		private int m_curPresent;				//兑换前魅力点
		private int m_convertPresent;			//兑换点数
		private int m_convertRate;				//兑换比例
		private byte m_isGamePlaza;				//兑换场所(0:大厅,1:网页)
		private string m_clientIP;				//兑换地址
		private DateTime m_collectDate;			//兑换日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordConvertPresent
		/// </summary>
		public RecordConvertPresent()
		{
			m_recordID=0;
			m_userID=0;
			m_kindID=0;
			m_serverID=0;
			m_curInsureScore=0;
			m_curPresent=0;
			m_convertPresent=0;
			m_convertRate=0;
			m_isGamePlaza=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
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
		/// 游戏标识
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
		/// 兑换前银行
		/// </summary>
		public long CurInsureScore
		{
			get { return m_curInsureScore; }
			set { m_curInsureScore = value; }
		}

		/// <summary>
		/// 兑换前魅力点
		/// </summary>
		public int CurPresent
		{
			get { return m_curPresent; }
			set { m_curPresent = value; }
		}

		/// <summary>
		/// 兑换点数
		/// </summary>
		public int ConvertPresent
		{
			get { return m_convertPresent; }
			set { m_convertPresent = value; }
		}

		/// <summary>
		/// 兑换比例
		/// </summary>
		public int ConvertRate
		{
			get { return m_convertRate; }
			set { m_convertRate = value; }
		}

		/// <summary>
		/// 兑换场所(0:大厅,1:网页)
		/// </summary>
		public byte IsGamePlaza
		{
			get { return m_isGamePlaza; }
			set { m_isGamePlaza = value; }
		}

		/// <summary>
		/// 兑换地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 兑换日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
