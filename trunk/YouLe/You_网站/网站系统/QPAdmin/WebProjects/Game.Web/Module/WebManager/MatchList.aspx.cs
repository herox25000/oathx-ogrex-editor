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
using Game.Entity.Enum;
using Game.Entity.GameMatch;

namespace Game.Web.Module.WebManager
{
    public partial class MatchList : AdminPage
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

        //删除
        protected void btnDel_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "DELETE MatchInfo WHERE MatchID in (" + Checkbox_Value + ")";
            int result = aideGameMatchFacade.ExecuteSql( strQuery );
            if ( result > 0 )
            {
                ShowInfo( "删除成功" );
            }
            else
            {
                ShowError( "删除失败，没有需要冻结的比赛" );
            }
            BindData( );
        }
        //冻结
        protected void btnDisable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "Update MatchInfo Set Nullity=1 WHERE Nullity = 0 AND  MatchID in (" + Checkbox_Value + ")";
            int result = aideGameMatchFacade.ExecuteSql( strQuery );
            if ( result > 0 )
            {
                ShowInfo( "冻结成功" );
            }
            else
            {
                ShowError( "冻结失败，没有需要冻结的比赛" );
            }
            BindData( );
        }
        //解冻
        protected void btnEnable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "Update MatchInfo Set Nullity=0 WHERE Nullity = 1 AND MatchID in (" + Checkbox_Value + ")";
            int result=aideGameMatchFacade.ExecuteSql( strQuery );
            if ( result > 0 )
            {
                ShowInfo( "解冻成功" );
            }
            else
            {
                ShowError( "解冻失败，没有需要解冻的比赛" );
            }         
            BindData( );
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            //PagerSet pagerSet = aideNativeWebFacade.GetGameMatchInfoList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            PagerSet pagerSet = aideGameMatchFacade.GetList( Game.Entity.GameMatch.MatchInfo.Tablename , anpNews.CurrentPageIndex , anpNews.PageSize , Orderby , SearchItems );
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
                    ViewState["Orderby"] = "ORDER BY CollectDate DESC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        /// <summary>
        /// 赛事状态(0:未开始,1:进行中,2:结束)
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        protected string GetMatchStatus( byte matchID )
        {
            string result = "";
            switch ( matchID )
            {
                case 0:
                    result = "未开始";
                    break;
                case 1:
                    result = "进行中";
                    break;
                case 2:
                    result = "结束";
                    break;
                default:
                    result = "";
                    break;
            }
            return result;
        }
        #endregion
    }
}
