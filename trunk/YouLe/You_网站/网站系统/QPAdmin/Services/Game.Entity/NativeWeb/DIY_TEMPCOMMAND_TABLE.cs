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

namespace Game.Entity.NativeWeb
{
	/// <summary>
	/// 实体类 DIY_TEMPCOMMAND_TABLE。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class DIY_TEMPCOMMAND_TABLE  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "DIY_TEMPCOMMAND_TABLE" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ResultTxt = "ResultTxt" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ID = "ID" ;
		#endregion

		#region 私有变量
		private string m_resultTxt;			//
		private int m_iD;					//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化DIY_TEMPCOMMAND_TABLE
		/// </summary>
		public DIY_TEMPCOMMAND_TABLE()
		{
			m_resultTxt="";
			m_iD=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public string ResultTxt
		{
			get { return m_resultTxt; }
			set { m_resultTxt = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int ID
		{
			get { return m_iD; }
			set { m_iD = value; }
		}
		#endregion
	}
}
