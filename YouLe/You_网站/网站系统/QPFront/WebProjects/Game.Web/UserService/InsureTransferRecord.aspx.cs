using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Kernel;
using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using System.Text;

namespace Game.Web.UserService
{
    public partial class InsureTransferRecord : System.Web.UI.Page
    {
        private AccountsFacade accountsFacade = new AccountsFacade( );
        private TreasureFacade treasureFacade = new TreasureFacade( );

        protected void Page_Load ( object sender , EventArgs e )
        {
            //判断是否登录
            if( !Fetch.IsUserOnline( ) )
            {
                return;
            }

            if( !IsPostBack )
            {
                this.txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-01" );
                this.txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                DataBindInsure( );
            }
        }

        /// <summary>
        /// 绑定查询数据
        /// </summary>
        private void DataBindInsure ( )
        {
            StringBuilder sWhere = new StringBuilder( );
            sWhere.Append( " WHERE " );
            sWhere.AppendFormat( "( SourceUserID = {0} OR TargetUserID = {0} ) and (TradeType = 3 or TradeType = 4)" , Fetch.GetUserCookie( ).UserID );
            sWhere.AppendFormat(" AND CollectDate >= '{0}' AND CollectDate <= '{1}'", CtrlHelper.GetText(txtStartDate) + " 00:00:00", CtrlHelper.GetText(txtEndDate) + " 23:59:59");

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = treasureFacade.GetInsureTradeRecord( sWhere.ToString( ) , sPageIndex , sPageSize );
            anpPage.RecordCount = pagerSet.RecordCount;

            if( pagerSet.PageSet.Tables[ 0 ].Rows.Count > 0 )
            {
                rptInsureList.DataSource = pagerSet.PageSet;
                rptInsureList.DataBind( );

                this.rptInsureList.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptInsureList.Visible = false;
                this.trNoData.Visible = true;
            }
        }


        protected void anpPage_PageChanging ( object src , Wuqi.Webdiyer.PageChangingEventArgs e )
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            DataBindInsure( );
        }

        /// <summary>
        /// 查询按钮的事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnSelect_Click ( object sender , EventArgs e )
        {
            anpPage.CurrentPageIndex = 1;
            DataBindInsure( );
        }

        /// <summary>
        /// 根据用户ID获取用户名
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public string GetAccountsByUserID ( int userID )
        {
            UserInfo user = accountsFacade.GetUserBaseInfoByUserID( userID );
            if( user == null )
                return "";
            return user.Accounts;
        }

    }
}
