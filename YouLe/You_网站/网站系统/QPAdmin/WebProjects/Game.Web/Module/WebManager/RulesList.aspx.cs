using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Web.UI;
using Game.Kernel;
using Game.Utils;
using Game.Entity.Enum;

namespace Game.Web.Module.WebManager
{
    public partial class RulesList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                RulesDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            RulesDataBind();
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString("cid");
            string strQuery = "WHERE KindID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.DeleteGameRules(strQuery);
                ShowInfo("删除成功");
            }
            catch
            {
                ShowError("删除失败");
            }
            RulesDataBind();
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void RulesDataBind()
        {
            PagerSet pagerSet = aideNativeWebFacade.GetGameRulesList(anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby);
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptRules.DataSource = pagerSet.PageSet;
            rptRules.DataBind();
            anpNews.RecordCount = pagerSet.RecordCount;
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if (ViewState["SearchItems"] == null)
                {
                    StringBuilder condition = new StringBuilder();
                    condition.Append(" WHERE 1=1 ");

                    ViewState["SearchItems"] = condition.ToString();
                }

                return (string)ViewState["SearchItems"];
            }

            set { ViewState["SearchItems"] = value; }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if (ViewState["Orderby"] == null)
                {
                    ViewState["Orderby"] = "ORDER BY KindID ASC";
                }

                return (string)ViewState["Orderby"];
            }

            set { ViewState["Orderby"] = value; }
        }

        #endregion                       
    }
}
