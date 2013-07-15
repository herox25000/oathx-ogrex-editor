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
using Game.Facade;
using Game.Utils;
using Game.Kernel;

namespace Game.Web
{
    public partial class Login : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("用户登录 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 登录按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnLogon_Click(object sender, ImageClickEventArgs e)
        {
            if (TextUtility.EmptyTrimOrNull(CtrlHelper.GetText(txtAccounts)) || TextUtility.EmptyTrimOrNull(CtrlHelper.GetText(txtLogonPass)))
            {
                Show("抱歉！您输入的用户名或密码错误了。");
                this.txtLogonPass.Text = "";
                this.txtCode.Text = "";
                return;
            }

            //验证码错误
            if (!txtCode.Text.Trim().Equals(Fetch.GetVerifyCode(), StringComparison.InvariantCultureIgnoreCase))
            {
                Show("抱歉！您输入的验证码错误了。");
                this.txtLogonPass.Text = "";
                this.txtCode.Text = "";
                this.txtLogonPass.Focus();
                return;
            }

            Message umsg = accountsFacade.Logon(CtrlHelper.GetText(txtAccounts), CtrlHelper.GetText(txtLogonPass));
            if (umsg.Success)
            {
                UserInfo ui = umsg.EntityList[0] as UserInfo;
                ui.LogonPass = TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtLogonPass));

                Fetch.SetUserCookie(ui.ToUserTicketInfo());
                if (GameRequest.GetQueryString("url") != "")
                    Response.Redirect(GameRequest.GetQueryString("url"));
                else
                    Response.Redirect("/Member/MIndex.aspx");
            }
            else
            {
                Show(umsg.Content);
            }
        }
    }
}
