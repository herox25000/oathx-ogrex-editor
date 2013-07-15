/*
 * 版本：4.0
 * 时间：2012-2-15
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
    /// 实体类 ReturnDayDetailInfo。(属性说明自动提取数据库字段的描述信息)
    /// </summary>
    [Serializable]
    public partial class ReturnDayDetailInfo
    {
        #region 常量

        /// <summary>
        /// 表名
        /// </summary>
        public const string Tablename = "ReturnDayDetailInfo";

        /// <summary>
        /// 流水号
        /// </summary>
        public const string _DetailID = "DetailID";

        /// <summary>
        /// 订单号
        /// </summary>
        public const string _OrderID = "OrderID";

        /// <summary>
        /// 商户ID
        /// </summary>
        public const string _MerID = "MerID";

        /// <summary>
        /// 金额
        /// </summary>
        public const string _PayMoney = "PayMoney";

        /// <summary>
        /// 用户名
        /// </summary>
        public const string _UserName = "UserName";

        /// <summary>
        /// 支付类型（1：网银支付 ）
        /// </summary>
        public const string _PayType = "PayType";

        /// <summary>
        /// 支付状态
        /// </summary>
        public const string _Status = "Status";

        /// <summary>
        /// 签名
        /// </summary>
        public const string _Sign = "Sign";

        /// <summary>
        /// 充值时间
        /// </summary>
        public const string _InputDate = "InputDate";
        #endregion

        #region 私有变量
        private int m_detailID;					//流水号
        private string m_orderID;				//订单号
        private string m_merID;					//商户ID
        private decimal m_payMoney;				//金额
        private string m_userName;				//用户名
        private int m_payType;					//支付类型（1：网银支付 ）
        private string m_status;				//支付状态
        private string m_sign;					//签名
        private DateTime m_inputDate;			//充值时间
        #endregion

        #region 构造方法

        /// <summary>
        /// 初始化ReturnDayDetailInfo
        /// </summary>
        public ReturnDayDetailInfo( )
        {
            m_detailID = 0;
            m_orderID = "";
            m_merID = "";
            m_payMoney = 0;
            m_userName = "";
            m_payType = 0;
            m_status = "";
            m_sign = "";
            m_inputDate = DateTime.Now;
        }

        #endregion

        #region 公共属性

        /// <summary>
        /// 流水号
        /// </summary>
        public int DetailID
        {
            get
            {
                return m_detailID;
            }
            set
            {
                m_detailID = value;
            }
        }

        /// <summary>
        /// 订单号
        /// </summary>
        public string OrderID
        {
            get
            {
                return m_orderID;
            }
            set
            {
                m_orderID = value;
            }
        }

        /// <summary>
        /// 商户ID
        /// </summary>
        public string MerID
        {
            get
            {
                return m_merID;
            }
            set
            {
                m_merID = value;
            }
        }

        /// <summary>
        /// 金额
        /// </summary>
        public decimal PayMoney
        {
            get
            {
                return m_payMoney;
            }
            set
            {
                m_payMoney = value;
            }
        }

        /// <summary>
        /// 用户名
        /// </summary>
        public string UserName
        {
            get
            {
                return m_userName;
            }
            set
            {
                m_userName = value;
            }
        }

        /// <summary>
        /// 支付类型（1：网银支付 ）
        /// </summary>
        public int PayType
        {
            get
            {
                return m_payType;
            }
            set
            {
                m_payType = value;
            }
        }

        /// <summary>
        /// 支付状态
        /// </summary>
        public string Status
        {
            get
            {
                return m_status;
            }
            set
            {
                m_status = value;
            }
        }

        /// <summary>
        /// 签名
        /// </summary>
        public string Sign
        {
            get
            {
                return m_sign;
            }
            set
            {
                m_sign = value;
            }
        }

        /// <summary>
        /// 充值时间
        /// </summary>
        public DateTime InputDate
        {
            get
            {
                return m_inputDate;
            }
            set
            {
                m_inputDate = value;
            }
        }
        #endregion
    }
}
