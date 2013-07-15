/*
 * 版本：4.0
 * 时间：2012-2-28
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.GameMatch
{
	/// <summary>
	/// 实体类 GameProperty。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameProperty  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameProperty" ;

		/// <summary>
		/// 道具标识
		/// </summary>
		public const string _ID = "ID" ;

		/// <summary>
		/// 道具名字
		/// </summary>
		public const string _Name = "Name" ;

		/// <summary>
		/// 道具价格
		/// </summary>
		public const string _Cash = "Cash" ;

		/// <summary>
		/// 道具金币
		/// </summary>
		public const string _Gold = "Gold" ;

		/// <summary>
		/// 会员折扣
		/// </summary>
		public const string _Discount = "Discount" ;

		/// <summary>
		/// 发行范围
		/// </summary>
		public const string _IssueArea = "IssueArea" ;

		/// <summary>
		/// 使用范围
		/// </summary>
		public const string _ServiceArea = "ServiceArea" ;

		/// <summary>
		/// 增加魅力
		/// </summary>
		public const string _SendLoveLiness = "SendLoveLiness" ;

		/// <summary>
		/// 增加魅力
		/// </summary>
		public const string _RecvLoveLiness = "RecvLoveLiness" ;

		/// <summary>
		/// 使用说明
		/// </summary>
		public const string _RegulationsInfo = "RegulationsInfo" ;

		/// <summary>
		/// 禁止标志
		/// </summary>
		public const string _Nullity = "Nullity" ;
		#endregion

		#region 私有变量
		private int m_iD;							//道具标识
		private string m_name;						//道具名字
		private decimal m_cash;						//道具价格
		private long m_gold;						//道具金币
		private short m_discount;					//会员折扣
		private short m_issueArea;					//发行范围
		private short m_serviceArea;				//使用范围
		private long m_sendLoveLiness;				//增加魅力
		private long m_recvLoveLiness;				//增加魅力
		private string m_regulationsInfo;			//使用说明
		private byte m_nullity;						//禁止标志
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameProperty
		/// </summary>
		public GameProperty()
		{
			m_iD=0;
			m_name="";
			m_cash=0;
			m_gold=0;
			m_discount=0;
			m_issueArea=0;
			m_serviceArea=0;
			m_sendLoveLiness=0;
			m_recvLoveLiness=0;
			m_regulationsInfo="";
			m_nullity=0;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 道具标识
		/// </summary>
		public int ID
		{
			get { return m_iD; }
			set { m_iD = value; }
		}

		/// <summary>
		/// 道具名字
		/// </summary>
		public string Name
		{
			get { return m_name; }
			set { m_name = value; }
		}

		/// <summary>
		/// 道具价格
		/// </summary>
		public decimal Cash
		{
			get { return m_cash; }
			set { m_cash = value; }
		}

		/// <summary>
		/// 道具金币
		/// </summary>
		public long Gold
		{
			get { return m_gold; }
			set { m_gold = value; }
		}

		/// <summary>
		/// 会员折扣
		/// </summary>
		public short Discount
		{
			get { return m_discount; }
			set { m_discount = value; }
		}

		/// <summary>
		/// 发行范围
		/// </summary>
		public short IssueArea
		{
			get { return m_issueArea; }
			set { m_issueArea = value; }
		}

		/// <summary>
		/// 使用范围
		/// </summary>
		public short ServiceArea
		{
			get { return m_serviceArea; }
			set { m_serviceArea = value; }
		}

		/// <summary>
		/// 增加魅力
		/// </summary>
		public long SendLoveLiness
		{
			get { return m_sendLoveLiness; }
			set { m_sendLoveLiness = value; }
		}

		/// <summary>
		/// 增加魅力
		/// </summary>
		public long RecvLoveLiness
		{
			get { return m_recvLoveLiness; }
			set { m_recvLoveLiness = value; }
		}

		/// <summary>
		/// 使用说明
		/// </summary>
		public string RegulationsInfo
		{
			get { return m_regulationsInfo; }
			set { m_regulationsInfo = value; }
		}

		/// <summary>
		/// 禁止标志
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}
		#endregion
	}
}
