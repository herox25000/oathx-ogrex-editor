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
	/// 实体类 Jiaozhu。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Jiaozhu  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "jiaozhu" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DirName = "DirName" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DirAtt = "DirAtt" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DirFile = "DirFile" ;
		#endregion

		#region 私有变量
		private string m_dirName;			//
		private string m_dirAtt;			//
		private string m_dirFile;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Jiaozhu
		/// </summary>
		public Jiaozhu()
		{
			m_dirName="";
			m_dirAtt="";
			m_dirFile="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public string DirName
		{
			get { return m_dirName; }
			set { m_dirName = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string DirAtt
		{
			get { return m_dirAtt; }
			set { m_dirAtt = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string DirFile
		{
			get { return m_dirFile; }
			set { m_dirFile = value; }
		}
		#endregion
	}
}
