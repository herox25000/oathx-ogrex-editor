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
    public partial class OrderKQInfo : AdminPage
    {
        #region Fields

        int id = GameRequest.GetQueryInt("id", 0);
        BillPayType billPayType = new BillPayType(TextUtility.GetRealPath("/config/BillPayType.xml"));
        BillBanks billBanks = new BillBanks(TextUtility.GetRealPath("/config/BillBanks.xml"));
        BillErrorMsg billErrorMsg = new BillErrorMsg(TextUtility.GetRealPath("/config/BillErrorMsg.xml"));

        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                KQDetailDataBind();
            }
        }        
        #endregion

        #region 数据加载

        private void KQDetailDataBind()
        {
            if (id <= 0)
            {
                return;
            }

            //获取站点信息
            ReturnKQDetailInfo kQDetailInfo = aideTreasureFacade.GetKQDetailInfo(id);
            if (kQDetailInfo == null)
            {
                ShowError("信息不存在");
                return;
            }

            CtrlHelper.SetText(litOrderID, "<a class='l' href='javascript:void(0)' onclick=\"javascript:openWindowOwn('OnLineOrderInfo.aspx?OrderID=" + kQDetailInfo.OrderID + "','online_" + kQDetailInfo.OrderID + "',600,465)\">" + kQDetailInfo.OrderID + "</a>");
            CtrlHelper.SetText(litOrderTime, kQDetailInfo.OrderTime.ToString("yyyy-MM-dd HH:ss:mm"));
            CtrlHelper.SetText(litOrderAmount, kQDetailInfo.OrderAmount.ToString("N"));
            CtrlHelper.SetText(litPayAmount, kQDetailInfo.PayAmount.ToString("N"));
            CtrlHelper.SetText(litFee, kQDetailInfo.Fee.ToString("f3"));
            CtrlHelper.SetText(litRevenue, (kQDetailInfo.PayAmount - kQDetailInfo.Fee).ToString("f3"));
            if (kQDetailInfo.PayResult == "10")
                CtrlHelper.SetText(litPayResult, "<span class='lan'>成功</span>");
            else
                CtrlHelper.SetText(litPayResult, "<span class='hong'>失败</span>");
            CtrlHelper.SetText(litDealID, kQDetailInfo.DealID);
            CtrlHelper.SetText(litDealTime, kQDetailInfo.DealTime.ToString("yyyy-MM-dd HH:mm:ss"));
            CtrlHelper.SetText(litBankDealID, kQDetailInfo.BankDealID);
            CtrlHelper.SetText(litPayType, billPayType.GetBillPayType(kQDetailInfo.PayType.Trim()));
            CtrlHelper.SetText(litBankID, billBanks.GetBillBanksByCode(kQDetailInfo.BankID.Trim()));
            CtrlHelper.SetText(litErrCode, kQDetailInfo.ErrCode);
            CtrlHelper.SetText(litVersion, kQDetailInfo.Version);
            CtrlHelper.SetText(litLanguage, "中文");
            CtrlHelper.SetText(litExt1, kQDetailInfo.Ext1 + "&nbsp;&nbsp;" + IPQuery.GetAddressWithIP(kQDetailInfo.Ext1));
            CtrlHelper.SetText(litExt2, kQDetailInfo.Ext2);
            CtrlHelper.SetText(litSignType, "与提交订单时的签名类型保持一致");
            CtrlHelper.SetText(litSignMsg, kQDetailInfo.SignMsg);
        }
        #endregion
    }
}
