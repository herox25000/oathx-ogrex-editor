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
    public partial class FeedbackList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                FeedbackDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            FeedbackDataBind();
        }

        protected void btnQuery_Click(object sender, EventArgs e)
        {
            string queryContent = txtSearch.Text.Trim();
            string revertStatus = ddlRevertStatus.SelectedValue.Trim();
            StringBuilder condition = new StringBuilder(" WHERE 1=1 ");
            if (queryContent != "")
            {
                condition.AppendFormat(" AND Accounts='{0}'", queryContent);
            }
            switch (revertStatus)
            {
                case "1":
                    condition.Append(" AND RevertDate IS NOT NULL");
                    break;
                case "2":
                    condition.Append(" AND RevertDate IS NULL");
                    break;
                default:
                    break;
            }
            ViewState["SearchItems"] = condition.ToString();
            FeedbackDataBind();
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
            string strQuery = "WHERE FeedbackID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.DeleteGameFeedback(strQuery);
                ShowInfo("删除成功");
            }
            catch
            {
                ShowError("删除失败");
            }
            FeedbackDataBind();
        }
        //冻结
        protected void btnDisable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE FeedbackID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.SetFeedbackDisbale( strQuery );
                ShowInfo( "冻结成功" );
            }
            catch
            {
                ShowError( "冻结失败" );
            }
            FeedbackDataBind( );
        }
        //解冻
        protected void btnEnable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE FeedbackID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.SetFeedbackEnbale( strQuery );
                ShowInfo( "解冻成功" );
            }
            catch
            {
                ShowError( "解冻失败" );
            }
            FeedbackDataBind( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void FeedbackDataBind()
        {
            PagerSet pagerSet = aideNativeWebFacade.GetGameFeedbackList(anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby);
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptFeedback.DataSource = pagerSet.PageSet;
            rptFeedback.DataBind();
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
                    ViewState["Orderby"] = "ORDER BY FeedbackDate DESC";
                }

                return (string)ViewState["Orderby"];
            }

            set { ViewState["Orderby"] = value; }
        }

        #endregion                       
    }
}
