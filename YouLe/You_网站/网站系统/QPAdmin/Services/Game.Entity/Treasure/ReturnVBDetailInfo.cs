/*
 * 版本：4.0
 * 时间：2011-10-14
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
	/// 实体类 ReturnVBDetailInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class ReturnVBDetailInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "ReturnVBDetailInfo" ;

		/// <summary>
		/// 流水标识
		/// </summary>
		public const string _DetailID = "DetailID" ;

		/// <summary>
		/// 操作站点
		/// </summary>
		public const string _OperStationID = "OperStationID" ;

		/// <summary>
		/// V币服务器MD5
		/// </summary>
		public const string _Rtmd5 = "Rtmd5" ;

		/// <summary>
		/// V币号码
		/// </summary>
		public const string _Rtka = "Rtka" ;

		/// <summary>
		/// V币密码
		/// </summary>
		public const string _Rtmi = "Rtmi" ;

		/// <summary>
		/// 面值
		/// </summary>
		public const string _Rtmz = "Rtmz" ;

		/// <summary>
		/// 卡的类型(1:正式卡 2:测试卡 3 :促销卡)
		/// </summary>
		public const string _Rtlx = "Rtlx" ;

		/// <summary>
		/// 盈华讯方服务器端订单
		/// </summary>
		public const string _Rtoid = "Rtoid" ;

		/// <summary>
		/// 订单号码
		/// </summary>
		public const string _OrderID = "OrderID" ;

		/// <summary>
		/// 商户的用户ID
		/// </summary>
		public const string _Rtuserid = "Rtuserid" ;

		/// <summary>
		/// 商户自己定义数据
		/// </summary>
		public const string _Rtcustom = "Rtcustom" ;

		/// <summary>
		/// 返回状态(1:为正常发送回来,2:为补单发送回来)
		/// </summary>
		public const string _Rtflag = "Rtflag" ;

		/// <summary>
		/// 回传字符
		/// </summary>
		public const string _EcryptStr = "EcryptStr" ;

		/// <summary>
		/// 签名字符串
		/// </summary>
		public const string _SignMsg = "SignMsg" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_detailID;				//流水标识
		private int m_operStationID;		//操作站点
		private string m_rtmd5;				//V币服务器MD5
		private string m_rtka;				//V币号码
		private string m_rtmi;				//V币密码
		private int m_rtmz;					//面值
		private int m_rtlx;					//卡的类型(1:正式卡 2:测试卡 3 :促销卡)
		private string m_rtoid;				//盈华讯方服务器端订单
		private string m_orderID;			//订单号码
		private string m_rtuserid;			//商户的用户ID
		private string m_rtcustom;			//商户自己定义数据
		private int m_rtflag;				//返回状态(1:为正常发送回来,2:为补单发送回来)
		private string m_ecryptStr;			//回传字符
		private string m_signMsg;			//签名字符串
		private DateTime m_collectDate;		//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化ReturnVBDetailInfo
		/// </summary>
		public ReturnVBDetailInfo()
		{
			m_detailID=0;
			m_operStationID=0;
			m_rtmd5="";
			m_rtka="";
			m_rtmi="";
			m_rtmz=0;
			m_rtlx=0;
			m_rtoid="";
			m_orderID="";
			m_rtuserid="";
			m_rtcustom="";
			m_rtflag=0;
			m_ecryptStr="";
			m_signMsg="";
			m_collectDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 流水标识
		/// </summary>
		public int DetailID
		{
			get { return m_detailID; }
			set { m_detailID = value; }
		}

		/// <summary>
		/// 操作站点
		/// </summary>
		public int OperStationID
		{
			get { return m_operStationID; }
			set { m_operStationID = value; }
		}

		/// <summary>
		/// V币服务器MD5
		/// </summary>
		public string Rtmd5
		{
			get { return m_rtmd5; }
			set { m_rtmd5 = value; }
		}

		/// <summary>
		/// V币号码
		/// </summary>
		public string Rtka
		{
			get { return m_rtka; }
			set { m_rtka = value; }
		}

		/// <summary>
		/// V币密码
		/// </summary>
		public string Rtmi
		{
			get { return m_rtmi; }
			set { m_rtmi = value; }
		}

		/// <summary>
		/// 面值
		/// </summary>
		public int Rtmz
		{
			get { return m_rtmz; }
			set { m_rtmz = value; }
		}

		/// <summary>
		/// 卡的类型(1:正式卡 2:测试卡 3 :促销卡)
		/// </summary>
		public int Rtlx
		{
			get { return m_rtlx; }
			set { m_rtlx = value; }
		}

		/// <summary>
		/// 盈华讯方服务器端订单
		/// </summary>
		public string Rtoid
		{
			get { return m_rtoid; }
			set { m_rtoid = value; }
		}

		/// <summary>
		/// 订单号码
		/// </summary>
		public string OrderID
		{
			get { return m_orderID; }
			set { m_orderID = value; }
		}

		/// <summary>
		/// 商户的用户ID
		/// </summary>
		public string Rtuserid
		{
			get { return m_rtuserid; }
			set { m_rtuserid = value; }
		}

		/// <summary>
		/// 商户自己定义数据
		/// </summary>
		public string Rtcustom
		{
			get { return m_rtcustom; }
			set { m_rtcustom = value; }
		}

		/// <summary>
		/// 返回状态(1:为正常发送回来,2:为补单发送回来)
		/// </summary>
		public int Rtflag
		{
			get { return m_rtflag; }
			set { m_rtflag = value; }
		}

		/// <summary>
		/// 回传字符
		/// </summary>
		public string EcryptStr
		{
			get { return m_ecryptStr; }
			set { m_ecryptStr = value; }
		}

		/// <summary>
		/// 签名字符串
		/// </summary>
		public string SignMsg
		{
			get { return m_signMsg; }
			set { m_signMsg = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
