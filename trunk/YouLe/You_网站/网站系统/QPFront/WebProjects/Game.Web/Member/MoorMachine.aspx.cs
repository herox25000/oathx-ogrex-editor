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
    public partial class MoorMachine : UCPageBase
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
                Message msg = accountsFacade.GetUserSecurityByUserID(Fetch.GetUserCookie().UserID);
                if (msg.Success)
                {
                    AccountsProtect protect = msg.EntityList[0] as AccountsProtect;
                    this.lblQuestion1.Text = protect.Question1;
                    this.lblQuestion2.Text = protect.Question2;
                    this.lblQuestion3.Text = protect.Question3;
                }
                else
                {                   
                    switch ( msg.MessageID )
                    {
                        case 4:
                            ShowAndRedirect( "您还没有申请“密码保护”功能，请先申请！", "/Member/ApplyProtect.aspx" );                            
                            break;
                        default:
                          Show( msg.Content );
                          break;
                    }
                    
                }

                Message umsg = accountsFacade.GetUserGlobalInfo(Fetch.GetUserCookie().UserID, 0, "");
                if (umsg.Success)
                {
                    UserInfo userInfo = umsg.EntityList[0] as UserInfo;
                    if (userInfo.MoorMachine == 0)
                    {
                        this.btnUpdate.Text = "申请绑定";
                    }
                    else
                    {
                        this.btnUpdate.Text = "取消绑定";
                    }
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            AccountsProtect protect = new AccountsProtect();
            protect.Response1 = CtrlHelper.GetText(txtResponse1);
            protect.Response2 = CtrlHelper.GetText(txtResponse2);
            protect.Response3 = CtrlHelper.GetText(txtResponse3);

            protect.UserID = Fetch.GetUserCookie().UserID;
            protect.LastLogonIP = GameRequest.GetUserIP();

            if (btnUpdate.Text == "申请绑定")
            {
                Message umsg = accountsFacade.ApplyUserMoorMachine(protect);
                if (umsg.Success)
                {
                    ShowAndRedirect(umsg.Content, "/Member/MoorMachine.aspx");
                }
                else
                {
                    Show(umsg.Content);
                }
            }
            else if (btnUpdate.Text == "取消绑定")
            {
                Message umsg = accountsFacade.RescindUserMoorMachine(protect);
                if (umsg.Success)
                {
                    ShowAndRedirect(umsg.Content, "/Member/MoorMachine.aspx");
                }
                else
                {
                    Show(umsg.Content);
                }
            }
        }
    }
}
