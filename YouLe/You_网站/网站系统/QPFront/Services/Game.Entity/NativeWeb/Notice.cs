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
	/// 实体类 Notice。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Notice  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "Notice" ;

		/// <summary>
		/// 窗口标识
		/// </summary>
		public const string _NoticeID = "NoticeID" ;

		/// <summary>
		/// 窗口标题
		/// </summary>
		public const string _Subject = "Subject" ;

		/// <summary>
		/// 外部链接
		/// </summary>
		public const string _IsLink = "IsLink" ;

		/// <summary>
		/// 窗口地址
		/// </summary>
		public const string _LinkUrl = "LinkUrl" ;

		/// <summary>
		/// 窗口内容
		/// </summary>
		public const string _Body = "Body" ;

		/// <summary>
		/// 弹出位置
		/// </summary>
		public const string _Location = "Location" ;

		/// <summary>
		/// 窗口宽度
		/// </summary>
		public const string _Width = "Width" ;

		/// <summary>
		/// 窗口高度
		/// </summary>
		public const string _Height = "Height" ;

		/// <summary>
		/// 开始时间
		/// </summary>
		public const string _StartDate = "StartDate" ;

		/// <summary>
		/// 结束时间
		/// </summary>
		public const string _OverDate = "OverDate" ;

		/// <summary>
		/// 无效标识
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_noticeID;					//窗口标识
		private string m_subject;				//窗口标题
		private byte m_isLink;					//外部链接
		private string m_linkUrl;				//窗口地址
		private string m_body;					//窗口内容
		private string m_location;				//弹出位置
		private int m_width;					//窗口宽度
		private int m_height;					//窗口高度
		private DateTime m_startDate;			//开始时间
		private DateTime m_overDate;			//结束时间
		private byte m_nullity;					//无效标识
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Notice
		/// </summary>
		public Notice()
		{
			m_noticeID=0;
			m_subject="";
			m_isLink=0;
			m_linkUrl="";
			m_body="";
			m_location="";
			m_width=0;
			m_height=0;
			m_startDate=DateTime.Now;
			m_overDate=DateTime.Now;
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 窗口标识
		/// </summary>
		public int NoticeID
		{
			get { return m_noticeID; }
			set { m_noticeID = value; }
		}

		/// <summary>
		/// 窗口标题
		/// </summary>
		public string Subject
		{
			get { return m_subject; }
			set { m_subject = value; }
		}

		/// <summary>
		/// 外部链接
		/// </summary>
		public byte IsLink
		{
			get { return m_isLink; }
			set { m_isLink = value; }
		}

		/// <summary>
		/// 窗口地址
		/// </summary>
		public string LinkUrl
		{
			get { return m_linkUrl; }
			set { m_linkUrl = value; }
		}

		/// <summary>
		/// 窗口内容
		/// </summary>
		public string Body
		{
			get { return m_body; }
			set { m_body = value; }
		}

		/// <summary>
		/// 弹出位置
		/// </summary>
		public string Location
		{
			get { return m_location; }
			set { m_location = value; }
		}

		/// <summary>
		/// 窗口宽度
		/// </summary>
		public int Width
		{
			get { return m_width; }
			set { m_width = value; }
		}

		/// <summary>
		/// 窗口高度
		/// </summary>
		public int Height
		{
			get { return m_height; }
			set { m_height = value; }
		}

		/// <summary>
		/// 开始时间
		/// </summary>
		public DateTime StartDate
		{
			get { return m_startDate; }
			set { m_startDate = value; }
		}

		/// <summary>
		/// 结束时间
		/// </summary>
		public DateTime OverDate
		{
			get { return m_overDate; }
			set { m_overDate = value; }
		}

		/// <summary>
		/// 无效标识
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}
		#endregion
	}
}
