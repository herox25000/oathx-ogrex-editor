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
using Game.Entity.Record;


namespace Game.Web.Module.AccountManager
{
    public partial class RecordPasswdExpendConfirm : AdminPage
    {
        #region Fields

        /// <summary>
        /// 确认的密码类型
        /// </summary>
        protected int IntPassType
        {
            get
            {
                return GameRequest.GetQueryInt( "type", 0 );
            }
        }
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
                BindData( );
                if ( Header != null )
                    Title = StrTitle;
            }

        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            string strPass = CtrlHelper.GetText( txtConfirmPass );
            if ( string.IsNullOrEmpty( strPass ) )
            {
                MessageBox( "密码不能为空" );
                return;
            }
            if ( aideRecordFacade.ConfirmPass( IntParam, Utility.MD5( strPass ), IntPassType ) )
                MessageBox( "确认成功" );
            else
                MessageBox( "确认失败" );
        }
        #endregion

        #region 数据加载
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;

            //获取信息        
            RecordPasswdExpend pwExpend = aideRecordFacade.GetRecordPasswdExpendByRid( IntParam );
            if ( pwExpend == null )
            {
                MessageBox( "密码修改记录不存在" );
                btnSave.Enabled = false;
                return;
            }
            AccountsInfo account = aideAccountsFacade.GetAccountInfoByUserID( pwExpend.UserID );
            if ( account == null )
            {
                MessageBox( "用户不存在" );
                btnSave.Enabled = false;
                return;
            }
            StrTitle = "玩家-" + account.Accounts + "-确认密码信息";
            CtrlHelper.SetText( ltUserID, account.UserID.ToString( ) );
            CtrlHelper.SetText( ltAccounts, account.Accounts.Trim( ) );
        }
        #endregion
    }
}
