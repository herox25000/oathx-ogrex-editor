using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Facade;
using Game.Kernel;
using Game.Entity;
using Game.Entity.PlatformManager;

namespace Game.Web
{
    public partial class Login : System.Web.UI.Page
    {
        #region Fields

        private PlatformManagerFacade aidePlatformManagerFacade = new PlatformManagerFacade( );
        //标题
        protected string SiteName
        {
            get
            {
                QPAdminSiteInfo siteInfo = aidePlatformManagerFacade.GetQPAdminSiteInfo( 1 );
                if ( siteInfo == null )
                    return "网站管理后台 - 管理员登录";
                else
                    return siteInfo.SiteName + " - 管理员登录";
            }
        }
        #endregion

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                switch ( GameRequest.GetQueryString( "errtype" ) )
                {
                    case "errorLogonTimeout":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorLogonTimeout\");", true );
                        return;

                    case "verifycode":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorVerifyCode\");", true );
                        return;

                    case "accounts":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorUserName\");", true );
                        return;

                    case "errorNamePassowrd":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorNamePassowrd\");", true );
                        return;

                    case "errorUserRole":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorUserRole\");", true );
                        return;

                    case "relogon":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"emptyUserName\");", true );
                        return;

                    case "errorBindIP":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorBindIP\");", true );
                        return;

                    case "errorNullity":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorNullity\");", true );
                        return;

                    case "errorUnknown":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "showMsg(\"errorUnknown\");", true );
                        return;

                    case "overtime":
                        Page.ClientScript.RegisterStartupScript( typeof( Page ), "", "redirect();", true );
                        return;

                }
            }
        }

        /// <summary>
        /// 登录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnLogin_Click( object sender, ImageClickEventArgs e )
        {
            string verifyCode = CtrlHelper.GetText( txtVerifyCode );
            string accounts = TextFilter.FilterScript( CtrlHelper.GetText( txtLoginName ) );
            string passwd = Utility.MD5( CtrlHelper.GetText( txtLoginPass ) );

            if ( !Fetch.ValidVerifyCodeVer2( verifyCode ) )
            {
                Fetch.Redirect( "Login.aspx?errtype=verifycode" );
            }

            Base_Users user = new Base_Users( );
            user.Username = accounts;
            user.Password = passwd;
            user.LastLoginIP = GameRequest.GetUserIP( );

            Message msg = aidePlatformManagerFacade.UserLogon( user );
            if ( !msg.Success )
            {
                string errtype = "errorUnknown";
                switch ( msg.MessageID )
                {
                    case 100:
                        errtype = "errorNamePassowrd";
                        break;
                    case 101:
                        errtype = "errorBindIP";
                        break;
                    case 102:
                        errtype = "errorNullity";
                        break;
                    default:
                        errtype = "errorUnknown";
                        break;
                }
                Fetch.Redirect( string.Format( "Login.aspx?errtype={0}", errtype ) );
            }
            user = msg.EntityList[0] as Base_Users;
            if ( user == null || ( user.UserID != ApplicationConfig.SUPER_ADMINISTRATOR_ID && user.RoleID < 0 ) )
            {
                Fetch.Redirect( "Login.aspx?errtype=errorUserRole" );
            }

            //转向
            Fetch.Redirect( "Index.aspx" );
        }
        #endregion
    }
}
