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
	/// 实体类 Base_Roles。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Base_Roles  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "Base_Roles" ;

		/// <summary>
		/// 角色流水标识
		/// </summary>
		public const string _RoleID = "RoleID" ;

		/// <summary>
		/// 角色名称
		/// </summary>
		public const string _RoleName = "RoleName" ;

		/// <summary>
		/// 角色描述
		/// </summary>
		public const string _Description = "Description" ;
		#endregion

		#region 私有变量
		private int m_roleID;					//角色流水标识
		private string m_roleName;				//角色名称
		private string m_description;			//角色描述
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Base_Roles
		/// </summary>
		public Base_Roles()
		{
			m_roleID=0;
			m_roleName="";
			m_description="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 角色流水标识
		/// </summary>
		public int RoleID
		{
			get { return m_roleID; }
			set { m_roleID = value; }
		}

		/// <summary>
		/// 角色名称
		/// </summary>
		public string RoleName
		{
			get { return m_roleName; }
			set { m_roleName = value; }
		}

		/// <summary>
		/// 角色描述
		/// </summary>
		public string Description
		{
			get { return m_description; }
			set { m_description = value; }
		}
		#endregion
	}
}
