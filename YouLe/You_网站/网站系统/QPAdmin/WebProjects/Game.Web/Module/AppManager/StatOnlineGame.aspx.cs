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
using System.Web.UI.DataVisualization.Charting;
using System.Data;

namespace Game.Web.Module.AppManager
{
    public partial class StatOnlineGame : AdminPage
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
                BindDataList();
            }
        }

        #endregion

        #region 数据绑定

        private void BindDataList()
        {
            string year = "";
            string month = "";
            string day = "";
            if (time.Split('-').Length == 2)
            {
                year = time.Split('-')[0].ToString().Trim();
                month = time.Split('-')[1].ToString().Trim();
                day = "-1";
                hour = "-1";
            }
            else if (hour == "")
            {
                year = time.Split('-')[0].ToString().Trim();
                month = time.Split('-')[1].ToString().Trim();
                day = time.Split('-')[2].ToString().Trim();
                hour = "-1";
            }
            else
            {
                year = time.Split('-')[0].ToString().Trim();
                month = time.Split('-')[1].ToString().Trim();
                day = time.Split('-')[2].ToString().Trim();
            }
            ShowNoteInfo(year, month, day, hour);
            DrawImage(year, month, day, hour);
        }  

        /// <summary>
        /// 列表显示信息
        /// </summary>
        private void DrawImage(string year, string month, string day, string hour)
        {
            string[] gameInfo;//游戏信息
            int maxCount = 0;//最大数量

            //获取游戏列表
            DataSet dsGame = aidePlatformFacade.GetGameKindItemList(1, Int32.MaxValue, "", "ORDER BY KindID ASC").PageSet;
            DataSet ds = aidePlatformFacade.GetOnlineStreamGameInfoList(year, month, day, hour);
            DataTable dtGame = dsGame.Tables[0];
            DataTable dt = ds.Tables[0];

            DataTable dtNew = new DataTable();
            dtNew.Columns.Add("Type");
            dtNew.Columns.Add("Count");

            for (int i = 0; i < dtGame.Rows.Count; i++)
            {
                DataRow drNew = dtNew.NewRow();
                drNew[0] = dtGame.Rows[i]["KindName"].ToString();
                for (int j = 0; j < dt.Rows.Count; j++)
                {
                    gameInfo = dt.Rows[j]["OnLineCountKind"].ToString().Split(';');
                    for (int k = 0; k < gameInfo.Length; k++)
                    {
                        if (dtGame.Rows[i]["KindID"].ToString().Trim() == gameInfo[k].Split(':')[0].Trim())
                        {
                            if (maxCount < Convert.ToInt32(gameInfo[k].Split(':')[1].Trim()))
                            {
                                maxCount = Convert.ToInt32(gameInfo[k].Split(':')[1].Trim());
                            }
                            break;
                        }
                    }
                }
                drNew[1] = maxCount;
                dtNew.Rows.Add(drNew);
                maxCount = 0;
            }

            //画图
            string toolTipInfo = "";

            for (int i = 0; i < dtNew.Rows.Count; i++)
            {
                Series series = new Series(i + "：" + dtNew.Rows[i][0].ToString());
                series.Points.AddY(dtNew.Rows[i][1].ToString());
                if (dtNew.Rows[i][1].ToString() != "0")
                {
                    series.Label = i.ToString();
                    toolTipInfo += "游戏名称：" + dtNew.Rows[i][0].ToString() + "\n";
                    toolTipInfo += "最高在线：" + dtNew.Rows[i][1].ToString();
                    series.ToolTip = toolTipInfo;
                    toolTipInfo = "";
                }
                Chart1.Series.Add(series);
            }
        }

        /// <summary>
        /// 显示备注信息
        /// </summary>
        /// <param name="year"></param>
        /// <param name="month"></param>
        /// <param name="day"></param>
        /// <param name="hour"></param>
        private void ShowNoteInfo(string year, string month, string day, string hour)
        {
            string rString = "";
            string date = "";
            if (day == "-1")
            {
                date = year + "-" + month;
            }
            else if (hour == "-1")
            {
                date = year + "-" + month + "-" + day;
            }
            else
            {
                date = year + "-" + month + "-" + day + " " + FormatDate(hour);
            }
            rString = "以下是 " + date + " 其间每款游戏的人数统计信息！";
            lblInfo.Text = rString;
        }

        /// <summary>
        /// 格式化小时
        /// </summary>
        /// <param name="date"></param>
        /// <returns></returns>
        protected string FormatDate(string date)
        {
            return date + ":00 - " + date + ":59";
        }

        #endregion                       
    }
}
