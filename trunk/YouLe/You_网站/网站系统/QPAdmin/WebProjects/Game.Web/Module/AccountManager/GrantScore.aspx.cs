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
using System.Text;
using Game.Facade;
using System.Data;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class GrantScore : AdminPage
    {
        #region Fields


        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-赠送积分";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.GrantScore );
            if ( !IsPostBack )
            {
                if ( Header != null )
                    Title = StrTitle;
                BindGameInfo( );
            }
        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            string strReason = CtrlHelper.GetText( txtReason );
            int score = CtrlHelper.GetInt( txtScore, 0 );
            int kindID = int.Parse( ddlGame.SelectedValue );

            if ( score == 0 )
            {
                MessageBox( "赠送积分不能为零" );
                return;
            }
            if( kindID <= 0)
            {
                MessageBox( "请选择游戏" );
                return;
            }
            if ( string.IsNullOrEmpty( strReason ) )
            {
                MessageBox( "赠送原因不能为空" );
                return;
            }

            AccountsInfo modelAccountInfo = new AccountsInfo( );
            string[ ] arrUserIDList = StrParamsList.Split( new char[ ] { ',' } );
            foreach ( string strid in arrUserIDList )
            {
                if ( Utils.Validate.IsPositiveInt( strid ) )
                {
                    modelAccountInfo = aideAccountsFacade.GetAccountInfoByUserID( int.Parse( strid ) );
                    if ( modelAccountInfo == null )
                        continue;

                    new TreasureFacade( kindID ).GrantScore( int.Parse( strid ), kindID, score, userExt.UserID, strReason, GameRequest.GetUserIP( ) );
                }
            }
            MessageBox( "确认成功" );
        }
        #endregion
        private void BindGameInfo( )
        {
            DataSet ds = aidePlatformFacade.GetGameList( );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                ddlGame.DataSource = ds.Tables[0];
                ddlGame.DataTextField = "KindName";
                ddlGame.DataValueField = "KindID";
                ddlGame.DataBind( );
            }
            ddlGame.Items.Insert( 0, new ListItem( "选择游戏", "0" ) );
        }
    }
}
