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

namespace Game.Entity.Accounts
{
	/// <summary>
	/// 实体类 SystemGrantCount。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class SystemGrantCount  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "SystemGrantCount" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DateID = "DateID" ;

		/// <summary>
		/// 注册地址
		/// </summary>
		public const string _RegisterIP = "RegisterIP" ;

		/// <summary>
		/// 注册机器
		/// </summary>
		public const string _RegisterMachine = "RegisterMachine" ;

		/// <summary>
		/// 赠送金币
		/// </summary>
		public const string _GrantScore = "GrantScore" ;

		/// <summary>
		/// 赠送次数
		/// </summary>
		public const string _GrantCount = "GrantCount" ;

		/// <summary>
		/// 收集时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_dateID;						//
		private string m_registerIP;				//注册地址
		private string m_registerMachine;			//注册机器
		private long m_grantScore;					//赠送金币
		private long m_grantCount;					//赠送次数
		private DateTime m_collectDate;				//收集时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化SystemGrantCount
		/// </summary>
		public SystemGrantCount()
		{
			m_dateID=0;
			m_registerIP="";
			m_registerMachine="";
			m_grantScore=0;
			m_grantCount=0;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int DateID
		{
			get { return m_dateID; }
			set { m_dateID = value; }
		}

		/// <summary>
		/// 注册地址
		/// </summary>
		public string RegisterIP
		{
			get { return m_registerIP; }
			set { m_registerIP = value; }
		}

		/// <summary>
		/// 注册机器
		/// </summary>
		public string RegisterMachine
		{
			get { return m_registerMachine; }
			set { m_registerMachine = value; }
		}

		/// <summary>
		/// 赠送金币
		/// </summary>
		public long GrantScore
		{
			get { return m_grantScore; }
			set { m_grantScore = value; }
		}

		/// <summary>
		/// 赠送次数
		/// </summary>
		public long GrantCount
		{
			get { return m_grantCount; }
			set { m_grantCount = value; }
		}

		/// <summary>
		/// 收集时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
