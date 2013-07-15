/*
 * 版本：4.0
 * 时间：2012-3-1
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
	/// 实体类 SystemStatusInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class SystemStatusInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "SystemStatusInfo" ;

		/// <summary>
		/// 状态名字
		/// </summary>
		public const string _StatusName = "StatusName" ;

		/// <summary>
		/// 状态数值
		/// </summary>
		public const string _StatusValue = "StatusValue" ;

		/// <summary>
		/// 状态字符
		/// </summary>
		public const string _StatusString = "StatusString" ;

		/// <summary>
		/// 状态显示名称
		/// </summary>
		public const string _StatusTip = "StatusTip" ;

		/// <summary>
		/// 字符的描述
		/// </summary>
		public const string _StatusDescription = "StatusDescription" ;
		#endregion

		#region 私有变量
		private string m_statusName;				//状态名字
		private int m_statusValue;					//状态数值
		private string m_statusString;				//状态字符
		private string m_statusTip;					//状态显示名称
		private string m_statusDescription;			//字符的描述
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化SystemStatusInfo
		/// </summary>
		public SystemStatusInfo()
		{
			m_statusName="";
			m_statusValue=0;
			m_statusString="";
			m_statusTip="";
			m_statusDescription="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 状态名字
		/// </summary>
		public string StatusName
		{
			get { return m_statusName; }
			set { m_statusName = value; }
		}

		/// <summary>
		/// 状态数值
		/// </summary>
		public int StatusValue
		{
			get { return m_statusValue; }
			set { m_statusValue = value; }
		}

		/// <summary>
		/// 状态字符
		/// </summary>
		public string StatusString
		{
			get { return m_statusString; }
			set { m_statusString = value; }
		}

		/// <summary>
		/// 状态显示名称
		/// </summary>
		public string StatusTip
		{
			get { return m_statusTip; }
			set { m_statusTip = value; }
		}

		/// <summary>
		/// 字符的描述
		/// </summary>
		public string StatusDescription
		{
			get { return m_statusDescription; }
			set { m_statusDescription = value; }
		}
		#endregion
	}
}
