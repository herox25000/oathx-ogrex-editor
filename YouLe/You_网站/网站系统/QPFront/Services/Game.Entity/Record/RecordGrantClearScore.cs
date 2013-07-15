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

namespace Game.Entity.Record
{
	/// <summary>
	/// 实体类 RecordGrantClearScore。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordGrantClearScore  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordGrantClearScore" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 管理员ID
		/// </summary>
		public const string _MasterID = "MasterID" ;

		/// <summary>
		/// 客户端IP
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 收集日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 玩家标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 当前积分
		/// </summary>
		public const string _CurScore = "CurScore" ;

		/// <summary>
		/// 清零负分原因
		/// </summary>
		public const string _Reason = "Reason" ;
		#endregion

		#region 私有变量
		private int m_recordID;					//记录标识
		private int m_masterID;					//管理员ID
		private string m_clientIP;				//客户端IP
		private DateTime m_collectDate;			//收集日期
		private int m_userID;					//玩家标识
		private int m_kindID;					//游戏标识
		private long m_curScore;				//当前积分
		private string m_reason;				//清零负分原因
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordGrantClearScore
		/// </summary>
		public RecordGrantClearScore()
		{
			m_recordID=0;
			m_masterID=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
			m_userID=0;
			m_kindID=0;
			m_curScore=0;
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
		/// 管理员ID
		/// </summary>
		public int MasterID
		{
			get { return m_masterID; }
			set { m_masterID = value; }
		}

		/// <summary>
		/// 客户端IP
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

		/// <summary>
		/// 玩家标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 游戏标识
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 当前积分
		/// </summary>
		public long CurScore
		{
			get { return m_curScore; }
			set { m_curScore = value; }
		}

		/// <summary>
		/// 清零负分原因
		/// </summary>
		public string Reason
		{
			get { return m_reason; }
			set { m_reason = value; }
		}
		#endregion
	}
}
