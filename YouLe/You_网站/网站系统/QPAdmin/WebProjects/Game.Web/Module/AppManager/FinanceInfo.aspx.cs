using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using System.Collections;
using System.Data;

namespace Game.Web.Module.AppManager
{
    public partial class FinanceInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindData( );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        //查询
        protected void btnSearch_OnClick( object sender, EventArgs e )
        {
            StringBuilder condition = new StringBuilder( "WHERE 1=1 " );
            string strKeyword = CtrlHelper.GetText( txtKeyword );
            string type = ddlSearchtype.SelectedValue;
            if ( !string.IsNullOrEmpty( strKeyword ) )
            {
                if ( type.Equals( "1" ) )//GAMEID
                {
                    if ( Utils.Validate.IsPositiveInt( strKeyword ) )
                    {
                        condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE GameID='{0}')", strKeyword );
                    }
                    else
                    {
                        ShowError( "你输入的游戏ID必须为正整数" );
                        return;
                    }
                }
                else
                    condition.AppendFormat( " AND UserID=(SELECT UserID FROM QPAccountsDB.dbo.AccountsInfo WHERE Accounts='{0}')", strKeyword );                
            }
            ViewState["SearchItems"] = condition.ToString( );
            BindData( );
        }
        /// <summary>
        /// 刷新
        /// </summary>
        protected void btnRefresh_Click( object sender, EventArgs e )
        {
            ViewState["SearchItems"] = null;

            txtKeyword.Text = "";
            BindData( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetRecordSpreadInfoList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptDataList.DataSource = pagerSet.PageSet;
            rptDataList.DataBind( );
            anpNews.RecordCount = pagerSet.RecordCount;

            //数据合计
            ltExpendGold.Text = "0";
            ltGainGold.Text = "0";
            string whereGain = SearchItems + " and Score > 0";
            string sqlQuery = "Select Sum(Score) AS GainGold From RecordSpreadInfo " + whereGain;
            DataSet ds = aideTreasureFacade.GetDataSetBySql( sqlQuery );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                DataRow row = ds.Tables[0].Rows[0];
                if ( !string.IsNullOrEmpty( row["GainGold"].ToString( ) ) )
                {
                    CtrlHelper.SetText( ltGainGold , FormatMoney( row["GainGold"].ToString( ) ) );
                }
            }
            string whereSpend = SearchItems + " and Score < 0";
            sqlQuery = "Select Sum(Score) AS CardGold From RecordSpreadInfo " + whereSpend;
            ds = aideTreasureFacade.GetDataSetBySql( sqlQuery );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                DataRow row = ds.Tables[0].Rows[0];
                if ( !string.IsNullOrEmpty( row["CardGold"].ToString( ) ) )
                {
                    object o = row["CardGold"];
                    CtrlHelper.SetText( ltExpendGold , FormatMoney( ( Convert.ToInt32( row["CardGold"] ) * -1 ).ToString( ) ) );
                }
            }
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if ( ViewState["SearchItems"] == null )
                {
                    StringBuilder condition = new StringBuilder( );
                    condition.Append( " WHERE 1=1 " );

                    ViewState["SearchItems"] = condition.ToString( );
                }

                return ( string ) ViewState["SearchItems"];
            }

            set
            {
                ViewState["SearchItems"] = value;
            }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if ( ViewState["Orderby"] == null )
                {
                    ViewState["Orderby"] = "ORDER BY CollectDate DESC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        /// <summary>
        /// 1.注册2.游戏时长3.充值4.结算
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        protected string GetTypeName( int type )
        {
            string result = "";
            switch ( type )
            {
                case 1:
                    result = "注册";
                    break;
                case 2:
                    result = "游戏时长";
                    break;
                case 3:
                    result = "充值";
                    break;
                case 4:
                    result = "结算";
                    break;
                default:
                    break;
            }
            return result;
        }

        #endregion
    }
}
