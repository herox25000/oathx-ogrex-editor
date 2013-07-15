/*
 * 版本：4.0
 * 时间：2011-8-30
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.PlatformManager
{
	/// <summary>
	/// 实体类 SystemSecurity。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class SystemSecurity  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "SystemSecurity" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _OperatingTime = "OperatingTime" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _OperatingName = "OperatingName" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _OperatingIP = "OperatingIP" ;

		/// <summary>
		/// 操作帐号
		/// </summary>
		public const string _OperatingAccounts = "OperatingAccounts" ;
		#endregion

		#region 私有变量
		private int m_recordID;						//
		private DateTime m_operatingTime;			//
		private string m_operatingName;				//
		private string m_operatingIP;				//
		private string m_operatingAccounts;			//操作帐号
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化SystemSecurity
		/// </summary>
		public SystemSecurity()
		{
			m_recordID=0;
			m_operatingTime=DateTime.Now;
			m_operatingName="";
			m_operatingIP="";
			m_operatingAccounts="";
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
		/// 
		/// </summary>
		public DateTime OperatingTime
		{
			get { return m_operatingTime; }
			set { m_operatingTime = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string OperatingName
		{
			get { return m_operatingName; }
			set { m_operatingName = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string OperatingIP
		{
			get { return m_operatingIP; }
			set { m_operatingIP = value; }
		}

		/// <summary>
		/// 操作帐号
		/// </summary>
		public string OperatingAccounts
		{
			get { return m_operatingAccounts; }
			set { m_operatingAccounts = value; }
		}
		#endregion
	}
}
