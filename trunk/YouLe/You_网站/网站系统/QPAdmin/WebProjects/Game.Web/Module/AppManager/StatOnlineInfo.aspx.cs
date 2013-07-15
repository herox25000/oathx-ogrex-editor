using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using System.Text;

namespace Game.Web.Module.AppManager
{
    public partial class StatOnlineInfo : AdminPage
    {
        #region Fields

        string time = GameRequest.GetQueryString("Time");
        string hour = GameRequest.GetQueryString("Hour");

        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                GetSearchItems();
                OnLineStreamDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            OnLineStreamDataBind();
        }

        #endregion

        #region 数据绑定

        private void GetSearchItems()
        {
            string year = "";
            string month = "";
            string day = "";
            if (time.Split('-').Length == 2)
            {
                year = time.Split('-')[0].ToString().Trim();
                month = time.Split('-')[1].ToString().Trim();
                DateTime startTime = Convert.ToDateTime(year + "-" + month + "-" + "01");
                DateTime endTime = startTime.AddMonths(1);
                SearchItems = " where InsertDateTime>'" + startTime.ToString() + "' and InsertDateTime<'" + endTime.ToString() + "'";
            }
            else if (hour == "")
            {
                year = time.Split('-')[0].ToString().Trim();
                month = time.Split('-')[1].ToString().Trim();
                day = time.Split('-')[2].ToString().Trim();
                string date = year + "-" + month + "-" + day;
                SearchItems = " where convert(varchar(10),InsertDateTime,120)='" + date + "'";
            }
            else
            {
                year = time.Split('-')[0].ToString().Trim();
                month = time.Split('-')[1].ToString().Trim();
                day = time.Split('-')[2].ToString().Trim();
                string date = year + "-" + month + "-" + day;
                SearchItems = " where convert(varchar(10),InsertDateTime,120)='" + date + "' and datepart(hh,InsertDateTime)='" + hour + "'";
            }
        }

        //绑定数据
        private void OnLineStreamDataBind()
        {
            PagerSet pagerSet = aidePlatformFacade.GetOnLineStreamInfoList(anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby);
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptOnLineStream.DataSource = pagerSet.PageSet;
            rptOnLineStream.DataBind();
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
                    ViewState["Orderby"] = "ORDER BY InsertDateTime DESC";
                }

                return (string)ViewState["Orderby"];
            }

            set { ViewState["Orderby"] = value; }
        }

        #endregion                       
    }
}
