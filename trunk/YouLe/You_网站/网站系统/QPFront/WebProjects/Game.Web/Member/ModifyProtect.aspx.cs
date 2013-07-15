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
    public partial class ModifyProtect : UCPageBase
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

        private AccountsFacade accountsFacade = new AccountsFacade( );

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                Message umsg = accountsFacade.GetUserSecurityByUserID( Fetch.GetUserCookie( ).UserID );
                if ( umsg.Success )
                {
                    AccountsProtect protect = umsg.EntityList[0] as AccountsProtect;
                    lblQuestion1.Text = protect.Question1;
                    lblQuestion2.Text = protect.Question2;
                    lblQuestion3.Text = protect.Question3;

                    this.form1.Visible = true;
                    this.form2.Visible = false;
                    this.divRight.Visible = false;
                }
                else
                {
                    this.form1.Visible = false;
                    this.form2.Visible = false;
                    this.divRight.Visible = true;
                    this.divRight.InnerHtml = "<div class=\"Uerror\">您还没有申请密码保护功能，请先<a href='/Member/ApplyProtect.aspx'>申请密保</a></div>";
                }
            }

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header ) this.FindControl( "sHeader" );
            sHeader.title = "会员中心";
        }

        protected void btnConfirm_Click( object sender, EventArgs e )
        {
            AccountsProtect protect = new AccountsProtect( );
            protect.Response1 = CtrlHelper.GetText(txtResponse1);
            protect.Response2 = CtrlHelper.GetText(txtResponse2);
            protect.Response3 = CtrlHelper.GetText(txtResponse3);

            protect.UserID = Fetch.GetUserCookie( ).UserID;

            Message umsg = accountsFacade.ConfirmUserSecurity( protect );
            if ( umsg.Success )
            {
                this.form1.Visible = false;
                this.form2.Visible = true;

                BindProtectQuestion( );
            }
            else
            {
                Show( umsg.Content );
            }
        }

        private void BindProtectQuestion( )
        {
            ddlQuestion1.DataSource = Fetch.ProtectionQuestiongs;
            ddlQuestion1.DataBind( );

            ddlQuestion2.DataSource = Fetch.ProtectionQuestiongs;
            ddlQuestion2.DataBind( );

            ddlQuestion3.DataSource = Fetch.ProtectionQuestiongs;
            ddlQuestion3.DataBind( );

            ddlQuestion1.Items.Insert( 0, new ListItem( "请选择密保问题", "0" ) );
            ddlQuestion2.Items.Insert( 0, new ListItem( "请选择密保问题", "0" ) );
            ddlQuestion3.Items.Insert( 0, new ListItem( "请选择密保问题", "0" ) );
        }

        protected void btnUpdate_Click( object sender, EventArgs e )
        {
            AccountsProtect protect = new AccountsProtect( );
            protect.UserID = Fetch.GetUserCookie( ).UserID;
            protect.SafeEmail = TextFilter.FilterScript( txtSafeEmail.Text.Trim( ) );
            protect.ModifyIP = GameRequest.GetUserIP( );

            protect.Question1 = ddlQuestion1.SelectedValue;
            protect.Question2 = ddlQuestion2.SelectedValue;
            protect.Question3 = ddlQuestion3.SelectedValue;
            protect.Response1 = TextFilter.FilterScript( txtMResponse1.Text.Trim( ) );
            protect.Response2 = TextFilter.FilterScript( txtMResponse2.Text.Trim( ) );
            protect.Response3 = TextFilter.FilterScript( txtMResponse3.Text.Trim( ) );

            Message umsg = accountsFacade.ModifyUserSecurity( protect );
            if ( umsg.Success )
            {
                this.form2.Visible = false;
                this.divRight.Visible = true;
                this.divRight.InnerHtml = "<div class=\"Uright\">您已经成功修改了密码保护！</div>";
            }
            else
            {
                Show( umsg.Content );
            }
        }
    }
}
