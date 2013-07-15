using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Facade;
using Game.Entity;
using Game.Utils;
using Game.Entity.PlatformManager;

namespace Game.Web
{
    public partial class Index : Page
    {
        #region Fields

        protected Base_Users userExt = new Base_Users( );

        private PlatformManagerFacade aidePlatformManagerFacade = new PlatformManagerFacade( );

        protected string roleName;

        //标题
        protected string SiteName
        {
            get
            {
                QPAdminSiteInfo siteInfo = aidePlatformManagerFacade.GetQPAdminSiteInfo( 1 );
                if ( siteInfo == null )
                    return "网站管理后台";
                else
                    return siteInfo.SiteName;
            }
        }
        #endregion

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            //登录判断
            userExt = AdminCookie.GetUserFromCookie( );
            if ( userExt == null || userExt.UserID <= 0 ||
                ( userExt.UserID != ApplicationConfig.SUPER_ADMINISTRATOR_ID && userExt.RoleID <= 0 ) )
            {
                Response.Redirect( "Login.aspx" );
            }
            if ( userExt.UserID == ApplicationConfig.SUPER_ADMINISTRATOR_ID || userExt.RoleID == 1 )
            {
                roleName = "超级管理员";
            }
            else
            {
                roleName = aidePlatformManagerFacade.GetRolenameByRoleID( userExt.RoleID );
            }

            Utility.ClearPageClientCache( );
        }
        #endregion  
    }
}
