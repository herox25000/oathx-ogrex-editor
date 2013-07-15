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
using Game.Entity.Enum;
using Game.Entity.Treasure;

namespace Game.Web.Module.FilledManager
{
    public partial class GlobalLivcardList : AdminPage
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
        protected void btnQuery_Click( object sender, EventArgs e )
        {
           /* string startDate = CtrlHelper.GetText( txtStartDate );
            string endDate = CtrlHelper.GetText( txtEndDate );
            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND BuildDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );*/

            BindData( );
        }



        //销售商查询
        protected void btnQueryOrder_Click( object sender, EventArgs e )
        {
            /* string queryContent = CtrlHelper.GetText(txtSearch);
             if (queryContent == "")
             {
                 ShowError("查询条件不能为空");
                 return;
             }
             StringBuilder condition = new StringBuilder(" WHERE 1=1 ");
             condition.AppendFormat( " AND (OrderID='{0}' OR DealID='{0}')", queryContent );

             ViewState["SearchItems"] = condition.ToString();
             OnLineOrderDataBind();*/
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click( object sender , EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string sqlQuery = "Delete " + GlobalLivcard.Tablename + " WHERE CardTypeID in (" + Checkbox_Value + ")";
            int resutl=aideTreasureFacade.ExecuteSql( sqlQuery );
            if ( resutl > 0 )
            {
                ShowInfo( "删除成功" );
            }
            else
            {
                ShowInfo( "删除失败" );
            }
           
            BindData( );
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGlobalLivcardList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
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
                    condition.Append( " WHERE 1=1 " );
                    
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
                    ViewState["Orderby"] = "ORDER BY CardTypeID ASC";
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
