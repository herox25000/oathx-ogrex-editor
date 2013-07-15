using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Web.UI;
using Game.Kernel;
using Game.Utils;
using Game.Facade;

namespace Game.Web.Module.AccountManager
{
    public partial class RecordInsureList : AdminPage
    {
        #region Fields
        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-银行记录";
            }
        }
        #endregion

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
            {
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-" ) + "01";
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            RecordInsureDataBind( );
        }

        //列表绑定
        protected void rptInsure_ItemDataBound( object sender, RepeaterItemEventArgs e )
        {
            if ( e.Item.ItemType == ListItemType.Item || e.Item.ItemType == ListItemType.AlternatingItem )
            {
                byte tradeType = ( byte ) DataBinder.Eval( e.Item.DataItem, "TradeType" );
                string userID = DataBinder.Eval( e.Item.DataItem , "SourceUserID" ).ToString();
                switch ( tradeType )
                {
                    case 1:
                        ( ( Label )e.Item.FindControl( "lblTradeType" ) ).Text = "存款";
                        break;
                    case 2:
                        ( ( Label )e.Item.FindControl( "lblTradeType" ) ).Text = "取款";
                        break;
                    case 3:
                        if ( userID == IntParam.ToString( ) )
                        {
                            ( ( Label )e.Item.FindControl( "lblTradeType" ) ).Text = "转出";
                        }
                        else
                        {
                            ( ( Label )e.Item.FindControl( "lblTradeType" ) ).Text = "转入";
                        }
                        break;
                    default:
                        break;
                }
            }
        }
       
        protected void btnQuery_Click( object sender, EventArgs e )
        {
            string startDate = CtrlHelper.GetText( txtStartDate );
            string endDate = CtrlHelper.GetText( txtEndDate );
            int tradeType = Convert.ToInt32( ddlTradeType.SelectedValue.Trim( ) );

            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }

            switch ( tradeType )
            {
                case 1:
                    condition.AppendFormat( " AND TradeType=1 AND  SourceUserID= " + IntParam );
                    break;
                case 2:
                    condition.AppendFormat( " AND TradeType=2 AND  SourceUserID= " + IntParam );
                    break;
                case 3:
                    condition.AppendFormat( " AND TradeType=3 AND TargetUserID=" + IntParam );
                    break;
                case 4:
                    condition.AppendFormat( " AND TradeType=3 AND SourceUserID=" + IntParam );
                    break;
                default:
                    condition.AppendFormat( " AND (SourceUserID= " + IntParam + " OR TargetUserID =" + IntParam + ")" );
                    break;
            }
           
            ViewState["SearchItems"] = condition.ToString( );
            RecordInsureDataBind( );
        }

        //今天
        protected void btnQueryTD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetTodayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetTodayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            StringBuilder condition = new StringBuilder( " WHERE SourceUserID= " + IntParam + " OR TargetUserID ="+IntParam );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
            RecordInsureDataBind( );
        }

        //昨天
        protected void btnQueryYD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetYesterdayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetYesterdayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            StringBuilder condition = new StringBuilder( " WHERE SourceUserID= " + IntParam + " OR TargetUserID =" + IntParam );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
            RecordInsureDataBind( );
        }

        //本周
        protected void btnQueryTW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            StringBuilder condition = new StringBuilder( " WHERE SourceUserID= " + IntParam + " OR TargetUserID =" + IntParam );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
            RecordInsureDataBind( );
        }

        //上周
        protected void btnQueryYW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetLastWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetLastWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            StringBuilder condition = new StringBuilder( " WHERE SourceUserID= " + IntParam + " OR TargetUserID =" + IntParam );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CollectDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
            RecordInsureDataBind( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void RecordInsureDataBind( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetRecordInsureList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptInsure.DataSource = pagerSet.PageSet;
            rptInsure.DataBind( );
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
                    condition.AppendFormat( " WHERE SourceUserID={0} OR TargetUserID={0}" , IntParam );

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
                    ViewState["Orderby"] = "ORDER BY CollectDate DESC";
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
