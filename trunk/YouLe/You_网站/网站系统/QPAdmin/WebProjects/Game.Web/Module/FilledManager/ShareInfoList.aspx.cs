using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Web.UI;
using System.Text;

using Game.Kernel;
using Game.Utils;
using Game.Facade;
using System.Data;

namespace Game.Web.Module.FilledManager
{
    public partial class ShareInfoList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-" ) + "01";
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                BindGlobalShare( );
                BindCardType( );
                ShareInfoDataBind( );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            ShareInfoDataBind( );
        }
        /// <summary>
        /// 设置查询条件
        /// </summary>
        /// <param name="startDate"></param>
        /// <param name="endDate"></param>
        private void SetCondition( string startDate, string endDate )
        {
            int service = int.Parse( ddlGlobalShareInfo.SelectedValue );
            int type = int.Parse( ddlCardType.SelectedValue );
            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( service > 0 )
                condition.AppendFormat( " AND ShareID={0}", service );
            if ( type > 0 )
                condition.AppendFormat( " AND CardTypeID={0} ", type );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND ApplyDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
        }
        //查询
        protected void btnQuery_Click( object sender, EventArgs e )
        {
            string startDate = CtrlHelper.GetText( txtStartDate );
            string endDate = CtrlHelper.GetText( txtEndDate );
            SetCondition( startDate, endDate );
            ShareInfoDataBind( );
        }

        //今天
        protected void btnQueryTD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetTodayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetTodayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareInfoDataBind( );
        }

        //昨天
        protected void btnQueryYD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetYesterdayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetYesterdayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareInfoDataBind( );
        }

        //本周
        protected void btnQueryTW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareInfoDataBind( );
        }

        //上周
        protected void btnQueryYW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetLastWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetLastWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareInfoDataBind( );
        }

        //用户查询
        protected void btnQueryAcc_Click( object sender, EventArgs e )
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
                        condition.AppendFormat( " AND Accounts='{0}' ", queryContent );
                        break;
                    case 2:
                        if ( Utils.Validate.IsPositiveInt( queryContent ) )
                            condition.AppendFormat( " AND GameID='{0}'", queryContent );
                        else
                        {
                            ShowError( "你输入的游戏ID必须为正整数" );
                            return;
                        }
                        break;
                    case 3:
                        condition.AppendFormat( " AND SerialID IN (SELECT SerialID FROM QPTreasureDB.dbo.LivcardAssociator WHERE SalesPerson='{0}')", queryContent );
                        break;
                    case 4:
                        condition.AppendFormat( " AND SerialID='{0}'" , queryContent );
                        break;
                    default:
                        break;
                }
            }
           

            ViewState["SearchItems"] = condition.ToString( );
            ShareInfoDataBind( );
        }

        #endregion

        #region 数据绑定
        //充值服务
        private void BindGlobalShare( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGlobalShareList( 1, 1000, "", "ORDER BY ShareID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlGlobalShareInfo.DataSource = pagerSet.PageSet;
                ddlGlobalShareInfo.DataTextField = "ShareName";
                ddlGlobalShareInfo.DataValueField = "ShareID";
                ddlGlobalShareInfo.DataBind( );
            }
            ddlGlobalShareInfo.Items.Insert( 0, new ListItem( "全部服务", "0" ) );
        }
        //实卡类型
        private void BindCardType( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGlobalLivcardList( 1, 1000, "", "ORDER BY CardTypeID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlCardType.DataSource = pagerSet.PageSet;
                ddlCardType.DataTextField = "CardName";
                ddlCardType.DataValueField = "CardTypeID";
                ddlCardType.DataBind( );
            }
            ddlCardType.Items.Insert( 0, new ListItem( "全部卡片", "0" ) );
        }
        //绑定数据
        private void ShareInfoDataBind( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetShareDetailList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
                trPayStat.Visible = false;
            }

            rptShareInfo.DataSource = pagerSet.PageSet;
            rptShareInfo.DataBind( );
            anpNews.RecordCount = pagerSet.RecordCount;

            string sqlQuery = "Select Sum(OrderAmount) AS OrderAmount, Sum(PayAmount) AS PayAmount, Sum(CardGold) AS CardGold, Sum(CardPrice) As CardPrice From ShareDetailInfo " + SearchItems;
            DataSet ds = aideTreasureFacade.GetDataSetBySql( sqlQuery );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                DataRow row = ds.Tables[0].Rows[0];
                CtrlHelper.SetText( ltCardPrice , row["CardPrice"].ToString( ) );
                CtrlHelper.SetText( ltGrantGold , FormatMoney( row["CardGold"].ToString( ) ) );
                CtrlHelper.SetText( ltOrderAmounts , row["OrderAmount"].ToString( ) );
                CtrlHelper.SetText( ltPayAmounts , row["PayAmount"].ToString( ) );
            }
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
                        condition.AppendFormat( " AND ApplyDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                    }

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
                    ViewState["Orderby"] = "ORDER BY ApplyDate DESC";
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
