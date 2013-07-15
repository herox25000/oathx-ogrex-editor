using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

using Game.Facade;
using Game.Entity.PlatformManager;


namespace Game.Web
{
    public partial class Left : System.Web.UI.Page
    {
        private PlatformManagerFacade aidePlatformManagerFacade = new PlatformManagerFacade( );
        DataSet ds = null;

        protected override void OnInit( EventArgs e )
        {
            LoadNavmenu( );
        }

        //加载菜单
        private void LoadNavmenu( )
        {
            Base_Users userExt = aidePlatformManagerFacade.GetUserInfoFromCookie( );
            if ( userExt == null || userExt.UserID < 0 )
            {
                Fetch.Redirect( "Login.aspx" );
                return;
            }

            ds = aidePlatformManagerFacade.GetMenuByUserID( userExt.UserID );
            BindMenu( );
        }

        #region 绑定主菜单
        /// <summary>
        /// 绑定主菜单
        /// </summary>
        private void BindMenu( )
        {
            LeftMenu.DataSource = ds.Tables[0];
            LeftMenu.DataBind( );
        }
        #endregion

        #region 绑定子菜单
        /// <summary>
        /// 绑定子菜单事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void LeftMenu_ItemDataBound( object sender, RepeaterItemEventArgs e )
        {
            DataTable dt = ds.Tables[1];
            DataTable dtNew = dt.Clone( );
            int moduleID = Convert.ToInt32( DataBinder.Eval( e.Item.DataItem, "ModuleID" ) );
            DataRow[ ] drArray = dt.Select( "ParentID=" + moduleID );

            //复制
            foreach ( DataRow dr in drArray )
            {
                DataRow drNew = dtNew.NewRow( );
                drNew.ItemArray = dr.ItemArray;
                dtNew.Rows.Add( drNew );
            }

            Repeater leftSubID = ( Repeater ) e.Item.FindControl( "LeftMenu_Sub" );
            leftSubID.DataSource = dtNew;
            leftSubID.DataBind( );
        }

        #endregion
    }
}
