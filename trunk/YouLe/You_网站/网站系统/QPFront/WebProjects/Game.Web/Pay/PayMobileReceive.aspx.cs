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
    public partial class PayMobileReceive : System.Web.UI.Page
    {
        #region 公共属性

        private TreasureFacade treasureFacade = new TreasureFacade();

        public int rtnOk = 0;
        public String rtnUrl = "";

        #endregion

        protected void Page_Load(object sender, EventArgs e)
        {
            //初始化结果及地址
            ReturnKQDetailInfo result = new ReturnKQDetailInfo();

            string showUrl = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayShow.aspx";

            //获取网关账户号
            string merchantAcctId = Request["merchantAcctId"].ToString().Trim();
            result.MerchantAcctID = merchantAcctId;

            //设置网关密钥
            ///区分大小写    
            string bossType1 = Request["bossType"].ToString().Trim();//根据获取的支付卡类型判断加载相应的密钥
            string key = bossType1 == "0" ? ApplicationSettings.Get("keyValueYD") : bossType1 == "1" ? ApplicationSettings.Get("keyValueLT") : ApplicationSettings.Get("keyValueDX");

            //获取网关版本.固定值
            ///本代码版本号固定为v2.0
            string version = Request["version"].ToString().Trim();
            result.Version = version.Trim();

            //获取语言种类.固定选择值。
            ///只能选择1、2
            ///1代表中文；2代表英文
            string language = Request["language"].ToString().Trim();
            result.Language = Convert.ToInt32(language.Trim());

            //获取支付方式
            ///可选择00、41、42、52
            ///00 代表快钱默认支付方式，目前为神州行卡密支付和快钱账户支付；41 代表快钱账户支付；42 代表神州行卡密支付和快钱账户支付；52 代表神州行卡密支付
            string payType = Request["payType"].ToString().Trim();
            result.PayType = payType.Trim();

            //神州行卡序号
            ///如果通过神州行卡直接支付时返回
            string cardNumber = Request["cardNumber"].ToString().Trim();
            result.CardNumber = cardNumber;

            //获取神州行卡密码
            ///如果通过神州行卡直接支付时返回
            string cardPwd = Request["cardPwd"].ToString().Trim();
            result.CardPwd = cardPwd;

            //获取商户订单号
            string orderId = Request["orderId"].ToString().Trim();
            result.OrderID = orderId.Trim();

            //获取原始订单金额
            ///订单提交到快钱时的金额，单位为分。
            ///比方2 ，代表0.02元
            string orderAmount = Request["orderAmount"].ToString().Trim();
            result.OrderAmount = Convert.ToDecimal(orderAmount.Trim()) / 100;

            //获取快钱交易号
            ///获取该交易在快钱的交易号
            string dealId = Request["dealId"].ToString().Trim();
            result.DealID = dealId.Trim();

            //获取商户提交订单时的时间
            ///14位数字。年[4位]月[2位]日[2位]时[2位]分[2位]秒[2位]
            ///如：20080101010101
            string orderTime = Request["orderTime"].ToString().Trim();

            //获取扩展字段1
            ///与商户提交订单时的扩展字段1保持一致
            string ext1 = Request["ext1"].ToString().Trim();
            result.Ext1 = ext1.Trim();

            //获取扩展字段2
            ///与商户提交订单时的扩展字段2保持一致
            string ext2 = Request["ext2"].ToString().Trim();
            result.Ext2 = ext2.Trim();

            //获取实际支付金额
            ///单位为分
            ///比方 2 ，代表0.02元
            string payAmount = Request["payAmount"].ToString().Trim();
            result.PayAmount = Convert.ToDecimal(payAmount.Trim()) / 100;

            //获取快钱处理时间
            string billOrderTime = Request["billOrderTime"].ToString().Trim();

            //获取处理结果
            ///10代表支付成功； 11代表支付失败
            string payResult = Request["payResult"].ToString().Trim();
            result.PayResult = payResult.Trim();

            //获取签名类型
            ///1代表MD5签名
            ///当前版本固定为1
            string signType = Request["signType"].ToString().Trim();
            result.SignType = Convert.ToInt32(signType.Trim());

            //充值卡类型
            ////与提交订单时的充值卡类型保持一致
            string bossType = Request["bossType"].ToString().Trim();
            result.BossType = bossType;

            //支付卡类型
            ////固定选择值：0、1、3、4、9，用户实际支付的卡类型
            ////0 代表神州行充值卡
            ////1 代表联通充值卡
            ////3 代表电信充值卡
            ////4 代表骏网一卡通
            ////9 代表已开通任一卡类型
            ////比喻商户提交bossType类型为9，用户实际支付卡类型为0，则receiveBossType返回为0
            string receiveBossType = Request["receiveBossType"].ToString().Trim();
            result.ReceiveBossType = receiveBossType;

            //实际收款账号
            ////用户实际支付的卡类型对应收款帐号必须对应receiveBossType卡类型收款帐号
            ////比如提交的merchantAcctId=1000300079902，bossType=9，是全部支付方式都有，但实际支付时选择的是联通充值卡支付
            ////那返回的receiveBossType=1，返回的bossType，返回的merchantAcctId=1000300079902，返回的receiverAcctId=1000300079909
            string receiverAcctId = Request["receiverAcctId"].ToString().Trim();
            result.ReceiverAcctId = receiverAcctId;

            //获取加密签名串
            string signMsg = Request["signMsg"].ToString().Trim();
            result.SignMsg = signMsg.Trim();


            //生成加密串。必须保持如下顺序。
            string merchantSignMsgVal = "";
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "merchantAcctId", merchantAcctId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "version", version);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "language", language);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "payType", payType);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "cardNumber", cardNumber);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "cardPwd", cardPwd);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "orderId", orderId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "orderAmount", orderAmount);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "dealId", dealId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "orderTime", orderTime);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "ext1", ext1);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "ext2", ext2);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "payAmount", payAmount);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "billOrderTime", billOrderTime);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "payResult", payResult);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "signType", signType);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "bossType", bossType);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "receiveBossType", receiveBossType);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "receiverAcctId", receiverAcctId);
            merchantSignMsgVal = AppendParam(merchantSignMsgVal, "key", key);

            string merchantSignMsg = FormsAuthentication.HashPasswordForStoringInConfigFile(merchantSignMsgVal, "MD5").ToUpper();

            //订单提交时间
            orderTime = orderTime.Substring(0, 4) + "-" + orderTime.Substring(4, 2) + "-" + orderTime.Substring(6, 2) + " " + orderTime.Substring(8, 2) + ":" + orderTime.Substring(10, 2) + ":" + orderTime.Substring(12, 2);
            result.OrderTime = Convert.ToDateTime(orderTime);

            //快钱交易时间
            billOrderTime = billOrderTime.Substring(0, 4) + "-" + billOrderTime.Substring(4, 2) + "-" + billOrderTime.Substring(6, 2) + " " + billOrderTime.Substring(8, 2) + ":" + billOrderTime.Substring(10, 2) + ":" + billOrderTime.Substring(12, 2);
            result.DealTime = Convert.ToDateTime(billOrderTime);

            //快钱支付结果入库
            treasureFacade.WriteReturnKQDetail(result);

            //商家进行数据处理，并跳转回商家显示支付结果的页面
            ///首先进行签名字符串验证
            if (signMsg.ToUpper() == merchantSignMsg.ToUpper())
            {
                switch (payResult)
                {

                    case "10":
                        /*  
                         // 商户网站逻辑处理，比方更新订单支付状态为成功
                        // 特别注意：只有signMsg.ToUpper() == merchantSignMsg.ToUpper()，且payResult=10，才表示支付成功！
                        */

                        //报告给快钱处理结果，并提供将要重定向的地址。
                        rtnOk = 1;

                        ShareDetialInfo detailInfo = new ShareDetialInfo();
                        detailInfo.OrderID = result.OrderID;
                        detailInfo.IPAddress = Utility.UserIP;
                        detailInfo.PayAmount = result.PayAmount;

                        //写充值记录
                        try
                        {
                            Message msg = treasureFacade.FilliedOnline(detailInfo, 0);
                            if (msg.Success)
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
