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
	/// 实体类 AccountsProtect。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class AccountsProtect  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "AccountsProtect" ;

		/// <summary>
		/// 密保标识
		/// </summary>
		public const string _ProtectID = "ProtectID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 问题一
		/// </summary>
		public const string _Question1 = "Question1" ;

		/// <summary>
		/// 答案一
		/// </summary>
		public const string _Response1 = "Response1" ;

		/// <summary>
		/// 问题二
		/// </summary>
		public const string _Question2 = "Question2" ;

		/// <summary>
		/// 答案二
		/// </summary>
		public const string _Response2 = "Response2" ;

		/// <summary>
		/// 问题三
		/// </summary>
		public const string _Question3 = "Question3" ;

		/// <summary>
		/// 答案三
		/// </summary>
		public const string _Response3 = "Response3" ;

		/// <summary>
		/// 证件号码
		/// </summary>
		public const string _PassportID = "PassportID" ;

		/// <summary>
		/// 证件类型
		/// </summary>
		public const string _PassportType = "PassportType" ;

		/// <summary>
		/// 安全邮箱
		/// </summary>
		public const string _SafeEmail = "SafeEmail" ;

		/// <summary>
		/// 创建地址
		/// </summary>
		public const string _CreateIP = "CreateIP" ;

		/// <summary>
		/// 修改地址
		/// </summary>
		public const string _ModifyIP = "ModifyIP" ;

		/// <summary>
		/// 创建日期
		/// </summary>
		public const string _CreateDate = "CreateDate" ;

		/// <summary>
		/// 修改日期
		/// </summary>
		public const string _ModifyDate = "ModifyDate" ;
		#endregion

		#region 私有变量
		private int m_protectID;			//密保标识
		private int m_userID;				//用户标识
		private string m_question1;			//问题一
		private string m_response1;			//答案一
		private string m_question2;			//问题二
		private string m_response2;			//答案二
		private string m_question3;			//问题三
		private string m_response3;			//答案三
		private string m_passportID;		//证件号码
		private byte m_passportType;		//证件类型
		private string m_safeEmail;			//安全邮箱
		private string m_createIP;			//创建地址
		private string m_modifyIP;			//修改地址
		private DateTime m_createDate;		//创建日期
		private DateTime m_modifyDate;		//修改日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化AccountsProtect
		/// </summary>
		public AccountsProtect()
		{
			m_protectID=0;
			m_userID=0;
			m_question1="";
			m_response1="";
			m_question2="";
			m_response2="";
			m_question3="";
			m_response3="";
			m_passportID="";
			m_passportType=0;
			m_safeEmail="";
			m_createIP="";
			m_modifyIP="";
			m_createDate=DateTime.Now;
			m_modifyDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 密保标识
		/// </summary>
		public int ProtectID
		{
			get { return m_protectID; }
			set { m_protectID = value; }
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
		/// 问题一
		/// </summary>
		public string Question1
		{
			get { return m_question1; }
			set { m_question1 = value; }
		}

		/// <summary>
		/// 答案一
		/// </summary>
		public string Response1
		{
			get { return m_response1; }
			set { m_response1 = value; }
		}

		/// <summary>
		/// 问题二
		/// </summary>
		public string Question2
		{
			get { return m_question2; }
			set { m_question2 = value; }
		}

		/// <summary>
		/// 答案二
		/// </summary>
		public string Response2
		{
			get { return m_response2; }
			set { m_response2 = value; }
		}

		/// <summary>
		/// 问题三
		/// </summary>
		public string Question3
		{
			get { return m_question3; }
			set { m_question3 = value; }
		}

		/// <summary>
		/// 答案三
		/// </summary>
		public string Response3
		{
			get { return m_response3; }
			set { m_response3 = value; }
		}

		/// <summary>
		/// 证件号码
		/// </summary>
		public string PassportID
		{
			get { return m_passportID; }
			set { m_passportID = value; }
		}

		/// <summary>
		/// 证件类型
		/// </summary>
		public byte PassportType
		{
			get { return m_passportType; }
			set { m_passportType = value; }
		}

		/// <summary>
		/// 安全邮箱
		/// </summary>
		public string SafeEmail
		{
			get { return m_safeEmail; }
			set { m_safeEmail = value; }
		}

		/// <summary>
		/// 创建地址
		/// </summary>
		public string CreateIP
		{
			get { return m_createIP; }
			set { m_createIP = value; }
		}

		/// <summary>
		/// 修改地址
		/// </summary>
		public string ModifyIP
		{
			get { return m_modifyIP; }
			set { m_modifyIP = value; }
		}

		/// <summary>
		/// 创建日期
		/// </summary>
		public DateTime CreateDate
		{
			get { return m_createDate; }
			set { m_createDate = value; }
		}

		/// <summary>
		/// 修改日期
		/// </summary>
		public DateTime ModifyDate
		{
			get { return m_modifyDate; }
			set { m_modifyDate = value; }
		}
		#endregion
	}
}
