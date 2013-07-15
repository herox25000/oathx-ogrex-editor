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
	/// 实体类 LivcardAssociator。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class LivcardAssociator  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "LivcardAssociator" ;

		/// <summary>
		/// 会员卡索引
		/// </summary>
		public const string _CardID = "CardID" ;

		/// <summary>
		/// 卡号
		/// </summary>
		public const string _SerialID = "SerialID" ;

		/// <summary>
		/// 密码
		/// </summary>
		public const string _Password = "Password" ;

		/// <summary>
		/// 生产批次
		/// </summary>
		public const string _BuildID = "BuildID" ;

		/// <summary>
		/// 会员卡类型标识
		/// </summary>
		public const string _CardTypeID = "CardTypeID" ;

		/// <summary>
		/// 会员卡价格
		/// </summary>
		public const string _CardPrice = "CardPrice" ;

		/// <summary>
		/// 会员卡金币数
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

		/// <summary>
		/// 有效时间
		/// </summary>
		public const string _ValidDate = "ValidDate" ;

		/// <summary>
		/// 生产日期
		/// </summary>
		public const string _BuildDate = "BuildDate" ;

		/// <summary>
		/// 使用时间
		/// </summary>
		public const string _ApplyDate = "ApplyDate" ;

		/// <summary>
		/// 0:全部用户,1:新注册用户,2:第一次充值用户
		/// </summary>
		public const string _UseRange = "UseRange" ;

		/// <summary>
		/// 销售商
		/// </summary>
		public const string _SalesPerson = "SalesPerson" ;

		/// <summary>
		/// 禁用标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_cardID;				//会员卡索引
		private string m_serialID;			//卡号
		private string m_password;			//密码
		private int m_buildID;				//生产批次
		private int m_cardTypeID;			//会员卡类型标识
		private decimal m_cardPrice;		//会员卡价格
		private long m_cardGold;			//会员卡金币数
		private byte m_memberOrder;			//会员等级
		private int m_memberDays;			//会员天数
		private int m_userRight;			//用户权限
		private int m_serviceRight;			//服务权限
		private DateTime m_validDate;		//有效时间
		private DateTime m_buildDate;		//生产日期
		private DateTime m_applyDate;		//使用时间
		private int m_useRange;				//0:全部用户,1:新注册用户,2:第一次充值用户
		private string m_salesPerson;		//销售商
		private byte m_nullity;				//禁用标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化LivcardAssociator
		/// </summary>
		public LivcardAssociator()
		{
			m_cardID=0;
			m_serialID="";
			m_password="";
			m_buildID=0;
			m_cardTypeID=0;
			m_cardPrice=0;
			m_cardGold=0;
			m_memberOrder=0;
			m_memberDays=0;
			m_userRight=0;
			m_serviceRight=0;
			m_validDate=DateTime.Now;
			m_buildDate=DateTime.Now;
			m_applyDate=DateTime.Now;
			m_useRange=0;
			m_salesPerson="";
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 会员卡索引
		/// </summary>
		public int CardID
		{
			get { return m_cardID; }
			set { m_cardID = value; }
		}

		/// <summary>
		/// 卡号
		/// </summary>
		public string SerialID
		{
			get { return m_serialID; }
			set { m_serialID = value; }
		}

		/// <summary>
		/// 密码
		/// </summary>
		public string Password
		{
			get { return m_password; }
			set { m_password = value; }
		}

		/// <summary>
		/// 生产批次
		/// </summary>
		public int BuildID
		{
			get { return m_buildID; }
			set { m_buildID = value; }
		}

		/// <summary>
		/// 会员卡类型标识
		/// </summary>
		public int CardTypeID
		{
			get { return m_cardTypeID; }
			set { m_cardTypeID = value; }
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
		/// 会员卡金币数
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

		/// <summary>
		/// 有效时间
		/// </summary>
		public DateTime ValidDate
		{
			get { return m_validDate; }
			set { m_validDate = value; }
		}

		/// <summary>
		/// 生产日期
		/// </summary>
		public DateTime BuildDate
		{
			get { return m_buildDate; }
			set { m_buildDate = value; }
		}

		/// <summary>
		/// 使用时间
		/// </summary>
		public DateTime ApplyDate
		{
			get { return m_applyDate; }
			set { m_applyDate = value; }
		}

		/// <summary>
		/// 0:全部用户,1:新注册用户,2:第一次充值用户
		/// </summary>
		public int UseRange
		{
			get { return m_useRange; }
			set { m_useRange = value; }
		}

		/// <summary>
		/// 销售商
		/// </summary>
		public string SalesPerson
		{
			get { return m_salesPerson; }
			set { m_salesPerson = value; }
		}

		/// <summary>
		/// 禁用标志
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}
		#endregion
	}
}
