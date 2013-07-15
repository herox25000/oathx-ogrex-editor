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
    public partial class IssueView : UCPageBase
    {
        private NativeWebFacade webFacade = new NativeWebFacade();
        private int issueID = GameRequest.GetQueryInt("XID", 0);

        public string title = "";
        public string content = "";

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                GameIssueInfo issure = webFacade.GetIssueByIssueID(issueID, 0);
                if (issure != null)
                {
                    title = issure.IssueTitle;
                    content = Utility.HtmlDecode(issure.IssueContent);
                }

                GameIssueInfo issure1 = webFacade.GetIssueByIssueID(issueID, 1);
                if (issure1 != null)
                {
                    this.linLast1.Title = "上一篇新闻：" + issure1.IssueTitle;
                    this.linLast1.HRef = "/Service/IssueView.aspx?XID=" + issure1.IssueID;

                    this.linLast2.Title = "上一篇新闻：" + issure1.IssueTitle;
                    this.linLast2.HRef = "/Service/IssueView.aspx?XID=" + issure1.IssueID;
                }
                else
                {
                    this.linLast1.Title = "已经是第一篇了！";
                    this.linLast1.Disabled = true;
                    this.linLast1.Visible = false;

                    this.linLast2.Title = "已经是第一篇了！";
                    this.linLast2.Disabled = true;
                    this.linLast2.Visible = false;
                }

                GameIssueInfo issure2 = webFacade.GetIssueByIssueID(issueID, 2);
                if (issure2 != null)
                {
                    this.linNext1.Title = "下一篇新闻：" + issure2.IssueTitle;
                    this.linNext1.HRef = "/Service/IssueView.aspx?XID=" + issure2.IssueID;

                    this.linNext2.Title = "下一篇新闻：" + issure2.IssueTitle;
                    this.linNext2.HRef = "/Service/IssueView.aspx?XID=" + issure2.IssueID;
                }
                else
                {
                    this.linNext1.Title = "已经是最后一篇了！";
                    this.linNext1.Disabled = true;
                    this.linNext1.Visible = false;
                    this.linNext2.Title = "已经是最后一篇了！";
                    this.linNext2.Disabled = true;
                    this.linNext2.Visible = false;
                }
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "客服中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            GameIssueInfo issure = webFacade.GetIssueByIssueID(issueID, 0);
            if (issure != null)
            {
                AddMetaTitle(issure.IssueTitle + " - " + ApplicationSettings.Get("title"));
            }
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }
    }
}
