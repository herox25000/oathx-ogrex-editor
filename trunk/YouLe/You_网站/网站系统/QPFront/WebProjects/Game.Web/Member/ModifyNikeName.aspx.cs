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
    public partial class ModifyNikeName : UCPageBase
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
                Message umsg = accountsFacade.GetUserGlobalInfo(Fetch.GetUserCookie().UserID, 0, "");
                if (umsg.Success)
                {
                    UserInfo ui = umsg.EntityList[0] as UserInfo;
                    this.lblGameID.Text = ui.GameID.ToString();
                    this.lblNickname.Text = ui.NickName;
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }
       
        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            if (TextUtility.EmptyTrimOrNull(CtrlHelper.GetText(txtNickName)))
            {
                Show("抱歉！您输入的昵称错误了。");
                return;
            }

            Message umsg = accountsFacade.ModifyUserNickname( Fetch.GetUserCookie( ).UserID , TextFilter.FilterScript( txtNickName.Text.Trim( ) ) , GameRequest.GetUserIP( ) );
            if (umsg.Success)
            {
                ShowAndRedirect("昵称修改成功!", "/Member/ModifyNikeName.aspx");
            }
            else
            {
                Show(umsg.Content);
            }    
        }
    }
}
