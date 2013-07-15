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

namespace Game.Web.Module.WebManager
{
    public partial class MatchUserList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindMatchInfo( );
                BindData( );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        protected void ddlMatch_SelectedIndexChanged( object sender, EventArgs e )
        {
            StringBuilder condition = new StringBuilder( );

            int matchid = string.IsNullOrEmpty( ddlMatch.SelectedValue ) ? 0 : int.Parse( ddlMatch.SelectedValue );
            if ( matchid <= 0 )
                return;
            condition.AppendFormat( " WHERE MatchID={0}", matchid );

            ViewState["SearchItems"] = condition.ToString( );
            BindData( );
        }
        //查询
        protected void btnSearch_OnClick( object sender, EventArgs e )
        {
            /*StringBuilder condition = new StringBuilder( );

            int matchid = string.IsNullOrEmpty( ddlMatch.SelectedValue ) ? 0 : int.Parse( ddlMatch.SelectedValue );
            if ( matchid <= 0 )
                return;
            condition.AppendFormat( " WHERE MatchID={0}", matchid );

            ViewState["SearchItems"] = condition.ToString( );
            BindData( );*/
        }
        //冻结
        protected void btnDisable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            int userid = 0;
            int matchid = 0;
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string[ ] arrayValue = Checkbox_Value.Split( new char[ ] { ',' }, StringSplitOptions.RemoveEmptyEntries );
            for ( int i = 0; i < arrayValue.Length; i++ )
            {
                matchid = int.Parse( arrayValue[i].Split( new char[ ] { '_' }, StringSplitOptions.RemoveEmptyEntries )[0] );
                userid = int.Parse( arrayValue[i].Split( new char[ ] { '_' }, StringSplitOptions.RemoveEmptyEntries )[1] );
                aideNativeWebFacade.SetUserMatchDisbale( string.Format( "WHERE MatchID ={0} AND UserID={1}", matchid, userid ) );
            }
            ShowInfo( "冻结成功" );
            BindData( );
        }
        //解冻
        protected void btnEnable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            int userid = 0;
            int matchid = 0;
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string[ ] arrayValue = Checkbox_Value.Split( new char[ ] { ',' }, StringSplitOptions.RemoveEmptyEntries );
            for ( int i = 0; i < arrayValue.Length; i++ )
            {
                matchid = int.Parse( arrayValue[i].Split( new char[ ] { '_' }, StringSplitOptions.RemoveEmptyEntries )[0] );
                userid = int.Parse( arrayValue[i].Split( new char[ ] { '_' }, StringSplitOptions.RemoveEmptyEntries )[1] );
                aideNativeWebFacade.SetUserMatchEnbale( string.Format( "WHERE MatchID ={0} AND UserID={1}", matchid, userid ) );
            }
            ShowInfo( "解冻成功" );
            BindData( );
        }

        #endregion

        #region 数据绑定
        //绑定赛事
        private void BindMatchInfo( )
        {
            PagerSet ps = aideNativeWebFacade.GetGameMatchInfoList( 1, 10000, "", "ORDER BY CollectDate DESC" );
            if ( ps.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlMatch.DataSource = ps.PageSet;
                ddlMatch.DataValueField = "MatchID";
                ddlMatch.DataTextField = "MatchTitle";
                ddlMatch.DataBind( );
            }
        }
        //绑定数据
        private void BindData( )
        {

            PagerSet pagerSet = aideNativeWebFacade.GetGameMatchUserInfoList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
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
                    condition.AppendFormat( " WHERE MatchID={0}", string.IsNullOrEmpty( ddlMatch.SelectedValue ) ? 0 : int.Parse( ddlMatch.SelectedValue ) );
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
