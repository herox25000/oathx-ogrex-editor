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
	/// 实体类 ConfineContent。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class ConfineContent  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "ConfineContent" ;

		/// <summary>
		/// 保留字符
		/// </summary>
		public const string _String = "String" ;

		/// <summary>
		/// 有效时间
		/// </summary>
		public const string _EnjoinOverDate = "EnjoinOverDate" ;

		/// <summary>
		/// 录入日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private string m_string;					//保留字符
		private DateTime m_enjoinOverDate;			//有效时间
		private DateTime m_collectDate;				//录入日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化ConfineContent
		/// </summary>
		public ConfineContent()
		{
			m_string="";
			m_enjoinOverDate=DateTime.Now;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 保留字符
		/// </summary>
		public string String
		{
			get { return m_string; }
			set { m_string = value; }
		}

		/// <summary>
		/// 有效时间
		/// </summary>
		public DateTime EnjoinOverDate
		{
			get { return m_enjoinOverDate; }
			set { m_enjoinOverDate = value; }
		}

		/// <summary>
		/// 录入日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
