using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Kernel;
using Game.Entity.PlatformManager;
using Game.Entity.Enum;


namespace Game.Web.Module.BackManager
{
    public partial class BaseRoleInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                GameRoleDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        private void GameRoleDataBind()
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
            }
            else
            {
                litInfo.Text = "更新";
            }

            if (IntParam <= 0)
            {
                return;
            }

            //获取角色信息
            Base_Roles role = aidePlatformManagerFacade.GetRoleInfo( IntParam );
            if (role == null)
            {
                ShowError("角色信息不存在");
                Redirect("BaseRoleInfo.aspx");
                return;
            }
            CtrlHelper.SetText(txtRoleName, role.RoleName);
            CtrlHelper.SetText(txtDescription, role.Description);
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            Base_Roles role = new Base_Roles();
            role.RoleName = CtrlHelper.GetText(txtRoleName);
            role.Description = CtrlHelper.GetText(txtDescription);

            Message msg = new Message();
            if ( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                msg = aidePlatformManagerFacade.InsertRole( role );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                role.RoleID = IntParam;
                msg = aidePlatformManagerFacade.UpdateRole( role );
            }

            if (msg.Success)
            {
                if ( StrCmd == "add" )
                {
                    ShowInfo("角色信息增加成功", "BaseRoleList.aspx", 1200);
                }
                else
                {
                    ShowInfo("角色信息修改成功", "BaseRoleList.aspx", 1200);
                }
            }
            else
            {
                ShowError(msg.Content);
            }
        }
        #endregion        
    }
}
