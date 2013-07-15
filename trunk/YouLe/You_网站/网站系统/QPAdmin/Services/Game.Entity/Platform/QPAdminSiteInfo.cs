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

namespace Game.Entity.Platform
{
	/// <summary>
	/// 实体类 QPAdminSiteInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class QPAdminSiteInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "QPAdminSiteInfo" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _SiteID = "SiteID" ;

		/// <summary>
		/// 转帐税收
		/// </summary>
		public const string _Revenue = "Revenue" ;

		/// <summary>
		/// 注册赠送金币
		/// </summary>
		public const string _GameScore = "GameScore" ;
		#endregion

		#region 私有变量
		private int m_siteID;				//
		private decimal m_revenue;			//转帐税收
		private long m_gameScore;			//注册赠送金币
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化QPAdminSiteInfo
		/// </summary>
		public QPAdminSiteInfo()
		{
			m_siteID=0;
			m_revenue=0;
			m_gameScore=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int SiteID
		{
			get { return m_siteID; }
			set { m_siteID = value; }
		}

		/// <summary>
		/// 转帐税收
		/// </summary>
		public decimal Revenue
		{
			get { return m_revenue; }
			set { m_revenue = value; }
		}

		/// <summary>
		/// 注册赠送金币
		/// </summary>
		public long GameScore
		{
			get { return m_gameScore; }
			set { m_gameScore = value; }
		}
		#endregion
	}
}
