using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Pay
{
    public partial class PayReceive : System.Web.UI.Page
    {
        #region 公共属性

        TreasureFacade treasureFacade = new TreasureFacade();

        public int rtnOk = 0;
        public String rtnUrl = "";

        #endregion

        protected void Page_Load(object sender, EventArgs e)
        {
            #region  获取快钱支付结果，并且保存在数据库中-->跳转

            //初始化结果及地址
            ReturnKQDetailInfo result = new ReturnKQDetailInfo();

            string showUrl = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayShow.aspx";

            //人民币网关账户号
            String merchantAcctId = Request["merchantAcctId"];
            if (String.IsNullOrEmpty(merchantAcctId))
            {
                merchantAcctId = ApplicationSettings.Get("merchantIdRMB");
            }
            result.MerchantAcctID = merchantAcctId.Trim();

            //人民币网关密钥--区分大小写
            String key = ApplicationSettings.Get("keyValueRMB");

            //网关版本.固定值
            ///快钱会根据版本号来调用对应的接口处理程序。
            ///本代码版本号固定为v2.0
            String version = Request["version"];
            if (String.IsNullOrEmpty(version))
                version = "v2.0";
            result.Version = version.Trim();

            //语言种类.固定选择值。
            ///只能选择1、2、3
            ///1代表中文；2代表英文
            ///默认值为1
            String language = Request["language"];
            if (String.IsNullOrEmpty(language))
                language = "1";
            result.Language = Convert.ToInt32(language.Trim());

            //签名类型.固定值--1代表MD5签名
            ///当前版本固定为1
            String signType = Request["signType"];
            if (String.IsNullOrEmpty(signType))
                signType = "1";
            result.SignType = Convert.ToInt32(signType.Trim());

            //支付方式--值为：10、11、12、13、14
            //00：组合支付（网关支付页面显示快钱支持的各种支付方式，推荐使用）10：银行卡支付（网关支付页面只显示银行卡支付）.11：电话银行支付（网关支付页面只显示电话支付）.12：快钱账户支付（网关支付页面只显示快钱账户支付）.13：线下支付（网关支付页面只显示线下支付方式）.14：B2B支付（网关支付页面只显示B2B支付，但需要向快钱申请开通才能使用）
            String payType = Request["payType"];
            if (String.IsNullOrEmpty(payType))
                payType = "00";
            result.PayType = payType.Trim();


            //银行代码-参见银行代码列表
            String bankId = Request["bankId"];
            if (String.IsNullOrEmpty(bankId))
                bankId = "";
            result.BankID = bankId.Trim();


            //商户订单号
            String orderId = Request["orderId"];
            //String orderId = "KQ20120321094644143608554";
            if (String.IsNullOrEmpty(orderId))
                orderId = "";
            result.OrderID = orderId.Trim();

            //订单提交时间
            ///商户提交订单时的时间.14位数字。年[4位]月[2位]日[2位]时[2位]分[2位]秒[2位]
            ///如：20080101010101
            String orderTime = Request["orderTime"];
            if (String.IsNullOrEmpty(orderTime))
                orderTime = "19000101010101";

            //原始订单金额-单位为分。
            String orderAmount = Request["orderAmount"];
            if (String.IsNullOrEmpty(orderAmount))
                orderAmount = "0";
            result.OrderAmount = Convert.ToDecimal(orderAmount.Trim()) / 100;

            //快钱交易号
            String dealId = Request["dealId"];
            if (String.IsNullOrEmpty(dealId))
                dealId = "";
            result.DealID = dealId.Trim();


            //银行交易号--如未通过银行支付，则为空
            String bankDealId = Request["bankDealId"];
            if (String.IsNullOrEmpty(bankDealId))
                bankDealId = "";
            result.BankDealID = bankDealId.Trim();


            //快钱交易时间-14位数字。年[4位]月[2位]日[2位]时[2位]分[2位]秒[2位]
            ///如；20080101010101
            String dealTime = Request["dealTime"];
            if (String.IsNullOrEmpty(dealTime))
            {
                dealTime = "19000101010101";
            }

            //实际支付金额-单位为分
            String payAmount = Request["payAmount"];
            //String payAmount = "3000";
            if (String.IsNullOrEmpty(payAmount))
                payAmount = "0";
            result.PayAmount = Convert.ToDecimal(payAmount.Trim()) / 100;


            //交易手续费-单位为分
            String fee = Request["fee"];
            //String fee = "30";
            if (String.IsNullOrEmpty(fee))
            {
                fee = "0";
            }
            result.Fee = Convert.ToDecimal(fee.Trim()) / 100;

            //扩展字段1 --损耗比例
            String ext1 = Request["ext1"];
            //String ext1 = "10";
            if (String.IsNullOrEmpty(ext1))
                ext1 = "0";
            result.Ext1 = ext1.Trim();


            //扩展字段2
            String ext2 = Request["ext2"];
            //String ext2 = "1000";
            if (String.IsNullOrEmpty(ext2))
            {
                ext2 = "";
            }
            result.Ext2 = ext2.Trim();


            //处理结果  10:成功; 11:失败
            String payResult = Request["payResult"];
            //payResult = "10";
            if (String.IsNullOrEmpty(payResult))
            {
                payResult = "11";
            }
            result.PayResult = payResult.Trim();


            //错误代码
            String errCode = Request["errCode"];
            if (String.IsNullOrEmpty(errCode))
            {
                errCode = "";
            }
            result.ErrCode = errCode.Trim();


            //加密签名
            String signMsg = Request["signMsg"];
            if (String.IsNullOrEmpty(signMsg))
            {
                signMsg = "";
            }
            result.SignMsg = signMsg.Trim();


            //生成加密串
            String merchantSignMsgVal = "";
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "merchantAcctId", merchantAcctId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "version", version);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "language", language);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "signType", signType);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "payType", payType);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "bankId", bankId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "orderId", orderId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "orderTime", orderTime);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "orderAmount", orderAmount);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "dealId", dealId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "bankDealId", bankDealId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "dealTime", dealTime);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "payAmount", payAmount);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "fee", fee);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "ext1", ext1);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "ext2", ext2);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "payResult", payResult);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "errCode", errCode);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "key", key);

            String merchantSignMsg = FormsAuthentication.HashPasswordForStoringInConfigFile(merchantSignMsgVal, "MD5");

            //订单提交时间
            orderTime = orderTime.Substring(0, 4) + "-" + orderTime.Substring(4, 2) + "-" + orderTime.Substring(6, 2) + " " + orderTime.Substring(8, 2) + ":" + orderTime.Substring(10, 2) + ":" + orderTime.Substring(12, 2);
            result.OrderTime = Convert.ToDateTime(orderTime);

            //快钱交易时间
            dealTime = dealTime.Substring(0, 4) + "-" + dealTime.Substring(4, 2) + "-" + dealTime.Substring(6, 2) + " " + dealTime.Substring(8, 2) + ":" + dealTime.Substring(10, 2) + ":" + dealTime.Substring(12, 2);
            result.DealTime = Convert.ToDateTime(dealTime);

            //快钱支付结果入库
            treasureFacade.WriteReturnKQDetail(result);

            ///签名验证
            if (signMsg.ToUpper() == merchantSignMsg.ToUpper())
            {
                switch (payResult)
                {
                    case "10":

                        /* 商户网站逻辑处理，比方更新订单支付状态为成功
                           特别注意：只有signMsg.ToUpper() == merchantSignMsg.ToUpper()，且payResult=10，才表示支付成功！同时将订单金额与提交订单前的订单金额进行对比校验。*/

                        //报告给快钱处理结果，并提供将要重定向的地址。
                        rtnOk = 1;

                        ShareDetialInfo detailInfo = new ShareDetialInfo();

                        detailInfo.OrderID = result.OrderID;
                        detailInfo.IPAddress = Utility.UserIP;
                        detailInfo.PayAmount = result.PayAmount;

                        //写充值记录
                        try
                        {
                            Message umsg = treasureFacade.FilliedOnline(detailInfo, 0);
                            if (umsg.Success)
                            {
                                rtnUrl = showUrl + "?msg=1";//在线充值成功
                            }
                            else
                            {
                                rtnUrl = showUrl + "?msg=2";//在线充值成功,数据正在更新中
                            }
                        }
                        catch
                        {
                            rtnUrl = showUrl + "?msg=2";//在线充值成功,数据正在更新中
                        }
                        break;
                    default:
                        rtnOk = 1;
                        rtnUrl = showUrl + "?msg=3"; //在线充值失败!
                        break;
                }
            }
            else
            {
                rtnOk = 1;
                rtnUrl = showUrl + "?msg=3";
            }

            #endregion
        }


        //功能函数。将变量值不为空的参数组成字符串
        private String AppendParam(String returnStr, String paramId, String paramValue)
        {
            if (returnStr != "")
            {
                if (paramValue != "")
                {
                    returnStr += "&" + paramId + "=" + paramValue;
                }
            }
            else
            {
                if (paramValue != "")
                {
                    returnStr = paramId + "=" + paramValue;
                }
            }
            return returnStr;
        }
    }
}
