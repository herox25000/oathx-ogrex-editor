using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using System.Data;

namespace Game.Web.Module.BackManager
{
    public partial class SystemStat : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindData( );
                BindDataList( );
            }
        }

        #endregion

        #region 数据加载
        private void BindDataList( )
        {
            DataTable dt = new DataTable( );
            //游戏税收
            dt = aideTreasureFacade.GetGameRevenue( );
            if ( dt.Rows.Count > 0 )
            {
                rptGameTax.DataSource = dt;
                rptGameTax.DataBind( );
            }
            dt.Clear( );
            //房间税收
            dt = aideTreasureFacade.GetRoomRevenue( );
            if ( dt.Rows.Count > 0 )
            {
                rptRoomTax.DataSource = dt;
                rptRoomTax.DataBind( );
            }
            dt.Clear( );
            //游戏损耗
            dt = aideTreasureFacade.GetGameWaste( );
            if ( dt.Rows.Count > 0 )
            {
                rptGameWast.DataSource = dt;
                rptGameWast.DataBind( );
            }
            dt.Clear( );
            //房间损耗
            dt = aideTreasureFacade.GetRoomWaste( );
            if ( dt.Rows.Count > 0 )
            {
                rptRoomWast.DataSource = dt;
                rptRoomWast.DataBind( );
            }

        }

        private void BindData( )
        {
            DataSet ds = aideTreasureFacade.GetStatInfo( );
            DataTable dt = ds.Tables[0];
            if ( dt.Rows.Count > 0 )
            {
                //在线统计
                CtrlHelper.SetText( ltOnLineCount , FormatMoney( dt.Rows[0]["OnLineCount"].ToString( ) ) );
                CtrlHelper.SetText( ltDisenableCount , FormatMoney( dt.Rows[0]["DisenableCount"].ToString( ) ) );
                CtrlHelper.SetText( ltAllCount , FormatMoney( dt.Rows[0]["AllCount"].ToString( ) ) );
                //金币统计
                CtrlHelper.SetText( ltScore , FormatMoney( dt.Rows[0]["Score"].ToString( ) ) );
                CtrlHelper.SetText( ltInsureScore , FormatMoney( dt.Rows[0]["InsureScore"].ToString( ) ) );
                CtrlHelper.SetText( ltAllScore , FormatMoney( dt.Rows[0]["AllScore"].ToString( ) ) );
                //赠送统计
                CtrlHelper.SetText( ltRegGrantScore , FormatMoney( dt.Rows[0]["RegGrantScore"].ToString( ) ) );
                CtrlHelper.SetText( ltPresentScore , FormatMoney( dt.Rows[0]["PresentScore"].ToString( ) ) );
                CtrlHelper.SetText( ltManagerGrantScore , FormatMoney( dt.Rows[0]["ManagerGrantScore"].ToString( ) ) );

                //魅力统计
                CtrlHelper.SetText( ltLoveLiness , FormatMoney( dt.Rows[0]["LoveLiness"].ToString( ) ) );
                CtrlHelper.SetText( ltPresent , FormatMoney( dt.Rows[0]["Present"].ToString( ) ) );
                CtrlHelper.SetText( ltRemainLove , FormatMoney( dt.Rows[0]["RemainLove"].ToString( ) ) );
                CtrlHelper.SetText( ltConvertPresent , FormatMoney( dt.Rows[0]["ConvertPresent"].ToString( ) ) );

                //税收统计
                CtrlHelper.SetText( ltRevenue , FormatMoney( dt.Rows[0]["Revenue"].ToString( ) ) );
                CtrlHelper.SetText( ltTransferRevenue , FormatMoney( dt.Rows[0]["TransferRevenue"].ToString( ) ) );
                //损耗统计
                CtrlHelper.SetText( ltWaste , FormatMoney( dt.Rows[0]["Waste"].ToString( ) ) );
                //点卡统计
                CtrlHelper.SetText( ltCardCount , FormatMoney( dt.Rows[0]["CardCount"].ToString( ) ) );
                CtrlHelper.SetText( ltCardGold , FormatMoney( dt.Rows[0]["CardGold"].ToString( ) ) );
                CtrlHelper.SetText( ltCardPrice , FormatMoney( dt.Rows[0]["CardPrice"].ToString( ) ) );
                CtrlHelper.SetText( ltCardPayCount , FormatMoney( dt.Rows[0]["CardPayCount"].ToString( ) ) );

                CtrlHelper.SetText( ltCardPayGold , FormatMoney( dt.Rows[0]["CardPayGold"].ToString( ) ) );
                CtrlHelper.SetText( ltCardPayPrice , FormatMoney( dt.Rows[0]["CardPayPrice"].ToString( ) ) );
                CtrlHelper.SetText( ltMemberCardCount , FormatMoney( dt.Rows[0]["MemberCardCount"].ToString( ) ) );
            }
           
        }
        #endregion
    }
}
