using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Utils;
using Game.Web.UI;
using Game.Entity.Accounts;
using Game.Kernel;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class AccountsDetailInfo : AdminPage
    {
        #region Fields
        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-详细信息";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
                BindData( );
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            bool ret = false;
            IndividualDatum modelExists = aideAccountsFacade.GetAccountDetailByUserID( IntParam );
            if ( modelExists == null )
            {
                ret = true;
            }

            IndividualDatum model = new IndividualDatum( );
            model.UserID = IntParam;
            model.QQ = TextFilter.FilterAll( CtrlHelper.GetText( txtQQ ) );
            model.EMail = TextFilter.FilterAll( CtrlHelper.GetText( txtEMail ) );
            model.SeatPhone = TextFilter.FilterAll( CtrlHelper.GetText( txtSeatPhone ) );
            model.MobilePhone = TextFilter.FilterAll( CtrlHelper.GetText( txtMobilePhone ) );
            model.PostalCode = TextFilter.FilterAll( CtrlHelper.GetText( txtPostalCode ) );
            model.DwellingPlace = TextFilter.FilterAll( CtrlHelper.GetText( txtDwellingPlace ) );
            model.UserNote = TextFilter.FilterAll( CtrlHelper.GetText( txtUserNote ) );

            Message msg = new Message( );
            if ( ret )
            {
                msg = aideAccountsFacade.InsertAccountDetail( model );
            }
            else
            {
                msg = aideAccountsFacade.UpdateAccountDetail( model );
            }

            if ( msg.Success )
            {
                MessageBox( "信息修改成功" );
            }
            else
            {
                MessageBox( msg.Content );
            }
        }
        #endregion

        #region 数据加载
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;

            //获取信息
            IndividualDatum accountDetail = aideAccountsFacade.GetAccountDetailByUserID( IntParam );
            AccountsInfo account = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            CtrlHelper.SetText( ltGameID, account.GameID.ToString( ) );
            CtrlHelper.SetText( ltAccounts, account.Accounts.Trim( ) );

            if( account != null )
            {
                CtrlHelper.SetText( ltCardNum , account.PassPortID );
                CtrlHelper.SetText( ltName , account.Compellation.Trim( ) );
            }
            if ( accountDetail != null )
            {
                CtrlHelper.SetText( txtQQ , accountDetail.QQ.Trim( ) );
                CtrlHelper.SetText( txtEMail , accountDetail.EMail.Trim( ) );
                CtrlHelper.SetText( txtSeatPhone , accountDetail.SeatPhone.ToString( ).Trim( ) );
                CtrlHelper.SetText( txtMobilePhone , accountDetail.MobilePhone.ToString( ).Trim( ) );
                CtrlHelper.SetText( txtPostalCode , accountDetail.PostalCode.ToString( ).Trim( ) );
                CtrlHelper.SetText( txtDwellingPlace , accountDetail.DwellingPlace.ToString( ).Trim( ) );
                CtrlHelper.SetText( txtUserNote , accountDetail.UserNote.ToString( ).Trim( ) );
            }
        }
        #endregion
    }
}
