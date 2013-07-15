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

namespace Game.Entity.Treasure
{
	/// <summary>
	/// 实体类 LivcardBuildStream。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class LivcardBuildStream  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "LivcardBuildStream" ;

		/// <summary>
		/// 生产批次
		/// </summary>
		public const string _BuildID = "BuildID" ;

		/// <summary>
		/// 管理员名称
		/// </summary>
		public const string _AdminName = "AdminName" ;

		/// <summary>
		/// 卡类型标识
		/// </summary>
		public const string _CardTypeID = "CardTypeID" ;

		/// <summary>
		/// 卡价格
		/// </summary>
		public const string _CardPrice = "CardPrice" ;

		/// <summary>
		/// 卡金币数
		/// </summary>
		public const string _CardGold = "CardGold" ;

		/// <summary>
		/// 生产数量
		/// </summary>
		public const string _BuildCount = "BuildCount" ;

		/// <summary>
		/// 生产地址
		/// </summary>
		public const string _BuildAddr = "BuildAddr" ;

		/// <summary>
		/// 生产日期
		/// </summary>
		public const string _BuildDate = "BuildDate" ;

		/// <summary>
		/// 下载次数
		/// </summary>
		public const string _DownLoadCount = "DownLoadCount" ;

		/// <summary>
		/// 备注信息
		/// </summary>
		public const string _NoteInfo = "NoteInfo" ;

		/// <summary>
		/// 会员卡数据
		/// </summary>
		public const string _BuildCardPacket = "BuildCardPacket" ;
		#endregion

		#region 私有变量
		private int m_buildID;							//生产批次
		private string m_adminName;						//管理员名称
		private int m_cardTypeID;						//卡类型标识
		private decimal m_cardPrice;					//卡价格
		private long m_cardGold;						//卡金币数
		private int m_buildCount;						//生产数量
		private string m_buildAddr;						//生产地址
		private DateTime m_buildDate;					//生产日期
		private int m_downLoadCount;					//下载次数
		private string m_noteInfo;						//备注信息
		private System.Byte[] m_buildCardPacket;		//会员卡数据
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化LivcardBuildStream
		/// </summary>
		public LivcardBuildStream()
		{
			m_buildID=0;
			m_adminName="";
			m_cardTypeID=0;
			m_cardPrice=0;
			m_cardGold=0;
			m_buildCount=0;
			m_buildAddr="";
			m_buildDate=DateTime.Now;
			m_downLoadCount=0;
			m_noteInfo="";
			m_buildCardPacket=null;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 生产批次
		/// </summary>
		public int BuildID
		{
			get { return m_buildID; }
			set { m_buildID = value; }
		}

		/// <summary>
		/// 管理员名称
		/// </summary>
		public string AdminName
		{
			get { return m_adminName; }
			set { m_adminName = value; }
		}

		/// <summary>
		/// 卡类型标识
		/// </summary>
		public int CardTypeID
		{
			get { return m_cardTypeID; }
			set { m_cardTypeID = value; }
		}

		/// <summary>
		/// 卡价格
		/// </summary>
		public decimal CardPrice
		{
			get { return m_cardPrice; }
			set { m_cardPrice = value; }
		}

		/// <summary>
		/// 卡金币数
		/// </summary>
		public long CardGold
		{
			get { return m_cardGold; }
			set { m_cardGold = value; }
		}

		/// <summary>
		/// 生产数量
		/// </summary>
		public int BuildCount
		{
			get { return m_buildCount; }
			set { m_buildCount = value; }
		}

		/// <summary>
		/// 生产地址
		/// </summary>
		public string BuildAddr
		{
			get { return m_buildAddr; }
			set { m_buildAddr = value; }
		}

		/// <summary>
		/// 生产日期
		/// </summary>
		public DateTime BuildDate
		{
			get { return m_buildDate; }
			set { m_buildDate = value; }
		}

		/// <summary>
		/// 下载次数
		/// </summary>
		public int DownLoadCount
		{
			get { return m_downLoadCount; }
			set { m_downLoadCount = value; }
		}

		/// <summary>
		/// 备注信息
		/// </summary>
		public string NoteInfo
		{
			get { return m_noteInfo; }
			set { m_noteInfo = value; }
		}

		/// <summary>
		/// 会员卡数据
		/// </summary>
		public System.Byte[] BuildCardPacket
		{
			get { return m_buildCardPacket; }
			set { m_buildCardPacket = value; }
		}
		#endregion
	}
}
