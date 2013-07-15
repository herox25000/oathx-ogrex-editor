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
    public partial class GameTypeItemInfo : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                if ( IntParam <= 0 && StrCmd.Equals( "add" ) )
                    txtTypeID.Text = ( aidePlatformFacade.GetMaxGameTypeID( ) + 1 ).ToString( );
                BindJoin( );
                GameTypeItemDataBind( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            ProcessData( );
        }
        #endregion

        #region 数据加载

        private void BindJoin( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameTypeItemList( 1, Int32.MaxValue, "", "ORDER BY TypeID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlJoin.DataSource = pagerSet.PageSet;
                ddlJoin.DataTextField = "TypeName";
                ddlJoin.DataValueField = "TypeID";
                ddlJoin.DataBind( );
            }
            ddlJoin.Items.Insert( 0, new ListItem( "无挂接", "0" ) );
        }

        private void GameTypeItemDataBind( )
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
                txtTypeID.Enabled = true;
            }
            else
            {
                litInfo.Text = "更新";
                txtTypeID.Enabled = false;
            }

            if ( IntParam <= 0 )
            {
                return;
            }

            //获取类型信息
            GameTypeItem gameTypeItem = aidePlatformFacade.GetGameTypeItemInfo( IntParam );
            if ( gameTypeItem == null )
            {
                ShowError( "类型信息不存在" );
                Redirect( "GameTypeItemList.aspx" );
                return;
            }

            CtrlHelper.SetText( txtTypeID, gameTypeItem.TypeID.ToString( ).Trim( ) );
            CtrlHelper.SetText( txtTypeName, gameTypeItem.TypeName.Trim( ) );
            ddlJoin.SelectedValue = gameTypeItem.JoinID.ToString( ).Trim( );
            CtrlHelper.SetText( txtSortID, gameTypeItem.SortID.ToString( ).Trim( ) );
            rbtnNullity.SelectedValue = gameTypeItem.Nullity.ToString( ).Trim( );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            string typeID = CtrlHelper.GetText( txtTypeID );
            string sortID = CtrlHelper.GetText( txtSortID );
            if ( !Utils.Validate.IsPositiveInt( typeID ) )
            {
                ShowError( "类型标识不规范，类型标识只能为正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( sortID ) )
            {
                ShowError( "排序输入不规范，排序只能为0或正整数" );
                return;
            }
            GameTypeItem gameTypeItem = new GameTypeItem( );
            gameTypeItem.TypeID = Convert.ToInt32( typeID );
            gameTypeItem.TypeName = CtrlHelper.GetText( txtTypeName );
            gameTypeItem.JoinID = int.Parse( ddlJoin.SelectedValue );
            gameTypeItem.SortID = CtrlHelper.GetInt( txtSortID, 0 );
            gameTypeItem.Nullity = Convert.ToByte( rbtnNullity.SelectedValue.Trim( ) );

            Message msg = new Message( );
            if ( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( aidePlatformFacade.IsExistsTypeID( gameTypeItem.TypeID ) )
                {
                    ShowError( "游戏类型标识已经存在" );
                    return;
                }
                msg = aidePlatformFacade.InsertGameTypeItem( gameTypeItem );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                msg = aidePlatformFacade.UpdateGameTypeItem( gameTypeItem );
            }

            if ( msg.Success )
            {
                if ( StrCmd == "add" )
                {
                    ShowInfo( "类型信息增加成功", "GameTypeItemList.aspx", 1200 );
                }
                else
                {
                    ShowInfo( "类型信息修改成功", "GameTypeItemList.aspx", 1200 );
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
