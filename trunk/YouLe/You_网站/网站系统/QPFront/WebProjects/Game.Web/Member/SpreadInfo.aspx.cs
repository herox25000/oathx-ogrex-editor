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
    public partial class SpreadInfo : UCPageBase
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

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindSpreaderInfoData();

                this.divContribution.Visible = false;

                ViewState["ChildrenID"] = "";
            }

            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        private void BindSpreaderInfoData()
        {
            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            DataSet ds = treasureFacade.GetUserSpreaderList(Fetch.GetUserCookie().UserID, sPageIndex, sPageSize);
            anpPage.RecordCount = Utility.StrToInt(ds.Tables[0].Rows[0]["Records"], 0);

            if (ds.Tables[1].Rows.Count > 0)
            {
                this.rptSpreaderList.DataSource = ds.Tables[1];
                this.rptSpreaderList.DataBind();

                this.rptSpreaderList.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptSpreaderList.Visible = false;
                this.trNoData.Visible = true;
            }
        }

        public string GetGameIDByUserID(int userID)
        {
            return accountsFacade.GetUserBaseInfoByUserID(userID) == null ? "0" : accountsFacade.GetUserBaseInfoByUserID(userID).GameID.ToString();
        }

        /// <summary>
        /// 分页事件
        /// </summary>
        /// <param name="src"></param>
        /// <param name="e"></param>
        protected void anpPage_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            BindSpreaderInfoData();
        }

        protected void anpPage2_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
        {
            anpPage2.CurrentPageIndex = e.NewPageIndex;
            BindSpreaderRecordData();
        }

        protected void rptSpreaderList_ItemCommand(object source, RepeaterCommandEventArgs e)
        {
            if (e.CommandName == "sel")
            {
                ViewState["ChildrenID"] = Utility.StrToInt(e.CommandArgument.ToString().Split('$')[0], 0);

                anpPage2.CurrentPageIndex = 1;

                BindSpreaderRecordData();

                this.lblAccounts.Text = this.GetNickNameByUserID( Utility.StrToInt( e.CommandArgument.ToString( ).Split( '$' )[0] , 0 ) );

                this.divSpread.Visible = false;
                this.divContribution.Visible = true;

                ViewState["total"] = e.CommandArgument.ToString().Split('$')[1];
            }
        }

        private void BindSpreaderRecordData()
        {
            int userID = Utility.StrToInt(ViewState["ChildrenID"],0);

            StringBuilder sWhere = new StringBuilder();
            sWhere.AppendFormat(" WHERE ChildrenID = {0} ", userID);

            int sPageIndex = anpPage2.CurrentPageIndex;
            int sPageSize = anpPage2.PageSize;

            PagerSet pagerSet = treasureFacade.GetSpreaderRecord(sWhere.ToString(), sPageIndex, sPageSize);
            anpPage2.RecordCount = pagerSet.RecordCount;

            this.rptContributionList.DataSource = pagerSet.PageSet;
            this.rptContributionList.DataBind();
        }

        protected void lbtnBack_Click(object sender, EventArgs e)
        {
            this.divSpread.Visible = true;
            this.divContribution.Visible = false;
        }
    }
}
