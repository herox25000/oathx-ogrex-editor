using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Facade;
using Game.Utils;
using Game.Entity.Treasure;
using Game.Kernel;

namespace Game.Web
{
    public partial class AppStorePay : System.Web.UI.Page
    {
        #region Fields

        TreasureFacade treasureFacade = new TreasureFacade();
        int userID = GameRequest.GetQueryInt("UserID", 0);
        string orderID = GameRequest.GetQueryString("OrderID");
        int payAmount = GameRequest.GetQueryInt("PayAmount", 0);
        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                Response.Write(PayApp());
                Response.End();
            }
        }
        #endregion

        #region 公共方法

        private string PayApp()
        {
            #region 验证

            if (userID == 0 || orderID == "" || payAmount == 0)
            {
                return "非法操作。";
            }
            #endregion

            #region 处理

            ShareDetialInfo detailInfo = new ShareDetialInfo();

            //request
            detailInfo.UserID = userID;
            detailInfo.OrderID = orderID;
            detailInfo.PayAmount = Convert.ToDecimal(payAmount);
            detailInfo.ShareID = 100;

            Message msg = treasureFacade.FilliedApp(detailInfo);
            if (msg.Success)
            {
                return "0";
            }
            else
            {
                return msg.Content;
            }
            #endregion
            
        }
        
        #endregion
    }
}
