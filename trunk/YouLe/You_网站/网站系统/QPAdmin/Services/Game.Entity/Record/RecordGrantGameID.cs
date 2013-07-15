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
	/// 实体类 RecordGrantGameID。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordGrantGameID  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordGrantGameID" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MasterID = "MasterID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 原游戏标识
		/// </summary>
		public const string _CurGameID = "CurGameID" ;

		/// <summary>
		/// 赠予标识
		/// </summary>
		public const string _ReGameID = "ReGameID" ;

		/// <summary>
		/// ID级别
		/// </summary>
		public const string _IDLevel = "IDLevel" ;

		/// <summary>
		/// 赠予地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 赠予时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Reason = "Reason" ;
		#endregion

		#region 私有变量
		private int m_recordID;					//记录标识
		private int m_masterID;					//
		private int m_userID;					//用户标识
		private int m_curGameID;				//原游戏标识
		private int m_reGameID;					//赠予标识
		private int m_iDLevel;					//ID级别
		private string m_clientIP;				//赠予地址
		private DateTime m_collectDate;			//赠予时间
		private string m_reason;				//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordGrantGameID
		/// </summary>
		public RecordGrantGameID()
		{
			m_recordID=0;
			m_masterID=0;
			m_userID=0;
			m_curGameID=0;
			m_reGameID=0;
			m_iDLevel=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
			m_reason="";
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
		/// 
		/// </summary>
		public int MasterID
		{
			get { return m_masterID; }
			set { m_masterID = value; }
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
		/// 原游戏标识
		/// </summary>
		public int CurGameID
		{
			get { return m_curGameID; }
			set { m_curGameID = value; }
		}

		/// <summary>
		/// 赠予标识
		/// </summary>
		public int ReGameID
		{
			get { return m_reGameID; }
			set { m_reGameID = value; }
		}

		/// <summary>
		/// ID级别
		/// </summary>
		public int IDLevel
		{
			get { return m_iDLevel; }
			set { m_iDLevel = value; }
		}

		/// <summary>
		/// 赠予地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 赠予时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string Reason
		{
			get { return m_reason; }
			set { m_reason = value; }
		}
		#endregion
	}
}
