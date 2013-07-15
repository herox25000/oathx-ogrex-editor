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
	/// 实体类 RecordSpreadInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordSpreadInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordSpreadInfo" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 推广积分
		/// </summary>
		public const string _Score = "Score" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _TypeID = "TypeID" ;

		/// <summary>
		/// 子类型标识
		/// </summary>
		public const string _ChildrenID = "ChildrenID" ;

		/// <summary>
		/// 银行金币
		/// </summary>
		public const string _InsureScore = "InsureScore" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 收集日期
		/// </summary>
		public const string _CollectNote = "CollectNote" ;
		#endregion

		#region 私有变量
		private int m_recordID;				//记录标识
		private int m_userID;				//用户标识
		private long m_score;				//推广积分
		private int m_typeID;				//类型标识
		private int m_childrenID;			//子类型标识
		private long m_insureScore;			//银行金币
		private DateTime m_collectDate;		//
		private string m_collectNote;		//收集日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordSpreadInfo
		/// </summary>
		public RecordSpreadInfo()
		{
			m_recordID=0;
			m_userID=0;
			m_score=0;
			m_typeID=0;
			m_childrenID=0;
			m_insureScore=0;
			m_collectDate=DateTime.Now;
			m_collectNote="";
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
		/// 用户标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 推广积分
		/// </summary>
		public long Score
		{
			get { return m_score; }
			set { m_score = value; }
		}

		/// <summary>
		/// 类型标识
		/// </summary>
		public int TypeID
		{
			get { return m_typeID; }
			set { m_typeID = value; }
		}

		/// <summary>
		/// 子类型标识
		/// </summary>
		public int ChildrenID
		{
			get { return m_childrenID; }
			set { m_childrenID = value; }
		}

		/// <summary>
		/// 银行金币
		/// </summary>
		public long InsureScore
		{
			get { return m_insureScore; }
			set { m_insureScore = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}

		/// <summary>
		/// 收集日期
		/// </summary>
		public string CollectNote
		{
			get { return m_collectNote; }
			set { m_collectNote = value; }
		}
		#endregion
	}
}
