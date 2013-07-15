/*
 * 版本：4.0
 * 时间：2011-8-30
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.PlatformManager
{
	/// <summary>
	/// 实体类 GrantTimeCountsInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GrantTimeCountsInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GrantTimeCountsInfo" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _GrantID = "GrantID" ;

		/// <summary>
		/// 赠送时段
		/// </summary>
		public const string _GrantCouts = "GrantCouts" ;

		/// <summary>
		/// 赠送积分数目
		/// </summary>
		public const string _GrantScore = "GrantScore" ;

		/// <summary>
		/// 赠送金币数目
		/// </summary>
		public const string _GrantGameScore = "GrantGameScore" ;

		/// <summary>
		/// 赠送魅力
		/// </summary>
		public const string _GrantLoveliness = "GrantLoveliness" ;

		/// <summary>
		/// 赠送类型(0,根据在线时间;1,根据游戏时间;2,根据整体时间)
		/// </summary>
		public const string _GrantType = "GrantType" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _GrantExp = "GrantExp" ;

		/// <summary>
		/// 增送经验
		/// </summary>
		public const string _SiteID = "SiteID" ;
		#endregion

		#region 私有变量
		private int m_grantID;					//
		private int m_grantCouts;				//赠送时段
		private int m_grantScore;				//赠送积分数目
		private int m_grantGameScore;			//赠送金币数目
		private int m_grantLoveliness;			//赠送魅力
		private int m_grantType;				//赠送类型(0,根据在线时间;1,根据游戏时间;2,根据整体时间)
		private int m_grantExp;					//
		private string m_siteID;				//增送经验
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GrantTimeCountsInfo
		/// </summary>
		public GrantTimeCountsInfo()
		{
			m_grantID=0;
			m_grantCouts=0;
			m_grantScore=0;
			m_grantGameScore=0;
			m_grantLoveliness=0;
			m_grantType=0;
			m_grantExp=0;
			m_siteID="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int GrantID
		{
			get { return m_grantID; }
			set { m_grantID = value; }
		}

		/// <summary>
		/// 赠送时段
		/// </summary>
		public int GrantCouts
		{
			get { return m_grantCouts; }
			set { m_grantCouts = value; }
		}

		/// <summary>
		/// 赠送积分数目
		/// </summary>
		public int GrantScore
		{
			get { return m_grantScore; }
			set { m_grantScore = value; }
		}

		/// <summary>
		/// 赠送金币数目
		/// </summary>
		public int GrantGameScore
		{
			get { return m_grantGameScore; }
			set { m_grantGameScore = value; }
		}

		/// <summary>
		/// 赠送魅力
		/// </summary>
		public int GrantLoveliness
		{
			get { return m_grantLoveliness; }
			set { m_grantLoveliness = value; }
		}

		/// <summary>
		/// 赠送类型(0,根据在线时间;1,根据游戏时间;2,根据整体时间)
		/// </summary>
		public int GrantType
		{
			get { return m_grantType; }
			set { m_grantType = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int GrantExp
		{
			get { return m_grantExp; }
			set { m_grantExp = value; }
		}

		/// <summary>
		/// 增送经验
		/// </summary>
		public string SiteID
		{
			get { return m_siteID; }
			set { m_siteID = value; }
		}
		#endregion
	}
}
