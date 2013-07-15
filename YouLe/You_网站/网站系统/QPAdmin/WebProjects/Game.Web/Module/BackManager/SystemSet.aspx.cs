using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using Game.Entity.PlatformManager;
using Game.Entity.Enum;

namespace Game.Web.Module.BackManager
{
    public partial class SystemSet : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindData( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            ProcessData( );
        }
        #endregion

        #region 数据加载

        private void BindData( )
        {
            QPAdminSiteInfo siteInfo = aidePlatformManagerFacade.GetQPAdminSiteInfo( 1 );
            if ( siteInfo == null )
                return;
            CtrlHelper.SetText( txtSiteName, siteInfo.SiteName );
            CtrlHelper.SetText( txtCopyRight, siteInfo.CopyRight );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            QPAdminSiteInfo siteInfo = aidePlatformManagerFacade.GetQPAdminSiteInfo( 1 );
            siteInfo.CopyRight = CtrlHelper.GetText( txtCopyRight );
            siteInfo.SiteName = CtrlHelper.GetText( txtSiteName );

            try
            {
                aidePlatformManagerFacade.UpdateQPAdminSiteInfo( siteInfo );
                ShowInfo( "操作成功" );
            }
            catch 
            {
                ShowError( "操作失败" );
            }
        }
        #endregion
    }
}
