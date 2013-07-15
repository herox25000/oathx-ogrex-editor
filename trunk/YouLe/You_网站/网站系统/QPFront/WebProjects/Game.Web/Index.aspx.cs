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

using Game.Entity.NativeWeb;
using Game.Entity.Platform;
using Game.Entity.Accounts;
using Game.Facade;
using Game.Kernel;
using Game.Utils;

namespace Game.Web
{
    public partial class Index : UCPageBase
    {
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
                UserLongout();

                BindNewsData();

                Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
                sHeader.title = "首页";
            }
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("首页 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 绑定新闻列表
        /// </summary>
        private void BindNewsData()
        {
            this.rptNews.DataSource = webFacade.GetTopNewsList(0, 0, 0, 5);
            this.rptNews.DataBind();
        }

        /// <summary>
        /// 获取新闻类型
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public string GetNewsType(object obj)
        {
            return Convert.ToInt32(obj) == 1 ? "新闻" : "公告";
           
        }

        /// <summary>
        /// 退出
        /// </summary>
        private void UserLongout()
        {
            string logout = GameRequest.GetQueryString("exit");
            if (logout == "true")
            {
                Fetch.DeleteUserCookie();
                Response.Redirect("/Index.aspx");
            }
        }
    }
}
