using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

using Game.Entity.Accounts;
using Game.Entity.NativeWeb;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Service
{
    public partial class FeedbackList : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade();
        private NativeWebFacade webFacade = new NativeWebFacade();

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Fetch.GetUserCookie() != null)
                {
                    this.txtAccounts.Text = Fetch.GetUserCookie().Accounts;
                }
                BindFeedBackData();
            }
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "客服中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("问题反馈 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        private void BindFeedBackData()
        {
            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = webFacade.GetFeedbacklist(sPageIndex, sPageSize);
            anpPage.RecordCount = pagerSet.RecordCount;

            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                this.rptFeedBackList.DataSource = pagerSet.PageSet;
                this.rptFeedBackList.DataBind();
            }
        }

        public string GetStringByObj(object obj, int len)
        {
            return obj.ToString().Length > len ? obj.ToString().Substring(0, len) + ".." : obj.ToString();
        }

        /// <summary>
        /// 分页事件
        /// </summary>
        /// <param name="src"></param>
        /// <param name="e"></param>
        protected void anpPage_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            BindFeedBackData();
        }

        protected void btnPublish_Click(object sender, EventArgs e)
        {
            if (txtAccounts.Text.Trim() != "")
            {
                Message umsg = accountsFacade.IsAccountsExist(CtrlHelper.GetText(txtAccounts));
                if (umsg.Success)
                {
                    Show("您输入的用户名不存在，请重新输入!");
                    this.txtAccounts.Text = "";
                    return;
                }
            }

            GameFeedbackInfo info = new GameFeedbackInfo();
            info.Accounts = txtAccounts.Text.Trim();
            info.FeedbackContent = TextFilter.FilterScript(txtContent.Text.Trim()).Replace("'", "\\'");
            info.FeedbackTitle = TextFilter.FilterScript(txtTitle.Text.Trim());
            info.ClientIP = GameRequest.GetUserIP();

            Message msg = webFacade.PublishFeedback(info);
            if (msg.Success)
            {
                ShowAndRedirect( "感谢您的问题反馈，我们将尽快给予回复，敬请留意！" , "/Service/FeedbackList.aspx" );
            }
            else
            {
                Show(msg.Content);
            }
        }
    }
}
