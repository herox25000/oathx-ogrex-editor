using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Entity.Accounts;
using Game.Entity.Record;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;


namespace Game.Web.Member
{
    public partial class ConvertMedalRecord : UCPageBase
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
        private RecordFacade recordFacade = new RecordFacade( );
        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-01" );
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                DataBindInsure( );
            }

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "会员中心";
        }

        /// 绑定数据
        private void DataBindInsure( )
        {
            StringBuilder sWhere = new StringBuilder( );
            sWhere.AppendFormat( " WHERE UserID = {0}" , Fetch.GetUserCookie( ).UserID );

            sWhere.AppendFormat( " AND CollectDate >= '{0}' AND CollectDate <= '{1}'" , this.txtStartDate.Text.Trim( ) + " 00:00:00" , this.txtEndDate.Text.Trim( ) + " 23:59:59" );

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = recordFacade.GetMedalConvertRecord( sWhere.ToString( ) , sPageIndex , sPageSize );
            anpPage.RecordCount = pagerSet.RecordCount;

            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptRecord.DataSource = pagerSet.PageSet;
                rptRecord.DataBind( );

                this.rptRecord.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptRecord.Visible = false;
                this.trNoData.Visible = true;
            }
        }

        //页选择
        protected void anpPage_PageChanging( object src , Wuqi.Webdiyer.PageChangingEventArgs e )
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            DataBindInsure( );
        }

        // 查询按钮的事件
        protected void btnSelect_Click( object sender , EventArgs e )
        {
            anpPage.CurrentPageIndex = 1;
            DataBindInsure( );
        }
    }
}
