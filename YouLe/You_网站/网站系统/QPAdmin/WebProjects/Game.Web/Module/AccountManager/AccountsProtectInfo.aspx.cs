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
using Game.Facade.Aide;


namespace Game.Web.Module.AccountManager
{
    public partial class AccountsProtectInfo : AdminPage
    {
        #region Fields
       
        private string _strTitle;
        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return _strTitle;
            }
            set
            {
                _strTitle = value;
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindQuestion( );
                BindData( );
                if ( Header != null )
                    Title = StrTitle;
            }

        }

        protected void btnSave_Click( object sender, EventArgs e )
        {

            AccountsProtect model = new AccountsProtect( );
            model.ProtectID = IntParam;
            model.Question1 = TextFilter.FilterAll( CtrlHelper.GetSelectValue( ddlQuestion1 ) );
            model.Question2 = TextFilter.FilterAll( CtrlHelper.GetSelectValue( ddlQuestion2 ) );
            model.Question3 = TextFilter.FilterAll( CtrlHelper.GetSelectValue( ddlQuestion3 ) );
            model.Response1 = TextFilter.FilterAll( CtrlHelper.GetText( txtResponse1 ) );
            model.Response2 = TextFilter.FilterAll( CtrlHelper.GetText( txtResponse2 ) );
            model.Response3 = TextFilter.FilterAll( CtrlHelper.GetText( txtResponse3 ) );
            model.SafeEmail = TextFilter.FilterAll( CtrlHelper.GetText( txtSafeEmail ) );


            Message msg = new Message( );
            msg = aideAccountsFacade.UpdateAccountsProtect( model );

            if ( msg.Success )
            {
                MessageBox( "密保信息修改成功" );
            }
            else
            {
                MessageBox( msg.Content );
            }
        }
        protected void btnDel_Click( object sender, EventArgs e )
        {
            aideAccountsFacade.DeleteAccountsProtect( IntParam );
            MessageBox( "操作成功" );
            BindData( );
        }
        #endregion

        #region 数据加载

        private void BindQuestion( )
        {
            Protection protect = new Protection( TextUtility.GetRealPath( "/config/protection.xml" ) );
            List<string> pList = protect.GetProtectionQuestions( );
            ddlQuestion1.DataSource = pList;
            ddlQuestion1.DataBind( );
            ddlQuestion2.DataSource = pList;
            ddlQuestion2.DataBind( );
            ddlQuestion3.DataSource = pList;
            ddlQuestion3.DataBind( );

        }
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;

            //获取信息
            AccountsProtect accountProtect = aideAccountsFacade.GetAccountsProtectByPID( IntParam );
            if ( accountProtect == null )
            {
               // MessageBox( "用户密保信息不存在" );
                StrTitle = "用户密保信息不存在";
                btnSave.Enabled = false;
                btnDel.Enabled = false;
                return;
            }
            AccountsInfo account = aideAccountsFacade.GetAccountInfoByUserID( accountProtect.UserID );
            if ( account == null )
            {
                MessageBox( "用户信息不存在" );
                return;
            }
            StrTitle = "玩家-" + account.Accounts + "-密保信息";
           
            CtrlHelper.SetText( ltAccounts, account.Accounts.Trim( ) );
            CtrlHelper.SetText( txtSafeEmail, accountProtect.SafeEmail.Trim( ) );
            ddlQuestion1.SelectedValue = accountProtect.Question1;
            ddlQuestion2.SelectedValue = accountProtect.Question2;
            ddlQuestion3.SelectedValue = accountProtect.Question3;
            CtrlHelper.SetText( txtResponse1, accountProtect.Response1.Trim( ) );
            CtrlHelper.SetText( txtResponse2, accountProtect.Response2.Trim( ) );
            CtrlHelper.SetText( txtResponse3, accountProtect.Response3.Trim( ) );
            CtrlHelper.SetText( ltPassportID, accountProtect.PassportID.Trim( ) );
            CtrlHelper.SetText( ltPassportType, GetPassPortType(accountProtect.PassportType ));
            CtrlHelper.SetText( ltCreateIP, accountProtect.CreateIP.Trim( ) );
            CtrlHelper.SetText( ltModifyIP, accountProtect.ModifyIP.Trim( ) );
            CtrlHelper.SetText( ltCreateDate, accountProtect.CreateDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            CtrlHelper.SetText( ltModifyDate, accountProtect.ModifyDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
        }
        #endregion
    }
}
