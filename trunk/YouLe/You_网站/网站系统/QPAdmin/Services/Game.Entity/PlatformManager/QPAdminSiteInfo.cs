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
		/// 
		/// </summary>
		public const string _SiteName = "SiteName" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _PageSize = "PageSize" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CopyRight = "CopyRight" ;
		#endregion

		#region 私有变量
		private int m_siteID;				//
		private string m_siteName;			//
		private int m_pageSize;				//
		private string m_copyRight;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化QPAdminSiteInfo
		/// </summary>
		public QPAdminSiteInfo()
		{
			m_siteID=0;
			m_siteName="";
			m_pageSize=0;
			m_copyRight="";
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
		/// 
		/// </summary>
		public string SiteName
		{
			get { return m_siteName; }
			set { m_siteName = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int PageSize
		{
			get { return m_pageSize; }
			set { m_pageSize = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string CopyRight
		{
			get { return m_copyRight; }
			set { m_copyRight = value; }
		}
		#endregion
	}
}
