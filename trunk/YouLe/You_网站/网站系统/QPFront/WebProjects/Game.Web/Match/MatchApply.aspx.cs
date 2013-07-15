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
using Game.Entity.NativeWeb;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Match
{
    public partial class MatchApply : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade( );
        private NativeWebFacade webFacade = new NativeWebFacade( );

        public string matchID = "";

        private int XID = GameRequest.GetQueryInt( "XID", 0 );

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load( object sender, EventArgs e )
        {
            matchID = XID.ToString( );

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header ) this.FindControl( "sHeader" );
            sHeader.title = "比赛中心";

            if ( !IsPostBack )
            {
                GameMatchInfo match = webFacade.GetMatchInfo( XID );
                if ( match == null )
                {
                    this.form1.Visible = false;
                    this.divRight.Visible = true;
                    this.divRight.InnerHtml = "比赛不存在！";

                    return;
                }
                else
                {
                    if ( match.ApplyBeginDate > DateTime.Now )
                    {
                        this.form1.Visible = false;
                        this.divRight.Visible = true;
                        this.divRight.InnerHtml = "报名时间：" + match.ApplyBeginDate.ToString( "yyyy-MM-dd HH:mm" ) + " 至 " + match.ApplyEndDate.ToString( "yyyy-MM-dd HH:mm" );
                        return;
                    }
                    if ( match.ApplyEndDate < DateTime.Now )
                    {
                        this.form1.Visible = false;
                        this.divRight.Visible = true;
                        this.divRight.InnerHtml = "报名已结束！";
                        return;
                    }
                }

                if ( Fetch.GetUserCookie( ) != null )
                {
                    this.txtAccounts.Text = Fetch.GetUserCookie( ).Accounts;
                }
            }
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle( )
        {
            AddMetaTitle( "比赛报名 - " + ApplicationSettings.Get( "title" ) );
            AddMetaKeywords( ApplicationSettings.Get( "keywords" ) );
            AddMetaDescription( ApplicationSettings.Get( "description" ) );
        }

        protected void btnConfirm_Click( object sender, EventArgs e )
        {
            GameMatchUserInfo userInfo = new GameMatchUserInfo( );
            userInfo.Accounts = CtrlHelper.GetText(txtAccounts);
            userInfo.ClientIP = GameRequest.GetUserIP( );
            userInfo.CollectDate = DateTime.Now;
            userInfo.Compellation = CtrlHelper.GetText(txtCompellation);
            userInfo.DwellingPlace = CtrlHelper.GetText(txtDwellingPlace);
            userInfo.EMail = CtrlHelper.GetText(txtEMail);
            userInfo.Gender = Convert.ToByte( rdoFemale.Checked == true ? 0 : 1 );
            userInfo.MatchID = XID;
            userInfo.MobilePhone = CtrlHelper.GetText(txtMobilePhone);
            userInfo.PassportID = CtrlHelper.GetText(txtPassportID);
            userInfo.PostalCode = CtrlHelper.GetText(txtPostalCode);
            userInfo.QQ = CtrlHelper.GetText(txtQQ);

            Message umsg = webFacade.AddGameMatch(userInfo, TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtPwd)));
            if ( umsg.Success )
            {
                ShowAndRedirect( "报名成功！", "/Match/Index.aspx" );
            }
            else
            {
                Show( umsg.Content );
            }
        }
    }
}
