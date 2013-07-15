using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using System.Web.UI.DataVisualization.Charting;

namespace Game.Web.Module.AppManager
{
    public partial class StatOnline : AdminPage
    {
        #region Fields

        string time = GameRequest.GetQueryString("Time");
        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindDropYear();
                BindDropMonth();

                if (time != "")
                {
                    BindDataList();
                }
            }
        }

        protected void btnQuery_Click(object sender, EventArgs e)
        {
            string type = ddlType.SelectedValue.Trim();
            if (type == "0")
            {
                BindAnalyseData(ddlSelectYear.SelectedValue.Trim(), "-1", "-1");
            }
            else if (type == "1")
            {
                BindAnalyseData(ddlSelectYear.SelectedValue.Trim(), ddlSelectMonth.SelectedValue.Trim(), "-1");
            }
            else
            {
                BindAnalyseData(ddlSelectYear.SelectedValue.Trim(), ddlSelectMonth.SelectedValue.Trim(), ddlSelectDay.SelectedValue.Trim());
            }
        }

        //今天
        protected void btnQueryTD_Click(object sender, EventArgs e)
        {
            string date = DateTime.Now.ToString("yyyy-MM-dd");
            BindAnalyseData(date.Split('-')[0].Trim(), date.Split('-')[1].Trim(), date.Split('-')[2].Trim());
        }

        //昨天
        protected void btnQueryYD_Click(object sender, EventArgs e)
        {
            string date = DateTime.Now.AddDays(-1).ToString("yyyy-MM-dd");
            BindAnalyseData(date.Split('-')[0].Trim(), date.Split('-')[1].Trim(), date.Split('-')[2].Trim());
        }

        //列表绑定
        protected void rptOnLineStream_ItemDataBound(object sender, RepeaterItemEventArgs e)
        {
            if (e.Item.ItemType == ListItemType.Item || e.Item.ItemType == ListItemType.AlternatingItem)
            {
                if (hfdTime.Value.Trim() != "")
                {
                    string url = "openWindowOwn('StatOnlineInfo.aspx?Time=" + hfdTime.Value.Trim() + "&Hour=" + DataBinder.Eval(e.Item.DataItem, "InsertDateTime").ToString() + "','',620,450);return false";
                    ((LinkButton)e.Item.FindControl("btnDetailInfo")).Attributes.Add("onclick", url);

                    string url2 = "openWindowOwn('StatOnlineGame.aspx?Time=" + hfdTime.Value.Trim() + "&Hour=" + DataBinder.Eval(e.Item.DataItem, "InsertDateTime").ToString() + "','',820,500);return false";
                    ((LinkButton)e.Item.FindControl("btnGameInfo")).Attributes.Add("onclick", url2);

                    ((LinkButton)e.Item.FindControl("btnNext")).Visible = false;
                    ((Label)e.Item.FindControl("lblNext")).Visible = true;
                }
                else
                {
                    string url = "openWindowOwn('StatOnlineInfo.aspx?Time=" + DataBinder.Eval(e.Item.DataItem, "InsertDateTime").ToString() + "','',620,450);return false";
                    ((LinkButton)e.Item.FindControl("btnDetailInfo")).Attributes.Add("onclick", url);

                    string url2 = "openWindowOwn('StatOnlineGame.aspx?Time=" + DataBinder.Eval(e.Item.DataItem, "InsertDateTime").ToString() + "','',820,500);return false";
                    ((LinkButton)e.Item.FindControl("btnGameInfo")).Attributes.Add("onclick", url2);

                    string url3 = "openWindowSelf('StatOnline.aspx?Time=" + DataBinder.Eval(e.Item.DataItem, "InsertDateTime").ToString() + "');return false";
                    ((LinkButton)e.Item.FindControl("btnNext")).Attributes.Add("onclick", url3);

                    ((LinkButton)e.Item.FindControl("btnNext")).Visible = true;
                    ((Label)e.Item.FindControl("lblNext")).Visible = false;
                }
            }
        }

        #endregion

        #region 数据分析

        /// <summary>
        /// 绑顶数据
        /// </summary>
        private void BindDataList()
        {
            string year = "";
            string month = "";
            string day = "";
            if (time.IndexOf('-') == -1)
            {
                year = time;
                month = "-1";
                day = "-1";
            }
            else
            {
                if ( time.Split('-').Length == 2 )
                {
                    year = time.Split( '-' )[ 0 ].ToString( ).Trim( );
                    month = time.Split( '-' )[ 1 ].ToString( ).Trim( );
                    day = "-1";
                }
                else
                {
                    year = time.Split( '-' )[ 0 ].ToString( ).Trim( );
                    month = time.Split( '-' )[ 1 ].ToString( ).Trim( );
                    day = time.Split( '-' )[ 2 ].ToString( ).Trim( );
                }
            }
            BindAnalyseData( year , month , day );
        }

        //统计数据
        private void BindAnalyseData(string year, string month, string day)
        {
            //日查询处理
            if (month != "-1" && day != "-1")
            {
                hfdTime.Value = year + "-" + month + "-" + day;
            }
            else
            {
                hfdTime.Value = "";
            }

            DataSet ds = aidePlatformFacade.GetOnLineStreamInfoList(year, month, day);
            DataTable dt = ds.Tables[0];
            DataTable dt2 = FormatTable(dt, year, month, day);
            rptOnLineStream.DataSource = dt2;
            rptOnLineStream.DataBind();

            //画图
            string toolTipInfo = "";
            if (dt2.Rows.Count > 0)
            {
                Series series = new Series("最高在线人数");
                series.ChartType = SeriesChartType.Line;
                series.BorderWidth = 2;
                series.ShadowOffset = 1;
                series.MarkerStyle = MarkerStyle.Circle;
                for (int i = 0; i < dt2.Rows.Count; i++)
                {
                    series.Points.AddXY(dt2.Rows[i]["InsertDateTime"].ToString(), dt2.Rows[i]["MaxCount"].ToString());
                    toolTipInfo += "统计时间：" + FormatDate(dt2.Rows[i][0].ToString()) + "\n";
                    toolTipInfo += "最高在线：" + dt2.Rows[ i ][ 1 ].ToString( ) + "\n";
                    toolTipInfo += "最低在线：" + dt2.Rows[ i ][ 2 ].ToString( ) + "\n";
                    toolTipInfo += "平均在线：" + dt2.Rows[ i ][ 3 ].ToString( );
                    series.Points[ i ].ToolTip = toolTipInfo.ToString( );
                    toolTipInfo = "";
                }
                Chart1.Series.Add(series);
            }
        }

        //格式化数据
        private DataTable FormatTable(DataTable sourceDt, string year, string month, string day)
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("InsertDateTime");
            dt.Columns.Add("MaxCount");
            dt.Columns.Add("MinCount");
            dt.Columns.Add("AvgCount");

            if (month == "-1")//按年统计
            {
                string date = "";
                DataRow[] drRow;
                for (int i = 1; i < 13; i++)
                {
                    date = year + "-" + i.ToString().PadLeft(2, '0');
                    DataRow dr = dt.NewRow();
                    dr[0] = date;//第一列
                    drRow = sourceDt.Select("InsertDateTime='" + date + "'");
                    if (drRow.Length == 0)
                    {
                        dr[1] = "--";
                        dr[2] = "--";
                        dr[3] = "--";
                    }
                    else
                    {
                        dr[1] = drRow[0].ItemArray[1].ToString();
                        dr[2] = drRow[0].ItemArray[2].ToString();
                        dr[3] = drRow[0].ItemArray[3].ToString();
                    }
                    dt.Rows.Add(dr);
                }
            }
            else if (day == "-1") //按月统计
            {
                DataRow[] drRow;
                DateTime startTime = Convert.ToDateTime(year + "-" + month + "-" + "01");
                DateTime endTime = startTime.AddMonths(1);
                while (startTime != endTime)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = startTime.ToString("yyyy-MM-dd");
                    drRow = sourceDt.Select("InsertDateTime='" + startTime.ToString("yyyy-MM-dd") + "'");
                    if (drRow.Length == 0)
                    {
                        dr[1] = "--";
                        dr[2] = "--";
                        dr[3] = "--";
                    }
                    else
                    {
                        dr[1] = drRow[0].ItemArray[1].ToString();
                        dr[2] = drRow[0].ItemArray[2].ToString();
                        dr[3] = drRow[0].ItemArray[3].ToString();
                    }
                    dt.Rows.Add(dr);
                    startTime = startTime.AddDays(1);
                }
            }
            else//按日统计
            {
                DataRow[] drRow;
                for (int i = 0; i < 24; i++)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = i.ToString();
                    drRow = sourceDt.Select("InsertDateTime=" + i + "");
                    if (drRow.Length == 0)
                    {
                        dr[1] = "--";
                        dr[2] = "--";
                        dr[3] = "--";
                    }
                    else
                    {
                        dr[1] = drRow[0].ItemArray[1].ToString();
                        dr[2] = drRow[0].ItemArray[2].ToString();
                        dr[3] = drRow[0].ItemArray[3].ToString();
                    }
                    dt.Rows.Add(dr);
                }
            }
            return dt;
        }

        /// <summary>
        /// 格式化时间
        /// </summary>
        /// <param name="date"></param>
        /// <returns></returns>
        protected string FormatDate(string date)
        {
            if (hfdTime.Value.Trim() != "")
            {
                date = date + ":00 - " + date + ":59";
            }
            return date;
        }
        #endregion

        #region 日期处理

        /// <summary>
        /// 绑定年份
        /// </summary>
        private void BindDropYear()
        {
            int year = System.DateTime.Now.Year;
            ddlSelectYear.Items.Clear();
            ddlSelectYear.ClearSelection();
            for (int i = 2007; i < year + 1; i++)
            {
                ListItem list = new ListItem();
                list.Value = i.ToString().Trim();
                list.Text = i.ToString() + "年";
                if (i == year)
                    list.Selected = true;
                ddlSelectYear.Items.Add(list);
            }
        }

        /// <summary>
        /// 绑定月份
        /// </summary>
        private void BindDropMonth()
        {
            int month = DateTime.Now.Month;
            string M = "";
            ddlSelectMonth.Items.Clear();
            for (int i = 1; i < 13; i++)
            {
                ListItem list = new ListItem();
                M = i.ToString().PadLeft(2, '0');
                list.Text = M + "月";
                list.Value = M;
                if (i == month)
                    list.Selected = true;
                ddlSelectMonth.Items.Add(list);
            }
        }

        /// <summary>
        /// 绑定天数
        /// </summary>
        private void BindDropDay()
        {
            string year = ddlSelectYear.SelectedValue.Trim();
            string month = ddlSelectMonth.SelectedValue.Trim();
            DateTime startTime = Convert.ToDateTime(year + "-" + month + "-" + "01");
            DateTime endTime = startTime.AddMonths(1);
            ddlSelectDay.Items.Clear();
            while (startTime != endTime)
            {
                ListItem list = new ListItem();
                list.Text = startTime.ToString("dd") + "日";
                list.Value = startTime.ToString("dd");
                if (startTime == DateTime.Now.Date)
                    list.Selected = true;
                ddlSelectDay.Items.Add(list);
                startTime = startTime.AddDays(1);
            }
        }

        /// <summary>
        /// 年改变事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void ddlSelectYear_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ddlType.SelectedValue.Trim() == "2")
            {
                BindDropDay();
                ddlSelectDay.UpdateAfterCallBack = true;
            }
        }

        /// <summary>
        /// 月改变事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void ddlSelectMonth_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ddlType.SelectedValue.Trim() == "2")
            {
                BindDropDay();
                ddlSelectDay.UpdateAfterCallBack = true;
            }
        }

        /// <summary>
        /// 查询方式改变事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void ddlType_SelectedIndexChanged(object sender, EventArgs e)
        {
            string type = ddlType.SelectedValue.Trim();
            switch (type)
            {
                case "0":
                    ddlSelectMonth.Visible = false;
                    ddlSelectMonth.UpdateAfterCallBack = true;
                    ddlSelectDay.Visible = false;
                    ddlSelectDay.UpdateAfterCallBack = true;
                    break;
                case "1":
                    ddlSelectMonth.Visible = true;
                    ddlSelectMonth.UpdateAfterCallBack = true;
                    ddlSelectDay.Visible = false;
                    ddlSelectDay.UpdateAfterCallBack = true;
                    BindDropMonth();
                    break;
                case "2":
                    ddlSelectYear.Visible = true;
                    ddlSelectMonth.Visible = true;
                    ddlSelectDay.Visible = true;
                    ddlSelectYear.UpdateAfterCallBack = true;
                    ddlSelectMonth.UpdateAfterCallBack = true;
                    ddlSelectDay.UpdateAfterCallBack = true;
                    BindDropMonth();
                    BindDropDay();
                    break;
            }
        }
        #endregion       
    }
}
