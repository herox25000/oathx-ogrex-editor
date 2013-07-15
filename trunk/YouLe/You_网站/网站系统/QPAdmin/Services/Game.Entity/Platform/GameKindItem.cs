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
	/// 实体类 GameKindItem。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameKindItem  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameKindItem" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _GameID = "GameID" ;

		/// <summary>
		/// 种类标识
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
		public const string _KindName = "KindName" ;

		/// <summary>
		/// 进程名字
		/// </summary>
		public const string _ProcessName = "ProcessName" ;

		/// <summary>
		/// 跳转地址
		/// </summary>
		public const string _GameRuleUrl = "GameRuleUrl" ;

		/// <summary>
		/// 下载地址
		/// </summary>
		public const string _DownLoadUrl = "DownLoadUrl" ;

		/// <summary>
		/// 无效标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_kindID;					//类型标识
		private int m_gameID;					//游戏标识
		private int m_typeID;					//种类标识
		private int m_joinID;					//挂接标识
		private int m_sortID;					//排序标识
		private string m_kindName;				//类型名字
		private string m_processName;			//进程名字
		private string m_gameRuleUrl;			//跳转地址
		private string m_downLoadUrl;			//下载地址
		private byte m_nullity;					//无效标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameKindItem
		/// </summary>
		public GameKindItem()
		{
			m_kindID=0;
			m_gameID=0;
			m_typeID=0;
			m_joinID=0;
			m_sortID=0;
			m_kindName="";
			m_processName="";
			m_gameRuleUrl="";
			m_downLoadUrl="";
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 类型标识
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 游戏标识
		/// </summary>
		public int GameID
		{
			get { return m_gameID; }
			set { m_gameID = value; }
		}

		/// <summary>
		/// 种类标识
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
		public string KindName
		{
			get { return m_kindName; }
			set { m_kindName = value; }
		}

		/// <summary>
		/// 进程名字
		/// </summary>
		public string ProcessName
		{
			get { return m_processName; }
			set { m_processName = value; }
		}

		/// <summary>
		/// 跳转地址
		/// </summary>
		public string GameRuleUrl
		{
			get { return m_gameRuleUrl; }
			set { m_gameRuleUrl = value; }
		}

		/// <summary>
		/// 下载地址
		/// </summary>
		public string DownLoadUrl
		{
			get { return m_downLoadUrl; }
			set { m_downLoadUrl = value; }
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
