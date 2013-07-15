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
using System.Data;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class GrantGameID : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-赠送靓号";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.GrantGameID );
            if ( !IsPostBack )
            {
                if ( Header != null )
                    Title = StrTitle;
                BindData( );
            }

        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            string strReason = CtrlHelper.GetText( txtReason );
            int gameID = CtrlHelper.GetInt( txtGameID, 0 );
            if ( IntParam <= 0 )
                return;
            if ( gameID <= 0 )
            {
                MessageBox( "靓号ID不正确" );
                return;
            }
            if ( string.IsNullOrEmpty( strReason ) )
            {
                MessageBox( "赠送原因不能为空" );
                return;
            }

            Message msg = aideRecordFacade.GrantGameID( IntParam, gameID, userExt.UserID, strReason, GameRequest.GetUserIP( ) );
            if ( msg.Success )
                MessageBox( "确认成功" );
            else
            {
                string strMessage = "";
                int intMsgID = msg.MessageID;
                switch ( intMsgID )
                {                   
                    case 2:
                        strMessage = "抱歉，赠送的靓号已被使用，请更换！";
                        break;
                    case 1:
                        strMessage = "抱歉，赠送的靓号不存在！";
                        break;
                    default:
                        strMessage = "抱歉，未知服务器错误！";
                        break;
                }
                MessageBox( strMessage );
            }
                
        }
        #endregion

        #region 数据加载
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;
            //获取信息
            AccountsInfo model = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            if ( model == null )
            {
                MessageBox( "用户信息不存在" );
                return;
            }

            CtrlHelper.SetText( ltUserID, model.UserID.ToString( ) );
            CtrlHelper.SetText( ltAccounts, model.Accounts.Trim( ) );

            // 读取靓号
            DataSet ds = aideAccountsFacade.GetReserveIdentifierList( );
            if ( ds.Tables[0].Rows.Count <= 0 )
                return;
            ddlGameID.DataSource = ds.Tables[0];
            ddlGameID.DataTextField = "GameID";
            ddlGameID.DataValueField = "GameID";
            ddlGameID.DataBind( );
        }
        #endregion
    }
}
