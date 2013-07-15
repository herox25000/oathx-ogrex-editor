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
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Member
{
    public partial class InsureIn : UCPageBase
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

        private TreasureFacade treasureFacade = new TreasureFacade();
        private AccountsFacade accountsFacade = new AccountsFacade( );
        protected int MinTradeScore = 0;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                GameScoreInfo scoreInfo = treasureFacade.GetTreasureInfo2(Fetch.GetUserCookie().UserID);
                if ( scoreInfo != null )
                {
                    int xx = scoreInfo.DrawCount;
                    this.lblInsureScore.Text = scoreInfo.InsureScore.ToString( );
                    this.lblScore.Text = scoreInfo.Score.ToString( );
                    this.txtScore.Text = scoreInfo.Score.ToString( );
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            int score =  Utility.StrToInt(txtScore.Text.Trim(), 0);
            string note = TextFilter.FilterScript( txtNode.Text.Trim( ) );
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.AppendFormat( "select {0} from {1} where {2}='{3}'" , SystemStatusInfo._StatusValue , SystemStatusInfo.Tablename , SystemStatusInfo._StatusName , "BankPrerequisite" );
            MinTradeScore = Convert.ToInt32( accountsFacade.GetObjectBySql( sqlQuery.ToString( ) ) );
            if ( score < MinTradeScore )
            {
                Show( "抱歉，您每笔存入数目最少 " + MinTradeScore + " 金币！" );
                return;
            }
            Message umsg = treasureFacade.InsureIn( Fetch.GetUserCookie( ).UserID , score , MinTradeScore , GameRequest.GetUserIP( ) , note );
            if (umsg.Success)
            {
                ShowAndRedirect("存款成功!", "/Member/InsureIn.aspx");
            }
            else
            {
                Show(umsg.Content);
            }
        }
    }
}
