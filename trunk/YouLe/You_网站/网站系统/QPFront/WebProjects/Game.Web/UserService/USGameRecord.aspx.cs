using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

using Game.Entity.Treasure;
using Game.Entity.Accounts;
using Game.Entity.Platform;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.UserService
{
    public partial class USGameRecord : UCPageBase
    {
        #region 窗体事件

        private AccountsFacade accountsFacade = new AccountsFacade( );
        private TreasureFacade treasureFacade = new TreasureFacade( );
        private PlatformFacade platformFacade = new PlatformFacade( );

        protected void Page_Load( object sender , EventArgs e )
        {
            //判断是否登录
            if ( !Fetch.IsUserOnline( ) )
            {
                return;
            }
            if ( !IsPostBack )
            {
                this.txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                this.txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-01" );

                BindInfoData( );
            }
        }

        #endregion

        #region 绑定数据

        private void BindInfoData( )
        {
            StringBuilder sWhere = new StringBuilder( );
            sWhere.AppendFormat( " WHERE DrawID IN (SELECT DrawID FROM RecordDrawScore WHERE UserID = {0}) " , Fetch.GetUserCookie( ).UserID );

            if ( txtStartDate.Text.Trim( ) != "" )
            {
                sWhere.AppendFormat(" AND StartTime >= '{0}'", CtrlHelper.GetText(txtStartDate));
            }

            if ( txtEndDate.Text.Trim( ) != "" )
            {
                sWhere.AppendFormat(" AND ConcludeTime < '{0}'", Convert.ToDateTime(CtrlHelper.GetText(txtEndDate)).AddDays(1).ToString("yyyy-MM-dd"));
            }

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = treasureFacade.GetDrawInfoRecord( sWhere.ToString( ) , sPageIndex , sPageSize );
            anpPage.RecordCount = pagerSet.RecordCount;

            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                this.rptDrawInfoList.DataSource = pagerSet.PageSet;
                this.rptDrawInfoList.DataBind( );

                this.rptDrawInfoList.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptDrawInfoList.Visible = false;
                this.trNoData.Visible = true;
            }
        }

        /// <summary>
        /// 分页事件
        /// </summary>
        /// <param name="src"></param>
        /// <param name="e"></param>
        protected void anpPage_PageChanging( object src , Wuqi.Webdiyer.PageChangingEventArgs e )
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            BindInfoData( );
        }

        /// <summary>
        /// 查询按钮的事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnSelect_Click( object sender , EventArgs e )
        {
            anpPage.CurrentPageIndex = 1;
            BindInfoData( );
        }

        /// <summary>
        /// 根据kindId获取游戏名
        /// </summary>
        /// <param name="kinId"></param>
        /// <returns></returns>
        protected string GetGameNameByKindId( int kindId )
        {
            StringBuilder sql = new StringBuilder( );
            sql.AppendFormat( "select {0} from {1} where {2}={3}" , GameKindItem._KindName , GameKindItem.Tablename , GameKindItem._KindID , kindId );
            object ob = platformFacade.GetObjectBySql( sql.ToString( ) );
            if ( ob != null )
            {
                return ob.ToString( );
            }
            return "未知";
        }

        /// <summary>
        /// 根据房间ID获取房间名
        /// </summary>
        /// <param name="kinId"></param>
        /// <returns></returns>
        protected string GetServerNameByServerId( int ServerId )
        {
            StringBuilder sql = new StringBuilder( );
            sql.AppendFormat( "select {0} from {1} where {2}={3}" , GameRoomInfo._ServerName , GameRoomInfo.Tablename , GameRoomInfo._ServerID , ServerId );
            object ob = platformFacade.GetObjectBySql( sql.ToString( ) );
            if ( ob != null )
            {
                return ob.ToString( );
            }
            return "未知";
        }

        protected void rptDrawInfoList_ItemDataBound( object sender , RepeaterItemEventArgs e )
        {
            if ( ( e.Item.ItemType == ListItemType.Item ) || ( e.Item.ItemType == ListItemType.AlternatingItem ) )
            {
                DataRowView dataItem = ( DataRowView )e.Item.DataItem;
                PagerSet pagerSet = treasureFacade.GetDrawScoreRecord( string.Format( " WHERE DrawID={0}" , dataItem["DrawID"].ToString( ) ) , 1 , 20 );

                if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
                {
                    Repeater rpt = ( Repeater )e.Item.FindControl( "rptDrawScoreList" );
                    rpt.DataSource = pagerSet.PageSet;
                    rpt.DataBind( );
                }
            }
        }

        #endregion
    }
}
