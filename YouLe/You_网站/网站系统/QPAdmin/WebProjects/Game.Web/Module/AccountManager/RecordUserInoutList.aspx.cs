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
    public partial class RecordUserInoutList : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-进出记录";
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
            UserInoutDataBind( );
        }

        //列表绑定
        protected void rptUserInout_ItemDataBound( object sender, RepeaterItemEventArgs e )
        {
            if ( e.Item.ItemType == ListItemType.Item || e.Item.ItemType == ListItemType.AlternatingItem )
            {
                if ( DataBinder.Eval( e.Item.DataItem, "LeaveTime" ) != DBNull.Value )
                {
                    int reason = ( int ) DataBinder.Eval( e.Item.DataItem, "LeaveReason" );
                    switch ( reason )
                    {
                        case 0:
                            ( ( Label ) e.Item.FindControl( "lblLeaveReason" ) ).Text = "常规离开";
                            break;
                        case 1:
                            ( ( Label ) e.Item.FindControl( "lblLeaveReason" ) ).Text = "系统原因";
                            break;
                        case 2:
                            ( ( Label ) e.Item.FindControl( "lblLeaveReason" ) ).Text = "用户冲突";
                            break;
                        case 3:
                            ( ( Label ) e.Item.FindControl( "lblLeaveReason" ) ).Text = "网络原因";
                            break;
                        default:
                            ( ( Label ) e.Item.FindControl( "lblLeaveReason" ) ).Text = "人满为患";
                            break;

                    }

                }
            }
        }
        /// <summary>
        /// 设置查询条件
        /// </summary>
        /// <param name="startDate"></param>
        /// <param name="endDate"></param>
        private void SetCondition( string startDate, string endDate )
        {
            int type = int.Parse( ddlTimeType.SelectedValue );
            StringBuilder condition = new StringBuilder( " WHERE UserID= " + IntParam );
            if ( startDate != "" && endDate != "" )
            {
                switch ( type )
                {
                    case 1:
                        condition.AppendFormat( " AND EnterTime BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                        break;
                    case 2:
                        condition.AppendFormat( " AND LeaveTime BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                        break;
                    case 3:
                        condition.AppendFormat( " AND EnterTime <= '{0}' AND LeaveTime<='{1}'", startDate, endDate );
                        break;
                    default:
                        condition.AppendFormat( " AND EnterTime BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                        break;
                }

            }
            ViewState["SearchItems"] = condition.ToString( );
        }
        protected void btnQuery_Click( object sender, EventArgs e )
        {
            string startDate = CtrlHelper.GetText( txtStartDate );
            string endDate = CtrlHelper.GetText( txtEndDate );
            SetCondition( startDate, endDate );
            UserInoutDataBind( );
        }

        //今天
        protected void btnQueryTD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetTodayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetTodayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            UserInoutDataBind( );
        }

        //昨天
        protected void btnQueryYD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetYesterdayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetYesterdayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            UserInoutDataBind( );
        }

        //本周
        protected void btnQueryTW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            UserInoutDataBind( );
        }

        //上周
        protected void btnQueryYW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetLastWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetLastWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            UserInoutDataBind( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void UserInoutDataBind( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetRecordUserInoutList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptUserInout.DataSource = pagerSet.PageSet;
            rptUserInout.DataBind( );
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
                    condition.AppendFormat( " WHERE UserID={0} ", IntParam );

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
                    ViewState["Orderby"] = "ORDER BY EnterTime DESC";
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
