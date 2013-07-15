using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using Game.Entity.GameMatch;
using Game.Entity.Enum;

namespace Game.Web.Module.WebManager
{
    public partial class MatchInfo : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindData( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            ProcessData( );
        }
        #endregion

        #region 数据加载

        private void BindData( )
        {
            if ( IntParam <= 0 )
            {
                return;
            }

            //获取问题信息
            string commandText = "SELECT * FROM MatchInfo Where MatchID =" + IntParam;
            Game.Entity.GameMatch.MatchInfo matchInfo = aideGameMatchFacade.GetEntity<Game.Entity.GameMatch.MatchInfo>( commandText );
            if ( matchInfo == null )
            {
                ShowError( "比赛信息不存在" );
                Redirect( "MatchList.aspx" );
                return;
            }
            CtrlHelper.SetText( txtMatchTitle, matchInfo.MatchName );
            CtrlHelper.SetText( txtMatchSummary, matchInfo.MatchSummary );
            CtrlHelper.SetText( txtMatchDate , matchInfo.MatchDate );
            rbtnNullity.SelectedValue = matchInfo.Nullity.ToString( ).Trim( );
            rblMatchStatus.SelectedValue = matchInfo.MatchStatus.ToString( ).Trim( );
            CtrlHelper.SetText( txtContent, matchInfo.MatchContent );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {

            Game.Entity.GameMatch.MatchInfo matchInfo = new Game.Entity.GameMatch.MatchInfo( );
            matchInfo.MatchName = CtrlHelper.GetText( txtMatchTitle );
            matchInfo.MatchSummary = CtrlHelper.GetText( txtMatchSummary );
            matchInfo.MatchDate = CtrlHelper.GetText( txtMatchDate );
            matchInfo.Nullity = byte.Parse( rbtnNullity.SelectedValue );
            matchInfo.MatchStatus = byte.Parse( rblMatchStatus.SelectedValue );
            matchInfo.MatchContent = txtContent.Text;

            if ( IntParam <= 0 )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                try
                {
                    aideGameMatchFacade.InsertMatchInfo( matchInfo );
                    ShowInfo( "增加成功", "MatchList.aspx", 1200 );
                }
                catch 
                {
                    ShowError( "增加失败" );
                }
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                try
                {
                    matchInfo.MatchID = IntParam;
                    aideGameMatchFacade.UpdateMatchInfo( matchInfo );
                    ShowInfo( "修改成功" );
                }
                catch
                {
                    ShowError( "修改失败" );
                }
            }
        }
        #endregion
    }
}
