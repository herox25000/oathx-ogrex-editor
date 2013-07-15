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

namespace Game.Web.Member
{
    public partial class ReLogonPass : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                this.form1.Visible = true;
                this.form2.Visible = false;

                this.divRight.Visible = false;
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        protected void btnConfirm_Click(object sender, EventArgs e)
        {
            if (this.radType2.Checked)
            {
                Message umsg = accountsFacade.GetUserGlobalInfo(0, Utility.StrToInt(txtContect.Text.Trim(), 0), "");
                if (!umsg.Success)
                {
                    Show("您输入的游戏ID号码错误，请重新输入！");
                    this.txtContect.Text = "";
                    this.txtContect.Focus();
                }
                else
                {
                    UserInfo user = umsg.EntityList[0] as UserInfo;
                    ViewState["UserID"] = user.UserID;

                    GetUserSecurityInfo(user.UserID);
                }
            }
            else
            {
                Message umsg = accountsFacade.GetUserGlobalInfo(0, 0, CtrlHelper.GetText(txtContect));
                if (umsg.Success)
                {
                    UserInfo user = umsg.EntityList[0] as UserInfo;
                    ViewState["UserID"] = user.UserID;
                    GetUserSecurityInfo(user.UserID);
                }
                else
                {
                    Show("您输入的用户名错误，请重新输入！");
                    this.txtContect.Text = "";
                    this.txtContect.Focus();
                }
            }
        }

        private void GetUserSecurityInfo(int userId)
        {
            Message umsg = accountsFacade.GetUserSecurityByUserID(userId);
            if (umsg.Success)
            {
                AccountsProtect protect = umsg.EntityList[0] as AccountsProtect;

                this.lblQuestion1.Text = protect.Question1;
                this.lblQuestion2.Text = protect.Question2;
                this.lblQuestion3.Text = protect.Question3;
            }
            else
            {
                this.form1.Visible = false;

                this.divRight.Visible = true;
                this.divRight.InnerHtml = "<div class=\"Uerror\" style=\"width:450px;\">抱歉，此账号还没有申请密码保护功能，不能重置登录密码！</div>";
                return;
            }

            this.form1.Visible = false;
            this.form2.Visible = true;
        }

        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            AccountsProtect protect = new AccountsProtect();
            protect.UserID = Utility.StrToInt(ViewState["UserID"], 0);
            protect.LogonPass = TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtNewPass));
            protect.Response1 = CtrlHelper.GetText(txtResponse1);
            protect.Response2 = CtrlHelper.GetText(txtResponse2);
            protect.Response3 = CtrlHelper.GetText(txtResponse3);
            protect.LastLogonIP = GameRequest.GetUserIP();

            Message umsg = accountsFacade.ResetLogonPasswd(protect);
            if (umsg.Success)
            {
                int userid = Utility.StrToInt(ViewState["UserID"], 0);
                if (Fetch.GetUserCookie() != null)
                {
                    if (userid == Fetch.GetUserCookie().UserID)
                    {
                        Fetch.DeleteUserCookie();
                        ShowAndRedirect("重置登录密码成功，请您重新登录！", "/Login.aspx");
                    }
                    else
                    {
                        this.form2.Visible = false;

                        this.divRight.Visible = true;
                        this.divRight.InnerHtml = "<div class=\"Uright\">重置登录密码成功，可用这个账号重新登录！</div>";
                    }   
                }
                ShowAndRedirect("重置登录密码成功，请登录！", "/Login.aspx");
            }
            else
            {
                Show(umsg.Content);
                txtResponse1.Text = "";
                txtResponse2.Text = "";
                txtResponse3.Text = "";
            }
        }
    }
};
