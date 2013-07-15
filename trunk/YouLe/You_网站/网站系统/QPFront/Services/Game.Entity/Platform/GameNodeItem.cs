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
	/// 实体类 GameNodeItem。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameNodeItem  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameNodeItem" ;

		/// <summary>
		/// 节点标识
		/// </summary>
		public const string _NodeID = "NodeID" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 挂接标识
		/// </summary>
		public const string _JoinID = "JoinID" ;

		/// <summary>
		/// 排序标识
		/// </summary>
		public const string _SortID = "SortID" ;

		/// <summary>
		/// 节点名字
		/// </summary>
		public const string _NodeName = "NodeName" ;

		/// <summary>
		/// 无效标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_nodeID;				//节点标识
		private int m_kindID;				//类型标识
		private int m_joinID;				//挂接标识
		private int m_sortID;				//排序标识
		private string m_nodeName;			//节点名字
		private byte m_nullity;				//无效标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameNodeItem
		/// </summary>
		public GameNodeItem()
		{
			m_nodeID=0;
			m_kindID=0;
			m_joinID=0;
			m_sortID=0;
			m_nodeName="";
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 节点标识
		/// </summary>
		public int NodeID
		{
			get { return m_nodeID; }
			set { m_nodeID = value; }
		}

		/// <summary>
		/// 类型标识
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
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
		/// 节点名字
		/// </summary>
		public string NodeName
		{
			get { return m_nodeName; }
			set { m_nodeName = value; }
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
