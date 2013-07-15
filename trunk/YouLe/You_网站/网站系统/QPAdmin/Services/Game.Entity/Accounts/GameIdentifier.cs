/*
 * 版本：4.0
 * 时间：2011-9-27
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
	/// 实体类 GameIdentifier。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameIdentifier  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameIdentifier" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _GameID = "GameID" ;

		/// <summary>
		/// 标识等级
		/// </summary>
		public const string _IDLevel = "IDLevel" ;
		#endregion

		#region 私有变量
		private int m_userID;			//用户标识
		private int m_gameID;			//游戏标识
		private int m_iDLevel;			//标识等级
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameIdentifier
		/// </summary>
		public GameIdentifier()
		{
			m_userID=0;
			m_gameID=0;
			m_iDLevel=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
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
		/// 标识等级
		/// </summary>
		public int IDLevel
		{
			get { return m_iDLevel; }
			set { m_iDLevel = value; }
		}
		#endregion
	}
}
