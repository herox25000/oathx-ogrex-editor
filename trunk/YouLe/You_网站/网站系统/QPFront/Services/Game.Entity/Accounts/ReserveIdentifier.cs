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

namespace Game.Entity.Accounts
{
	/// <summary>
	/// 实体类 ReserveIdentifier。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class ReserveIdentifier  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "ReserveIdentifier" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _GameID = "GameID" ;

		/// <summary>
		/// 标识等级
		/// </summary>
		public const string _IDLevel = "IDLevel" ;

		/// <summary>
		/// 分配标志
		/// </summary>
		public const string _Distribute = "Distribute" ;
		#endregion

		#region 私有变量
		private int m_gameID;				//游戏标识
		private int m_iDLevel;				//标识等级
		private bool m_distribute;			//分配标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化ReserveIdentifier
		/// </summary>
		public ReserveIdentifier()
		{
			m_gameID=0;
			m_iDLevel=0;
			m_distribute=false;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 游戏标识
		/// </summary>
		public int GameID
		{
			get { return m_gameID; }
			set { m_gameID = value; }
		}

		/// <summary>
		/// 标识等级
		/// </summary>
		public int IDLevel
		{
			get { return m_iDLevel; }
			set { m_iDLevel = value; }
		}

		/// <summary>
		/// 分配标志
		/// </summary>
		public bool Distribute
		{
			get { return m_distribute; }
			set { m_distribute = value; }
		}
		#endregion
	}
}
