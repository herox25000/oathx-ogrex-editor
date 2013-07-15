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
    public partial class ApplyProtect : UCPageBase
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
                    this.form1.Visible = false;
                    this.divRight.Visible = true;
                }
                else
                {
                    this.divRight.Visible = false;
                }

                BindProtectQuestion( );
            }

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header ) this.FindControl( "sHeader" );
            sHeader.title = "会员中心";
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
            protect.PassportID = TextFilter.FilterScript( txtPassportID.Text.Trim( ) );
            protect.PassportType = Convert.ToByte( ddlPassportType.SelectedValue );
            protect.CreateIP = GameRequest.GetUserIP( );

            protect.Question1 = ddlQuestion1.SelectedValue;
            protect.Question2 = ddlQuestion2.SelectedValue;
            protect.Question3 = ddlQuestion3.SelectedValue;
            protect.Response1 = TextFilter.FilterScript( txtResponse1.Text.Trim( ) );
            protect.Response2 = TextFilter.FilterScript( txtResponse2.Text.Trim( ) );
            protect.Response3 = TextFilter.FilterScript( txtResponse3.Text.Trim( ) );

            Message umsg = accountsFacade.ApplyUserSecurity( protect );
            if ( umsg.Success )
            {
                this.form1.Visible = false;
                this.divRight.Visible = true;
            }
            else
            {
                Show( umsg.Content );
            }
        }
    }
}
