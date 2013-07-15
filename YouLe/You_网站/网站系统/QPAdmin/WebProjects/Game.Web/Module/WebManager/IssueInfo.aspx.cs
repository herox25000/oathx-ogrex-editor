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
    public partial class IssueInfo : AdminPage
    {

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                GameIssueDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        private void GameIssueDataBind()
        {
            if (StrCmd == "add")
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

            //获取问题信息
            GameIssueInfo issue = aideNativeWebFacade.GetGameIssueInfo(IntParam);
            if (issue == null)
            {
                ShowError("问题信息不存在");
                Redirect("IssueList.aspx");
                return;
            }
            CtrlHelper.SetText(txtIssueTitle, issue.IssueTitle);
            rbtnNullity.SelectedValue = issue.Nullity.ToString().Trim();
            CtrlHelper.SetText(txtIssueContent, issue.IssueContent);
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            GameIssueInfo issue = new GameIssueInfo();
            issue.IssueTitle = CtrlHelper.GetText(txtIssueTitle);
            issue.IssueContent = CtrlHelper.GetText(txtIssueContent);
            issue.Nullity = Convert.ToByte(rbtnNullity.SelectedValue.Trim());

            Message msg = new Message();
            if (StrCmd == "add")
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                msg = aideNativeWebFacade.InsertGameIssue(issue);
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                issue.IssueID = IntParam;
                msg = aideNativeWebFacade.UpdateGameIssue(issue);
            }

            if (msg.Success)
            {
                if (StrCmd == "add")
                {
                    ShowInfo("问题信息增加成功", "IssueList.aspx", 1200);
                }
                else
                {
                    ShowInfo("问题信息修改成功", "IssueList.aspx", 1200);
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
