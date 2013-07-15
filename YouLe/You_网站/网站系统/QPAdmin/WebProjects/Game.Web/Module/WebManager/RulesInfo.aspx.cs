using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using Game.Entity.NativeWeb;
using Game.Entity.Enum;

namespace Game.Web.Module.WebManager
{
    public partial class RulesInfo : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender , EventArgs e )
        {
            if( !Page.IsPostBack )
            {
                BindKindList( );
                GameFeedbackDataBind( );
            }
        }

        protected void btnSave_Click( object sender , EventArgs e )
        {
            ProcessData( );
        }
        #endregion

        #region 数据加载

        //绑定游戏
        private void BindKindList( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameKindItemList( 1 , Int32.MaxValue , "" , "ORDER BY KindID ASC" );
            if( pagerSet.PageSet.Tables[ 0 ].Rows.Count > 0 )
            {
                ddlKind.DataSource = pagerSet.PageSet;
                ddlKind.DataTextField = "KindName";
                ddlKind.DataValueField = "KindID";
                ddlKind.DataBind( );
            }
        }

        private void GameFeedbackDataBind( )
        {
            if( StrCmd == "add" )
            {
                litInfo.Text = "新增";
            }
            else
            {
                litInfo.Text = "更新";
            }

            if( IntParam <= 0 )
            {
                return;
            }

            //获取规则信息
            GameRulesInfo gameRules = aideNativeWebFacade.GetGameRulesInfo( IntParam );
            if( gameRules == null )
            {
                ShowError( "规则信息不存在" );
                Redirect( "RulesList.aspx" );
                return;
            }
            ddlKind.SelectedValue = gameRules.KindID.ToString( ).Trim( );
            CtrlHelper.SetText( inImgRuleUrl , gameRules.ImgRuleUrl );
            CtrlHelper.SetText( txtHelpIntro , gameRules.HelpIntro );
            CtrlHelper.SetText( txtHelpRule , gameRules.HelpRule );
            CtrlHelper.SetText( txtHelpGrade , gameRules.HelpGrade );
            rbtnNullity.SelectedValue = gameRules.Nullity.ToString( ).Trim( );

            rbtnIsJoin.SelectedValue = gameRules.JoinIntro.ToString( ).Trim( );
            CtrlHelper.SetText( lblCollectDate , gameRules.CollectDate.ToString( ) );
            CtrlHelper.SetText( lblModifyDate , gameRules.ModifyDate.ToString( ) );

            StringBuffer bufferFileView = new StringBuffer( );

            //游戏截图
            if( !TextUtility.EmptyTrimOrNull( gameRules.ImgRuleUrl ) )
            {
                bufferFileView.InnerBuilder.AppendFormat( "setImgFilePath(\"frImgRuleUrl\",\"{0}\");" , gameRules.ImgRuleUrl );
                imgGame.ImageUrl = gameRules.ImgRuleUrl;
                trGameImage.Visible = true;
            }

            if( bufferFileView.Length > 0 )
            {
                bufferFileView.Replace( "'" , "\\'" );
                bufferFileView.Replace( "\r\n" , "" );
                ClientScript.RegisterStartupScript( this.GetType( ) , "" , "window.onload=function(){" + bufferFileView.ToString( ) + "}" , true );
            }
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            GameRulesInfo gameRules = new GameRulesInfo( );
            gameRules.KindID = Convert.ToInt32( ddlKind.SelectedValue.Trim( ) );
            gameRules.KindName = ddlKind.SelectedItem.Text;
            string imgUrl = CtrlHelper.GetText( inImgRuleUrl );
            if( string.IsNullOrEmpty( imgUrl ) )
            {
                ShowError( "请上传游戏截图" );
                return;
            }
            if( imgUrl.Contains( "http://" ) )
            {
                gameRules.ImgRuleUrl = imgUrl;
            }
            else
            {
                gameRules.ImgRuleUrl = "http://" + GameRequest.GetCurrentFullHost( ) + imgUrl;
            }
            gameRules.HelpIntro = CtrlHelper.GetText( txtHelpIntro );
            gameRules.HelpRule = CtrlHelper.GetText( txtHelpRule );
            gameRules.HelpGrade = CtrlHelper.GetText( txtHelpGrade );
            gameRules.JoinIntro = Convert.ToByte( rbtnIsJoin.SelectedValue.Trim( ) );
            gameRules.Nullity = Convert.ToByte( rbtnNullity.SelectedValue.Trim( ) );

            Message msg = new Message( );
            if( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Delete );
                if( aideNativeWebFacade.JudgeRulesIsExistence( gameRules.KindID ) )
                {
                    ShowError( "该游戏规则已存在" );
                    return;
                }
                msg = aideNativeWebFacade.InsertGameRules( gameRules );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                if( aideNativeWebFacade.JudgeRulesIsExistence( gameRules.KindID ) && gameRules.KindID != IntParam )
                {
                    ShowError( "该游戏规则已存在" );
                    return;
                }
                msg = aideNativeWebFacade.UpdateGameRules( gameRules , IntParam );
            }

            if( msg.Success )
            {
                if( StrCmd == "add" )
                {
                    ShowInfo( "规则增加成功" , "RulesList.aspx" , 1200 );
                }
                else
                {
                    ShowInfo( "规则修改成功" , "RulesList.aspx" , 1200 );
                }
            }
            else
            {
                ShowError( msg.Content );
            }
        }
        #endregion

    }
}
