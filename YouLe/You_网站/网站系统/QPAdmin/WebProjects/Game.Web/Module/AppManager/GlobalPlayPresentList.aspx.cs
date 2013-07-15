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
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class GlobalPlayPresentList : AdminPage
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
            string strQuery = "WHERE ServerID in (" + Checkbox_Value + ")";
            try
            {
                aidePlatformFacade.DeleteGlobalPlayPresent( strQuery );
                ShowInfo( "删除成功" );
            }
            catch
            {
                ShowError( "删除失败" );
            }
            BindData( );
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGlobalPlayPresentList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
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
                    condition.Append( " WHERE ServerID <> -3" );

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

        protected string GetRoomName( int serverID )
        {
            if ( serverID == -1 )
                return "金币房间";
            else if ( serverID == -2 )
                return "积分房间";
            else
                return GetGameRoomName( serverID );
        }

        protected string GetMemberList( string list )
        {
            StringBuilder sb = new StringBuilder( );
            string[ ] array = list.Split( new char[ ] { ',' }, StringSplitOptions.RemoveEmptyEntries );
            //ArrayList list = new ArrayList( arrMemberOrder );
            for ( int i=0;i< array.Length;i++)
            {
                sb.AppendFormat( "{0},", GetMemberName( byte.Parse( array[i] ) ) );
            }
            return sb.ToString( ).TrimEnd( new char[ ] { ',' } );
        }

        #endregion
    }
}
