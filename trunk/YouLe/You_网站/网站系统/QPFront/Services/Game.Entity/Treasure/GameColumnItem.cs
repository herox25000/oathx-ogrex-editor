/*
 * 版本：4.0
 * 时间：2011-8-1
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
	/// 实体类 GameColumnItem。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameColumnItem  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameColumnItem" ;

		/// <summary>
		/// 排列标识
		/// </summary>
		public const string _SortID = "SortID" ;

		/// <summary>
		/// 列头名字
		/// </summary>
		public const string _ColumnName = "ColumnName" ;

		/// <summary>
		/// 列表宽度
		/// </summary>
		public const string _ColumnWidth = "ColumnWidth" ;

		/// <summary>
		/// 数据描述
		/// </summary>
		public const string _DataDescribe = "DataDescribe" ;
		#endregion

		#region 私有变量
		private int m_sortID;				//排列标识
		private string m_columnName;		//列头名字
		private byte m_columnWidth;			//列表宽度
		private byte m_dataDescribe;		//数据描述
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameColumnItem
		/// </summary>
		public GameColumnItem()
		{
			m_sortID=0;
			m_columnName="";
			m_columnWidth=0;
			m_dataDescribe=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 排列标识
		/// </summary>
		public int SortID
		{
			get { return m_sortID; }
			set { m_sortID = value; }
		}

		/// <summary>
		/// 列头名字
		/// </summary>
		public string ColumnName
		{
			get { return m_columnName; }
			set { m_columnName = value; }
		}

		/// <summary>
		/// 列表宽度
		/// </summary>
		public byte ColumnWidth
		{
			get { return m_columnWidth; }
			set { m_columnWidth = value; }
		}

		/// <summary>
		/// 数据描述
		/// </summary>
		public byte DataDescribe
		{
			get { return m_dataDescribe; }
			set { m_dataDescribe = value; }
		}
		#endregion
	}
}
