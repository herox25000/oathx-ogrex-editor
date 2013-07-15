using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;

using Game.Web.UI;
using Game.Utils;
using Game.Kernel;
using Game.Entity.PlatformManager;
using Game.Entity.Enum;


namespace Game.Web.Module.BackManager
{
    public partial class BaseUserInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                GetUserRoleList( );
                GameUserDataBind( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            ProcessData( );
        }
        #endregion

        #region 数据加载

        //绑定角色
        private void GetUserRoleList( )
        {
            PagerSet pagerSet = aidePlatformManagerFacade.GetRoleList( 1, Int32.MaxValue, "", "ORDER BY RoleID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlRole.DataSource = pagerSet.PageSet;
                ddlRole.DataTextField = "RoleName";
                ddlRole.DataValueField = "RoleID";
                ddlRole.DataBind( );
            }
        }

        private void GameUserDataBind( )
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
                txtAccounts.Enabled = true;
            }
            else
            {
                litInfo.Text = "更新";
                txtAccounts.Enabled = false;
            }

            if ( IntParam <= 0 )
            {
                return;
            }

            //获取用户信息
            Base_Users user = aidePlatformManagerFacade.GetUserByUserID( IntParam );
            if ( user == null )
            {
                ShowError( "用户信息不存在" );
                Redirect( "BaseUserList.aspx" );
                return;
            }
            CtrlHelper.SetText( txtAccounts, user.Username );
            txtLogonPass.Attributes.Add( "value", "********" );
            txtConfirmPass.Attributes.Add( "value", "********" );
            CtrlHelper.SetText( hidfLogonPass, user.Password );
            ddlRole.SelectedValue = user.RoleID.ToString( ).Trim( );
            rbtnNullity.SelectedValue = user.Nullity.ToString( );
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            Base_Users user = new Base_Users( );
            user.Username = CtrlHelper.GetText( txtAccounts );
            user.IsBand = 1;//未绑定IP
            user.Nullity = byte.Parse( rbtnNullity.SelectedValue );
            if ( hidfLogonPass.Value.Trim( ) == "********" )
            {
                user.Password = Utility.MD5( txtLogonPass.Text.Trim( ) );
            }
            else
            {
                user.Password = hidfLogonPass.Value.Trim( );
            }
            user.RoleID = Convert.ToInt32( ddlRole.SelectedValue.Trim( ) );


            Message msg = new Message( );
            if ( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                user.LastLoginIP = Utility.UserIP;
                msg = aidePlatformManagerFacade.Register( user );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                user.UserID = IntParam;
                msg = aidePlatformManagerFacade.ModifyUserInfo( user );
            }

            if ( msg.Success )
            {
                if ( StrCmd == "add" )
                {
                    ShowInfo( "用户信息增加成功", "BaseUserList.aspx", 1200 );
                }
                else
                {
                    ShowInfo( "用户信息修改成功", "BaseUserList.aspx", 1200 );
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
