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
	/// 实体类 GamePageItem。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GamePageItem  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GamePageItem" ;

		/// <summary>
		/// 页面标识
		/// </summary>
		public const string _PageID = "PageID" ;

		/// <summary>
		/// 类型索引
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 节点索引
		/// </summary>
		public const string _NodeID = "NodeID" ;

		/// <summary>
		/// 排序标识
		/// </summary>
		public const string _SortID = "SortID" ;

		/// <summary>
		/// 操作类型
		/// </summary>
		public const string _OperateType = "OperateType" ;

		/// <summary>
		/// 显示名字
		/// </summary>
		public const string _DisplayName = "DisplayName" ;

		/// <summary>
		/// 跳转地址
		/// </summary>
		public const string _ResponseUrl = "ResponseUrl" ;

		/// <summary>
		/// 无效标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_pageID;				//页面标识
		private int m_kindID;				//类型索引
		private int m_nodeID;				//节点索引
		private int m_sortID;				//排序标识
		private int m_operateType;			//操作类型
		private string m_displayName;		//显示名字
		private string m_responseUrl;		//跳转地址
		private byte m_nullity;				//无效标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GamePageItem
		/// </summary>
		public GamePageItem()
		{
			m_pageID=0;
			m_kindID=0;
			m_nodeID=0;
			m_sortID=0;
			m_operateType=0;
			m_displayName="";
			m_responseUrl="";
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 页面标识
		/// </summary>
		public int PageID
		{
			get { return m_pageID; }
			set { m_pageID = value; }
		}

		/// <summary>
		/// 类型索引
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 节点索引
		/// </summary>
		public int NodeID
		{
			get { return m_nodeID; }
			set { m_nodeID = value; }
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
		/// 操作类型
		/// </summary>
		public int OperateType
		{
			get { return m_operateType; }
			set { m_operateType = value; }
		}

		/// <summary>
		/// 显示名字
		/// </summary>
		public string DisplayName
		{
			get { return m_displayName; }
			set { m_displayName = value; }
		}

		/// <summary>
		/// 跳转地址
		/// </summary>
		public string ResponseUrl
		{
			get { return m_responseUrl; }
			set { m_responseUrl = value; }
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
