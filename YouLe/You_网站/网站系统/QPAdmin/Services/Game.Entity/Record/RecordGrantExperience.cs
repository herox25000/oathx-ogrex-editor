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

namespace Game.Entity.Record
{
	/// <summary>
	/// 实体类 RecordGrantExperience。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordGrantExperience  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordGrantExperience" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 管理员标识
		/// </summary>
		public const string _MasterID = "MasterID" ;

		/// <summary>
		/// 赠予地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 赠予时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 当前经验
		/// </summary>
		public const string _CurExperience = "CurExperience" ;

		/// <summary>
		/// 补加经验
		/// </summary>
		public const string _AddExperience = "AddExperience" ;

		/// <summary>
		/// 赠予原因
		/// </summary>
		public const string _Reason = "Reason" ;
		#endregion

		#region 私有变量
		private int m_recordID;				//记录标识
		private int m_masterID;				//管理员标识
		private string m_clientIP;			//赠予地址
		private DateTime m_collectDate;		//赠予时间
		private int m_userID;				//用户标识
		private int m_curExperience;		//当前经验
		private int m_addExperience;		//补加经验
		private string m_reason;			//赠予原因
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordGrantExperience
		/// </summary>
		public RecordGrantExperience()
		{
			m_recordID=0;
			m_masterID=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
			m_userID=0;
			m_curExperience=0;
			m_addExperience=0;
			m_reason="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 记录标识
		/// </summary>
		public int RecordID
		{
			get { return m_recordID; }
			set { m_recordID = value; }
		}

		/// <summary>
		/// 管理员标识
		/// </summary>
		public int MasterID
		{
			get { return m_masterID; }
			set { m_masterID = value; }
		}

		/// <summary>
		/// 赠予地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 赠予时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
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
		/// 当前经验
		/// </summary>
		public int CurExperience
		{
			get { return m_curExperience; }
			set { m_curExperience = value; }
		}

		/// <summary>
		/// 补加经验
		/// </summary>
		public int AddExperience
		{
			get { return m_addExperience; }
			set { m_addExperience = value; }
		}

		/// <summary>
		/// 赠予原因
		/// </summary>
		public string Reason
		{
			get { return m_reason; }
			set { m_reason = value; }
		}
		#endregion
	}
}
