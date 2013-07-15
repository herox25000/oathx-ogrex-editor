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
	/// 实体类 ReturnKQDetailInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class ReturnKQDetailInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "ReturnKQDetailInfo" ;

		/// <summary>
		/// 流水标识
		/// </summary>
		public const string _DetailID = "DetailID" ;

		/// <summary>
		/// 收款帐号(人民币)
		/// </summary>
		public const string _MerchantAcctID = "MerchantAcctID" ;

		/// <summary>
		/// 快钱版本
		/// </summary>
		public const string _Version = "Version" ;

		/// <summary>
		/// 网关页面语言类别
		/// </summary>
		public const string _Language = "Language" ;

		/// <summary>
		/// 签名类别
		/// </summary>
		public const string _SignType = "SignType" ;

		/// <summary>
		/// 支付方式
		/// </summary>
		public const string _PayType = "PayType" ;

		/// <summary>
		/// 银行代码
		/// </summary>
		public const string _BankID = "BankID" ;

		/// <summary>
		/// 订单编号
		/// </summary>
		public const string _OrderID = "OrderID" ;

		/// <summary>
		/// 订单日期
		/// </summary>
		public const string _OrderTime = "OrderTime" ;

		/// <summary>
		/// 订单金额(元)
		/// </summary>
		public const string _OrderAmount = "OrderAmount" ;

		/// <summary>
		/// 快钱交易号
		/// </summary>
		public const string _DealID = "DealID" ;

		/// <summary>
		/// 银行交易号
		/// </summary>
		public const string _BankDealID = "BankDealID" ;

		/// <summary>
		/// 快钱交易时间
		/// </summary>
		public const string _DealTime = "DealTime" ;

		/// <summary>
		/// 订单实际支付金额(元)
		/// </summary>
		public const string _PayAmount = "PayAmount" ;

		/// <summary>
		/// 快钱收取商户的手续费(元)
		/// </summary>
		public const string _Fee = "Fee" ;

		/// <summary>
		/// 支付结果  10:支付成功; 11:支付失败
		/// </summary>
		public const string _PayResult = "PayResult" ;

		/// <summary>
		/// 错误代码
		/// </summary>
		public const string _ErrCode = "ErrCode" ;

		/// <summary>
		/// 签名字符串
		/// </summary>
		public const string _SignMsg = "SignMsg" ;

		/// <summary>
		/// 扩展字段
		/// </summary>
		public const string _Ext1 = "Ext1" ;

		/// <summary>
		/// 扩展字段
		/// </summary>
		public const string _Ext2 = "Ext2" ;

		/// <summary>
		/// 支付卡号
		/// </summary>
		public const string _CardNumber = "CardNumber" ;

		/// <summary>
		/// 支付卡密
		/// </summary>
		public const string _CardPwd = "CardPwd" ;

		/// <summary>
		/// 支付类型(只适合充值卡)
		/// </summary>
		public const string _BossType = "BossType" ;

		/// <summary>
		/// 实际支付类型
		/// </summary>
		public const string _ReceiveBossType = "ReceiveBossType" ;

		/// <summary>
		/// 实际收款账户
		/// </summary>
		public const string _ReceiverAcctId = "ReceiverAcctId" ;

		/// <summary>
		/// 支付时间
		/// </summary>
		public const string _PayDate = "PayDate" ;
		#endregion

		#region 私有变量
		private int m_detailID;						//流水标识
		private string m_merchantAcctID;			//收款帐号(人民币)
		private string m_version;					//快钱版本
		private int m_language;						//网关页面语言类别
		private int m_signType;						//签名类别
		private string m_payType;					//支付方式
		private string m_bankID;					//银行代码
		private string m_orderID;					//订单编号
		private DateTime m_orderTime;				//订单日期
		private decimal m_orderAmount;				//订单金额(元)
		private string m_dealID;					//快钱交易号
		private string m_bankDealID;				//银行交易号
		private DateTime m_dealTime;				//快钱交易时间
		private decimal m_payAmount;				//订单实际支付金额(元)
		private decimal m_fee;						//快钱收取商户的手续费(元)
		private string m_payResult;					//支付结果  10:支付成功; 11:支付失败
		private string m_errCode;					//错误代码
		private string m_signMsg;					//签名字符串
		private string m_ext1;						//扩展字段
		private string m_ext2;						//扩展字段
		private string m_cardNumber;				//支付卡号
		private string m_cardPwd;					//支付卡密
		private string m_bossType;					//支付类型(只适合充值卡)
		private string m_receiveBossType;			//实际支付类型
		private string m_receiverAcctId;			//实际收款账户
		private DateTime m_payDate;					//支付时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化ReturnKQDetailInfo
		/// </summary>
		public ReturnKQDetailInfo()
		{
			m_detailID=0;
			m_merchantAcctID="";
			m_version="";
			m_language=0;
			m_signType=0;
			m_payType="";
			m_bankID="";
			m_orderID="";
			m_orderTime=DateTime.Now;
			m_orderAmount=0;
			m_dealID="";
			m_bankDealID="";
			m_dealTime=DateTime.Now;
			m_payAmount=0;
			m_fee=0;
			m_payResult="";
			m_errCode="";
			m_signMsg="";
			m_ext1="";
			m_ext2="";
			m_cardNumber="";
			m_cardPwd="";
			m_bossType="";
			m_receiveBossType="";
			m_receiverAcctId="";
			m_payDate=DateTime.Now;
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
		/// 收款帐号(人民币)
		/// </summary>
		public string MerchantAcctID
		{
			get { return m_merchantAcctID; }
			set { m_merchantAcctID = value; }
		}

		/// <summary>
		/// 快钱版本
		/// </summary>
		public string Version
		{
			get { return m_version; }
			set { m_version = value; }
		}

		/// <summary>
		/// 网关页面语言类别
		/// </summary>
		public int Language
		{
			get { return m_language; }
			set { m_language = value; }
		}

		/// <summary>
		/// 签名类别
		/// </summary>
		public int SignType
		{
			get { return m_signType; }
			set { m_signType = value; }
		}

		/// <summary>
		/// 支付方式
		/// </summary>
		public string PayType
		{
			get { return m_payType; }
			set { m_payType = value; }
		}

		/// <summary>
		/// 银行代码
		/// </summary>
		public string BankID
		{
			get { return m_bankID; }
			set { m_bankID = value; }
		}

		/// <summary>
		/// 订单编号
		/// </summary>
		public string OrderID
		{
			get { return m_orderID; }
			set { m_orderID = value; }
		}

		/// <summary>
		/// 订单日期
		/// </summary>
		public DateTime OrderTime
		{
			get { return m_orderTime; }
			set { m_orderTime = value; }
		}

		/// <summary>
		/// 订单金额(元)
		/// </summary>
		public decimal OrderAmount
		{
			get { return m_orderAmount; }
			set { m_orderAmount = value; }
		}

		/// <summary>
		/// 快钱交易号
		/// </summary>
		public string DealID
		{
			get { return m_dealID; }
			set { m_dealID = value; }
		}

		/// <summary>
		/// 银行交易号
		/// </summary>
		public string BankDealID
		{
			get { return m_bankDealID; }
			set { m_bankDealID = value; }
		}

		/// <summary>
		/// 快钱交易时间
		/// </summary>
		public DateTime DealTime
		{
			get { return m_dealTime; }
			set { m_dealTime = value; }
		}

		/// <summary>
		/// 订单实际支付金额(元)
		/// </summary>
		public decimal PayAmount
		{
			get { return m_payAmount; }
			set { m_payAmount = value; }
		}

		/// <summary>
		/// 快钱收取商户的手续费(元)
		/// </summary>
		public decimal Fee
		{
			get { return m_fee; }
			set { m_fee = value; }
		}

		/// <summary>
		/// 支付结果  10:支付成功; 11:支付失败
		/// </summary>
		public string PayResult
		{
			get { return m_payResult; }
			set { m_payResult = value; }
		}

		/// <summary>
		/// 错误代码
		/// </summary>
		public string ErrCode
		{
			get { return m_errCode; }
			set { m_errCode = value; }
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
		/// 扩展字段
		/// </summary>
		public string Ext1
		{
			get { return m_ext1; }
			set { m_ext1 = value; }
		}

		/// <summary>
		/// 扩展字段
		/// </summary>
		public string Ext2
		{
			get { return m_ext2; }
			set { m_ext2 = value; }
		}

		/// <summary>
		/// 支付卡号
		/// </summary>
		public string CardNumber
		{
			get { return m_cardNumber; }
			set { m_cardNumber = value; }
		}

		/// <summary>
		/// 支付卡密
		/// </summary>
		public string CardPwd
		{
			get { return m_cardPwd; }
			set { m_cardPwd = value; }
		}

		/// <summary>
		/// 支付类型(只适合充值卡)
		/// </summary>
		public string BossType
		{
			get { return m_bossType; }
			set { m_bossType = value; }
		}

		/// <summary>
		/// 实际支付类型
		/// </summary>
		public string ReceiveBossType
		{
			get { return m_receiveBossType; }
			set { m_receiveBossType = value; }
		}

		/// <summary>
		/// 实际收款账户
		/// </summary>
		public string ReceiverAcctId
		{
			get { return m_receiverAcctId; }
			set { m_receiverAcctId = value; }
		}

		/// <summary>
		/// 支付时间
		/// </summary>
		public DateTime PayDate
		{
			get { return m_payDate; }
			set { m_payDate = value; }
		}
		#endregion
	}
}
