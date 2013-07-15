/*
 * 版本：4.0
 * 时间：2011-8-1
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
	/// 实体类 Admin。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Admin  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "admin" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _UserName = "UserName" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Password = "Password" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Classcode = "classcode" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Classname = "classname" ;
		#endregion

		#region 私有变量
		private int m_userID;				//
		private string m_userName;			//
		private string m_password;			//
		private string m_classcode;			//
		private string m_classname;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Admin
		/// </summary>
		public Admin()
		{
			m_userID=0;
			m_userName="";
			m_password="";
			m_classcode="";
			m_classname="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string UserName
		{
			get { return m_userName; }
			set { m_userName = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string Password
		{
			get { return m_password; }
			set { m_password = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string Classcode
		{
			get { return m_classcode; }
			set { m_classcode = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string Classname
		{
			get { return m_classname; }
			set { m_classname = value; }
		}
		#endregion
	}
}
