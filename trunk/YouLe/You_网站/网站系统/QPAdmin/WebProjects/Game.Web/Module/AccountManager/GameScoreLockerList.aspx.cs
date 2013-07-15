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
using Game.Entity;
using Game.Entity.Enum;

namespace Game.Web.Module.AccountManager
{
    public partial class GameScoreLockerList : AdminPage
    {

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                if ( IntParam > 0 && StrCmd.Equals( "del" ) )
                {
                    //判断权限
                    AuthUserOperationPermission( Permission.Delete );
                    aideTreasureFacade.DeleteGameScoreLockerByUserID( IntParam );
                    ShowInfo( "删除成功" );
                }
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
            StringBuilder condition = new StringBuilder( );
            condition.Append( " WHERE 1=1 " );
            if ( !string.IsNullOrEmpty( queryContent ) )
            {
                if ( ckbIsLike.Checked )
                {
                    condition.AppendFormat( " AND (UserID LIKE '%{0}%' OR EnterMachine LIKE '%{0}%')", queryContent );
                }
                else
                {
                    if ( Utils.Validate.IsPositiveInt( queryContent ) )
                        condition.AppendFormat( " AND (EnterMachine='{0}'OR UserID='{0}')", queryContent );
                    else
                        condition.AppendFormat( " AND (EnterMachine='{0}')", queryContent );
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
            ckbIsLike.Checked = false;
            BindData( );
        }
        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.DeleteGameScoreLocker( strQuery );
                ShowInfo( "删除成功" );
                BindData( );
            }
            catch
            {
                ShowError( "删除失败" );
            }
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGameScoreLockerList( anpPage.CurrentPageIndex, anpPage.PageSize, SearchItems, Orderby );
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
