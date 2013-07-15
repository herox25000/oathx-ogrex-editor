using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using Game.Entity.NativeWeb;
using Game.Entity.Enum;

namespace Game.Web.Module.WebManager
{
    public partial class FeedbackInfo : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                GameFeedbackDataBind( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            ProcessData( );
        }
        #endregion

        #region 数据加载

        private void GameFeedbackDataBind( )
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
            }
            else
            {
                litInfo.Text = "更新";
            }

            if ( IntParam <= 0 )
            {
                return;
            }

            //获取反馈信息
            GameFeedbackInfo feedback = aideNativeWebFacade.GetGameFeedbackInfo( IntParam );
            if ( feedback == null )
            {
                ShowError( "反馈信息不存在" );
                Redirect( "FeedbackList.aspx" );
                return;
            }
            CtrlHelper.SetText( lblFeedbackTitle, feedback.FeedbackTitle );
            CtrlHelper.SetText( lblFeedbackContent, feedback.FeedbackContent );
            CtrlHelper.SetText( lblAccounts, feedback.Accounts );
            CtrlHelper.SetText( lblFeedbackDate, feedback.FeedbackDate.ToString( ) );
            CtrlHelper.SetText( lblClientIP, feedback.ClientIP );
            CtrlHelper.SetText( lblViewCount, feedback.ViewCount.ToString( ) );
            CtrlHelper.SetText( txtRevertContent, feedback.RevertContent );
            CtrlHelper.SetText( lblRevertUserID, GetMasterName( feedback.RevertUserID ) );
            CtrlHelper.SetText( lblRevertDate, feedback.RevertUserID == 0 ? "" : feedback.RevertDate.ToString( ) );
            rbtnNullity.SelectedValue = feedback.Nullity.ToString( );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            GameFeedbackInfo feedback = new GameFeedbackInfo( );
            feedback.RevertContent = CtrlHelper.GetText( txtRevertContent );
            feedback.RevertUserID = userExt.UserID;
            feedback.RevertDate = DateTime.Now;
            feedback.Nullity = Convert.ToByte( rbtnNullity.SelectedValue.Trim( ) );

            Message msg = new Message( );
            if ( StrCmd == "edit" )
            {
                feedback.FeedbackID = IntParam;
                msg = aideNativeWebFacade.RevertGameFeedback( feedback );
            }

            if ( msg.Success )
            {
                ShowInfo( "反馈信息回复成功", "FeedbackList.aspx", 1200 );
            }
            else
            {
                ShowError( msg.Content );
            }
        }
        #endregion
    }
}
