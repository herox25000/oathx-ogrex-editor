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
	/// 实体类 AccountsMember。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class AccountsMember  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "AccountsMember" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 会员标识
		/// </summary>
		public const string _MemberOrder = "MemberOrder" ;

		/// <summary>
		/// 用户权限
		/// </summary>
		public const string _UserRight = "UserRight" ;

		/// <summary>
		/// 会员期限
		/// </summary>
		public const string _MemberOverDate = "MemberOverDate" ;
		#endregion

		#region 私有变量
		private int m_userID;						//用户标识
		private byte m_memberOrder;					//会员标识
		private int m_userRight;					//用户权限
		private DateTime m_memberOverDate;			//会员期限
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化AccountsMember
		/// </summary>
		public AccountsMember()
		{
			m_userID=0;
			m_memberOrder=0;
			m_userRight=0;
			m_memberOverDate=DateTime.Now;
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
		/// 会员标识
		/// </summary>
		public byte MemberOrder
		{
			get { return m_memberOrder; }
			set { m_memberOrder = value; }
		}

		/// <summary>
		/// 用户权限
		/// </summary>
		public int UserRight
		{
			get { return m_userRight; }
			set { m_userRight = value; }
		}

		/// <summary>
		/// 会员期限
		/// </summary>
		public DateTime MemberOverDate
		{
			get { return m_memberOverDate; }
			set { m_memberOverDate = value; }
		}
		#endregion
	}
}
