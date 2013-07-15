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
	/// 实体类 StreamPlayPresent。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class StreamPlayPresent  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "StreamPlayPresent" ;

		/// <summary>
		/// 时间标识
		/// </summary>
		public const string _DateID = "DateID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 赠送次数
		/// </summary>
		public const string _PresentCount = "PresentCount" ;

		/// <summary>
		/// 游戏泡分总数
		/// </summary>
		public const string _PresentScore = "PresentScore" ;

		/// <summary>
		/// 游戏时长
		/// </summary>
		public const string _PlayTimeCount = "PlayTimeCount" ;

		/// <summary>
		/// 在线时长
		/// </summary>
		public const string _OnLineTimeCount = "OnLineTimeCount" ;

		/// <summary>
		/// 开始统计时间
		/// </summary>
		public const string _FirstDate = "FirstDate" ;

		/// <summary>
		/// 最后统计时间
		/// </summary>
		public const string _LastDate = "LastDate" ;
		#endregion

		#region 私有变量
		private int m_dateID;					//时间标识
		private int m_userID;					//用户标识
		private int m_presentCount;				//赠送次数
		private int m_presentScore;				//游戏泡分总数
		private int m_playTimeCount;			//游戏时长
		private int m_onLineTimeCount;			//在线时长
		private DateTime m_firstDate;			//开始统计时间
		private DateTime m_lastDate;			//最后统计时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化StreamPlayPresent
		/// </summary>
		public StreamPlayPresent()
		{
			m_dateID=0;
			m_userID=0;
			m_presentCount=0;
			m_presentScore=0;
			m_playTimeCount=0;
			m_onLineTimeCount=0;
			m_firstDate=DateTime.Now;
			m_lastDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 时间标识
		/// </summary>
		public int DateID
		{
			get { return m_dateID; }
			set { m_dateID = value; }
		}

		/// <summary>
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 赠送次数
		/// </summary>
		public int PresentCount
		{
			get { return m_presentCount; }
			set { m_presentCount = value; }
		}

		/// <summary>
		/// 游戏泡分总数
		/// </summary>
		public int PresentScore
		{
			get { return m_presentScore; }
			set { m_presentScore = value; }
		}

		/// <summary>
		/// 游戏时长
		/// </summary>
		public int PlayTimeCount
		{
			get { return m_playTimeCount; }
			set { m_playTimeCount = value; }
		}

		/// <summary>
		/// 在线时长
		/// </summary>
		public int OnLineTimeCount
		{
			get { return m_onLineTimeCount; }
			set { m_onLineTimeCount = value; }
		}

		/// <summary>
		/// 开始统计时间
		/// </summary>
		public DateTime FirstDate
		{
			get { return m_firstDate; }
			set { m_firstDate = value; }
		}

		/// <summary>
		/// 最后统计时间
		/// </summary>
		public DateTime LastDate
		{
			get { return m_lastDate; }
			set { m_lastDate = value; }
		}
		#endregion
	}
}
