using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Entity.Accounts;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using Game.Entity.Treasure;

namespace Game.Web.Member
{
    public partial class ConvertMedal : UCPageBase
    {

        #region 继承属性

        protected override bool IsAuthenticatedUser
        {
            get
            {
                return true;
            }
        }

        #endregion

        private AccountsFacade accountsFacade = new AccountsFacade( );
        private TreasureFacade treasureFacade = new TreasureFacade( );
        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                Message umsg = accountsFacade.GetUserGlobalInfo( Fetch.GetUserCookie( ).UserID , 0 , "" );
                if ( umsg.Success )
                {
                    UserInfo user = umsg.EntityList[0] as UserInfo;
                    lblAccounts.Text = user.Accounts;
                    lblMedals.Text = user.UserMedal.ToString();
                    lblGameID.Text = user.GameID.ToString( );
                    txtMedals.Text = user.UserMedal.ToString();
                }

                GameScoreInfo scoreInfo = treasureFacade.GetTreasureInfo2( Fetch.GetUserCookie( ).UserID );
                if ( scoreInfo != null )
                {
                    this.lblInsureScore.Text = scoreInfo.InsureScore.ToString( );
                }
            }

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click( object sender , EventArgs e )
        {
            int medals = Utility.StrToInt( txtMedals.Text.Trim( ) , 0 );
            if ( medals <= 0 )
            {
                Show( "兑换的奖牌数必须为正整数！" );
                return;
            }
            Message umsg = accountsFacade.UserConvertMedal( Fetch.GetUserCookie( ).UserID , medals , 10 , GameRequest.GetUserIP( ) );
            if ( umsg.Success )
            {
                ShowAndRedirect( "奖牌兑换成功!" , "/Member/ConvertMedal.aspx" );
            }
            else
            {
                Show( umsg.Content );
            }
        }
    }
}
