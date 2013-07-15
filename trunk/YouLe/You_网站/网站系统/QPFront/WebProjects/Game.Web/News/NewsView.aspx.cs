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

namespace Game.Web.News
{
    public partial class NewsView : UCPageBase
    {
        private NativeWebFacade webFacade = new NativeWebFacade();

        public string source = "";
        public string type = "";
        public string issueDate = "";
        public string title = "";
        public string content = "";

        private int XID = GameRequest.GetQueryInt("XID",0);

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                Entity.NativeWeb.News news = webFacade.GetNewsByNewsID(XID, 0);
                if (news != null)
                {
                    source = news.IsLinks == 1 ? news.LinkUrl : ApplicationSettings.Get( "title" );
                    type = news.ClassID == 1 ? "新闻" : "公告";
                    issueDate = news.IssueDate.ToString("yyyy-MM-dd HH:mm:ss");
                    title = news.Subject;
                    content = news.Body;

                    Entity.NativeWeb.News news1 = webFacade.GetNewsByNewsID(XID, 1);
                    if (news1 != null)
                    {
                        this.next1.Title = "上一篇新闻：" + news1.Subject;
                        this.next1.HRef = "NewsView.aspx?XID=" + news1.NewsID;

                        this.next2.Title = "上一篇新闻：" + news1.Subject;
                        this.next2.HRef = "NewsView.aspx?XID=" + news1.NewsID;
                    }
                    else
                    {
                        this.next1.Title = "已经是第一篇了！";
                        this.next1.Disabled = true;
                        this.next1.Visible = false;
                        this.next2.Title = "已经是第一篇了！";
                        this.next2.Disabled = true;
                        this.next2.Visible = false;
                    }

                    Entity.NativeWeb.News news2 = webFacade.GetNewsByNewsID(XID, 2);
                    if (news2 != null)
                    {
                        this.last1.Title = "下一篇新闻：" + news2.Subject;
                        this.last1.HRef = "NewsView.aspx?XID=" + news2.NewsID;

                        this.last2.Title = "下一篇新闻：" + news2.Subject;
                        this.last2.HRef = "NewsView.aspx?XID=" + news2.NewsID;
                    }
                    else
                    {
                        this.last1.Title = "已经是最后一篇了！";
                        this.last1.Disabled = true;
                        this.last1.Visible = false;
                        this.last2.Title = "已经是最后一篇了！";
                        this.last2.Disabled = true;
                        this.last2.Visible = false;
                    }
                }
            }
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "新闻公告";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            Entity.NativeWeb.News news = webFacade.GetNewsByNewsID(XID, 0);
            if (news != null)
            {
                AddMetaTitle(news.Subject + " - " + ApplicationSettings.Get("title"));
            }
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }
    }
}
