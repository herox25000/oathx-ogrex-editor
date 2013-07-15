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
	/// 实体类 Base_ModulePermission。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Base_ModulePermission  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "Base_ModulePermission" ;

		/// <summary>
		/// 模块标识
		/// </summary>
		public const string _ModuleID = "ModuleID" ;

		/// <summary>
		/// 模块名称
		/// </summary>
		public const string _PermissionTitle = "PermissionTitle" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _PermissionValue = "PermissionValue" ;

		/// <summary>
		/// 禁止标识
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _StateFlag = "StateFlag" ;

		/// <summary>
		/// 父模块标识
		/// </summary>
		public const string _ParentID = "ParentID" ;
		#endregion

		#region 私有变量
		private int m_moduleID;						//模块标识
		private string m_permissionTitle;			//模块名称
		private long m_permissionValue;				//
		private byte m_nullity;						//禁止标识
		private int m_stateFlag;					//
		private int m_parentID;						//父模块标识
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Base_ModulePermission
		/// </summary>
		public Base_ModulePermission()
		{
			m_moduleID=0;
			m_permissionTitle="";
			m_permissionValue=0;
			m_nullity=0;
			m_stateFlag=0;
			m_parentID=0;
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
		/// 模块名称
		/// </summary>
		public string PermissionTitle
		{
			get { return m_permissionTitle; }
			set { m_permissionTitle = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public long PermissionValue
		{
			get { return m_permissionValue; }
			set { m_permissionValue = value; }
		}

		/// <summary>
		/// 禁止标识
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int StateFlag
		{
			get { return m_stateFlag; }
			set { m_stateFlag = value; }
		}

		/// <summary>
		/// 父模块标识
		/// </summary>
		public int ParentID
		{
			get { return m_parentID; }
			set { m_parentID = value; }
		}
		#endregion
	}
}
