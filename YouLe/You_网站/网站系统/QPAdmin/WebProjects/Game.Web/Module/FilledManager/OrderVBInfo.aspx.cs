using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Treasure;
using Game.Facade;

namespace Game.Web.Module.FilledManager
{
    public partial class OrderVBInfo : AdminPage
    {
        #region 字段 
        
        int id = GameRequest.GetQueryInt( "id" , 0 );

        #endregion

        #region 窗口事件

        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                VBDetailDataBind( );
            }
        }
        #endregion

        #region 数据加载

        private void VBDetailDataBind( )
        {
            if ( id <= 0 )
            {
                return;
            }
            //获取站点信息
            ReturnVBDetailInfo VBDetailInfo = aideTreasureFacade.GetVBDetailInfo( id );
            if ( VBDetailInfo == null )
            {
                ShowError( "信息不存在" );
                return;
            }
            CtrlHelper.SetText( litOrderID , "<a class='l' href='javascript:void(0)' onclick=\"javascript:openWindowOwn('OnLineOrderInfo.aspx?OrderID=" + VBDetailInfo.OrderID + "','online_" + VBDetailInfo.OrderID + "',600,465)\">" + VBDetailInfo.OrderID + "</a>" );
            CtrlHelper.SetText( litOrderTime , VBDetailInfo.CollectDate.ToString( "yyyy-MM-dd HH:ss:mm" ) );
            CtrlHelper.SetText( litOperStationID , VBDetailInfo.OperStationID.ToString( ) );
            CtrlHelper.SetText( litRtflag , VBDetailInfo.Rtflag == 1 ? "正常返回" : "补丁返回" );
            CtrlHelper.SetText( litRtka , VBDetailInfo.Rtka.ToString( ) );
            CtrlHelper.SetText( litRtlx , VBDetailInfo.Rtlx == 1 ? "正式卡" : VBDetailInfo.Rtlx == 2 ? "测试卡" : "促销卡" );
            CtrlHelper.SetText( litRtmd5 , VBDetailInfo.Rtmd5.ToString( ) );
            CtrlHelper.SetText( LitRtmi , VBDetailInfo.Rtmi );
            CtrlHelper.SetText( litRtmz , VBDetailInfo.Rtmz.ToString( ) );
            CtrlHelper.SetText( litRtoID , VBDetailInfo.Rtoid );
            CtrlHelper.SetText( litSignMsg , VBDetailInfo.SignMsg.ToString( ) );
        }
        #endregion
    }
}
