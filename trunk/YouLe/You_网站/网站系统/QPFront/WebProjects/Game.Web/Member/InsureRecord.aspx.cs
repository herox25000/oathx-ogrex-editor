﻿using System;
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
    public partial class InsureRecord : UCPageBase
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
            sWhere.Append(" WHERE ");

            if (Convert.ToInt32(ddlType.SelectedValue) != 0)
            {
                if (Convert.ToInt32(ddlType.SelectedValue) < 3)
                {
                    sWhere.AppendFormat(" TradeType = {0} AND SourceUserID = {1}", Convert.ToInt32(ddlType.SelectedValue) == 1 ? 1 : 2, Fetch.GetUserCookie().UserID);
                }
                else
                {
                    if (Convert.ToInt32(ddlType.SelectedValue) == 3)
                        sWhere.AppendFormat(" SourceUserID = {0} AND TradeType = 3 and TargetUserID <> {0}", Fetch.GetUserCookie().UserID);
                    else if (Convert.ToInt32(ddlType.SelectedValue) == 4)
                    {
                        sWhere.AppendFormat(" SourceUserID <> {0} AND TradeType = 3 and TargetUserID = {0}", Fetch.GetUserCookie().UserID);
                    }
                }
            }
            else
            {
                sWhere.AppendFormat(" SourceUserID = {0} OR TargetUserID = {0}", Fetch.GetUserCookie().UserID);
            }
            sWhere.AppendFormat(" AND CollectDate >= '{0}' AND CollectDate <= '{1}'", CtrlHelper.GetText(txtStartDate) + " 00:00:00", CtrlHelper.GetText(txtEndDate) + " 23:59:59");

            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize;

            PagerSet pagerSet = treasureFacade.GetInsureTradeRecord(sWhere.ToString(), sPageIndex, sPageSize);
            anpPage.RecordCount = pagerSet.RecordCount;

            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                rptInsureList.DataSource = pagerSet.PageSet;
                rptInsureList.DataBind();

                this.rptInsureList.Visible = true;
                this.trNoData.Visible = false;
            }
            else
            {
                this.rptInsureList.Visible = false;
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
