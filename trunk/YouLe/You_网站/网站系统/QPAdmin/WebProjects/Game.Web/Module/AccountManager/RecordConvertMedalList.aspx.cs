using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Kernel;
using System.Text;
using Game.Utils;
using Game.Entity.Accounts;
using Game.Entity.Record;
using Game.Facade;

namespace Game.Web.Module.AccountManager
{
    public partial class RecordConvertMedalList : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-魅力兑换记录";
            }
        }
        #endregion

        #region 窗口
        
        protected void Page_Load( object sender , EventArgs e )
        {
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
            {
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-" ) + "01";
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                BindData( );
            }
        }

        /// <summary>
        /// 设置查询条件
        /// </summary>
        /// <param name="startDate"></param>
        /// <param name="endDate"></param>
        private void SetCondition( string startDate , string endDate )
        {
            StringBuilder condition = new StringBuilder( );
            //condition.AppendFormat( " WHERE UserID={0} " , IntParam );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " WHERE CollectDate BETWEEN '{0}' AND '{1}'" , startDate , Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
        }
        // 查询
        protected void btnQuery_Click( object sender , EventArgs e )
        {
            string startDate = txtStartDate.Text.Trim( );
            string endDate = txtEndDate.Text.Trim( );
            StringBuilder condition = new StringBuilder( );

            SetCondition( startDate , endDate );
            BindData( );
        }
        //查询
        protected void btnQuery1_Click( object sender , EventArgs e )
        {
            string queryContent = txtSearch.Text.Trim( );
            int searchType = int.Parse( ddlSearchType.SelectedValue );
            StringBuilder condition = new StringBuilder( );
            condition.Append( " WHERE (1=1) " );

            if ( !string.IsNullOrEmpty( queryContent ) )
            {
                switch ( searchType )
                {
                    case 1:
                        condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE Accounts='{0}')" , queryContent );
                        break;
                    case 2:
                        if ( Utils.Validate.IsPositiveInt( queryContent ) )
                            condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE GameID='{0}')" , queryContent );
                        else
                        {
                            ShowError( "你输入的游戏ID必须为正整数" );
                            return;
                        }
                        break;
                }
            }
            ViewState["SearchItems"] = condition.ToString( );
            BindData( );
        }

        //今天
        protected void btnQueryTD_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetTodayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetTodayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            BindData( );
        }

        //昨天
        protected void btnQueryYD_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetYesterdayTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetYesterdayTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            BindData( );
        }

        //本周
        protected void btnQueryTW_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            BindData( );
        }

        //上周
        protected void btnQueryYW_Click( object sender , EventArgs e )
        {
            string startDate = Fetch.GetLastWeekTime( ).Split( '$' )[0].ToString( );
            string endDate = Fetch.GetLastWeekTime( ).Split( '$' )[1].ToString( );

            CtrlHelper.SetText( txtStartDate , Convert.ToDateTime( startDate ).ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtEndDate , Convert.ToDateTime( endDate ).ToString( "yyyy-MM-dd" ) );

            SetCondition( startDate , endDate );
            BindData( );
        }
        /// <summary>
        /// 刷新
        /// </summary>
        protected void btnRefresh_Click( object sender , EventArgs e )
        {
            ViewState["SearchItems"] = null;

            txtEndDate.Text = "";
            txtStartDate.Text = "";
            BindData( );
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideRecordFacade.GetList( RecordConvertUserMedal.Tablename , PageIndex , anpNews.PageSize , SearchItems , Orderby );
            anpNews.RecordCount = pagerSet.RecordCount;
            anpNews.CurrentPageIndex = PageIndex;
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptDataList.DataSource = pagerSet.PageSet;
                rptDataList.DataBind( );
                rptDataList.Visible = true;
                litNoData.Visible = false;
            }
            else
            {
                rptDataList.Visible = false;
                litNoData.Visible = true;
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
