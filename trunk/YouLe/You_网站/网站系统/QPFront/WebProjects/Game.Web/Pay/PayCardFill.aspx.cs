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
    public partial class PayCardFill : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade();
        private TreasureFacade treasureFacade = new TreasureFacade();

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                this.fmStep1.Visible = true;
                this.fmStep2.Visible = false;

                if (Fetch.GetUserCookie() != null)
                {
                    this.txtAccounts.Text = Fetch.GetUserCookie().Accounts;
                    this.txtAccounts2.Text = Fetch.GetUserCookie().Accounts;

                    this.txtAccounts.Focus();
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
            AddMetaTitle("实卡充值 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 充值按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnPay_Click(object sender, EventArgs e)
        {
            string strAccounts = CtrlHelper.GetText(txtAccounts);
            string strReAccounts = CtrlHelper.GetText(txtAccounts2);
            string serialID = CtrlHelper.GetText(txtSerialID);
            string password = CtrlHelper.GetText(txtPassword);

            if (strAccounts == "")
            {
                RenderAlertInfo(true, "抱歉，请输入游戏账号。", 2);
                return;
            }
            if (strReAccounts != strAccounts)
            {
                RenderAlertInfo(true, "抱歉，两次输入的帐号不一致。", 2);
                return;
            }
            if (serialID == "")
            {
                RenderAlertInfo(true, "抱歉，请输入充值卡号。", 2);
                return;
            }
            if (password == "")
            {
                RenderAlertInfo(true, "抱歉，请输入卡号密码。", 2);
                return;
            }

            //充值信息
            ShareDetialInfo detailInfo = new ShareDetialInfo();
            detailInfo.SerialID = CtrlHelper.GetText(txtSerialID);
            if (userTicket == null)
            {
                detailInfo.OperUserID = 0;
            }
            else
            {
                detailInfo.OperUserID = userTicket.UserID;
            }
            detailInfo.Accounts = strAccounts;
            detailInfo.ShareID = 1;             //实卡充值服务标识
            detailInfo.IPAddress = Utility.UserIP;

            #region 充值

            Message umsg = treasureFacade.FilledLivcard(detailInfo, TextEncrypt.EncryptPassword(txtPassword.Text.Trim()));
            if (umsg.Success)
            {
                RenderAlertInfo(false, "实卡充值成功。", 2);
            }
            else
            {
                RenderAlertInfo(true, umsg.Content, 2);
            }

            #endregion           
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

    }
}
