using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Platform;
using Game.Kernel;
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class GamePageItemInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindGameKindList( );
                BindNode( );
                BindData( );
                if ( IntParam <= 0 && StrCmd.Equals( "add" ) )
                    txtPageID.Text = ( aidePlatformFacade.GetMaxGamePageID( ) + 1 ).ToString( );

            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            ProcessData( );
        }
        #endregion

        #region 数据加载

        //绑定游戏
        private void BindGameKindList( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameKindItemList( 1, Int32.MaxValue, "", "ORDER BY KindID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlGameKind.DataSource = pagerSet.PageSet;
                ddlGameKind.DataTextField = "KindName";
                ddlGameKind.DataValueField = "KindID";
                ddlGameKind.DataBind( );
            }
            ddlGameKind.Items.Insert( 0, new ListItem( "无挂接", "0" ) );
        }
        //绑定节点
        private void BindNode( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameNodeItemList( 1, Int32.MaxValue, "", "ORDER BY NodeID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlNode.DataSource = pagerSet.PageSet;
                ddlNode.DataTextField = "NodeName";
                ddlNode.DataValueField = "NodeID";
                ddlNode.DataBind( );
            }
            ddlNode.Items.Insert( 0, new ListItem( "无挂接", "0" ) );
        }
        private void BindData( )
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
                txtPageID.Enabled = true;
            }
            else
            {
                litInfo.Text = "更新";
                txtPageID.Enabled = false;
            }

            if ( IntParam <= 0 )
            {
                return;
            }

            //获取信息
            GamePageItem gamePageItem = aidePlatformFacade.GetGamePageItemInfo( IntParam );
            if ( gamePageItem == null )
            {
                ShowError( "页面信息不存在" );
                Redirect( "GamePageItemList.aspx" );
                return;
            }

            CtrlHelper.SetText( txtPageID, gamePageItem.PageID.ToString( ).Trim( ) );
            CtrlHelper.SetText( txtPageName, gamePageItem.DisplayName.Trim( ) );
            ddlGameKind.SelectedValue = gamePageItem.KindID.ToString( ).Trim( );
            ddlNode.SelectedValue = gamePageItem.NodeID.ToString( ).Trim( );
            ddlOperateType.SelectedValue = gamePageItem.OperateType.ToString( ).Trim( );
            CtrlHelper.SetText( txtSortID, gamePageItem.SortID.ToString( ).Trim( ) );
            CtrlHelper.SetText( txtResponseUrl, gamePageItem.ResponseUrl.ToString( ).Trim( ) );
            rbtnNullity.SelectedValue = gamePageItem.Nullity.ToString( ).Trim( );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {

            string pageID = CtrlHelper.GetText( txtPageID );
            string sortID = CtrlHelper.GetText( txtSortID );
            if ( !Utils.Validate.IsPositiveInt( pageID ) )
            {
                ShowError( "页面标识不规范，页面标识只能为正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( sortID ) )
            {
                ShowError( "排序不规范，排序只能为0或正整数" );
                return;
            }
            GamePageItem gamePageItem = new GamePageItem( );
            gamePageItem.PageID = Convert.ToInt32( pageID );
            gamePageItem.DisplayName = CtrlHelper.GetText( txtPageName );
            gamePageItem.KindID = int.Parse( ddlGameKind.SelectedValue );
            gamePageItem.NodeID = int.Parse( ddlNode.SelectedValue );
            gamePageItem.OperateType = int.Parse( ddlOperateType.SelectedValue );
            gamePageItem.SortID = Convert.ToInt32( sortID );
            gamePageItem.ResponseUrl = CtrlHelper.GetText( txtResponseUrl );
            gamePageItem.Nullity = Convert.ToByte( rbtnNullity.SelectedValue.Trim( ) );

            Message msg = new Message( );
            if ( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( aidePlatformFacade.IsExistsPageID( gamePageItem.PageID ) )
                {
                    ShowError( "页面标识已经存在" );
                    return;
                }
                msg = aidePlatformFacade.InsertGamePageItem( gamePageItem );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                msg = aidePlatformFacade.UpdateGamePageItem( gamePageItem );
            }

            if ( msg.Success )
            {
                if ( StrCmd == "add" )
                {
                    ShowInfo( "页面信息增加成功", "GamePageItemList.aspx", 1200 );
                }
                else
                {
                    ShowInfo( "页面信息修改成功", "GamePageItemList.aspx", 1200 );
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
