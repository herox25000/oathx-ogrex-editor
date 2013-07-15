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

namespace Game.Web.Member
{
    public partial class InsureTransfer : UCPageBase
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
        protected double RevenueScale = 0.01;   // 手续费
        protected double MinTradeScore = 100;   //最低转账金额
        private AccountsFacade accountsFacade = new AccountsFacade();
        private TreasureFacade treasureFacade = new TreasureFacade();

        protected void Page_Load(object sender, EventArgs e)
        {

            if (!IsPostBack)
            {
                GameScoreInfo scoreInfo = treasureFacade.GetTreasureInfo2(Fetch.GetUserCookie().UserID);
                if ( scoreInfo != null )
                {
                    this.lblInsureScore.Text = scoreInfo.InsureScore.ToString( );
                    this.lblScore.Text = scoreInfo.Score.ToString( );
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            int userId = 0;

            if (this.radType1.Checked)
            {
                userId = accountsFacade.GetUserIDByNickName(txtUser.Text.Trim());
                if (userId == 0)
                {
                    Show("您输入的用户昵称错误，请重新输入！");
                    this.txtUser.Text = "";
                    this.txtUser.Focus();
                    return;
                }
            }
            else
            {
                Message umsg = accountsFacade.GetUserGlobalInfo(0, Utility.StrToInt(txtUser.Text.Trim(), 0), "");
                if (!umsg.Success)
                {
                    Show("您输入的游戏ID号码错误，请重新输入！");
                    this.txtUser.Text = "";
                    this.txtUser.Focus();
                    return;
                }

                UserInfo user = umsg.EntityList[0] as UserInfo;
                userId = user.UserID;
            }

            int score = Utility.StrToInt( txtScore.Text.Trim( ), 0 );
            string note = TextFilter.FilterScript( txtNote.Text.Trim( ) );
            if ( score <= 0 )
            {
                Show( "抱歉，您每笔转出数目最少 1000 金币！" );
                return;
            }

            Message msg = treasureFacade.InsureTransfer(Fetch.GetUserCookie().UserID, TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtInsurePass)), userId, score, 1000, GameRequest.GetUserIP(), note);
            if (msg.Success)
            {
                ShowAndRedirect("转账成功!", "/Member/InsureTransfer.aspx");
            }
            else
            {
                Show(msg.Content);
            }
        }
    }
}
