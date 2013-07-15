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
    public partial class ReInsurePass : UCPageBase
    {
        #region 继承属性

        protected override bool IsAuthenticatedUser
        {
            get
            {
                return true;
            }
        }

        #endregion

        private AccountsFacade accountsFacade = new AccountsFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                Message umsg = accountsFacade.GetUserSecurityByUserID(Fetch.GetUserCookie().UserID);
                if (umsg.Success)
                {
                    AccountsProtect protect = umsg.EntityList[0] as AccountsProtect;

                    this.lblQuestion1.Text = protect.Question1;
                    this.lblQuestion2.Text = protect.Question2;
                    lblQuestion3.Text = protect.Question3;

                    this.form1.Visible = true;
                    this.divRight.Visible = false;
                }
                else
                {
                    this.form1.Visible = false;

                    this.divRight.Visible = true;
                    this.divRight.InnerHtml = "<div class=\"Uerror\">抱歉，您还没有申请密码保护功能，不能重置银行密码！</div>";
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            AccountsProtect protect = new AccountsProtect();
            protect.UserID = Fetch.GetUserCookie().UserID;
            protect.InsurePass = TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtNewPass));
            protect.Response1 = CtrlHelper.GetText(txtResponse1);
            protect.Response2 = CtrlHelper.GetText(txtResponse2);
            protect.Response3 = CtrlHelper.GetText(txtResponse3);
            protect.LastLogonIP = GameRequest.GetUserIP();

            Message umsg = accountsFacade.ResetInsurePasswd(protect);
            if (umsg.Success)
            {
                this.form1.Visible = false;

                this.divRight.Visible = true;
                this.divRight.InnerHtml = "<div class=\"Uright\">重置银行密码成功！</div>";
            }
            else
            {
                Show(umsg.Content);
                this.txtResponse1.Text = "";
                this.txtResponse2.Text = "";
                this.txtResponse3.Text = "";
            }
        }
    }
}
