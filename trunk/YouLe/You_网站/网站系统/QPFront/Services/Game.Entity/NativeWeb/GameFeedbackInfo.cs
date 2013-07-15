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

namespace Game.Entity.NativeWeb
{
	/// <summary>
	/// 实体类 GameFeedbackInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameFeedbackInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameFeedbackInfo" ;

		/// <summary>
		/// 反馈标识
		/// </summary>
		public const string _FeedbackID = "FeedbackID" ;

		/// <summary>
		/// 反馈标题
		/// </summary>
		public const string _FeedbackTitle = "FeedbackTitle" ;

		/// <summary>
		/// 反馈内容
		/// </summary>
		public const string _FeedbackContent = "FeedbackContent" ;

		/// <summary>
		/// 游戏帐号
		/// </summary>
		public const string _Accounts = "Accounts" ;

		/// <summary>
		/// 提交时间
		/// </summary>
		public const string _FeedbackDate = "FeedbackDate" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 浏览次数
		/// </summary>
		public const string _ViewCount = "ViewCount" ;

		/// <summary>
		/// 回复人
		/// </summary>
		public const string _RevertUserID = "RevertUserID" ;

		/// <summary>
		/// 回复内容
		/// </summary>
		public const string _RevertContent = "RevertContent" ;

		/// <summary>
		/// 回复日期
		/// </summary>
		public const string _RevertDate = "RevertDate" ;

		/// <summary>
		/// 禁用标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_feedbackID;					//反馈标识
		private string m_feedbackTitle;				//反馈标题
		private string m_feedbackContent;			//反馈内容
		private string m_accounts;					//游戏帐号
		private DateTime m_feedbackDate;			//提交时间
		private string m_clientIP;					//
		private int m_viewCount;					//浏览次数
		private int m_revertUserID;					//回复人
		private string m_revertContent;				//回复内容
		private DateTime m_revertDate;				//回复日期
		private byte m_nullity;						//禁用标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameFeedbackInfo
		/// </summary>
		public GameFeedbackInfo()
		{
			m_feedbackID=0;
			m_feedbackTitle="";
			m_feedbackContent="";
			m_accounts="";
			m_feedbackDate=DateTime.Now;
			m_clientIP="";
			m_viewCount=0;
			m_revertUserID=0;
			m_revertContent="";
			m_revertDate=DateTime.Now;
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 反馈标识
		/// </summary>
		public int FeedbackID
		{
			get { return m_feedbackID; }
			set { m_feedbackID = value; }
		}

		/// <summary>
		/// 反馈标题
		/// </summary>
		public string FeedbackTitle
		{
			get { return m_feedbackTitle; }
			set { m_feedbackTitle = value; }
		}

		/// <summary>
		/// 反馈内容
		/// </summary>
		public string FeedbackContent
		{
			get { return m_feedbackContent; }
			set { m_feedbackContent = value; }
		}

		/// <summary>
		/// 游戏帐号
		/// </summary>
		public string Accounts
		{
			get { return m_accounts; }
			set { m_accounts = value; }
		}

		/// <summary>
		/// 提交时间
		/// </summary>
		public DateTime FeedbackDate
		{
			get { return m_feedbackDate; }
			set { m_feedbackDate = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 浏览次数
		/// </summary>
		public int ViewCount
		{
			get { return m_viewCount; }
			set { m_viewCount = value; }
		}

		/// <summary>
		/// 回复人
		/// </summary>
		public int RevertUserID
		{
			get { return m_revertUserID; }
			set { m_revertUserID = value; }
		}

		/// <summary>
		/// 回复内容
		/// </summary>
		public string RevertContent
		{
			get { return m_revertContent; }
			set { m_revertContent = value; }
		}

		/// <summary>
		/// 回复日期
		/// </summary>
		public DateTime RevertDate
		{
			get { return m_revertDate; }
			set { m_revertDate = value; }
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
