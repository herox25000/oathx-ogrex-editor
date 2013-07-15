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
    public partial class PayGame : UCPageBase
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
            AddMetaTitle("游戏卡充值 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        protected void btnPay_Click(object sender, EventArgs e)
        {
            string strAccounts = CtrlHelper.GetText(txtPayAccounts);
            string strReAccounts = CtrlHelper.GetText(txtPayReAccounts);
            int salePrice = GameRequest.GetFormInt("rbSaleType", 0);
            string gamePayType = GameRequest.GetFormString("rbPayGType");

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
            onlineOrder.ShareID = gamePayType == "C" ? 7 : gamePayType == "D" ? 8 : gamePayType == "M" ? 9 : gamePayType == "N" ? 10 : 11;
            onlineOrder.OrderID = gamePayType == "C" ? PayHelper.GetOrderIDByPrefix("SD") : gamePayType == "D" ? PayHelper.GetOrderIDByPrefix("ZT") : gamePayType == "M" ? PayHelper.GetOrderIDByPrefix("WY") : gamePayType == "N" ? PayHelper.GetOrderIDByPrefix("SH") : PayHelper.GetOrderIDByPrefix("WM");

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

            //商户号
            string merchantAcctId = ApplicationSettings.Get("merchantIdGame");

            //人民币网关密钥
            ///区分大小写.请与快钱联系索取
            string key = ApplicationSettings.Get("keyValueGame");

            //商户订单号
            string orderId = onlineOrder.OrderID.Trim();

            //支付金额
            string orderAmount = onlineOrder.OrderAmount.ToString();
            //string orderAmount = "1.00";

            //充值卡类型c 盛大一卡通d 征途游戏卡m网易一卡通n 搜狐一卡通u 完美一卡通
            string payType = gamePayType;

            //前台接收并显示页面，公网地址
            string pageUrl = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayShow.aspx";

            //支付结果底层发送的接收页面 后台接收页面
            string bgUrl = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayGameReceive.aspx";

            //扩展字段1
            string ext1 = "0";
            //扩展字段2
            string ext2 = "";

            //MD5签名 MD5签名：把请求支付的部分参数与KEY（商户后台可自行修改）拼凑成字符串经过国际标准32位MD5加密转换成大写

            String signMsgVal = "";
            signMsgVal = AppendParam(signMsgVal, "merchantAcctId", merchantAcctId);
            signMsgVal = AppendParam(signMsgVal, "orderId", orderId);
            signMsgVal = AppendParam(signMsgVal, "orderAmount", orderAmount);
            signMsgVal = AppendParam(signMsgVal, "payType", payType);
            signMsgVal = AppendParam(signMsgVal, "pageUrl", pageUrl);
            signMsgVal = AppendParam(signMsgVal, "bgUrl", bgUrl);
            signMsgVal = AppendParam(signMsgVal, "ext1", HttpUtility.UrlEncode(ext1, Encoding.GetEncoding("gb2312")).Trim());
            signMsgVal = AppendParam(signMsgVal, "ext2", HttpUtility.UrlEncode(ext2, Encoding.GetEncoding("gb2312")).Trim());
            signMsgVal = AppendParam(signMsgVal, "key", key);
            string signMsg = TextEncrypt.EncryptPassword(signMsgVal).ToUpper();
            #endregion

            RenderAlertInfo(false, "页面正跳转到支付平台，请稍候。。。", 2);

            #region 整理参数

            string getData = "";
            getData = AppendAllParam(getData, "merchantAcctId", merchantAcctId);
            getData = AppendAllParam(getData, "orderId", orderId);
            getData = AppendAllParam(getData, "orderAmount", orderAmount);
            getData = AppendAllParam(getData, "payType", payType);
            getData = AppendAllParam(getData, "pageUrl", HttpUtility.UrlEncode(pageUrl, Encoding.GetEncoding("gb2312")).Trim());
            getData = AppendAllParam(getData, "bgUrl", HttpUtility.UrlEncode(bgUrl, Encoding.GetEncoding("gb2312")).Trim());
            getData = AppendAllParam(getData, "ext1", HttpUtility.UrlEncode(ext1, Encoding.GetEncoding("gb2312")).Trim());
            getData = AppendAllParam(getData, "ext2", HttpUtility.UrlEncode(ext2, Encoding.GetEncoding("gb2312")).Trim());
            getData = AppendAllParam(getData, "signMsg", signMsg);

            string posturl = this.Page.Form.Action + "?" + getData;

            #endregion

            Response.Redirect(posturl);
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

        /// <summary>
        /// 将所有参数组成字符串返回
        /// </summary>
        /// <param name="returnStr"></param>
        /// <param name="paramId"></param>
        /// <param name="paramValue"></param>
        /// <returns></returns>
        private String AppendAllParam(String returnStr, String paramId, String paramValue)
        {
            if (returnStr != "")
            {
                returnStr += "&" + paramId + "=" + paramValue;
            }
            else
            {
                returnStr = paramId + "=" + paramValue;
            }

            return returnStr;
        }
    }
}
