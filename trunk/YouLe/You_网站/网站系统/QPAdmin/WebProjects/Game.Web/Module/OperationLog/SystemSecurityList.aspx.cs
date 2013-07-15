using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using System.Collections;


namespace Game.Web.Module.OperationLog
{
    public partial class SystemSecurityList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindData( );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        //查询
        protected void btnSearch_OnClick( object sender, EventArgs e )
        {
            StringBuilder condition = new StringBuilder( );
            string keyword = CtrlHelper.GetText( txtKeyword );
            if ( string.IsNullOrEmpty( keyword ) )
                condition.Append( "WHERE 1=1 " );
            else
                condition.AppendFormat( " WHERE OperatingAccounts='{0}'", keyword );

            ViewState["SearchItems"] = condition.ToString( );
            BindData( );
        }
        /// <summary>
        /// 刷新
        /// </summary>
        protected void btnRefresh_Click( object sender, EventArgs e )
        {
            ViewState["SearchItems"] = null;
            txtKeyword.Text = "";
            BindData( );
        }      
        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aidePlatformManagerFacade.GetSystemSecurityList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptDataList.DataSource = pagerSet.PageSet;
            rptDataList.DataBind( );
            anpNews.RecordCount = pagerSet.RecordCount;
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if ( ViewState["SearchItems"] == null )
                {
                    StringBuilder condition = new StringBuilder( );
                    condition.AppendFormat( " WHERE 1=1 " );
                    ViewState["SearchItems"] = condition.ToString( );
                }

                return ( string ) ViewState["SearchItems"];
            }

            set
            {
                ViewState["SearchItems"] = value;
            }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if ( ViewState["Orderby"] == null )
                {
                    ViewState["Orderby"] = "ORDER BY OperatingTime DESC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        #endregion
    }
}
