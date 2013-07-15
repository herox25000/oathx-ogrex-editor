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
using Game.Facade;
using Game.Utils;
using Game.Kernel;

namespace Game.Web.Member
{
    public partial class ModifyUserInfo : UCPageBase
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

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                UserInfo user = accountsFacade.GetUserBaseInfoByUserID( Fetch.GetUserCookie( ).UserID );
                this.lblAccounts.Text = user.Accounts;
                lblGameID.Text = user.GameID.ToString( );
                ddlGender.SelectedValue = user.Gender.ToString( );
                txtUnderWrite.Text = user.UnderWrite;

                IndividualDatum contact = accountsFacade.GetUserContactInfoByUserID( Fetch.GetUserCookie( ).UserID );
                this.txtAddress.Text = contact.DwellingPlace;
                this.txtCompellation.Text = contact.Compellation;
                this.txtEmail.Text = contact.EMail;
                this.txtMobilePhone.Text = contact.MobilePhone;
                this.txtQQ.Text = contact.QQ;
                this.txtSeatPhone.Text = contact.SeatPhone;
                this.txtUserNote.Text = contact.UserNote;
            }

            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header ) this.FindControl( "sHeader" );
            sHeader.title = "会员中心";
        }

        /// <summary>
        /// 更新用户资料
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnUpdate_Click( object sender, EventArgs e )
        {
            IndividualDatum contact = new IndividualDatum( );
            contact.Gender = Convert.ToByte( ddlGender.SelectedValue );
            contact.UnderWrite = TextFilter.FilterScript( txtUnderWrite.Text.Trim( ) );
            contact.Compellation = TextFilter.FilterScript( txtCompellation.Text.Trim( ) );
            contact.MobilePhone = TextFilter.FilterScript( txtMobilePhone.Text.Trim( ) );
            contact.SeatPhone = TextFilter.FilterScript( txtSeatPhone.Text.Trim( ) );
            contact.QQ = TextFilter.FilterScript( txtQQ.Text.Trim( ) );
            contact.EMail = TextFilter.FilterScript( txtEmail.Text.Trim( ) );
            contact.DwellingPlace = TextFilter.FilterScript( txtAddress.Text.Trim( ) );
            contact.UserNote = TextFilter.FilterScript( txtUserNote.Text.Trim( ) );

            contact.UserID = Fetch.GetUserCookie( ).UserID;

            Message umsg = accountsFacade.ModifyUserIndividual( contact );
            if ( umsg.Success )
            {
                ShowAndRedirect( "个人资料修改成功!", "/Member/ModifyUserInfo.aspx" );
            }
            else
            {
                Show( umsg.Content );
            }
        }
    }
}
