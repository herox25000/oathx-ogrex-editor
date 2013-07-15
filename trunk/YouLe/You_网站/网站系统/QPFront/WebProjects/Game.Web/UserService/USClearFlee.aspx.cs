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
    public partial class USClearFlee : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade( );
        private PlatformFacade platformFacade = new PlatformFacade( );

        #region 窗口

        protected void Page_Load( object sender , EventArgs e )
        {
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

                        this.divRight.InnerHtml = "<div class=\"Uerror\">抱歉！您不是会员，不能进行逃跑清零操作。<br /><a href=\"/Pay/PayIndex.aspx\" class=\"lan\" target=\"_blank\">点击购买会员</a></div>";
                        return;
                    }
                }

                DataTable dtFlee = new DataTable( );
                DataColumn colKindName = new DataColumn( "KindName" );
                DataColumn colScore = new DataColumn( "FleeCount" );
                DataColumn colKindID = new DataColumn( "KindID" );

                dtFlee.Columns.Add( colKindName );
                dtFlee.Columns.Add( colScore );
                dtFlee.Columns.Add( colKindID );

                IList<GameKindItem> kinds = platformFacade.GetIntegralKinds( );

                foreach ( GameKindItem kind in kinds )
                {
                    TreasureFacade treasureFacade = new TreasureFacade( kind.KindID );

                    GameScoreInfo scoreInfo = treasureFacade.GetTreasureInfo2( Fetch.GetUserCookie( ).UserID );
                    if ( scoreInfo == null ) continue;
                    if ( scoreInfo.FleeCount > 0 )
                    {
                        DataRow r = dtFlee.NewRow( );
                        r["KindName"] = kind.KindName;
                        r["KindID"] = kind.KindID;
                        r["FleeCount"] = scoreInfo.FleeCount;

                        dtFlee.Rows.Add( r );
                    }
                }

                if ( dtFlee.Rows.Count > 0 )
                {
                    rptFleeList.DataSource = dtFlee;
                    rptFleeList.DataBind( );

                    this.lblAccounts.Text = Fetch.GetUserCookie( ).Accounts;
                    this.lblNumber.Text = dtFlee.Rows.Count.ToString( );

                    this.form1.Visible = true;
                    this.divRight.Visible = false;
                }
                else
                {
                    this.form1.Visible = false;
                    this.divRight.Visible = true;

                    this.divRight.InnerHtml = "<div class=\"Uright\">恭喜！您的游戏成绩保持的非常好，没有逃跑需要清零。</div>";
                }
            }
        }

        #endregion

        #region 按钮事件

        protected void rptFleeList_ItemCommand( object source , RepeaterCommandEventArgs e )
        {
            if ( e.CommandName == "Clear" )
            {
                int kindID = Convert.ToInt32( e.CommandArgument.ToString( ) );

                TreasureFacade treasureFacade = new TreasureFacade( kindID );
                Message umsg = treasureFacade.ClearGameFlee( Fetch.GetUserCookie( ).UserID , GameRequest.GetUserIP( ) );
                if ( umsg.Success )
                {
                    ShowAndRedirect( "逃跑清零成功!" , "/Member/ClearFlee.aspx" );
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
