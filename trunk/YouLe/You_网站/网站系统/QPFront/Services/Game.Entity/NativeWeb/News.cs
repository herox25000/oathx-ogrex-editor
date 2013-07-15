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
	/// 实体类 News。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class News  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "News" ;

		/// <summary>
		/// 公告标识
		/// </summary>
		public const string _NewsID = "NewsID" ;

		/// <summary>
		/// 弹出窗口
		/// </summary>
		public const string _PopID = "PopID" ;

		/// <summary>
		/// 新闻主标题
		/// </summary>
		public const string _Subject = "Subject" ;

		/// <summary>
		/// 新闻副标题
		/// </summary>
		public const string _Subject1 = "Subject1" ;

		/// <summary>
		/// 置顶标识
		/// </summary>
		public const string _OnTop = "OnTop" ;

		/// <summary>
		/// 总置顶标识
		/// </summary>
		public const string _OnTopAll = "OnTopAll" ;

		/// <summary>
		/// 精华标识
		/// </summary>
		public const string _IsElite = "IsElite" ;

		/// <summary>
		/// 热点标识 (0, 1　热点)
		/// </summary>
		public const string _IsHot = "IsHot" ;

		/// <summary>
		/// 锁定标识(0 锁定 1 发布)
		/// </summary>
		public const string _IsLock = "IsLock" ;

		/// <summary>
		/// 删除标识
		/// </summary>
		public const string _IsDelete = "IsDelete" ;

		/// <summary>
		/// 外部链接标识
		/// </summary>
		public const string _IsLinks = "IsLinks" ;

		/// <summary>
		/// 外部链接地址
		/// </summary>
		public const string _LinkUrl = "LinkUrl" ;

		/// <summary>
		/// 公告内容
		/// </summary>
		public const string _Body = "Body" ;

		/// <summary>
		/// 带格式公告内容
		/// </summary>
		public const string _FormattedBody = "FormattedBody" ;

		/// <summary>
		/// 标题颜色
		/// </summary>
		public const string _HighLight = "HighLight" ;

		/// <summary>
		/// 新闻类别 (新闻 1; 公告 2)
		/// </summary>
		public const string _ClassID = "ClassID" ;

		/// <summary>
		/// 发布人标识
		/// </summary>
		public const string _UserID = "UserID" ;

		/// <summary>
		/// 发布地址
		/// </summary>
		public const string _IssueIP = "IssueIP" ;

		/// <summary>
		/// 最后更新地址
		/// </summary>
		public const string _LastModifyIP = "LastModifyIP" ;

		/// <summary>
		/// 发布时间
		/// </summary>
		public const string _IssueDate = "IssueDate" ;

		/// <summary>
		/// 更新时间
		/// </summary>
		public const string _LastModifyDate = "LastModifyDate" ;
		#endregion

		#region 私有变量
		private int m_newsID;						//公告标识
		private int m_popID;						//弹出窗口
		private string m_subject;					//新闻主标题
		private string m_subject1;					//新闻副标题
		private byte m_onTop;						//置顶标识
		private byte m_onTopAll;					//总置顶标识
		private byte m_isElite;						//精华标识
		private byte m_isHot;						//热点标识 (0, 1　热点)
		private byte m_isLock;						//锁定标识(0 锁定 1 发布)
		private byte m_isDelete;					//删除标识
		private byte m_isLinks;						//外部链接标识
		private string m_linkUrl;					//外部链接地址
		private string m_body;						//公告内容
		private string m_formattedBody;				//带格式公告内容
		private string m_highLight;					//标题颜色
		private byte m_classID;						//新闻类别 (新闻 1; 公告 2)
		private int m_userID;						//发布人标识
		private string m_issueIP;					//发布地址
		private string m_lastModifyIP;				//最后更新地址
		private DateTime m_issueDate;				//发布时间
		private DateTime m_lastModifyDate;			//更新时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化News
		/// </summary>
		public News()
		{
			m_newsID=0;
			m_popID=0;
			m_subject="";
			m_subject1="";
			m_onTop=0;
			m_onTopAll=0;
			m_isElite=0;
			m_isHot=0;
			m_isLock=0;
			m_isDelete=0;
			m_isLinks=0;
			m_linkUrl="";
			m_body="";
			m_formattedBody="";
			m_highLight="";
			m_classID=0;
			m_userID=0;
			m_issueIP="";
			m_lastModifyIP="";
			m_issueDate=DateTime.Now;
			m_lastModifyDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 公告标识
		/// </summary>
		public int NewsID
		{
			get { return m_newsID; }
			set { m_newsID = value; }
		}

		/// <summary>
		/// 弹出窗口
		/// </summary>
		public int PopID
		{
			get { return m_popID; }
			set { m_popID = value; }
		}

		/// <summary>
		/// 新闻主标题
		/// </summary>
		public string Subject
		{
			get { return m_subject; }
			set { m_subject = value; }
		}

		/// <summary>
		/// 新闻副标题
		/// </summary>
		public string Subject1
		{
			get { return m_subject1; }
			set { m_subject1 = value; }
		}

		/// <summary>
		/// 置顶标识
		/// </summary>
		public byte OnTop
		{
			get { return m_onTop; }
			set { m_onTop = value; }
		}

		/// <summary>
		/// 总置顶标识
		/// </summary>
		public byte OnTopAll
		{
			get { return m_onTopAll; }
			set { m_onTopAll = value; }
		}

		/// <summary>
		/// 精华标识
		/// </summary>
		public byte IsElite
		{
			get { return m_isElite; }
			set { m_isElite = value; }
		}

		/// <summary>
		/// 热点标识 (0, 1　热点)
		/// </summary>
		public byte IsHot
		{
			get { return m_isHot; }
			set { m_isHot = value; }
		}

		/// <summary>
		/// 锁定标识(0 锁定 1 发布)
		/// </summary>
		public byte IsLock
		{
			get { return m_isLock; }
			set { m_isLock = value; }
		}

		/// <summary>
		/// 删除标识
		/// </summary>
		public byte IsDelete
		{
			get { return m_isDelete; }
			set { m_isDelete = value; }
		}

		/// <summary>
		/// 外部链接标识
		/// </summary>
		public byte IsLinks
		{
			get { return m_isLinks; }
			set { m_isLinks = value; }
		}

		/// <summary>
		/// 外部链接地址
		/// </summary>
		public string LinkUrl
		{
			get { return m_linkUrl; }
			set { m_linkUrl = value; }
		}

		/// <summary>
		/// 公告内容
		/// </summary>
		public string Body
		{
			get { return m_body; }
			set { m_body = value; }
		}

		/// <summary>
		/// 带格式公告内容
		/// </summary>
		public string FormattedBody
		{
			get { return m_formattedBody; }
			set { m_formattedBody = value; }
		}

		/// <summary>
		/// 标题颜色
		/// </summary>
		public string HighLight
		{
			get { return m_highLight; }
			set { m_highLight = value; }
		}

		/// <summary>
		/// 新闻类别 (新闻 1; 公告 2)
		/// </summary>
		public byte ClassID
		{
			get { return m_classID; }
			set { m_classID = value; }
		}

		/// <summary>
		/// 发布人标识
		/// </summary>
		public int UserID
		{
			get { return m_userID; }
			set { m_userID = value; }
		}

		/// <summary>
		/// 发布地址
		/// </summary>
		public string IssueIP
		{
			get { return m_issueIP; }
			set { m_issueIP = value; }
		}

		/// <summary>
		/// 最后更新地址
		/// </summary>
		public string LastModifyIP
		{
			get { return m_lastModifyIP; }
			set { m_lastModifyIP = value; }
		}

		/// <summary>
		/// 发布时间
		/// </summary>
		public DateTime IssueDate
		{
			get { return m_issueDate; }
			set { m_issueDate = value; }
		}

		/// <summary>
		/// 更新时间
		/// </summary>
		public DateTime LastModifyDate
		{
			get { return m_lastModifyDate; }
			set { m_lastModifyDate = value; }
		}
		#endregion
	}
}
