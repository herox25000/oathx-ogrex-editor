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

namespace Game.Web.Module.FilledManager
{
    public partial class OrderVBList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-" ) + "01";
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                OnLineOrderDataBind( );
            }
        }

        protected void anpNews_PageChanged( object sender , EventArgs e )
        {
            OnLineOrderDataBind( );
        }

        /// <summary>
        /// 设置查询条件
        /// </summary>
        /// <param name="startDate"></param>
        /// <param name="endDate"></param>
        private void SetCondition( string startDate , string endDate )
        {
            int status = int.Parse( ddlStatus.SelectedValue );
            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( status > 0 )
                condition.AppendFormat( " AND r1_Code={0} " , status );

            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'" , startDate , Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
        }

        //查询
        protected void btnQuery_Click( object sender , EventArgs e )
        {
            string startDate = CtrlHelper.GetText( txtStartDate );
            string endDate = CtrlHelper.GetText( txtEndDate );

            SetCondition( startDate , endDate );
            OnLineOrderDataBind( );
        }

        //今天
        protected void btnQueryTD_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetTodayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetTodayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            OnLineOrderDataBind( );
        }

        //昨天
        protected void btnQueryYD_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetYesterdayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetYesterdayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            OnLineOrderDataBind( );
        }

        //本周
        protected void btnQueryTW_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            OnLineOrderDataBind( );
        }

        //上周
        protected void btnQueryYW_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetLastWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetLastWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            OnLineOrderDataBind( );
        }

        //订单查询
        protected void btnQueryOrder_Click( object sender , EventArgs e )
        {
            int searchType = int.Parse( ddlSearchType.SelectedValue );
            string queryContent = CtrlHelper.GetText( txtSearch );
            if ( queryContent == "" )
            {
                ShowError( "查询条件不能为空" );
                return;
            }
            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( !string.IsNullOrEmpty( queryContent ) )
            {
                switch ( searchType )
                {
                    case 1:
                        condition.AppendFormat( " AND r6_Order='{0}' " , queryContent );
                        break;
                    case 2:
                        condition.AppendFormat( " AND r2_TrxId='{0}'" , queryContent );
                        break;
                }
            }

            ViewState["SearchItems"] = condition.ToString( );
            OnLineOrderDataBind( );
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click( object sender , EventArgs e )
        {
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE DetailID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.DeleteKQDetail( strQuery );
                ShowInfo( "删除成功" );
            }
            catch
            {
                ShowError( "删除失败" );
            }
            OnLineOrderDataBind( );
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void OnLineOrderDataBind( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetVBDetailList( anpNews.CurrentPageIndex , anpNews.PageSize , SearchItems , Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptYPDetail.DataSource = pagerSet.PageSet;
            rptYPDetail.DataBind( );
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

                    string startDate = CtrlHelper.GetText( txtStartDate );
                    string endDate = CtrlHelper.GetText( txtEndDate );
                    if ( startDate != "" && endDate != "" )
                    {
                        condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'" , startDate , Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                    }

                    ViewState["SearchItems"] = condition.ToString( );
                }
                return ( string )ViewState["SearchItems"];
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
                    ViewState["Orderby"] = "ORDER BY CollectDate DESC";
                }

                return ( string )ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }

        #endregion
    }
}
