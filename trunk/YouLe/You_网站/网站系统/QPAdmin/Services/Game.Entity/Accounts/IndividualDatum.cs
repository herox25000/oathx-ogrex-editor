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
	/// 实体类 IndividualDatum。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class IndividualDatum  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "IndividualDatum" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 真实姓名
		/// </summary>
		public const string _Compellation = "Compellation" ;

		/// <summary>
		/// QQ 号码
		/// </summary>
		public const string _QQ = "QQ" ;

		/// <summary>
		/// 电子邮件
		/// </summary>
		public const string _EMail = "EMail" ;

		/// <summary>
		/// 固定电话
		/// </summary>
		public const string _SeatPhone = "SeatPhone" ;

		/// <summary>
		/// 手机号码
		/// </summary>
		public const string _MobilePhone = "MobilePhone" ;

		/// <summary>
		/// 详细住址
		/// </summary>
		public const string _DwellingPlace = "DwellingPlace" ;

		/// <summary>
		/// 邮政编码
		/// </summary>
		public const string _PostalCode = "PostalCode" ;

		/// <summary>
		/// 收集日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 用户备注
		/// </summary>
		public const string _UserNote = "UserNote" ;
		#endregion

		#region 私有变量
		private int m_userID;					//用户标识
		private string m_compellation;			//真实姓名
		private string m_qQ;					//QQ 号码
		private string m_eMail;					//电子邮件
		private string m_seatPhone;				//固定电话
		private string m_mobilePhone;			//手机号码
		private string m_dwellingPlace;			//详细住址
		private string m_postalCode;			//邮政编码
		private DateTime m_collectDate;			//收集日期
		private string m_userNote;				//用户备注
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化IndividualDatum
		/// </summary>
		public IndividualDatum()
		{
			m_userID=0;
			m_compellation="";
			m_qQ="";
			m_eMail="";
			m_seatPhone="";
			m_mobilePhone="";
			m_dwellingPlace="";
			m_postalCode="";
			m_collectDate=DateTime.Now;
			m_userNote="";
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
		/// 真实姓名
		/// </summary>
		public string Compellation
		{
			get { return m_compellation; }
			set { m_compellation = value; }
		}

		/// <summary>
		/// QQ 号码
		/// </summary>
		public string QQ
		{
			get { return m_qQ; }
			set { m_qQ = value; }
		}

		/// <summary>
		/// 电子邮件
		/// </summary>
		public string EMail
		{
			get { return m_eMail; }
			set { m_eMail = value; }
		}

		/// <summary>
		/// 固定电话
		/// </summary>
		public string SeatPhone
		{
			get { return m_seatPhone; }
			set { m_seatPhone = value; }
		}

		/// <summary>
		/// 手机号码
		/// </summary>
		public string MobilePhone
		{
			get { return m_mobilePhone; }
			set { m_mobilePhone = value; }
		}

		/// <summary>
		/// 详细住址
		/// </summary>
		public string DwellingPlace
		{
			get { return m_dwellingPlace; }
			set { m_dwellingPlace = value; }
		}

		/// <summary>
		/// 邮政编码
		/// </summary>
		public string PostalCode
		{
			get { return m_postalCode; }
			set { m_postalCode = value; }
		}

		/// <summary>
		/// 收集日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}

		/// <summary>
		/// 用户备注
		/// </summary>
		public string UserNote
		{
			get { return m_userNote; }
			set { m_userNote = value; }
		}
		#endregion
	}
}
