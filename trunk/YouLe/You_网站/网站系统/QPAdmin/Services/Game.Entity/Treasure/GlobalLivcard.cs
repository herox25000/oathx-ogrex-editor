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
	/// 实体类 GlobalLivcard。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GlobalLivcard  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GlobalLivcard" ;

		/// <summary>
		/// 会员卡标识
		/// </summary>
		public const string _CardTypeID = "CardTypeID" ;

		/// <summary>
		/// 会员卡名称
		/// </summary>
		public const string _CardName = "CardName" ;

		/// <summary>
		/// 会员卡价格
		/// </summary>
		public const string _CardPrice = "CardPrice" ;

		/// <summary>
		/// 金币数目
		/// </summary>
		public const string _CardGold = "CardGold" ;

		/// <summary>
		/// 会员等级
		/// </summary>
		public const string _MemberOrder = "MemberOrder" ;

		/// <summary>
		/// 会员天数
		/// </summary>
		public const string _MemberDays = "MemberDays" ;

		/// <summary>
		/// 用户权限
		/// </summary>
		public const string _UserRight = "UserRight" ;

		/// <summary>
		/// 服务权限
		/// </summary>
		public const string _ServiceRight = "ServiceRight" ;
		#endregion

		#region 私有变量
		private int m_cardTypeID;			//会员卡标识
		private string m_cardName;			//会员卡名称
		private decimal m_cardPrice;		//会员卡价格
		private long m_cardGold;			//金币数目
		private byte m_memberOrder;			//会员等级
		private int m_memberDays;			//会员天数
		private int m_userRight;			//用户权限
		private int m_serviceRight;			//服务权限
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GlobalLivcard
		/// </summary>
		public GlobalLivcard()
		{
			m_cardTypeID=0;
			m_cardName="";
			m_cardPrice=0;
			m_cardGold=0;
			m_memberOrder=0;
			m_memberDays=0;
			m_userRight=0;
			m_serviceRight=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 会员卡标识
		/// </summary>
		public int CardTypeID
		{
			get { return m_cardTypeID; }
			set { m_cardTypeID = value; }
		}

		/// <summary>
		/// 会员卡名称
		/// </summary>
		public string CardName
		{
			get { return m_cardName; }
			set { m_cardName = value; }
		}

		/// <summary>
		/// 会员卡价格
		/// </summary>
		public decimal CardPrice
		{
			get { return m_cardPrice; }
			set { m_cardPrice = value; }
		}

		/// <summary>
		/// 金币数目
		/// </summary>
		public long CardGold
		{
			get { return m_cardGold; }
			set { m_cardGold = value; }
		}

		/// <summary>
		/// 会员等级
		/// </summary>
		public byte MemberOrder
		{
			get { return m_memberOrder; }
			set { m_memberOrder = value; }
		}

		/// <summary>
		/// 会员天数
		/// </summary>
		public int MemberDays
		{
			get { return m_memberDays; }
			set { m_memberDays = value; }
		}

		/// <summary>
		/// 用户权限
		/// </summary>
		public int UserRight
		{
			get { return m_userRight; }
			set { m_userRight = value; }
		}

		/// <summary>
		/// 服务权限
		/// </summary>
		public int ServiceRight
		{
			get { return m_serviceRight; }
			set { m_serviceRight = value; }
		}
		#endregion
	}
}
