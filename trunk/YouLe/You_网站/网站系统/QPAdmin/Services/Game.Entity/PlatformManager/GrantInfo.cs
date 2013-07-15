/*
 * 版本：4.0
 * 时间：2011-8-30
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.PlatformManager
{
	/// <summary>
	/// 实体类 GrantInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GrantInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GrantInfo" ;

		/// <summary>
		/// 记录标识(-1,积分房间，-2金币房间)
		/// </summary>
		public const string _SiteID = "SiteID" ;

		/// <summary>
		/// 赠送房间(-1,金币房间;-2,积分房间;其他,GAMEID)
		/// </summary>
		public const string _GrantRoom = "GrantRoom" ;

		/// <summary>
		/// 赠送开始时间
		/// </summary>
		public const string _GrantStartDate = "GrantStartDate" ;

		/// <summary>
		/// 赠送结束时间
		/// </summary>
		public const string _GrantEndDate = "GrantEndDate" ;

		/// <summary>
		/// 赠送对象(0,全体用户;1,蓝钻会员;2,红钻会员;3,黄钻会员;4,紫钻会员)
		/// </summary>
		public const string _GrantObjet = "GrantObjet" ;

		/// <summary>
		/// 日赠送最大额度
		/// </summary>
		public const string _MaxGrant = "MaxGrant" ;

		/// <summary>
		/// 单日最大赠送量
		/// </summary>
		public const string _DayMaxGrant = "DayMaxGrant" ;
		#endregion

		#region 私有变量
		private int m_siteID;						//记录标识(-1,积分房间，-2金币房间)
		private int m_grantRoom;					//赠送房间(-1,金币房间;-2,积分房间;其他,GAMEID)
		private DateTime m_grantStartDate;			//赠送开始时间
		private DateTime m_grantEndDate;			//赠送结束时间
		private string m_grantObjet;				//赠送对象(0,全体用户;1,蓝钻会员;2,红钻会员;3,黄钻会员;4,紫钻会员)
		private int m_maxGrant;						//日赠送最大额度
		private int m_dayMaxGrant;					//单日最大赠送量
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GrantInfo
		/// </summary>
		public GrantInfo()
		{
			m_siteID=0;
			m_grantRoom=0;
			m_grantStartDate=DateTime.Now;
			m_grantEndDate=DateTime.Now;
			m_grantObjet="";
			m_maxGrant=0;
			m_dayMaxGrant=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 记录标识(-1,积分房间，-2金币房间)
		/// </summary>
		public int SiteID
		{
			get { return m_siteID; }
			set { m_siteID = value; }
		}

		/// <summary>
		/// 赠送房间(-1,金币房间;-2,积分房间;其他,GAMEID)
		/// </summary>
		public int GrantRoom
		{
			get { return m_grantRoom; }
			set { m_grantRoom = value; }
		}

		/// <summary>
		/// 赠送开始时间
		/// </summary>
		public DateTime GrantStartDate
		{
			get { return m_grantStartDate; }
			set { m_grantStartDate = value; }
		}

		/// <summary>
		/// 赠送结束时间
		/// </summary>
		public DateTime GrantEndDate
		{
			get { return m_grantEndDate; }
			set { m_grantEndDate = value; }
		}

		/// <summary>
		/// 赠送对象(0,全体用户;1,蓝钻会员;2,红钻会员;3,黄钻会员;4,紫钻会员)
		/// </summary>
		public string GrantObjet
		{
			get { return m_grantObjet; }
			set { m_grantObjet = value; }
		}

		/// <summary>
		/// 日赠送最大额度
		/// </summary>
		public int MaxGrant
		{
			get { return m_maxGrant; }
			set { m_maxGrant = value; }
		}

		/// <summary>
		/// 单日最大赠送量
		/// </summary>
		public int DayMaxGrant
		{
			get { return m_dayMaxGrant; }
			set { m_dayMaxGrant = value; }
		}
		#endregion
	}
}
