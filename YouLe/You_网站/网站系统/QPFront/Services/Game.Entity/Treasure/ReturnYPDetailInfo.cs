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
	/// 实体类 ReturnYPDetailInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class ReturnYPDetailInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "ReturnYPDetailInfo" ;

		/// <summary>
		/// 流水标识
		/// </summary>
		public const string _DetailID = "DetailID" ;

		/// <summary>
		/// 商户编号
		/// </summary>
		public const string _P1_MerId = "p1_MerId" ;

		/// <summary>
		/// 业务类型
		/// </summary>
		public const string _R0_Cmd = "r0_Cmd" ;

		/// <summary>
		/// 支付结果
		/// </summary>
		public const string _R1_Code = "r1_Code" ;

		/// <summary>
		/// 易宝支付交易流水号
		/// </summary>
		public const string _R2_TrxId = "r2_TrxId" ;

		/// <summary>
		/// 支付金额
		/// </summary>
		public const string _R3_Amt = "r3_Amt" ;

		/// <summary>
		/// 交易币种
		/// </summary>
		public const string _R4_Cur = "r4_Cur" ;

		/// <summary>
		/// 商品名称
		/// </summary>
		public const string _R5_Pid = "r5_Pid" ;

		/// <summary>
		/// 商户订单号
		/// </summary>
		public const string _R6_Order = "r6_Order" ;

		/// <summary>
		/// 易宝支付会员ID
		/// </summary>
		public const string _R7_Uid = "r7_Uid" ;

		/// <summary>
		///  商户扩展信息
		/// </summary>
		public const string _R8_MP = "r8_MP" ;

		/// <summary>
		/// 交易结果返回类型
		/// </summary>
		public const string _R9_BType = "r9_BType" ;

		/// <summary>
		/// 银行编码
		/// </summary>
		public const string _Rb_BankId = "rb_BankId" ;

		/// <summary>
		/// 银行订单号
		/// </summary>
		public const string _Ro_BankOrderId = "ro_BankOrderId" ;

		/// <summary>
		/// 支付成功时间
		/// </summary>
		public const string _Rp_PayDate = "rp_PayDate" ;

		/// <summary>
		///  神州行充值卡序列号
		/// </summary>
		public const string _Rq_CardNo = "rq_CardNo" ;

		/// <summary>
		///  交易结果通知时间
		/// </summary>
		public const string _Ru_Trxtime = "ru_Trxtime" ;

		/// <summary>
		/// 签名数据
		/// </summary>
		public const string _Hmac = "hmac" ;

		/// <summary>
		/// 收录时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;
		#endregion

		#region 私有变量
		private int m_detailID;					//流水标识
		private string m_p1_MerId;				//商户编号
		private string m_r0_Cmd;				//业务类型
		private string m_r1_Code;				//支付结果
		private string m_r2_TrxId;				//易宝支付交易流水号
		private decimal m_r3_Amt;				//支付金额
		private string m_r4_Cur;				//交易币种
		private string m_r5_Pid;				//商品名称
		private string m_r6_Order;				//商户订单号
		private string m_r7_Uid;				//易宝支付会员ID
		private string m_r8_MP;					// 商户扩展信息
		private string m_r9_BType;				//交易结果返回类型
		private string m_rb_BankId;				//银行编码
		private string m_ro_BankOrderId;		//银行订单号
		private string m_rp_PayDate;			//支付成功时间
		private string m_rq_CardNo;				// 神州行充值卡序列号
		private string m_ru_Trxtime;			// 交易结果通知时间
		private string m_hmac;					//签名数据
		private DateTime m_collectDate;			//收录时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化ReturnYPDetailInfo
		/// </summary>
		public ReturnYPDetailInfo()
		{
			m_detailID=0;
			m_p1_MerId="";
			m_r0_Cmd="";
			m_r1_Code="";
			m_r2_TrxId="";
			m_r3_Amt=0;
			m_r4_Cur="";
			m_r5_Pid="";
			m_r6_Order="";
			m_r7_Uid="";
			m_r8_MP="";
			m_r9_BType="";
			m_rb_BankId="";
			m_ro_BankOrderId="";
			m_rp_PayDate="";
			m_rq_CardNo="";
			m_ru_Trxtime="";
			m_hmac="";
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
		/// 商户编号
		/// </summary>
		public string P1_MerId
		{
			get { return m_p1_MerId; }
			set { m_p1_MerId = value; }
		}

		/// <summary>
		/// 业务类型
		/// </summary>
		public string R0_Cmd
		{
			get { return m_r0_Cmd; }
			set { m_r0_Cmd = value; }
		}

		/// <summary>
		/// 支付结果
		/// </summary>
		public string R1_Code
		{
			get { return m_r1_Code; }
			set { m_r1_Code = value; }
		}

		/// <summary>
		/// 易宝支付交易流水号
		/// </summary>
		public string R2_TrxId
		{
			get { return m_r2_TrxId; }
			set { m_r2_TrxId = value; }
		}

		/// <summary>
		/// 支付金额
		/// </summary>
		public decimal R3_Amt
		{
			get { return m_r3_Amt; }
			set { m_r3_Amt = value; }
		}

		/// <summary>
		/// 交易币种
		/// </summary>
		public string R4_Cur
		{
			get { return m_r4_Cur; }
			set { m_r4_Cur = value; }
		}

		/// <summary>
		/// 商品名称
		/// </summary>
		public string R5_Pid
		{
			get { return m_r5_Pid; }
			set { m_r5_Pid = value; }
		}

		/// <summary>
		/// 商户订单号
		/// </summary>
		public string R6_Order
		{
			get { return m_r6_Order; }
			set { m_r6_Order = value; }
		}

		/// <summary>
		/// 易宝支付会员ID
		/// </summary>
		public string R7_Uid
		{
			get { return m_r7_Uid; }
			set { m_r7_Uid = value; }
		}

		/// <summary>
		///  商户扩展信息
		/// </summary>
		public string R8_MP
		{
			get { return m_r8_MP; }
			set { m_r8_MP = value; }
		}

		/// <summary>
		/// 交易结果返回类型
		/// </summary>
		public string R9_BType
		{
			get { return m_r9_BType; }
			set { m_r9_BType = value; }
		}

		/// <summary>
		/// 银行编码
		/// </summary>
		public string Rb_BankId
		{
			get { return m_rb_BankId; }
			set { m_rb_BankId = value; }
		}

		/// <summary>
		/// 银行订单号
		/// </summary>
		public string Ro_BankOrderId
		{
			get { return m_ro_BankOrderId; }
			set { m_ro_BankOrderId = value; }
		}

		/// <summary>
		/// 支付成功时间
		/// </summary>
		public string Rp_PayDate
		{
			get { return m_rp_PayDate; }
			set { m_rp_PayDate = value; }
		}

		/// <summary>
		///  神州行充值卡序列号
		/// </summary>
		public string Rq_CardNo
		{
			get { return m_rq_CardNo; }
			set { m_rq_CardNo = value; }
		}

		/// <summary>
		///  交易结果通知时间
		/// </summary>
		public string Ru_Trxtime
		{
			get { return m_ru_Trxtime; }
			set { m_ru_Trxtime = value; }
		}

		/// <summary>
		/// 签名数据
		/// </summary>
		public string Hmac
		{
			get { return m_hmac; }
			set { m_hmac = value; }
		}

		/// <summary>
		/// 收录时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}
		#endregion
	}
}
