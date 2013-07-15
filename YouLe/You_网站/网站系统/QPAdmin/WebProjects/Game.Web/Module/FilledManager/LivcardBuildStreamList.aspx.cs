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
using Game.Entity.Treasure;

namespace Game.Web.Module.FilledManager
{
    public partial class LivcardBuildStreamList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                if ( StrCmd.Equals( "export" ) && IntParam > 0 )
                {
                    //判断权限
                    AuthUserOperationPermission( Permission.ExportCard );
                    aideTreasureFacade.UpdateLivcardBuildStream( IntParam );//更新导出次数
                    Export( );//导出 
                }
                txtStartDate.Text = DateTime.Now.ToString( "yyyy-MM-" ) + "01";
                txtEndDate.Text = DateTime.Now.ToString( "yyyy-MM-dd" );
                BindData( );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }

        //日期查询
        protected void btnQuery_Click( object sender, EventArgs e )
        {
            string startDate = CtrlHelper.GetText( txtStartDate );
            string endDate = CtrlHelper.GetText( txtEndDate );
            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );
            if ( startDate != "" && endDate != "" )
            {
                condition.AppendFormat( " AND BuildDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
            }
            ViewState["SearchItems"] = condition.ToString( );

            BindData( );
        }
        //销售商查询
        protected void btnQuery2_Click( object sender, EventArgs e )
        {
            string salesperson = CtrlHelper.GetText( txtsalesperson );
            StringBuilder condition = new StringBuilder( " WHERE 1=1 " );

            if ( !String.IsNullOrEmpty( salesperson ) )
            {
                condition.AppendFormat( " AND BuildID IN (SELECT BuildID FROM QPTreasureDB.dbo.LivcardAssociator WHERE SalesPerson='{0}' GROUP BY BUILDID)", salesperson );
            }
            ViewState["SearchItems"] = condition.ToString( );

            BindData( );
        }

        //导出
        protected void Export( )
        {
            LivcardBuildStream cardBuild = aideTreasureFacade.GetLivcardBuildStreamInfo( IntParam );
            if ( cardBuild == null )
            {
                ShowError( "实卡类型不存在" );
                return;
            }
            if ( cardBuild.BuildCardPacket.Length > 0 )
            {
                //string style = @"<style>.text { mso-number-format:\@; }</style> "; //设置格式
                byte[ ] bytes = cardBuild.BuildCardPacket;
                //兼容asp网站生成的点卡
                string str = Encoding.Default.GetString( bytes );
                if ( str.IndexOf( "/" ) != -1 )
                {
                    str = str.Replace( "/" , "\r\n" );
                    str = str.Replace( "," , ",\t" );
                    str = "第" + cardBuild.BuildID + "批次 (" + GetCardTypeName( cardBuild.CardTypeID ) + ") " + cardBuild.BuildCount + " 张\r\n卡号,\t卡密\r\n" + str;
                    bytes = Encoding.Default.GetBytes( str );
                } 
                Response.Clear( );
                Response.ContentType = "application/ms-excel";
                Response.AddHeader( "Content-Disposition" , "attachment;filename=" + HttpUtility.UrlEncode( "实卡信息" + DateTime.Now.ToString( "yyyy-MM-ddTHH-mm-ss" ) + ".csv" ) );
                int length = bytes.Length;
                Response.AddHeader( "Content-Length", length.ToString( ) );
                Response.BinaryWrite( bytes );
                Response.End( );
            }
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetLivcardBuildStreamList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
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
                    string startDate = CtrlHelper.GetText( txtStartDate );
                    string endDate = CtrlHelper.GetText( txtEndDate );
                    if ( startDate != "" && endDate != "" )
                    {
                        condition.AppendFormat( " AND BuildDate BETWEEN '{0}' AND '{1}'", startDate, Convert.ToDateTime( endDate ).AddDays( 1 ).ToString( "yyyy-MM-dd" ) );
                    }
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
                    ViewState["Orderby"] = "ORDER BY BuildDate DESC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        //获取实卡的销售商名称
        protected string GetSalesperson( int buildID )
        {
            if ( buildID <= 0 )
                return "";
            return aideTreasureFacade.GetSalesperson( buildID );
        }
        #endregion
    }
}
