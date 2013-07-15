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
	/// 实体类 GlobalShareInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GlobalShareInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GlobalShareInfo" ;

		/// <summary>
		/// 服务标识
		/// </summary>
		public const string _ShareID = "ShareID" ;

		/// <summary>
		/// 服务名称
		/// </summary>
		public const string _ShareName = "ShareName" ;

		/// <summary>
		/// 服务别名
		/// </summary>
		public const string _ShareAlias = "ShareAlias" ;

		/// <summary>
		/// 服务说明
		/// </summary>
		public const string _ShareNote = "ShareNote" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_shareID;					//服务标识
		private string m_shareName;				//服务名称
		private string m_shareAlias;			//服务别名
		private string m_shareNote;				//服务说明
		private DateTime m_collectDate;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GlobalShareInfo
		/// </summary>
		public GlobalShareInfo()
		{
			m_shareID=0;
			m_shareName="";
			m_shareAlias="";
			m_shareNote="";
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 服务标识
		/// </summary>
		public int ShareID
		{
			get { return m_shareID; }
			set { m_shareID = value; }
		}

		/// <summary>
		/// 服务名称
		/// </summary>
		public string ShareName
		{
			get { return m_shareName; }
			set { m_shareName = value; }
		}

		/// <summary>
		/// 服务别名
		/// </summary>
		public string ShareAlias
		{
			get { return m_shareAlias; }
			set { m_shareAlias = value; }
		}

		/// <summary>
		/// 服务说明
		/// </summary>
		public string ShareNote
		{
			get { return m_shareNote; }
			set { m_shareNote = value; }
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
