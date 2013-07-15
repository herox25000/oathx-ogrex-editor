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
	/// 实体类 AccountsFace。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class AccountsFace  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "AccountsFace" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ID = "ID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CustomFace = "CustomFace" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _InsertTime = "InsertTime" ;

		/// <summary>
		/// 登录地址
		/// </summary>
		public const string _InsertAddr = "InsertAddr" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _InsertMachine = "InsertMachine" ;
		#endregion

		#region 私有变量
		private int m_iD;						//
		private int m_userID;					//用户标识
		private System.Byte[] m_customFace;		//
		private DateTime m_insertTime;			//
		private string m_insertAddr;			//登录地址
		private string m_insertMachine;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化AccountsFace
		/// </summary>
		public AccountsFace()
		{
			m_iD=0;
			m_userID=0;
			m_customFace=null;
			m_insertTime=DateTime.Now;
			m_insertAddr="";
			m_insertMachine="";
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
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public System.Byte[] CustomFace
		{
			get { return m_customFace; }
			set { m_customFace = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public DateTime InsertTime
		{
			get { return m_insertTime; }
			set { m_insertTime = value; }
		}

		/// <summary>
		/// 登录地址
		/// </summary>
		public string InsertAddr
		{
			get { return m_insertAddr; }
			set { m_insertAddr = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string InsertMachine
		{
			get { return m_insertMachine; }
			set { m_insertMachine = value; }
		}
		#endregion
	}
}
