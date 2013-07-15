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
    public partial class NewsInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                GameNewsDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        private void GameNewsDataBind()
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

            //获取类型信息
            News news = aideNativeWebFacade.GetNewsInfo(IntParam);
            if (news == null)
            {
                ShowError("新闻信息不存在");
                Redirect("NewsList.aspx");
                return;
            }
            ddlClassID.SelectedValue = news.ClassID.ToString().Trim();
            CtrlHelper.SetText(txtSubject, news.Subject);
            chkOnTop.Checked = news.OnTop == 1;
            chkOnTopAll.Checked = news.OnTopAll == 1;
            chkIsElite.Checked = news.IsElite == 1;
            chkIsHot.Checked = news.IsHot == 1;
            chkIsLock.Checked = news.IsLock == 1;
            CtrlHelper.SetText(txtLinkUrl, news.LinkUrl == "" ? "http://" : news.LinkUrl);
            chkIsLinks.Checked = news.IsLinks == 1;
            CtrlHelper.SetText(txtBody, news.Body);
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            News news = new News();
            news.ClassID = Convert.ToByte(ddlClassID.SelectedValue.Trim());
            news.Subject = CtrlHelper.GetText(txtSubject);
            news.OnTop = Convert.ToByte(chkOnTop.Checked);
            news.OnTopAll = Convert.ToByte(chkOnTopAll.Checked);
            news.IsElite = Convert.ToByte(chkIsElite.Checked);
            news.IsHot = Convert.ToByte(chkIsHot.Checked);
            news.IsLock = Convert.ToByte(chkIsLock.Checked);
            news.LinkUrl = CtrlHelper.GetText(txtLinkUrl);
            news.IsLinks = Convert.ToByte(chkIsLinks.Checked);
            news.Body = txtBody.Text.Trim();

            Message msg = new Message();
            if (StrCmd == "add")
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                news.UserID = userExt.UserID;
                news.IssueIP = Utility.UserIP;
                msg = aideNativeWebFacade.InsertNews(news);
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                news.NewsID = IntParam;
                news.LastModifyIP = Utility.UserIP;
                msg = aideNativeWebFacade.UpdateNews(news);
            }

            if (msg.Success)
            {
                if (StrCmd == "add")
                {
                    ShowInfo("新闻信息增加成功", "NewsList.aspx", 1200);
                }
                else
                {
                    ShowInfo("新闻信息修改成功", "NewsList.aspx", 1200);
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
