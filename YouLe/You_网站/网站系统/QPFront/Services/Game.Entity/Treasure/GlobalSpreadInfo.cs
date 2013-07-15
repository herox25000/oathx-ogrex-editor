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
	/// 实体类 GlobalSpreadInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GlobalSpreadInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GlobalSpreadInfo" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ID = "ID" ;

		/// <summary>
		/// 注册时赠送金币数目
		/// </summary>
		public const string _RegisterGrantScore = "RegisterGrantScore" ;

		/// <summary>
		/// 在线时长（单位：秒）
		/// </summary>
		public const string _PlayTimeCount = "PlayTimeCount" ;

		/// <summary>
		/// 根据在线时长赠送金币数目
		/// </summary>
		public const string _PlayTimeGrantScore = "PlayTimeGrantScore" ;

		/// <summary>
		/// 充值赠送比率
		/// </summary>
		public const string _FillGrantRate = "FillGrantRate" ;

		/// <summary>
		/// 结算赠送比率
		/// </summary>
		public const string _BalanceRate = "BalanceRate" ;

		/// <summary>
		/// 结算最小值
		/// </summary>
		public const string _MinBalanceScore = "MinBalanceScore" ;
		#endregion

		#region 私有变量
		private int m_iD;							//
		private int m_registerGrantScore;			//注册时赠送金币数目
		private int m_playTimeCount;				//在线时长（单位：秒）
		private int m_playTimeGrantScore;			//根据在线时长赠送金币数目
		private decimal m_fillGrantRate;			//充值赠送比率
		private decimal m_balanceRate;				//结算赠送比率
		private int m_minBalanceScore;				//结算最小值
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GlobalSpreadInfo
		/// </summary>
		public GlobalSpreadInfo()
		{
			m_iD=0;
			m_registerGrantScore=0;
			m_playTimeCount=0;
			m_playTimeGrantScore=0;
			m_fillGrantRate=0;
			m_balanceRate=0;
			m_minBalanceScore=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int ID
		{
			get { return m_iD; }
			set { m_iD = value; }
		}

		/// <summary>
		/// 注册时赠送金币数目
		/// </summary>
		public int RegisterGrantScore
		{
			get { return m_registerGrantScore; }
			set { m_registerGrantScore = value; }
		}

		/// <summary>
		/// 在线时长（单位：秒）
		/// </summary>
		public int PlayTimeCount
		{
			get { return m_playTimeCount; }
			set { m_playTimeCount = value; }
		}

		/// <summary>
		/// 根据在线时长赠送金币数目
		/// </summary>
		public int PlayTimeGrantScore
		{
			get { return m_playTimeGrantScore; }
			set { m_playTimeGrantScore = value; }
		}

		/// <summary>
		/// 充值赠送比率
		/// </summary>
		public decimal FillGrantRate
		{
			get { return m_fillGrantRate; }
			set { m_fillGrantRate = value; }
		}

		/// <summary>
		/// 结算赠送比率
		/// </summary>
		public decimal BalanceRate
		{
			get { return m_balanceRate; }
			set { m_balanceRate = value; }
		}

		/// <summary>
		/// 结算最小值
		/// </summary>
		public int MinBalanceScore
		{
			get { return m_minBalanceScore; }
			set { m_minBalanceScore = value; }
		}
		#endregion
	}
}
