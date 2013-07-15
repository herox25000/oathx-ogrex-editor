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
    public partial class PayMobile : UCPageBase
    {
        private TreasureFacade treasureFacade = new TreasureFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                this.fmStep1.Visible = true;
                this.fmStep2.Visible = false;

                if (Fetch.GetUserCookie() != null)
                {
                    this.txtPayAccounts.Text = Fetch.GetUserCookie().Accounts;
                    this.txtPayReAccounts.Text = Fetch.GetUserCookie().Accounts;
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "充值中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("充值卡充值 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }


        protected void btnPay_Click(object sender, EventArgs e)
        {
            string strAccounts = CtrlHelper.GetText(txtPayAccounts);
            string strReAccounts = CtrlHelper.GetText(txtPayReAccounts);
            int salePrice = GameRequest.GetFormInt("rbSaleType", 0);
            int gamePayType = GameRequest.GetFormInt("rbPayMType", 1);

            if (strAccounts == "")
            {
                RenderAlertInfo(true, "抱歉，请输入充值帐号。", 2);
                return;
            }
            if (strReAccounts != strAccounts)
            {
                RenderAlertInfo(true, "抱歉，两次输入的帐号不一致。", 2);
                return;
            }
            if (salePrice < 30)
            {
                RenderAlertInfo(true, "抱歉，充值金额必须大于30元", 2);
                return;
            }

            OnLineOrder onlineOrder = new OnLineOrder();
            onlineOrder.ShareID = gamePayType == 1 ? 4 : gamePayType == 2 ? 5 : 6;
            onlineOrder.OrderID = gamePayType == 1 ? PayHelper.GetOrderIDByPrefix("SZX") : gamePayType == 2 ? PayHelper.GetOrderIDByPrefix("LT") : PayHelper.GetOrderIDByPrefix("DX");

            #region 订单处理

            if (Fetch.GetUserCookie() == null)
            {
                onlineOrder.OperUserID = 0;
            }
            else
            {
                onlineOrder.OperUserID = Fetch.GetUserCookie().UserID;
            }
            onlineOrder.Accounts = strAccounts;
            onlineOrder.CardTotal = 1;
            onlineOrder.CardTypeID = salePrice < 30 ? 1 : salePrice < 60 ? 2 : salePrice < 120 ? 3 : 4;
            onlineOrder.OrderAmount = salePrice;
            onlineOrder.IPAddress = GameRequest.GetUserIP();

            //生成订单
            Message umsg = treasureFacade.RequestOrder(onlineOrder);
            if (!umsg.Success)
            {
                RenderAlertInfo(true, umsg.Content, 2);
                return;
            }

            #endregion

            #region 提交给快钱支付网关

            //人民币网关账户号
            ///请登录快钱系统获取用户编号，用户编号后加01即为人民币网关账户号。
            string merchantAcctId = gamePayType == 1 ? ApplicationSettings.Get("merchantIdYD") : gamePayType == 2 ? ApplicationSettings.Get("merchantIdLT") : ApplicationSettings.Get("merchantIdDX");
            //string merchantAcctId = ApplicationSettings.Get( "merchantIdMobile" );

            //人民币网关密钥
            ///区分大小写.请与快钱联系索取
            string key = gamePayType == 1 ? ApplicationSettings.Get("keyValueYD") : gamePayType == 2 ? ApplicationSettings.Get("keyValueLT") : ApplicationSettings.Get("keyValueDX");
            //string key = ApplicationSettings.Get( "keyValueMobile" );

            //服务器接受支付结果的后台地址.与[pageUrl]不能同时为空。必须是绝对地址。
            ///快钱通过服务器连接的方式将交易结果发送到[bgUrl]对应的页面地址，在商户处理完成后输出的<result>如果为1，页面会转向到<redirecturl>对应的地址。
            ///如果快钱未接收到<redirecturl>对应的地址，快钱将把支付结果GET到[pageUrl]对应的页面。
            //bgUrl.Value = "http://www.yoursite.com/receive.aspx";
            string bgUrl = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayMobileReceive.aspx";

            //接受支付结果的页面地址.与[bgUrl]不能同时为空。必须是绝对地址。
            ////如果[bgUrl]为空，快钱将支付结果GET到[pageUrl]对应的地址。
            ////如果[bgUrl]不为空，并且[bgUrl]页面指定的<redirecturl>地址不为空，则转向到<redirecturl>对应的地址
            string pageUrl = "";

            //字符集.固定选择值。可为空。
            ////只能选择1、2、3、5
            ////1代表UTF-8; 2代表GBK; 3代表gb2312; 5 代表big5
            ////默认值为1
            string inputCharset = "1";

            //网关版本.固定值
            ////快钱会根据版本号来调用对应的接口处理程序。
            ////本代码版本号固定为v2.0
            string version = "v2.0";

            //语言种类.固定选择值。
            ////只能选择1、2、3
            ////1代表中文；2代表英文
            ////默认值为1
            string language = "1";

            //签名类型.固定值
            ////1代表MD5签名
            ////当前版本固定为1
            string signType = "1";

            //支付人姓名
            ///可为中文或英文字符
            string payerName = HttpUtility.UrlEncode(onlineOrder.Accounts, Encoding.GetEncoding("UTF-8")).ToUpper();

            //支付人联系方式类型.固定选择值
            ////只能选择1
            ////1代表Email
            string payerContactType = "1";

            //支付人联系方式
            ////只能选择Email或手机号
            string payerContact = "";

            //商户订单号
            ///由字母、数字、或[-][_]组成
            string orderId = onlineOrder.OrderID;

            //订单金额
            ///以分为单位，必须是整型数字
            ///比方2，代表0.02元
            string orderAmount = (salePrice * 100).ToString("f0");

            //支付方式.固定选择值
            ////可选择00、41、42、52
            ////00 代表快钱默认支付方式，目前为神州行卡密支付和快钱账户支付；41 代表快钱账户支付；42 代表神州行卡密支付和快钱账户支付；52 代表神州行卡密支付
            string payType = "42";

            //神州行卡序号
            ////仅在商户定制了神州行卡密直连功能时填写
            string cardNumber = "";

            //神州行卡密码
            ////仅在商户定制了神州行卡密直连功能时填写
            string cardPwd = "";

            //全额支付标志
            ////只能选择数字 0 或 1
            ////0代表非全额支付方式，支付完成后返回订单金额为商户提交的订单金额。如果预付费卡面额小于订单金额时，返回支付结果为失败；预付费卡面额大于或等于订单金额时，返回支付结果为成功；
            ////1 代表全额支付方式，支付完成后返回订单金额为用户预付费卡的面额。只要预付费卡销卡成功，返回支上海快钱信息服务有限公司 版权所有 第 6 页付结果都为成功。如果商户定制神州行卡密直连时，本参数固定值为1
            string fullAmountFlag = "0";

            //订单提交时间
            ///14位数字。年[4位]月[2位]日[2位]时[2位]分[2位]秒[2位]
            ///如；20080101010101
            string orderTime = DateTime.Now.ToString("yyyyMMddHHmmss");

            //商品名称
            ////可为中文或英文字符
            string productName = HttpUtility.UrlEncode((salePrice < 30 ? "蓝钻会员卡" : salePrice < 60 ? "黄钻会员卡" : salePrice < 120 ? "白钻会员卡" : "红钻会员卡"), Encoding.GetEncoding("UTF-8")).ToUpper();

            //商品数量
            ////可为空，非空时必须为数字
            string productNum = onlineOrder.CardTotal.ToString();

            //商品代码
            ///可为字符或者数字
            string productId = "";

            //商品描述
            string productDesc = "";

            //扩展字段1
            ///在支付结束后原样返回给商户 服务损耗比例(*1000)
            string ext1 = "0";

            //扩展字段2
            //在支付结束后原样返回给商户 
            string ext2 = "";

            //充值卡类型
            ////固定选择值：0、1、3、4、9
            ////0 代表神州行充值卡
            ////1 代表联通充值卡
            ////3 代表电信充值卡
            ////4 代表骏网一卡通
            ////9 代表已开通任一卡类型
            string bossType = (gamePayType == 1 ? 0 : gamePayType == 2 ? 1 : 3).ToString().Trim();

            //生成加密签名串
            ///请务必按照如下顺序和规则组成加密串！
            string signMsgVal = "";
            signMsgVal = AppendParam(signMsgVal, "inputCharset", inputCharset);
            signMsgVal = AppendParam(signMsgVal, "bgUrl", bgUrl);
            signMsgVal = AppendParam(signMsgVal, "pageUrl", pageUrl);
            signMsgVal = AppendParam(signMsgVal, "version", version);
            signMsgVal = AppendParam(signMsgVal, "language", language);
            signMsgVal = AppendParam(signMsgVal, "signType", signType);
            signMsgVal = AppendParam(signMsgVal, "merchantAcctId", merchantAcctId);
            signMsgVal = AppendParam(signMsgVal, "payerName", payerName);
            signMsgVal = AppendParam(signMsgVal, "payerContactType", payerContactType);
            signMsgVal = AppendParam(signMsgVal, "payerContact", payerContact);
            signMsgVal = AppendParam(signMsgVal, "orderId", orderId);
            signMsgVal = AppendParam(signMsgVal, "orderAmount", orderAmount);
            signMsgVal = AppendParam(signMsgVal, "payType", payType);
            signMsgVal = AppendParam(signMsgVal, "cardNumber", cardNumber);
            signMsgVal = AppendParam(signMsgVal, "cardPwd", cardPwd);
            signMsgVal = AppendParam(signMsgVal, "fullAmountFlag", fullAmountFlag);
            signMsgVal = AppendParam(signMsgVal, "orderTime", orderTime);
            signMsgVal = AppendParam(signMsgVal, "productName", productName);
            signMsgVal = AppendParam(signMsgVal, "productNum", productNum);
            signMsgVal = AppendParam(signMsgVal, "productId", productId);
            signMsgVal = AppendParam(signMsgVal, "productDesc", productDesc);
            signMsgVal = AppendParam(signMsgVal, "ext1", ext1);
            signMsgVal = AppendParam(signMsgVal, "ext2", ext2);
            signMsgVal = AppendParam(signMsgVal, "bossType", bossType);
            signMsgVal = AppendParam(signMsgVal, "key", key);

            string signMsg = FormsAuthentication.HashPasswordForStoringInConfigFile(signMsgVal, "MD5").ToUpper();
            #endregion

            #region 整理参数
            RenderAlertInfo(false, "页面正跳转到支付平台，请稍候。。。", 2);

            StringBuilder builder = new StringBuilder();
            builder.AppendLine(CreateInputHidden("inputCharset", inputCharset));
            builder.AppendLine(CreateInputHidden("bgUrl", bgUrl));
            builder.AppendLine(CreateInputHidden("pageUrl", pageUrl));
            builder.AppendLine(CreateInputHidden("version", version));
            builder.AppendLine(CreateInputHidden("language", language));
            builder.AppendLine(CreateInputHidden("signType", signType));
            builder.AppendLine(CreateInputHidden("merchantAcctId", merchantAcctId));
            builder.AppendLine(CreateInputHidden("payerName", payerName));
            builder.AppendLine(CreateInputHidden("payerContactType", payerContactType));
            builder.AppendLine(CreateInputHidden("payerContact", payerContact));
            builder.AppendLine(CreateInputHidden("orderId", orderId));
            builder.AppendLine(CreateInputHidden("orderAmount", orderAmount));
            builder.AppendLine(CreateInputHidden("payType", payType));
            builder.AppendLine(CreateInputHidden("cardNumber", cardNumber));
            builder.AppendLine(CreateInputHidden("cardPwd", cardPwd));
            builder.AppendLine(CreateInputHidden("fullAmountFlag", fullAmountFlag));
            builder.AppendLine(CreateInputHidden("orderTime", orderTime));
            builder.AppendLine(CreateInputHidden("productName", productName));
            builder.AppendLine(CreateInputHidden("productNum", productNum));
            builder.AppendLine(CreateInputHidden("productId", productId));
            builder.AppendLine(CreateInputHidden("productDesc", productDesc));
            builder.AppendLine(CreateInputHidden("ext1", ext1));
            builder.AppendLine(CreateInputHidden("ext2", ext2));
            builder.AppendLine(CreateInputHidden("bossType", bossType));
            builder.AppendLine(CreateInputHidden("signMsg", signMsg));

            lit99Bill.Text = builder.ToString();
            #endregion

            this.Page.ClientScript.RegisterStartupScript(this.GetType(), "message", "window.onload = function() { document.forms[0].submit(); }", true);
        }

        //提示样式类
        private static string[] ALERT_STYLE_CLASS = { "tips_correct_big", "green bold", "tips_error_big", "hong bold" };

        /// <summary>
        /// 提示信息
        /// </summary>
        /// <param name="isError"></param>
        public new virtual void RenderAlertInfo(bool isError, string alertText, int step)
        {
            if (step == 2)
            {
                this.fmStep1.Visible = false;
                this.fmStep2.Visible = true;
            }

            //查找提示控件
            Label lblAlertIcon = this.FindControl("lblAlertIcon") as Label;
            Label lblAlertInfo = this.FindControl("lblAlertInfo") as Label;
            if (lblAlertIcon != null && lblAlertInfo != null)
            {
                if (isError)
                {
                    lblAlertIcon.CssClass = ALERT_STYLE_CLASS[2];
                    lblAlertInfo.CssClass = ALERT_STYLE_CLASS[3];
                    lblAlertInfo.Text = alertText;

                    this.pnlContinue.Visible = true;
                }
                else
                {
                    lblAlertIcon.CssClass = ALERT_STYLE_CLASS[0];
                    lblAlertInfo.CssClass = ALERT_STYLE_CLASS[1];
                    lblAlertInfo.Text = alertText;

                    this.pnlContinue.Visible = false;
                }
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

        //隐藏字段
        private string CreateInputHidden(string idName, string value)
        {
            return String.Format("<input type=\"hidden\" id=\"{0}\" value=\"{1}\" name=\"{0}\" />", idName, value);
        }
    }
}
