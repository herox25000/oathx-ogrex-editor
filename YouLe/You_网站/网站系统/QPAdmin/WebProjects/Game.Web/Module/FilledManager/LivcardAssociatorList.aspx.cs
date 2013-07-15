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
using Game.Entity.Enum;
using System.Data;

namespace Game.Web.Module.FilledManager
{
    public partial class LivcardAssociatorList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {          
                BindData( );
            }
            if ( IntParam == 0 )
            {
                btBatch.Visible = false;
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        //批量禁用
        protected void btnDisable_Click( object sender, EventArgs e )
        {
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE CardID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.SetCardDisbale( strQuery );
                MessageBox( "禁用成功" );
            }
            catch
            {
                MessageBox( "禁用失败" );
            }
            BindData( );
        }
        //批量启用
        protected void btnEnable_Click( object sender, EventArgs e )
        {
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE CardID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.SetCardEnbale( strQuery );
                MessageBox( "启用成功" );
            }
            catch
            {
                MessageBox( "启用失败" );
            }
            BindData( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetLivcardAssociatorList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
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

            Int64 amount = 0;
            Int64 gold = 0;
            int useNumber = 0;
            int notUserNumber = 0;
            int pastdueNumber = 0;
            int outNumber = 0;
            int count = 0;
            DataSet ds = aideTreasureFacade.GetLivcardStatByBuildID( IntParam );
            DataRow rows = ds.Tables[0].Rows[0];
            if ( rows["TotalCount"].ToString( ) != "0" )
            {
                amount = Convert.ToInt64( rows["TotalPrice"] );
                gold = Convert.ToInt64( rows["TotalGold"] );
                useNumber = Convert.ToInt32( rows["TotalUsed"] );
                notUserNumber = Convert.ToInt32( rows["TotalNoUsed"] );
                pastdueNumber = Convert.ToInt32( rows["TotalOut"] );
                outNumber = Convert.ToInt32( rows["TotalNullity"] );
                count = Convert.ToInt32( rows["TotalCount"] );

                string textStat = "总金额：￥" + FormatMoney( amount.ToString( ) ) + "，总金币：" + FormatMoney( gold.ToString( ) ) + "，充值 " + useNumber.ToString( ) + " 张" + "，未充值 " + notUserNumber.ToString( ) + " 张" + "，已过期 " + pastdueNumber.ToString( ) + " 张" + "，禁用 " + outNumber.ToString( ) + " 张" + "，激活 " + ( count - outNumber ).ToString( ) + " 张";
                CtrlHelper.SetText( ltStat , textStat );
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
                    BuildWheres condition = new BuildWheres( );
                    if ( IntParam != 0 )
                    {
                        condition.Append( " BuildID=" + IntParam + " " );
                    }
                    switch ( StrCmd )
                    {
                        case "1":
                            condition.Append( " ApplyDate IS NOT NULL " );
                            break;
                        case "2":
                            condition.Append( " ApplyDate IS NULL " );
                            break;
                        case "3":
                            condition.Append( " Nullity=1 " );
                            break;
                        case "4":
                            condition.Append( " Nullity=0 " );
                            break;
                        case "0":                          
                        default:
                            break;
                    }

                    ViewState["SearchItems"] = condition.ToString( );
                }

                return ( string )ViewState["SearchItems"];
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
                    ViewState["Orderby"] = "ORDER BY CardID ASC";
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
