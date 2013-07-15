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
	/// 实体类 RecordAccountsExpend。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordAccountsExpend  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordAccountsExpend" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 操作网管
		/// </summary>
		public const string _OperMasterID = "OperMasterID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 用户帐号
		/// </summary>
		public const string _ReAccounts = "ReAccounts" ;

		/// <summary>
		/// 修改地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 修改日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_recordID;				//记录标识
		private int m_operMasterID;			//操作网管
		private int m_userID;				//用户标识
		private string m_reAccounts;		//用户帐号
		private string m_clientIP;			//修改地址
		private DateTime m_collectDate;		//修改日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordAccountsExpend
		/// </summary>
		public RecordAccountsExpend()
		{
			m_recordID=0;
			m_operMasterID=0;
			m_userID=0;
			m_reAccounts="";
			m_clientIP="";
			m_collectDate=DateTime.Now;
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
		/// 操作网管
		/// </summary>
		public int OperMasterID
		{
			get { return m_operMasterID; }
			set { m_operMasterID = value; }
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
		/// 用户帐号
		/// </summary>
		public string ReAccounts
		{
			get { return m_reAccounts; }
			set { m_reAccounts = value; }
		}

		/// <summary>
		/// 修改地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 修改日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
