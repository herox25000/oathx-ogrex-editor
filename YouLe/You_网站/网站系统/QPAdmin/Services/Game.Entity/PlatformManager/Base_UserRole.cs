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
	/// 实体类 Base_UserRole。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Base_UserRole  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "Base_UserRole" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 角色标识
		/// </summary>
		public const string _RoleID = "RoleID" ;
		#endregion

		#region 私有变量
		private int m_userID;			//用户标识
		private int m_roleID;			//角色标识
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Base_UserRole
		/// </summary>
		public Base_UserRole()
		{
			m_userID=0;
			m_roleID=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 角色标识
		/// </summary>
		public int RoleID
		{
			get { return m_roleID; }
			set { m_roleID = value; }
		}
		#endregion
	}
}
