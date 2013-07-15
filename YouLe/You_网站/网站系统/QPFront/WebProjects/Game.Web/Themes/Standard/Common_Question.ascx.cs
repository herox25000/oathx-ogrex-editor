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
using Game.Facade;

namespace Game.Web.Themes.Standard
{
    public partial class Common_Question : System.Web.UI.UserControl
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
                BindIssueData();
            }
        }

        /// <summary>
        /// 问题列表
        /// </summary>
        private void BindIssueData()
        {
            this.rptIssueList.DataSource = webFacade.GetTopIssueList(5);
            this.rptIssueList.DataBind();
        }
    }
}