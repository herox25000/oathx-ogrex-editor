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
    public partial class BaseUserUpdate : AdminPage
    {

        #region 重写父类方法

        //验证页面权限
        protected override void AuthUserPagePermission( )
        {
            if ( userExt.UserID != id )
            {
                Redirect( "/NotPower.html" );
            }
        }

        #endregion

        #region Fields

        int id = GameRequest.GetQueryInt("id", 0);
        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                GameUserDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        private void GameUserDataBind()
        {
            //验证数据
            if (id <= 0)
            {
                return;
            }

            //获取用户信息
            Base_Users user = aidePlatformManagerFacade.GetUserByUserID( id );
            if (user == null)
            {
                MessageBox("用户信息不存在");
                return;
            }
            CtrlHelper.SetText(lblAccounts, user.Username);
            CtrlHelper.SetText(lblRoleID, GetRoleName(user.RoleID));
            CtrlHelper.SetText(hdfOldLogonPass, user.Password);
            CtrlHelper.SetText(lblLoginTimes, user.LoginTimes.ToString());
            CtrlHelper.SetText(lblLastLogonIP, IPQuery.GetAddressWithIP(user.LastLoginIP));
            CtrlHelper.SetText(lblLastLogonDate, user.LastLogintime.ToString());
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            #region 检查密码

            string oldLogonPass = Utility.MD5(CtrlHelper.GetText(txtOldLogonPass));
            string oldConfirmLogonPass = CtrlHelper.GetText(hdfOldLogonPass);
            string logonPass = CtrlHelper.GetText(txtLogonPass);
            string confirmlogonPass = CtrlHelper.GetText(txtConfirmLogonPass);
            if (oldLogonPass != oldConfirmLogonPass)
            {
                MessageBox("原始密码输入错误！");
                return;
            }
            if (logonPass == "")
            {
                MessageBox("新密码不能为空！");
                return;
            }
            if (logonPass != confirmlogonPass)
            {
                MessageBox("两次输入的密码不一样，请重新输入！");
                return;
            }
            #endregion

            Base_Users user = new Base_Users();
            user.UserID = id;
            Message msg = new Message();
            msg = aidePlatformManagerFacade.ModifyUserLogonPass( user, oldConfirmLogonPass, logonPass );

            if (msg.Success)
            {
                MessageBoxClose("密码修改成功！");
            }
            else
            {
                MessageBox(msg.Content);
            }
        }
        #endregion        
    }
}
