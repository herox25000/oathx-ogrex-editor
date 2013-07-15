/*
 * 版本：4.0
 * 时间：2011-9-28
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.Treasure
{
	/// <summary>
	/// 实体类 StreamShareInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class StreamShareInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "StreamShareInfo" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DateID = "DateID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ShareID = "ShareID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ShareTotals = "ShareTotals" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_dateID;				//
		private int m_shareID;				//
		private int m_shareTotals;			//
		private DateTime m_collectDate;		//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化StreamShareInfo
		/// </summary>
		public StreamShareInfo()
		{
			m_dateID=0;
			m_shareID=0;
			m_shareTotals=0;
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int DateID
		{
			get { return m_dateID; }
			set { m_dateID = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int ShareID
		{
			get { return m_shareID; }
			set { m_shareID = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int ShareTotals
		{
			get { return m_shareTotals; }
			set { m_shareTotals = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
