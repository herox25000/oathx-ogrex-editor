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
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Member
{
    public partial class InsureOut : UCPageBase
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

        private TreasureFacade treasureFacade = new TreasureFacade( );
        private AccountsFacade accountsFacade = new AccountsFacade( );
        protected int MinTradeScore = 0;

        protected void Page_Load( object sender , EventArgs e )
        {
            if( !IsPostBack )
            {
                GameScoreInfo scoreInfo = treasureFacade.GetTreasureInfo2( Fetch.GetUserCookie( ).UserID );
                if( scoreInfo != null )
                {
                    this.lblInsureScore.Text = scoreInfo.InsureScore.ToString( );
                    this.lblScore.Text = scoreInfo.Score.ToString( );
                    this.txtScore.Text = scoreInfo.InsureScore.ToString( );
                }
            }

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click( object sender , EventArgs e )
        {
            int score = Utility.StrToInt( txtScore.Text.Trim( ) , 0 );
            string note = TextFilter.FilterScript( txtNote.Text.Trim( ) );
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.AppendFormat( "select {0} from {1} where {2}='{3}'" , SystemStatusInfo._StatusValue , SystemStatusInfo.Tablename , SystemStatusInfo._StatusName , "BankPrerequisite" );
            MinTradeScore = Convert.ToInt32( accountsFacade.GetObjectBySql( sqlQuery.ToString( ) ) );
            if( score < MinTradeScore )
            {
                Show( "抱歉，您每笔取出数目最少 " + MinTradeScore + " 金币！" );
                return;
            }
            Message umsg = treasureFacade.InsureOut( Fetch.GetUserCookie( ).UserID , TextEncrypt.EncryptPassword( CtrlHelper.GetText( txtInsurePass ) ) , score , MinTradeScore , GameRequest.GetUserIP( ) , note );
            if( umsg.Success )
            {
                ShowAndRedirect( "取款成功!" , "/Member/InsureOut.aspx" );
            }
            else
            {
                Show( umsg.Content );
            }
        }
    }
}
