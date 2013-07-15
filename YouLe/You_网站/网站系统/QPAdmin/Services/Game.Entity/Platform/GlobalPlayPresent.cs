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
	/// 实体类 GlobalPlayPresent。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GlobalPlayPresent  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GlobalPlayPresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _PresentMember = "PresentMember" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MaxDatePresent = "MaxDatePresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MaxPresent = "MaxPresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CellPlayPresnet = "CellPlayPresnet" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CellPlayTime = "CellPlayTime" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _StartPlayTime = "StartPlayTime" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CellOnlinePresent = "CellOnlinePresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CellOnlineTime = "CellOnlineTime" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _StartOnlineTime = "StartOnlineTime" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _IsPlayPresent = "IsPlayPresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _IsOnlinePresent = "IsOnlinePresent" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_serverID;					//
		private string m_presentMember;			//
		private int m_maxDatePresent;			//
		private int m_maxPresent;				//
		private int m_cellPlayPresnet;			//
		private int m_cellPlayTime;				//
		private int m_startPlayTime;			//
		private int m_cellOnlinePresent;		//
		private int m_cellOnlineTime;			//
		private int m_startOnlineTime;			//
		private byte m_isPlayPresent;			//
		private byte m_isOnlinePresent;			//
		private DateTime m_collectDate;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GlobalPlayPresent
		/// </summary>
		public GlobalPlayPresent()
		{
			m_serverID=0;
			m_presentMember="";
			m_maxDatePresent=0;
			m_maxPresent=0;
			m_cellPlayPresnet=0;
			m_cellPlayTime=0;
			m_startPlayTime=0;
			m_cellOnlinePresent=0;
			m_cellOnlineTime=0;
			m_startOnlineTime=0;
			m_isPlayPresent=0;
			m_isOnlinePresent=0;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int ServerID
		{
			get { return m_serverID; }
			set { m_serverID = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string PresentMember
		{
			get { return m_presentMember; }
			set { m_presentMember = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int MaxDatePresent
		{
			get { return m_maxDatePresent; }
			set { m_maxDatePresent = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int MaxPresent
		{
			get { return m_maxPresent; }
			set { m_maxPresent = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int CellPlayPresnet
		{
			get { return m_cellPlayPresnet; }
			set { m_cellPlayPresnet = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int CellPlayTime
		{
			get { return m_cellPlayTime; }
			set { m_cellPlayTime = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int StartPlayTime
		{
			get { return m_startPlayTime; }
			set { m_startPlayTime = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int CellOnlinePresent
		{
			get { return m_cellOnlinePresent; }
			set { m_cellOnlinePresent = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int CellOnlineTime
		{
			get { return m_cellOnlineTime; }
			set { m_cellOnlineTime = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int StartOnlineTime
		{
			get { return m_startOnlineTime; }
			set { m_startOnlineTime = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public byte IsPlayPresent
		{
			get { return m_isPlayPresent; }
			set { m_isPlayPresent = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public byte IsOnlinePresent
		{
			get { return m_isOnlinePresent; }
			set { m_isOnlinePresent = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
