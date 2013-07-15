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

namespace Game.Entity.Platform
{
	/// <summary>
	/// 实体类 GameTypeItem。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameTypeItem  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameTypeItem" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _TypeID = "TypeID" ;

		/// <summary>
		/// 挂接标识
		/// </summary>
		public const string _JoinID = "JoinID" ;

		/// <summary>
		/// 排序标识
		/// </summary>
		public const string _SortID = "SortID" ;

		/// <summary>
		/// 类型名字
		/// </summary>
		public const string _TypeName = "TypeName" ;

		/// <summary>
		/// 无效标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_typeID;				//类型标识
		private int m_joinID;				//挂接标识
		private int m_sortID;				//排序标识
		private string m_typeName;			//类型名字
		private byte m_nullity;				//无效标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameTypeItem
		/// </summary>
		public GameTypeItem()
		{
			m_typeID=0;
			m_joinID=0;
			m_sortID=0;
			m_typeName="";
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 类型标识
		/// </summary>
		public int TypeID
		{
			get { return m_typeID; }
			set { m_typeID = value; }
		}

		/// <summary>
		/// 挂接标识
		/// </summary>
		public int JoinID
		{
			get { return m_joinID; }
			set { m_joinID = value; }
		}

		/// <summary>
		/// 排序标识
		/// </summary>
		public int SortID
		{
			get { return m_sortID; }
			set { m_sortID = value; }
		}

		/// <summary>
		/// 类型名字
		/// </summary>
		public string TypeName
		{
			get { return m_typeName; }
			set { m_typeName = value; }
		}

		/// <summary>
		/// 无效标志
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}
		#endregion
	}
}
