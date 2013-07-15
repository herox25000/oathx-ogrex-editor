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
    public partial class ModifyLogonPass : UCPageBase
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
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            Message umsg = accountsFacade.ModifyLogonPasswd(Fetch.GetUserCookie().UserID, TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtOldPass)), TextEncrypt.EncryptPassword(txtNewPass.Text.Trim()), GameRequest.GetUserIP());

            if (umsg.Success)
            {
                Fetch.DeleteUserCookie();
                ShowAndRedirect("登录密码修改成功，请重新登录", "/Login.aspx");
            }
            else
            {
                Show(umsg.Content);
            }
        }
    }
}
