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

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Entity.Platform;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Collections.Generic;

namespace Game.Web.UserService
{
    public partial class USClearScore : UCPageBase
    {

        private AccountsFacade accountsFacade = new AccountsFacade( );
        private PlatformFacade platformFacade = new PlatformFacade( );

        #region 窗口载入

        protected void Page_Load( object sender , EventArgs e )
        {
            //判断是否登录
            if ( !Fetch.IsUserOnline( ) )
            {
                return;
            }

            if ( !IsPostBack )
            {
                Message umsg = accountsFacade.GetUserGlobalInfo( Fetch.GetUserCookie( ).UserID , 0 , "" );
                if ( umsg.Success )
                {
                    UserInfo user = umsg.EntityList[0] as UserInfo;
                    if ( user != null && user.MemberOrder <= 0 )
                    {
                        this.form1.Visible = false;
                        this.divRight.Visible = true;
                        this.divRight.InnerHtml = "<div class=\"Uerror\">抱歉！您不是会员，不能进行负分清零操作。<br /><a href=\"/Pay/PayIndex.aspx\" class=\"lan\" target=\"_blank\">点击购买会员</a></div>";
                        return;
                    }
                }

                DataTable dtScore = new DataTable( );
                DataColumn colKindName = new DataColumn( "KindName" );
                DataColumn colScore = new DataColumn( "Score" );
                DataColumn colKindID = new DataColumn( "KindID" );

                dtScore.Columns.Add( colKindName );
                dtScore.Columns.Add( colScore );
                dtScore.Columns.Add( colKindID );

                IList<GameKindItem> kinds = platformFacade.GetAllKinds( );

                foreach ( GameKindItem kind in kinds )
                {
                    TreasureFacade treasureFacade = new TreasureFacade( kind.KindID );

                    GameScoreInfo scoreInfo = treasureFacade.GetTreasureInfo2( Fetch.GetUserCookie( ).UserID );
                    if ( scoreInfo == null ) continue;
                    if ( scoreInfo.Score < 0 )
                    {
                        DataRow r = dtScore.NewRow( );
                        r["KindName"] = kind.KindName;
                        r["KindID"] = kind.KindID;
                        r["Score"] = scoreInfo.Score;

                        dtScore.Rows.Add( r );
                    }
                }

                if ( dtScore.Rows.Count > 0 )
                {
                    rptScoreList.DataSource = dtScore;
                    rptScoreList.DataBind( );

                    this.lblAccounts.Text = Fetch.GetUserCookie( ).Accounts;
                    this.lblNumber.Text = dtScore.Rows.Count.ToString( );

                    this.form1.Visible = true;
                    this.divRight.Visible = false;
                }
                else
                {
                    this.form1.Visible = false;
                    this.divRight.Visible = true;

                    this.divRight.InnerHtml = "<div class=\"Uright\">恭喜！您的游戏成绩保持的非常好，没有负分需要清零。</div>";
                }
            }

            /*Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "会员中心";*/

        }

        #endregion

        #region 按钮事件

        protected void rptScoreList_ItemCommand( object source , RepeaterCommandEventArgs e )
        {
            //判断是否登录
            if ( !Fetch.IsUserOnline( ) )
            {
                return;
            }

            if ( e.CommandName == "Clear" )
            {
                int kindID = Convert.ToInt32( e.CommandArgument.ToString( ) );

                TreasureFacade treasureFacade = new TreasureFacade( kindID );
                Message umsg = treasureFacade.ClearGameScore( Fetch.GetUserCookie( ).UserID , GameRequest.GetUserIP( ) );
                if ( umsg.Success )
                {
                    ShowAndRedirect( "负分清零成功!" , "/Member/ClearScore.aspx" );
                }
                else
                {
                    Show( umsg.Content );
                }
            }
        }

        #endregion
 
    }
}
