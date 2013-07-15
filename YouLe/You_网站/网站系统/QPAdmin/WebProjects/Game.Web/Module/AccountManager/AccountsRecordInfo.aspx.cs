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


namespace Game.Web.Module.AccountManager
{
    public partial class AccountsRecordInfo : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-记录信息";
            }
        }

        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
            {
                BindData( );
            }
        }

        #endregion

        #region 数据加载
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;
            //获取信息
            AccountsInfo account = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            if ( account == null )
            {
                MessageBox( "用户信息不存在" );
                return;
            }

            CtrlHelper.SetText( ltGameID, account.GameID.ToString( ) );
            CtrlHelper.SetText( ltAccounts, account.Accounts.Trim( ) );

        }
        #endregion
    }
}
