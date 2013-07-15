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
    public partial class GrantFlee : AdminPage
    {
        #region Fields
        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-清零积分";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.ClearFlee );
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
            int kindID = int.Parse( ddlGame.SelectedValue );


            if ( kindID <= 0 )
            {
                MessageBox( "请选择游戏" );
                return;
            }
            if ( string.IsNullOrEmpty( strReason ) )
            {
                MessageBox( "清零原因不能为空" );
                return;
            }
            AccountsInfo modelAccountInfo = new AccountsInfo( );
            string[ ] arrUserIDList = StrParamsList.Split( new char[ ] { ',' } );
            int count = 0;
            foreach ( string strid in arrUserIDList )
            {
                if ( Utils.Validate.IsPositiveInt( strid ) )
                {
                    modelAccountInfo = aideAccountsFacade.GetAccountInfoByUserID( int.Parse( strid ) );
                    if ( modelAccountInfo == null )
                        continue;
                    TreasureFacade tf = new TreasureFacade( kindID );
                    Message msg = tf.GrantFlee( int.Parse( strid ) , kindID , userExt.UserID , strReason , GameRequest.GetUserIP( ) );
                    if ( msg.Success )
                    {
                        count++;
                    }
                }
            }
            if ( count > 0 )
            {
                MessageBox( "所选用户共有" + count + "个用户逃跑记录，全部清除成功！" );
            }
            else
            {
                MessageBox( "所选用户没有有逃跑记录的用户" );
            }
        }
        #endregion

        #region 数据加载
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
        #endregion
    }
}
