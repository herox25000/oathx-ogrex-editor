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
	/// 实体类 SystemStreamInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class SystemStreamInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "SystemStreamInfo" ;

		/// <summary>
		/// 日期标识
		/// </summary>
		public const string _DateID = "DateID" ;

		/// <summary>
		/// 登录成功
		/// </summary>
		public const string _WebLogonSuccess = "WebLogonSuccess" ;

		/// <summary>
		/// 注册成功
		/// </summary>
		public const string _WebRegisterSuccess = "WebRegisterSuccess" ;

		/// <summary>
		/// 登录成功
		/// </summary>
		public const string _GameLogonSuccess = "GameLogonSuccess" ;

		/// <summary>
		/// 注册成功
		/// </summary>
		public const string _GameRegisterSuccess = "GameRegisterSuccess" ;

		/// <summary>
		/// 录入时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_dateID;						//日期标识
		private int m_webLogonSuccess;				//登录成功
		private int m_webRegisterSuccess;			//注册成功
		private int m_gameLogonSuccess;				//登录成功
		private int m_gameRegisterSuccess;			//注册成功
		private DateTime m_collectDate;				//录入时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化SystemStreamInfo
		/// </summary>
		public SystemStreamInfo()
		{
			m_dateID=0;
			m_webLogonSuccess=0;
			m_webRegisterSuccess=0;
			m_gameLogonSuccess=0;
			m_gameRegisterSuccess=0;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 日期标识
		/// </summary>
		public int DateID
		{
			get { return m_dateID; }
			set { m_dateID = value; }
		}

		/// <summary>
		/// 登录成功
		/// </summary>
		public int WebLogonSuccess
		{
			get { return m_webLogonSuccess; }
			set { m_webLogonSuccess = value; }
		}

		/// <summary>
		/// 注册成功
		/// </summary>
		public int WebRegisterSuccess
		{
			get { return m_webRegisterSuccess; }
			set { m_webRegisterSuccess = value; }
		}

		/// <summary>
		/// 登录成功
		/// </summary>
		public int GameLogonSuccess
		{
			get { return m_gameLogonSuccess; }
			set { m_gameLogonSuccess = value; }
		}

		/// <summary>
		/// 注册成功
		/// </summary>
		public int GameRegisterSuccess
		{
			get { return m_gameRegisterSuccess; }
			set { m_gameRegisterSuccess = value; }
		}

		/// <summary>
		/// 录入时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
