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
    public partial class IssueList : UCPageBase
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
                BindIssueData();
            }
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "客服中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("常见问题 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        private void BindIssueData()
        {
            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = webFacade.GetIssueList(sPageIndex, sPageSize);
            anpPage.RecordCount = pagerSet.RecordCount;
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                this.rptIssueList.DataSource = pagerSet.PageSet;
                this.rptIssueList.DataBind();
            }
        }

        /// <summary>
        /// 分页事件
        /// </summary>
        /// <param name="src"></param>
        /// <param name="e"></param>
        protected void anpPage_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            BindIssueData();
        }

    }
}
