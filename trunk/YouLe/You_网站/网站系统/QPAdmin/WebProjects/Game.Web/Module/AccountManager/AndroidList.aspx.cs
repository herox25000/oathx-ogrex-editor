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
using Game.Facade;
using Game.Entity.Enum;

namespace Game.Web.Module.AccountManager
{
    public partial class AndroidList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                txtStartDate.Text = DateTime.Now.ToString("yyyy-MM-") + "01";
                txtEndDate.Text = DateTime.Now.ToString("yyyy-MM-dd");
                BindServerList();
                AndroidDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            AndroidDataBind();
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
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.DeleteAndroid(strQuery);
                ShowInfo("删除成功");
            }
            catch
            {
                ShowError("删除失败");
            }
            AndroidDataBind();
        }

        /// <summary>
        /// 批量冻结机器人
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDongjie_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString("cid");
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.NullityAndroid(1, strQuery);
                ShowInfo("冻结成功");
            }
            catch
            {
                ShowError("冻结失败");
            }
            AndroidDataBind();
        }

        /// <summary>
        /// 批量解冻机器人
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnJiedong_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString("cid");
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.NullityAndroid(0, strQuery);
                ShowInfo("解冻成功");
            }
            catch
            {
                ShowError("解冻失败");
            }
            AndroidDataBind();
        }

        //帐号查询
        protected void btnQueryAcc_Click(object sender, EventArgs e)
        {
            string queryContent = txtSearch.Text.Trim();
            int searchType = int.Parse( ddlSearchType.SelectedValue );
            StringBuilder condition = new StringBuilder(" WHERE 1=1 ");           
            if ( !string.IsNullOrEmpty( queryContent ) )
            {
                switch ( searchType )
                {
                    case 1:
                        condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE Accounts='{0}')", queryContent );
                        break;
                    case 2:
                        if ( Utils.Validate.IsPositiveInt( queryContent ) )
                            condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE GameID='{0}')", queryContent );
                        else
                        {
                            ShowError( "你输入的游戏ID必须为正整数" );
                            return;
                        }
                        break;                   
                }
            }
            if (ddlServerID.SelectedValue.Trim() != "0")
            {
                condition.AppendFormat(" AND ServerID={0}", ddlServerID.SelectedValue.Trim());
            }
            ViewState["SearchItems"] = condition.ToString();
            AndroidDataBind();
        }
        //日期查询
        protected void btnQuery_Click(object sender, EventArgs e)
        {
            string startDate = CtrlHelper.GetText(txtStartDate);
            string endDate = CtrlHelper.GetText(txtEndDate);

            SetCondition( startDate, endDate );
            AndroidDataBind();
        }
         /// <summary>
        /// 设置查询条件
        /// </summary>
        /// <param name="startDate"></param>
        /// <param name="endDate"></param>
        private void SetCondition( string startDate, string endDate )
        {            
            string queryContent = CtrlHelper.GetText( txtSearch );

            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND CreateDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            if ( ddlNullity.SelectedValue.Trim( ) != "-1" )
            {
                condition.AppendFormat( " AND Nullity={0}", ddlNullity.SelectedValue.Trim( ) );
            }
            if ( ddlServerID1.SelectedValue.Trim( ) != "0" )
            {
                condition.AppendFormat( " AND ServerID={0}", ddlServerID1.SelectedValue.Trim( ) );
            }
            ViewState["SearchItems"] = condition.ToString( );
        }
        //今天
        protected void btnQueryTD_Click(object sender, EventArgs e)
        {
            string startDate = Fetch.GetTodayTime().Split('$')[0].ToString();
            string endDate = Fetch.GetTodayTime().Split('$')[1].ToString();

            CtrlHelper.SetText(txtStartDate, Convert.ToDateTime(startDate).ToString("yyyy-MM-dd"));
            CtrlHelper.SetText(txtEndDate, Convert.ToDateTime(endDate).ToString("yyyy-MM-dd"));

            SetCondition( startDate, endDate );
            AndroidDataBind();
        }

        //昨天
        protected void btnQueryYD_Click(object sender, EventArgs e)
        {
            string startDate = Fetch.GetYesterdayTime().Split('$')[0].ToString();
            string endDate = Fetch.GetYesterdayTime().Split('$')[1].ToString();

            CtrlHelper.SetText(txtStartDate, Convert.ToDateTime(startDate).ToString("yyyy-MM-dd"));
            CtrlHelper.SetText(txtEndDate, Convert.ToDateTime(endDate).ToString("yyyy-MM-dd"));

            SetCondition( startDate, endDate );
            AndroidDataBind();
        }

        //本周
        protected void btnQueryTW_Click(object sender, EventArgs e)
        {
            string startDate = Fetch.GetWeekTime().Split('$')[0].ToString();
            string endDate = Fetch.GetWeekTime().Split('$')[1].ToString();

            CtrlHelper.SetText(txtStartDate, Convert.ToDateTime(startDate).ToString("yyyy-MM-dd"));
            CtrlHelper.SetText(txtEndDate, Convert.ToDateTime(endDate).ToString("yyyy-MM-dd"));

            SetCondition( startDate, endDate );
            AndroidDataBind();
        }

        //上周
        protected void btnQueryYW_Click(object sender, EventArgs e)
        {
            string startDate = Fetch.GetLastWeekTime().Split('$')[0].ToString();
            string endDate = Fetch.GetLastWeekTime().Split('$')[1].ToString();

            CtrlHelper.SetText(txtStartDate, Convert.ToDateTime(startDate).ToString("yyyy-MM-dd"));
            CtrlHelper.SetText(txtEndDate, Convert.ToDateTime(endDate).ToString("yyyy-MM-dd"));

            SetCondition( startDate, endDate );
            AndroidDataBind();
        }
        #endregion

        #region 数据绑定

        //绑定房间
        private void BindServerList()
        {
           PagerSet pagerSet = aidePlatformFacade.GetGameRoomInfoList(1, Int32.MaxValue, "WHERE Nullity=0", "ORDER BY ServerID ASC");

            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                ddlServerID.DataSource = pagerSet.PageSet;
                ddlServerID.DataTextField = "ServerName";
                ddlServerID.DataValueField = "ServerID";
                ddlServerID.DataBind();

                ddlServerID1.DataSource = pagerSet.PageSet;
                ddlServerID1.DataTextField = "ServerName";
                ddlServerID1.DataValueField = "ServerID";
                ddlServerID1.DataBind( );
            }

            ddlServerID.Items.Insert( 0 , new ListItem( "全部房间" , "0" ) );
            ddlServerID1.Items.Insert( 0, new ListItem( "全部房间", "0" ) );
        }

        //绑定数据
        private void AndroidDataBind()
        {
            PagerSet pagerSet = aideTreasureFacade.GetAndroidList( anpNews.CurrentPageIndex , anpNews.PageSize , SearchItems , Orderby );
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }
            rptAndroid.DataSource = pagerSet.PageSet;
            rptAndroid.DataBind( );
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
                    StringBuilder condition = new StringBuilder( );
                    condition.Append( " WHERE 1=1 " );

                    string startDate = CtrlHelper.GetText( txtStartDate );
                    string endDate = CtrlHelper.GetText( txtEndDate );
                    if (startDate != "" && endDate != "")
                    {
                        condition.AppendFormat( " AND CreateDate BETWEEN '{0}' AND '{1}'" , startDate , Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                    }
                    ViewState["SearchItems"] = condition.ToString( );
                }
                return ( string )ViewState["SearchItems"];
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
                    ViewState["Orderby"] = "ORDER BY CreateDate DESC";
                }
                return ( string )ViewState["Orderby"];
            }
            set
            {
                ViewState["Orderby"] = value;
            }
        }

        #endregion
    }
}
