/*
 * 版本：4.0
 * 时间：2012-2-23
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
	/// 实体类 RecordConvertUserMedal。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordConvertUserMedal  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordConvertUserMedal" ;

		/// <summary>
		/// 记录标识
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 用户标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 当前银行金币
		/// </summary>
		public const string _CurInsureScore = "CurInsureScore" ;

		/// <summary>
		/// 当前奖牌
		/// </summary>
		public const string _CurUserMedal = "CurUserMedal" ;

		/// <summary>
		/// 兑换奖牌
		/// </summary>
		public const string _ConvertUserMedal = "ConvertUserMedal" ;

		/// <summary>
		/// 兑换比例
		/// </summary>
		public const string _ConvertRate = "ConvertRate" ;

		/// <summary>
		/// 是否大厅(0:大厅,1:网站)
		/// </summary>
		public const string _IsGamePlaza = "IsGamePlaza" ;

		/// <summary>
		/// 兑换地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 兑换时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_recordID;					//记录标识
		private int m_userID;					//用户标识
		private long m_curInsureScore;			//当前银行金币
		private int m_curUserMedal;				//当前奖牌
		private int m_convertUserMedal;			//兑换奖牌
		private decimal m_convertRate;			//兑换比例
		private byte m_isGamePlaza;				//是否大厅(0:大厅,1:网站)
		private string m_clientIP;				//兑换地址
		private DateTime m_collectDate;			//兑换时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordConvertUserMedal
		/// </summary>
		public RecordConvertUserMedal()
		{
			m_recordID=0;
			m_userID=0;
			m_curInsureScore=0;
			m_curUserMedal=0;
			m_convertUserMedal=0;
			m_convertRate=0;
			m_isGamePlaza=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
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
		/// 当前银行金币
		/// </summary>
		public long CurInsureScore
		{
			get { return m_curInsureScore; }
			set { m_curInsureScore = value; }
		}

		/// <summary>
		/// 当前奖牌
		/// </summary>
		public int CurUserMedal
		{
			get { return m_curUserMedal; }
			set { m_curUserMedal = value; }
		}

		/// <summary>
		/// 兑换奖牌
		/// </summary>
		public int ConvertUserMedal
		{
			get { return m_convertUserMedal; }
			set { m_convertUserMedal = value; }
		}

		/// <summary>
		/// 兑换比例
		/// </summary>
		public decimal ConvertRate
		{
			get { return m_convertRate; }
			set { m_convertRate = value; }
		}

		/// <summary>
		/// 是否大厅(0:大厅,1:网站)
		/// </summary>
		public byte IsGamePlaza
		{
			get { return m_isGamePlaza; }
			set { m_isGamePlaza = value; }
		}

		/// <summary>
		/// 兑换地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 兑换时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
