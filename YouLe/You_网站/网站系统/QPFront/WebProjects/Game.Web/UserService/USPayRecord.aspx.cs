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
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.UserService
{
    public partial class USPayRecord : System.Web.UI.Page
    {
        #region 窗口事件

        private AccountsFacade accountsFacade = new AccountsFacade( );
        private TreasureFacade treasureFacade = new TreasureFacade( );

        protected void Page_Load( object sender , EventArgs e )
        {
            //判断是否登录
            if ( !Fetch.IsUserOnline( ) )
            {
                return;
            }

            if ( !IsPostBack )
            {
                this.txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-01" );
                this.txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );

                BindPayData( );
            }
        }

        #endregion

        #region 绑定数据

        private void BindPayData( )
        {
            //判断是否登录
            if ( !Fetch.IsUserOnline( ) )
            {
                return;
            }

            StringBuilder sWhere = new StringBuilder( );
            sWhere.AppendFormat( " WHERE UserID = {0} " , Fetch.GetUserCookie( ).UserID );

            if ( Convert.ToInt32( ddlShareType.SelectedValue ) != 0 )
            {
                sWhere.AppendFormat( " AND CardTypeID = {0}" , Convert.ToInt32( ddlShareType.SelectedValue ) );
            }

            sWhere.AppendFormat(" AND ApplyDate >= '{0}' AND ApplyDate <= '{1}'", CtrlHelper.GetText(txtStartDate) + " 00:00:00", CtrlHelper.GetText(txtEndDate) + " 23:59:59");

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = treasureFacade.GetPayRecord( sWhere.ToString( ) , sPageIndex , sPageSize );
            anpPage.RecordCount = pagerSet.RecordCount;

            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptPayList.DataSource = pagerSet.PageSet;
                rptPayList.DataBind( );

                this.rptPayList.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptPayList.Visible = false;
                this.trNoData.Visible = true;
            }
        }

        /// <summary>
        /// 分页事件
        /// </summary>
        /// <param name="src"></param>
        /// <param name="e"></param>
        protected void anpPage_PageChanging( object src , Wuqi.Webdiyer.PageChangingEventArgs e )
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            BindPayData( );
        }

        /// <summary>
        /// 查询按钮的事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnSelect_Click( object sender , EventArgs e )
        {
            anpPage.CurrentPageIndex = 1;
            BindPayData( );
        }

        #endregion
    }
}
