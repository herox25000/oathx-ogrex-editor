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
    public partial class ShareDetailList : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-充值记录";
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
                BindShareList( );
                BindCardType( );
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-" ) + "01";
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            ShareDetailDataBind( );
        }
        /// <summary>
        /// 设置查询条件
        /// </summary>
        /// <param name="startDate"></param>
        /// <param name="endDate"></param>
        private void SetCondition( string startDate, string endDate )
        {
            int service = int.Parse( ddlShareID.SelectedValue );
            int type = int.Parse( ddlCardType.SelectedValue );
            StringBuilder condition = new StringBuilder( " WHERE UserID= " + IntParam );
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
            ShareDetailDataBind( );
        }

        //今天
        protected void btnQueryTD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetTodayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetTodayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareDetailDataBind( );
        }

        //昨天
        protected void btnQueryYD_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetYesterdayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetYesterdayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareDetailDataBind( );
        }

        //本周
        protected void btnQueryTW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareDetailDataBind( );
        }

        //上周
        protected void btnQueryYW_Click( object sender, EventArgs e )
        {
            string startDate = Fetch.GetLastWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetLastWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate, Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate, Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate, endDate );
            ShareDetailDataBind( );
        }
        #endregion

        #region 数据绑定

        //绑定类型
        private void BindShareList( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGlobalShareList( 1, Int32.MaxValue, "", "ORDER BY ShareID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlShareID.DataSource = pagerSet.PageSet;
                ddlShareID.DataTextField = "ShareName";
                ddlShareID.DataValueField = "ShareID";
                ddlShareID.DataBind( );
            }
            ddlShareID.Items.Insert( 0, new ListItem( "全部服务", "0" ) );
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
        private void ShareDetailDataBind( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetShareDetailList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptShareDetail.DataSource = pagerSet.PageSet;
            rptShareDetail.DataBind( );
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
