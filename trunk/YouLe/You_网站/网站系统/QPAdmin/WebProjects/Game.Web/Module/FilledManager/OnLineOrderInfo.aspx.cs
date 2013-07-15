using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Treasure;

namespace Game.Web.Module.FilledManager
{
    public partial class OnLineOrderInfo : AdminPage
    {
        #region Fields

        string orderID = GameRequest.GetQueryString("OrderID");

        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                OnLineOrderDataBind();
            }
        }
        #endregion

        #region 数据加载

        private void OnLineOrderDataBind()
        {
            if (orderID == "")
            {
                return;
            }

            //获取站点信息
            OnLineOrder onLineOrderInfo = aideTreasureFacade.GetOnLineOrderInfo(orderID);
            if (onLineOrderInfo == null)
            {
                ShowError("信息不存在");
                return;
            }

            CtrlHelper.SetText(litOrderID, onLineOrderInfo.OrderID.Trim());
            CtrlHelper.SetText(litApplyDate, onLineOrderInfo.ApplyDate.ToString("yyyy-MM-dd HH:mm:ss"));
            CtrlHelper.SetText(litAccounts, onLineOrderInfo.Accounts.Trim());
            CtrlHelper.SetText(litOrderAmount, onLineOrderInfo.OrderAmount.ToString("N"));
            CtrlHelper.SetText(litPayAmount, onLineOrderInfo.PayAmount.ToString("N"));
            CtrlHelper.SetText(litPresentScore, onLineOrderInfo.CardGold.ToString());
            if (onLineOrderInfo.OrderStatus == 0)
                CtrlHelper.SetText(litOrderStatus, "<span class='hong'>未付款</span>");
            else if (onLineOrderInfo.OrderStatus == 1)
                CtrlHelper.SetText(litOrderStatus, "<span class='lan'>已付款待处理</span>");
            else
                CtrlHelper.SetText(litOrderStatus, "<span class='lan'>成功</span>");
            CtrlHelper.SetText(litIPAddress, onLineOrderInfo.IPAddress.Trim() + "&nbsp;&nbsp;" + IPQuery.GetAddressWithIP(onLineOrderInfo.IPAddress.Trim()));
            CtrlHelper.SetText(litOperUserID, onLineOrderInfo.OperUserID.ToString());
        }
        #endregion
    }
}
