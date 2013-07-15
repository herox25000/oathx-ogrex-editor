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
    public partial class PayVB : UCPageBase
    {
        private TreasureFacade treasureFacade = new TreasureFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                this.fmStep1.Visible = true;
                this.pnlStep2.Visible = false;

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
            AddMetaTitle("电话充值 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        protected void btnPay_Click(object sender, EventArgs e)
        {
            string strAccounts = CtrlHelper.GetText(txtPayAccounts);
            string strReAccounts = CtrlHelper.GetText(txtPayReAccounts);
            int salePrice = GameRequest.GetFormInt("rbSaleType", 0);

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
            if (salePrice < 10)
            {
                RenderAlertInfo(true, "抱歉，充值金额必须大于10元", 2);
                return;
            }

            OnLineOrder onlineOrder = new OnLineOrder();
            onlineOrder.ShareID = 12;
            onlineOrder.OrderID = PayHelper.GetOrderIDByPrefix("SX");

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

            #region 提交给V币网关

            string spid = ApplicationSettings.Get("spId");//换成商户sp号码 长度5位
            string sppwd = ApplicationSettings.Get("spKeyValue");//换成商户sp校验密钥  长度18位
            string spreq = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayVB.aspx";//换成商户请求地址
            string sprec = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayVBReceive.aspx";    //换成商户接收地址
            string spname = Server.UrlEncode(ApplicationSettings.Get("spName"));//需要 Server.UrlEncode编码
            string spcustom = onlineOrder.CardTotal.ToString("f0");//需要 Server.UrlEncode编码  '客户自定义 30字符内 只能是数字、字母或数字字母的组合。不能用汉字。
            string spversion = "vpay1001";//此接口的版本号码 此版本是"vpay1001"
            string money = onlineOrder.OrderAmount.ToString("f0");//接参数面值元    
            string userid = Server.UrlEncode(onlineOrder.Accounts);//接参数用户ID 需要 Server.UrlEncode编码
            string urlcode = "utf-8";//编码  gbk  gb2312   utf-8  unicode   big5(注意不能一个繁体和简体字交叉写)  你程序的编码
            string orderId = onlineOrder.OrderID;//客户订单 请妥善管理客户的订单  长度：30字符以内（只能是数字、字母或数字字母的组合。不能用汉字订单）
            string post_key = orderId + spreq + sprec + spid + sppwd + spversion + money;
            // '网站订单号码+ 请求地址+ 接收地址 + 5位spid+ 18位SP密码+支付的版本号+面值
            //'LCase函数是将字符转换为小写; Ucase函数是将字符转换为大写
            //'全国声讯支付联盟全国声讯电话支付接口对MD5值只认大写字符串，所以小写的MD5值得转换为大写
            string md5password = TextEncrypt.EncryptPassword(post_key).ToUpper();//  '先MD532 然后转大写
            md5password = md5( post_key , 32 ).ToUpper( );
            string IpAddress = (HttpContext.Current.Request.ServerVariables["HTTP_X_FORWARDED_FOR"] != null
              && HttpContext.Current.Request.ServerVariables["HTTP_X_FORWARDED_FOR"] != String.Empty)
              ? HttpContext.Current.Request.ServerVariables["HTTP_X_FORWARDED_FOR"]
              : HttpContext.Current.Request.ServerVariables["REMOTE_ADDR"];

            #endregion

            #region 整理参数

            RenderAlertInfo(false, "页面正跳转到支付平台，请稍候。。。", 2);

            HtmlGenericControl pnlSubmit = this.FindControl("pnlSubmit") as HtmlGenericControl;
            if (pnlSubmit != null)
            {
                pnlSubmit.Visible = true;
            }

            StringBuilder builder = new StringBuilder();
            builder.AppendLine(CreateInputHidden("spid", spid));
            builder.AppendLine(CreateInputHidden("spname", spname));
            builder.AppendLine(CreateInputHidden("spoid", orderId));
            builder.AppendLine(CreateInputHidden("spreq", spreq));
            builder.AppendLine(CreateInputHidden("sprec", sprec));
            builder.AppendLine(CreateInputHidden("userid", userid));
            builder.AppendLine(CreateInputHidden("userip", IpAddress));
            builder.AppendLine(CreateInputHidden("spmd5", md5password));
            builder.AppendLine(CreateInputHidden("spcustom", spcustom));
            builder.AppendLine(CreateInputHidden("spversion", spversion));
            builder.AppendLine(CreateInputHidden("money", money));
            builder.AppendLine(CreateInputHidden("urlcode", urlcode));

            litVB.Text = builder.ToString();

            #endregion

            //this.Page.ClientScript.RegisterStartupScript( this.GetType( ) , "message" , "window.onload = function() {  document.forms[1].submit(); }" , true );
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
                this.pnlStep2.Visible = true;
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

        //MD5加密
        private string md5( string str , int code )
        {
            if ( code == 16 ) //16位MD5加密（取32位加密的9~25字符） 
            {
                return System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile( str , "MD5" ).ToUpper( ).Substring( 8 , 16 );
            }
            else//32位加密 
            {
                return System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile( str , "MD5" ).ToUpper( );
            }
        } 
    }
}
