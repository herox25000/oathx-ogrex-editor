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
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Member
{
    public partial class SpreadIn : UCPageBase
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
        private TreasureFacade treasureFacade = new TreasureFacade();

        public string total = "";

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                this.txtStartDate.Text = DateTime.Now.ToString("yyyy-MM-01");
                this.txtEndDate.Text = DateTime.Now.ToString("yyyy-MM-dd");

                BindSpreaderData();
            }

            StringBuilder sWhere = new StringBuilder();
            sWhere.AppendFormat(" WHERE UserID = {0} AND Score > 0", Fetch.GetUserCookie().UserID);

            if (txtStartDate.Text.Trim() != "")
            {
                sWhere.AppendFormat(" AND CollectDate >= '{0}' ", CtrlHelper.GetText(txtStartDate) + " 00:00:00");
            }

            if (txtEndDate.Text.Trim() != "")
            {
                sWhere.AppendFormat(" AND CollectDate < '{0}'", Convert.ToDateTime(CtrlHelper.GetText(txtEndDate)).AddDays(1));
            }

            total = treasureFacade.GetUserSpreaderTotal(sWhere.ToString()).ToString("N");

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        private void BindSpreaderData()
        {
            StringBuilder sWhere = new StringBuilder();
            sWhere.AppendFormat(" WHERE UserID = {0} AND Score > 0 ", Fetch.GetUserCookie().UserID);

            if (txtStartDate.Text.Trim() != "")
            {
                sWhere.AppendFormat(" AND CollectDate >= '{0}' ", CtrlHelper.GetText(txtStartDate) + " 00:00:00");
            }

            if (txtEndDate.Text.Trim() != "")
            {
                sWhere.AppendFormat(" AND CollectDate < '{0}'", Convert.ToDateTime(CtrlHelper.GetText(txtEndDate)).AddDays(1));
            }

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = treasureFacade.GetSpreaderRecord(sWhere.ToString(), sPageIndex, sPageSize);
            anpPage.RecordCount = pagerSet.RecordCount;

            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                this.rptSpreaderList.DataSource = pagerSet.PageSet;
                this.rptSpreaderList.DataBind();

                this.rptSpreaderList.Visible = true;
                this.divTotal.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptSpreaderList.Visible = false;
                this.divTotal.Visible = false;
                this.trNoData.Visible = true;
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
            BindSpreaderData();
        }

        /// <summary>
        /// 查询按钮的事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnSelect_Click(object sender, EventArgs e)
        {
            anpPage.CurrentPageIndex = 1;
            BindSpreaderData();
        }
    }
}
