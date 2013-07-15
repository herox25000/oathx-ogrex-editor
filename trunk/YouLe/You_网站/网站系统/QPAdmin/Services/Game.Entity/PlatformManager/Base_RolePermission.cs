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
	/// 实体类 Base_RolePermission。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Base_RolePermission  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "Base_RolePermission" ;

		/// <summary>
		/// 角色标识
		/// </summary>
		public const string _RoleID = "RoleID" ;

		/// <summary>
		/// 模块标识
		/// </summary>
		public const string _ModuleID = "ModuleID" ;

		/// <summary>
		/// 管理权限
		/// </summary>
		public const string _ManagerPermission = "ManagerPermission" ;

		/// <summary>
		/// 操作权限
		/// </summary>
		public const string _OperationPermission = "OperationPermission" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _StateFlag = "StateFlag" ;
		#endregion

		#region 私有变量
		private int m_roleID;						//角色标识
		private int m_moduleID;						//模块标识
		private long m_managerPermission;			//管理权限
		private long m_operationPermission;			//操作权限
		private int m_stateFlag;					//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Base_RolePermission
		/// </summary>
		public Base_RolePermission()
		{
			m_roleID=0;
			m_moduleID=0;
			m_managerPermission=0;
			m_operationPermission=0;
			m_stateFlag=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 角色标识
		/// </summary>
		public int RoleID
		{
			get { return m_roleID; }
			set { m_roleID = value; }
		}

		/// <summary>
		/// 模块标识
		/// </summary>
		public int ModuleID
		{
			get { return m_moduleID; }
			set { m_moduleID = value; }
		}

		/// <summary>
		/// 管理权限
		/// </summary>
		public long ManagerPermission
		{
			get { return m_managerPermission; }
			set { m_managerPermission = value; }
		}

		/// <summary>
		/// 操作权限
		/// </summary>
		public long OperationPermission
		{
			get { return m_operationPermission; }
			set { m_operationPermission = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int StateFlag
		{
			get { return m_stateFlag; }
			set { m_stateFlag = value; }
		}
		#endregion
	}
}
