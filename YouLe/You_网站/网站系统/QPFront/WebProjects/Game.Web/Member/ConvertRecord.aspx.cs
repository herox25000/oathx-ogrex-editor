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
using Game.Entity.Record;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Member
{
    public partial class ConvertRecord : UCPageBase
    {
        #region 继承属性

        protected override bool IsAuthenticatedUser
        {
            get
            {
                return true;
            }
        }

        #endregion

        private AccountsFacade accountsFacade = new AccountsFacade();
        private RecordFacade recordFacade = new RecordFacade();

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                this.txtStartDate.Text = DateTime.Now.ToString("yyyy-MM-01");
                this.txtEndDate.Text = DateTime.Now.ToString("yyyy-MM-dd");

                DataBindInsure();
            }
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        /// <summary>
        /// 绑定查询数据
        /// </summary>
        private void DataBindInsure()
        {
            StringBuilder sWhere = new StringBuilder();
            sWhere.AppendFormat(" WHERE UserID = {0}", Fetch.GetUserCookie().UserID);

            sWhere.AppendFormat(" AND CollectDate >= '{0}' AND CollectDate <= '{1}'", CtrlHelper.GetText(txtStartDate) + " 00:00:00", CtrlHelper.GetText(txtEndDate) + " 23:59:59");

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = recordFacade.GetLovesRecord(sWhere.ToString(), sPageIndex, sPageSize);
            anpPage.RecordCount = pagerSet.RecordCount;

            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                rptLovesList.DataSource = pagerSet.PageSet;
                rptLovesList.DataBind();

                this.rptLovesList.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptLovesList.Visible = false;
                this.trNoData.Visible = true;
            }
        }


        protected void anpPage_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            DataBindInsure();
        }

        /// <summary>
        /// 查询按钮的事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnSelect_Click(object sender, EventArgs e)
        {
            anpPage.CurrentPageIndex = 1;
            DataBindInsure();
        }
    }
}
