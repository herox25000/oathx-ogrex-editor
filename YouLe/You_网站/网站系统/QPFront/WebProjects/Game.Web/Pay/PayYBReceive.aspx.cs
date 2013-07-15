using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;

using com.yeepay.bank;

namespace Game.Web.Pay
{
    public partial class PayYBReceive : System.Web.UI.Page
    {
        #region Fields

        TreasureFacade treasureFacade = new TreasureFacade();
        #endregion

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                // 校验返回数据包
                BuyCallbackResult result = Buy.VerifyCallback(FormatQueryString.GetQueryString("p1_MerId"), FormatQueryString.GetQueryString("r0_Cmd"), FormatQueryString.GetQueryString("r1_Code"), FormatQueryString.GetQueryString("r2_TrxId"),
                    FormatQueryString.GetQueryString("r3_Amt"), FormatQueryString.GetQueryString("r4_Cur"), FormatQueryString.GetQueryString("r5_Pid"), FormatQueryString.GetQueryString("r6_Order"), FormatQueryString.GetQueryString("r7_Uid"),
                    FormatQueryString.GetQueryString("r8_MP"), FormatQueryString.GetQueryString("r9_BType"), FormatQueryString.GetQueryString("rp_PayDate"), FormatQueryString.GetQueryString("hmac"));

                if (string.IsNullOrEmpty(result.ErrMsg))
                {
                    //写易宝记录
                    ReturnYPDetailInfo resultYB = new ReturnYPDetailInfo();
                    resultYB.P1_MerId = FormatQueryString.GetQueryString("p1_MerId");
                    resultYB.R0_Cmd = FormatQueryString.GetQueryString("r0_Cmd");
                    resultYB.R1_Code = FormatQueryString.GetQueryString("r1_Code");
                    resultYB.R2_TrxId = FormatQueryString.GetQueryString("r2_TrxId");
                    resultYB.R3_Amt = Convert.ToDecimal(FormatQueryString.GetQueryString("r3_Amt"));
                    resultYB.R4_Cur = FormatQueryString.GetQueryString("r4_Cur");
                    resultYB.R5_Pid = FormatQueryString.GetQueryString("r5_Pid");
                    resultYB.R6_Order = FormatQueryString.GetQueryString("r6_Order");
                    resultYB.R7_Uid = FormatQueryString.GetQueryString("r7_Uid");
                    resultYB.R8_MP = FormatQueryString.GetQueryString("r8_MP");
                    resultYB.R9_BType = FormatQueryString.GetQueryString("r9_BType");
                    resultYB.Rb_BankId = FormatQueryString.GetQueryString("rb_BankId");
                    resultYB.Ro_BankOrderId = FormatQueryString.GetQueryString("ro_BankOrderId");
                    resultYB.Rp_PayDate = FormatQueryString.GetQueryString("rp_PayDate");
                    resultYB.Rq_CardNo = FormatQueryString.GetQueryString("rq_CardNo");
                    resultYB.Ru_Trxtime = FormatQueryString.GetQueryString("ru_Trxtime");
                    resultYB.Hmac = FormatQueryString.GetQueryString("hmac");
                    treasureFacade.WriteReturnYBDetail(resultYB);

                    if (result.R1_Code == "1")
                    {
                        if (result.R9_BType == "1")
                        {
                            // 写充值记录
                            ShareDetialInfo detailInfo = new ShareDetialInfo();
                            detailInfo.OrderID = resultYB.R6_Order;
                            detailInfo.IPAddress = Utility.UserIP;
                            detailInfo.PayAmount = resultYB.R3_Amt;
                            treasureFacade.FilliedOnline(detailInfo, 0);

                            //  callback方式:浏览器重定向
                            Response.Write("支付成功!<br>商品ID:" + result.R5_Pid + "<br>商户订单号:" + result.R6_Order + "<br>支付金额:" + result.R3_Amt + "<br>易宝支付交易流水号:" + result.R2_TrxId + "<BR>");
                        }
                        else if (result.R9_BType == "2")
                        {
                            // * 如果是服务器返回则需要回应一个特定字符串'SUCCESS',且在'SUCCESS'之前不可以有任何其他字符输出,保证首先输出的是'SUCCESS'字符串
                            Response.Write("SUCCESS");
                        }
                    }
                    else
                    {
                        Response.Write("支付失败!");
                    }
                }
                else
                {
                    Response.Write("交易签名无效!");
                }
            }
        }
    }
}
