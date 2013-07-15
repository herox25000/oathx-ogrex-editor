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
using Game.Entity.Treasure;

namespace Game.Web.Module.AppManager
{
    public partial class SpreadManager : AdminPage
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
            string strKeyword = CtrlHelper.GetText( txtKeyword );
            string type = ddlSearchtype.SelectedValue;
            if ( !string.IsNullOrEmpty( strKeyword ) )
            {
                if ( type.Equals( "1" ) )//GAMEID
                {
                    if ( Utils.Validate.IsPositiveInt( strKeyword ) )
                    {
                        condition.AppendFormat( " WHERE SpreaderID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE GameID='{0}')", strKeyword );
                    }
                    else
                    {
                        ShowError( "你输入的游戏ID必须为正整数" );
                        return;
                    }
                }
                else
                    condition.AppendFormat( " WHERE SpreaderID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE Accounts='{0}')", strKeyword );

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

            txtKeyword.Text = "";
            BindData( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            if ( string.IsNullOrEmpty( SearchItems ) )
                return;
            PagerSet pagerSet = aideAccountsFacade.GetAccountsList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
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

                    ViewState["SearchItems"] = "";
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
                    ViewState["Orderby"] = "ORDER BY RegisterDate DESC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        //获取推广收入
        protected string GetSpreadScore( int userid )
        {
            return aideTreasureFacade.GetSpreadScore( userid ).ToString( );
        }

        #endregion
    }
}
