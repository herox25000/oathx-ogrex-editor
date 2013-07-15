using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Facade;
using Game.Entity.Platform;
using Game.Entity.Enum;
using Game.Kernel;
using System.Collections;
using System.Text;

namespace Game.Web.Module.AppManager
{
    public partial class GlobalPlayPresentInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindGameRoom( );//绑定房间
                BindMemberOrder( );//绑定会员
                BindData( );
            }
        }

        #endregion

        #region 处理方法

        protected void btnSave_Click( object sender, EventArgs e )
        {
            GlobalPlayPresent present;
            if ( IntParam == 0 )
            {
                present = new GlobalPlayPresent( );
            }
            else
            {
                present = aidePlatformFacade.GetGlobalPlayPresentInfo( IntParam );
                if ( present == null )
                    return;
            }
            if ( IntParam == -3 )
                present.ServerID = IntParam;
            else
                present.ServerID = int.Parse( ddlGameRoom.SelectedValue.ToString( ) );
            StringBuilder sb = new StringBuilder( );
            foreach ( ListItem item in ckbMemberOrder.Items )
            {
                if ( item.Selected )
                    sb.AppendFormat( "{0},", item.Value );

            }
            present.PresentMember = sb.ToString( ).TrimEnd( new char[ ] { ',' } );
            present.MaxPresent = CtrlHelper.GetInt( txtMaxPresent, 0 );
            present.MaxDatePresent = CtrlHelper.GetInt( txtMaxDatePresent, 0 );
            present.CellPlayPresnet = CtrlHelper.GetInt( txtCellPlayPresnet, 0 );
            present.CellPlayTime = CtrlHelper.GetInt( txtCellPlayTime, 0 );
            present.StartPlayTime = CtrlHelper.GetInt( txtStartPlayTime, 0 );
            present.CellOnlinePresent = CtrlHelper.GetInt( txtCellOnlinePresent, 0 );
            present.CellOnlineTime = CtrlHelper.GetInt( txtCellOnlineTime, 0 );
            present.StartOnlineTime = CtrlHelper.GetInt( txtStartOnlineTime, 0 );
            present.IsPlayPresent = ( byte ) ( ckbIsPlayPresent.Checked ? 1 : 0 );
            present.IsOnlinePresent = ( byte ) ( ckbIsOnlinePresent.Checked ? 1 : 0 );
            present.CollectDate = DateTime.Now;
            if ( IntParam == 0 )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( aidePlatformFacade.GetGlobalPlayPresentInfo( present.ServerID ) != null )
                {
                    ShowError( "该房间的泡点设置已存在" );
                    return;
                }
                aidePlatformFacade.InsertGlobalPlayPresent( present );
                ShowInfo( "新增成功" );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                if ( aidePlatformFacade.GetGlobalPlayPresentInfo( present.ServerID ) != null && IntParam != present.ServerID )
                {
                    ShowError( "该房间的泡点设置已存在" );
                    return;
                }
                aidePlatformFacade.UpdateGlobalPlayPresent( present );
                ShowInfo( "更新成功" );
            }
        }

        #endregion

        #region 数据加载
        //
        private void BindMemberOrder( )
        {
            IList<EnumDescription> arrMemberOrder = MemberOrderHelper.GetMemberOrderStatusList( typeof( MemberOrderStatus ) );
            ckbMemberOrder.DataSource = arrMemberOrder;
            ckbMemberOrder.DataValueField = "EnumValue";
            ckbMemberOrder.DataTextField = "Description";
            ckbMemberOrder.DataBind( );
        }
        private void BindGameRoom( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameRoomInfoList( 1, int.MaxValue, "", "ORDER BY ServerID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlGameRoom.DataSource = pagerSet.PageSet;
                ddlGameRoom.DataTextField = "ServerName";
                ddlGameRoom.DataValueField = "ServerID";
                ddlGameRoom.DataBind( );
            }
            ddlGameRoom.Items.Insert( 0, new ListItem( "积分房间", "-2" ) );
            ddlGameRoom.Items.Insert( 1, new ListItem( "金币房间", "-1" ) );
        }
        private void BindData( )
        {
            if ( IntParam == 0 )
            {
                phPresent.Visible = true;
                phMaxPresent.Visible = false;
                return;
            }
            else
            {
                ddlGameRoom.Enabled = false;
            }
            GlobalPlayPresent globalPlayPresent = aidePlatformFacade.GetGlobalPlayPresentInfo( IntParam );
            if ( globalPlayPresent == null  )
            {
                return;
            }
            if ( IntParam == -3 )
            {
                CtrlHelper.SetText( txtMaxDatePresent, globalPlayPresent.MaxDatePresent.ToString( ) );
                CtrlHelper.SetText( txtMaxPresent, globalPlayPresent.MaxPresent.ToString( ) );
                phMaxPresent.Visible = true;
                phPresent.Visible = false;
                return;
            }
            phPresent.Visible = true;
            phMaxPresent.Visible = false;
            ddlGameRoom.SelectedValue = globalPlayPresent.ServerID.ToString( );
            string[ ] arrMemberOrder = globalPlayPresent.PresentMember.Split( new char[ ] { ',' }, StringSplitOptions.RemoveEmptyEntries );
            ArrayList list = new ArrayList( arrMemberOrder );
            foreach ( ListItem item in ckbMemberOrder.Items )
            {
                item.Selected = list.Contains( item.Value );
            }

            CtrlHelper.SetText( txtCellPlayPresnet, globalPlayPresent.CellPlayPresnet.ToString( ) );
            CtrlHelper.SetText( txtCellPlayTime, globalPlayPresent.CellPlayTime.ToString( ) );
            CtrlHelper.SetText( txtStartPlayTime, globalPlayPresent.StartPlayTime.ToString( ) );

            CtrlHelper.SetText( txtCellOnlinePresent, globalPlayPresent.CellOnlinePresent.ToString( ) );
            CtrlHelper.SetText( txtCellOnlineTime, globalPlayPresent.CellOnlineTime.ToString( ) );
            CtrlHelper.SetText( txtStartOnlineTime, globalPlayPresent.StartOnlineTime.ToString( ) );
            CtrlHelper.SetText( ltCollectDate, globalPlayPresent.CollectDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            ckbIsPlayPresent.Checked = globalPlayPresent.IsPlayPresent == 1;
            ckbIsOnlinePresent.Checked = globalPlayPresent.IsOnlinePresent == 1;
        }
        #endregion
    }
}
