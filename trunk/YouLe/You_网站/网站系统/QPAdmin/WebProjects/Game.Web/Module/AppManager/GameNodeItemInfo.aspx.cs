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
    public partial class GameNodeItemInfo : AdminPage
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
                    txtNodeID.Text = ( aidePlatformFacade.GetMaxGameNodeID( ) + 1 ).ToString( );
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
        }
        //绑定节点
        private void BindNode( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameNodeItemList( 1, Int32.MaxValue, "", "ORDER BY NodeID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlJoin.DataSource = pagerSet.PageSet;
                ddlJoin.DataTextField = "NodeName";
                ddlJoin.DataValueField = "NodeID";
                ddlJoin.DataBind( );
            }
            ddlJoin.Items.Insert( 0, new ListItem( "无挂接", "0" ) );
        }
        private void BindData( )
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
                txtNodeID.Enabled = true;
            }
            else
            {
                litInfo.Text = "更新";
                txtNodeID.Enabled = false;
            }

            if ( IntParam <= 0 )
            {
                return;
            }

            //获取信息
            GameNodeItem gameNodeItem = aidePlatformFacade.GetGameNodeItemInfo( IntParam );
            if ( gameNodeItem == null )
            {
                ShowError( "节点信息不存在" );
                Redirect( "GameNodeItemList.aspx" );
                return;
            }

            CtrlHelper.SetText( txtNodeID, gameNodeItem.NodeID.ToString( ).Trim( ) );
            CtrlHelper.SetText( txtNodeName, gameNodeItem.NodeName.Trim( ) );
            ddlGameKind.SelectedValue = gameNodeItem.KindID.ToString( ).Trim( );
            ddlJoin.SelectedValue = gameNodeItem.JoinID.ToString( ).Trim( );
            CtrlHelper.SetText( txtSortID, gameNodeItem.SortID.ToString( ).Trim( ) );
            rbtnNullity.SelectedValue = gameNodeItem.Nullity.ToString( ).Trim( );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            string nodeID = CtrlHelper.GetText( txtNodeID );
            string sortID = CtrlHelper.GetText( txtSortID );
            if ( !Utils.Validate.IsPositiveInt( nodeID ) )
            {
                ShowError( "节点标识不规范，节点标识只能为正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( sortID ) )
            {
                ShowError( "排序不规范，排序只能为0或正整数" );
                return;
            }
            GameNodeItem gameNodeItem = new GameNodeItem( );
            gameNodeItem.NodeID = Convert.ToInt32( nodeID );
            gameNodeItem.NodeName = CtrlHelper.GetText( txtNodeName );
            gameNodeItem.KindID = int.Parse( ddlGameKind.SelectedValue );
            gameNodeItem.JoinID = int.Parse( ddlJoin.SelectedValue );
            gameNodeItem.SortID = Convert.ToInt32( sortID );
            gameNodeItem.Nullity = Convert.ToByte( rbtnNullity.SelectedValue.Trim( ) );

            Message msg = new Message( );
            if ( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( aidePlatformFacade.IsExistsNodeID( gameNodeItem.NodeID ) )
                {
                    ShowError( "节点标识已经存在" );
                    return;
                }
                msg = aidePlatformFacade.InsertGameNodeItem( gameNodeItem );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                msg = aidePlatformFacade.UpdateGameNodeItem( gameNodeItem );
            }

            if ( msg.Success )
            {
                if ( StrCmd == "add" )
                {
                    ShowInfo( "节点信息增加成功", "GameNodeItemList.aspx", 1200 );
                }
                else
                {
                    ShowInfo( "节点信息修改成功", "GameNodeItemList.aspx", 1200 );
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
