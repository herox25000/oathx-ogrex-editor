using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Pay
{
    public partial class PayDayInform : UCPageBase
    {
        protected void Page_Load( object sender , EventArgs e )
        {
            string key = System.Configuration.ConfigurationSettings.AppSettings["DayKey"];       //密钥
            string merId = System.Configuration.ConfigurationSettings.AppSettings["DayMerId"];   //商户ID
            string status = GameRequest.GetFormString( "status" );                               //交易状态   
            string sign = GameRequest.GetFormString( "sign" );                                   //签名   
            string orderId = GameRequest.GetFormString( "orderId" );                             //订单号
            float payMoney = GameRequest.GetFormFloat( "payMoney",0 );                           //金额   
            string operDate = GameRequest.GetFormString( "operDate" );                           //订单日期   
            string userName = GameRequest.GetFormString( "userName" );                           //用户名   
            string showUrl = "http://" + HttpContext.Current.Request.Url.Authority + "/Pay/PayShow.aspx"; //交易完成后提示地址
            string signStr = merId + "|" + orderId + "|" + status + "|" + payMoney + "|" + operDate + "|" + userName + "|" + key;
            string testSign = EncryptMD5( signStr , false , 32 );                                //计算签名

            ReturnDayDetailInfo result = new ReturnDayDetailInfo( );
            result.OrderID = orderId;
            result.PayMoney = Convert.ToDecimal( payMoney );
            result.Sign = sign;
            result.UserName = userName;
            result.Status = status;

            //天天付支付结果入库
            TreasureFacade treasureFacade = new TreasureFacade( );
            treasureFacade.WriteReturnDayDetail( result );

            if ( signStr == testSign )
            {
                //交易状态为005时表示交易完成
                if ( status == "055" )
                {
                    ShareDetialInfo detailInfo = new ShareDetialInfo( );
                    detailInfo.OrderID = orderId;
                    detailInfo.IPAddress = Utility.UserIP;
                    Message umsg = treasureFacade.FilliedOnline( detailInfo , 0 );
                    if ( umsg.Success )
                    {
                        Response.Write( "OK" );
                    }
                }
            }
        }
    }
}
