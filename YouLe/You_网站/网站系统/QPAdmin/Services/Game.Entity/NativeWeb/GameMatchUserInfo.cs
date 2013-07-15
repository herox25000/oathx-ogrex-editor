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

namespace Game.Entity.NativeWeb
{
	/// <summary>
	/// 实体类 GameMatchUserInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameMatchUserInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameMatchUserInfo" ;

		/// <summary>
		/// 赛事标识
		/// </summary>
		public const string _MatchID = "MatchID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 用户帐号
		/// </summary>
		public const string _Accounts = "Accounts" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _GameID = "GameID" ;

		/// <summary>
		/// 姓名
		/// </summary>
		public const string _Compellation = "Compellation" ;

		/// <summary>
		/// 性别
		/// </summary>
		public const string _Gender = "Gender" ;

		/// <summary>
		/// 身份证
		/// </summary>
		public const string _PassportID = "PassportID" ;

		/// <summary>
		/// 手机
		/// </summary>
		public const string _MobilePhone = "MobilePhone" ;

		/// <summary>
		/// 电子邮箱
		/// </summary>
		public const string _EMail = "EMail" ;

		/// <summary>
		/// QQ
		/// </summary>
		public const string _QQ = "QQ" ;

		/// <summary>
		/// 详细地址
		/// </summary>
		public const string _DwellingPlace = "DwellingPlace" ;

		/// <summary>
		/// 邮编
		/// </summary>
		public const string _PostalCode = "PostalCode" ;

		/// <summary>
		/// 禁用状态
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 报名地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 收集日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_matchID;					//赛事标识
		private int m_userID;					//用户标识
		private string m_accounts;				//用户帐号
		private int m_gameID;					//游戏标识
		private string m_compellation;			//姓名
		private byte m_gender;					//性别
		private string m_passportID;			//身份证
		private string m_mobilePhone;			//手机
		private string m_eMail;					//电子邮箱
		private string m_qQ;					//QQ
		private string m_dwellingPlace;			//详细地址
		private string m_postalCode;			//邮编
		private byte m_nullity;					//禁用状态
		private string m_clientIP;				//报名地址
		private DateTime m_collectDate;			//收集日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameMatchUserInfo
		/// </summary>
		public GameMatchUserInfo()
		{
			m_matchID=0;
			m_userID=0;
			m_accounts="";
			m_gameID=0;
			m_compellation="";
			m_gender=0;
			m_passportID="";
			m_mobilePhone="";
			m_eMail="";
			m_qQ="";
			m_dwellingPlace="";
			m_postalCode="";
			m_nullity=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 赛事标识
		/// </summary>
		public int MatchID
		{
			get { return m_matchID; }
			set { m_matchID = value; }
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
		/// 用户帐号
		/// </summary>
		public string Accounts
		{
			get { return m_accounts; }
			set { m_accounts = value; }
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
		/// 姓名
		/// </summary>
		public string Compellation
		{
			get { return m_compellation; }
			set { m_compellation = value; }
		}

		/// <summary>
		/// 性别
		/// </summary>
		public byte Gender
		{
			get { return m_gender; }
			set { m_gender = value; }
		}

		/// <summary>
		/// 身份证
		/// </summary>
		public string PassportID
		{
			get { return m_passportID; }
			set { m_passportID = value; }
		}

		/// <summary>
		/// 手机
		/// </summary>
		public string MobilePhone
		{
			get { return m_mobilePhone; }
			set { m_mobilePhone = value; }
		}

		/// <summary>
		/// 电子邮箱
		/// </summary>
		public string EMail
		{
			get { return m_eMail; }
			set { m_eMail = value; }
		}

		/// <summary>
		/// QQ
		/// </summary>
		public string QQ
		{
			get { return m_qQ; }
			set { m_qQ = value; }
		}

		/// <summary>
		/// 详细地址
		/// </summary>
		public string DwellingPlace
		{
			get { return m_dwellingPlace; }
			set { m_dwellingPlace = value; }
		}

		/// <summary>
		/// 邮编
		/// </summary>
		public string PostalCode
		{
			get { return m_postalCode; }
			set { m_postalCode = value; }
		}

		/// <summary>
		/// 禁用状态
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 报名地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 收集日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
