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
using Game.Entity;
using System.Data;
using Game.Facade;
using Game.Entity.Enum;

namespace Game.Web.Module.AccountManager
{
    public partial class AccountsScoreList : AdminPage
    {

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindGameInfo( );
                BindData( );
            }
        }
        protected void anpPage_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        /// <summary>
        /// 查询
        /// </summary>
        protected void btnQuery_Click( object sender, EventArgs e )
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
                        condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE Accounts='{0}')", queryContent );
                        break;
                    case 2:
                        if ( Utils.Validate.IsPositiveInt( queryContent ) )
                            condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE GameID='{0}')", queryContent );
                        else
                        {
                            ShowError( "你输入的游戏ID必须为正整数" );
                            return;
                        }
                            break;
                    case 3:
                        if ( Utils.Validate.IsPositiveInt( queryContent ) )
                            condition.AppendFormat( " AND Score>={0} ", queryContent );
                        else
                        {
                            ShowError( "你输入的积分数必须为正整数" );
                            return;
                        }
                        break;
                    case 4:
                        if ( Utils.Validate.IsPositiveInt( queryContent ) )
                            condition.AppendFormat( " AND Score<={0} ", queryContent );
                        else
                        {
                            ShowError( "你输入的积分数必须为正整数" );
                            return;
                        }
                        break;
                } 
            }
            ViewState["SearchItems"] = condition.ToString( );
            BindData( );
        }
        /// <summary>
        /// 刷新
        /// </summary>
        protected void btnRefresh_Click( object sender, EventArgs e )
        {
            ViewState["SearchItems"] = null;
            txtSearch.Text = "";

            BindData( );
        }
        #endregion

        #region 数据绑定

        //绑定数据  
        private void BindGameInfo( )
        {
            DataSet ds = aidePlatformFacade.GetGameList( );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                ddlGame.DataSource = ds.Tables[0];
                ddlGame.DataTextField = "KindName";
                ddlGame.DataValueField = "KindID";
                ddlGame.DataBind( );
            }
            ddlGame.Items.Insert( 0, new ListItem( "选择游戏", "0" ) );
        }
        private void BindData( )
        {
            litNoSelect.Visible = false;
            int kindID = int.Parse( ddlGame.SelectedValue );
            if ( kindID <= 0 )
            {
                litNoSelect.Visible = true;
                return;
            }
            PagerSet pagerSet = new TreasureFacade( kindID ).GetGameScoreInfoList( anpPage.CurrentPageIndex, anpPage.PageSize, SearchItems, Orderby );
            anpPage.RecordCount = pagerSet.RecordCount;
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
                    ViewState["Orderby"] = "ORDER BY UserID DESC";
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
