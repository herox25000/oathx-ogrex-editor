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
    public partial class MIndex : UCPageBase
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
                    this.lblGender.Text = ui.Gender == 0 ? "女" : "男";
                    lblMember.Text = ui.MemberOrder == 0 ? "普通会员" : ui.MemberOrder == 1 ? "蓝钻会员" : ui.MemberOrder == 2 ? "黄钻会员" : ui.MemberOrder == 3 ? "白钻会员" : "红钻会员";
                    lblNickName.Text = ui.NickName;
                    lblAccounts.Text = ui.Accounts;
                    lblExperience.Text = ui.Experience.ToString();
                    lblUnderWrite.Text = ui.UnderWrite;
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }
    }
}
