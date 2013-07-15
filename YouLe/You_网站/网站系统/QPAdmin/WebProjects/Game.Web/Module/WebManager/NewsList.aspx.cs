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
    public partial class NewsList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                NewsDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            NewsDataBind();
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
            string strQuery = "WHERE NewsID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.DeleteNews(strQuery);
                ShowInfo("删除成功");
            }
            catch
            {
                ShowError("删除失败");
            }
            NewsDataBind();
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void NewsDataBind()
        {
            PagerSet pagerSet = aideNativeWebFacade.GetNewsList(anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby);
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptNews.DataSource = pagerSet.PageSet;
            rptNews.DataBind();
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
                    ViewState["Orderby"] = "ORDER BY IssueDate DESC";
                }

                return (string)ViewState["Orderby"];
            }

            set { ViewState["Orderby"] = value; }
        }

        #endregion                       

        #region 公共方法

        protected string GetClassName(byte classID)
        {
            string rValue = "";
            switch (classID)
            {
                case 1:
                    rValue = "新闻";
                    break;
                case 2:
                    rValue = "公告";
                    break;
                default:
                    break;
            }
            return rValue;
        }

        protected string GetStatusName(byte status)
        {
            string rValue = "";
            switch (status)
            {
                case 0:
                    rValue = "否";
                    break;
                case 1:
                    rValue = "<span class='hong'>是</span>";
                    break;
                default:
                    break;
            }
            return rValue;
        }
        #endregion
    }
}
