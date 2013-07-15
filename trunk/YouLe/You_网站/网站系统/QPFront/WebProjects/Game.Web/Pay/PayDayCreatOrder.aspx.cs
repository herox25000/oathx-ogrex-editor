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
    public partial class PayDayCreatOrder : UCPageBase
    {
        public string userName = string.Empty;  //用户名
        public string orderID = string.Empty;   //订单号
        protected int money = 0;                //充值金额
        protected string sign = string.Empty;
        protected string merId = string.Empty;
        protected string notifyUrl = string.Empty;
        protected string sendUrl = string.Empty;

        protected void Page_Load( object sender , EventArgs e )
        {
            //定义变量
            userName = GameRequest.GetFormString( "txtPayAccounts" );
            string reUserName = GameRequest.GetFormString( "txtPayReAccounts" );
            money = GameRequest.GetFormInt( "hdfSalePrice",0 );
            sendUrl = System.Configuration.ConfigurationSettings.AppSettings["DaySendUrl"];      //导向地址
            notifyUrl = System.Configuration.ConfigurationSettings.AppSettings["DayNotifyUrl"];  //同步回调地址
            string key = System.Configuration.ConfigurationSettings.AppSettings["DayKey"];       //密钥
            merId = System.Configuration.ConfigurationSettings.AppSettings["DayMerId"];          //商户ID


            //验证参数
            if ( userName != reUserName )
            {
                ShowAndRedirect( "两次输入的用户名不一致" , "/Pay/PayDay.aspx" );
                return;
            }
            if ( money == 0 )
            {
                ShowAndRedirect( "金额输入有误" , "/Pay/PayDay.aspx" );
                return;
            }

            //生成订单
            orderID = PayHelper.GetOrderIDByPrefix( "Day" );    //订单号
            OnLineOrder onlineOrder = new OnLineOrder( );
            onlineOrder.ShareID = 2;
            onlineOrder.OrderID = orderID;
            if ( Fetch.GetUserCookie( ) == null )
            {
                onlineOrder.OperUserID = 0;
            }
            else
            {
                onlineOrder.OperUserID = Fetch.GetUserCookie( ).UserID;
            }
            onlineOrder.Accounts = userName;
            onlineOrder.CardTotal = 1;
            onlineOrder.CardTypeID = money < 30 ? 1 : money < 60 ? 2 : money < 120 ? 3 : 4;
            onlineOrder.OrderAmount = money;
            onlineOrder.IPAddress = GameRequest.GetUserIP( );
            TreasureFacade treasureFacade = new TreasureFacade( );
            Message umsg = treasureFacade.RequestOrder( onlineOrder );
            if ( !umsg.Success )
            {
                RenderAlertInfo( true , umsg.Content , 2 );
                return;
            }

            //生成sign签名
            string signStr = merId + "|" + orderID + "|" + money + "|" + sendUrl + "|" + userName + "|" + key;
            sign = EncryptMD5( signStr , false , 32 );
        }
    }
}
