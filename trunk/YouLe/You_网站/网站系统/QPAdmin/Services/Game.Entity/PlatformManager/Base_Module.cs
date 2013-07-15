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
	/// 实体类 Base_Module。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Base_Module  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "Base_Module" ;

		/// <summary>
		/// 模块标识
		/// </summary>
		public const string _ModuleID = "ModuleID" ;

		/// <summary>
		/// 上级模块标识
		/// </summary>
		public const string _ParentID = "ParentID" ;

		/// <summary>
		/// 模块名称
		/// </summary>
		public const string _Title = "Title" ;

		/// <summary>
		/// 模块链接地址
		/// </summary>
		public const string _Link = "Link" ;

		/// <summary>
		/// 排序数值
		/// </summary>
		public const string _OrderNo = "OrderNo" ;

		/// <summary>
		/// 是否启用 0: 启用 ; 1:禁用
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 是否菜单 0:不是 ; 1:是
		/// </summary>
		public const string _IsMenu = "IsMenu" ;

		/// <summary>
		/// 模块说明
		/// </summary>
		public const string _Description = "Description" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ManagerPopedom = "ManagerPopedom" ;
		#endregion

		#region 私有变量
		private int m_moduleID;					//模块标识
		private int m_parentID;					//上级模块标识
		private string m_title;					//模块名称
		private string m_link;					//模块链接地址
		private int m_orderNo;					//排序数值
		private bool m_nullity;					//是否启用 0: 启用 ; 1:禁用
		private bool m_isMenu;					//是否菜单 0:不是 ; 1:是
		private string m_description;			//模块说明
		private int m_managerPopedom;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Base_Module
		/// </summary>
		public Base_Module()
		{
			m_moduleID=0;
			m_parentID=0;
			m_title="";
			m_link="";
			m_orderNo=0;
			m_nullity=false;
			m_isMenu=false;
			m_description="";
			m_managerPopedom=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 模块标识
		/// </summary>
		public int ModuleID
		{
			get { return m_moduleID; }
			set { m_moduleID = value; }
		}

		/// <summary>
		/// 上级模块标识
		/// </summary>
		public int ParentID
		{
			get { return m_parentID; }
			set { m_parentID = value; }
		}

		/// <summary>
		/// 模块名称
		/// </summary>
		public string Title
		{
			get { return m_title; }
			set { m_title = value; }
		}

		/// <summary>
		/// 模块链接地址
		/// </summary>
		public string Link
		{
			get { return m_link; }
			set { m_link = value; }
		}

		/// <summary>
		/// 排序数值
		/// </summary>
		public int OrderNo
		{
			get { return m_orderNo; }
			set { m_orderNo = value; }
		}

		/// <summary>
		/// 是否启用 0: 启用 ; 1:禁用
		/// </summary>
		public bool Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 是否菜单 0:不是 ; 1:是
		/// </summary>
		public bool IsMenu
		{
			get { return m_isMenu; }
			set { m_isMenu = value; }
		}

		/// <summary>
		/// 模块说明
		/// </summary>
		public string Description
		{
			get { return m_description; }
			set { m_description = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int ManagerPopedom
		{
			get { return m_managerPopedom; }
			set { m_managerPopedom = value; }
		}
		#endregion
	}
}
