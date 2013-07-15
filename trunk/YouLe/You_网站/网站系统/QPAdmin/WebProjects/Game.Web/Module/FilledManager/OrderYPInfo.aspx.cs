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
    public partial class OrderYPInfo : AdminPage
    {
        #region Fields

        int id = GameRequest.GetQueryInt("id", 0);      

        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                DetailDataBind();
            }
        }        
        #endregion

        #region 数据加载

        private void DetailDataBind()
        {
            if (id <= 0)
            {
                return;
            }

            //获取站点信息
            ReturnYPDetailInfo YBDetailInfo = aideTreasureFacade.GetYPDetailInfo(id);
            if (YBDetailInfo == null)
            {
                ShowError("信息不存在");
                return;
            }

            CtrlHelper.SetText(litR6_Order, "<a class='l' href='javascript:void(0)' onclick=\"javascript:openWindowOwn('OnLineOrderInfo.aspx?OrderID=" + YBDetailInfo.R6_Order + "','online_" + YBDetailInfo.R6_Order + "',600,465)\">" + YBDetailInfo.R6_Order + "</a>");
            if (YBDetailInfo.R1_Code == "1")
                CtrlHelper.SetText(litR1_Code, "<span class='lan'>成功</span>");
            else
                CtrlHelper.SetText(litR1_Code, "<span class='hong'>失败</span>");
            CtrlHelper.SetText(litR2_TrxId, YBDetailInfo.R2_TrxId.Trim());
            CtrlHelper.SetText(litR3_Amt, YBDetailInfo.R3_Amt.ToString("N"));
            CtrlHelper.SetText(litR5_Pid, YBDetailInfo.R5_Pid.Trim());
            CtrlHelper.SetText(litR8_MP, YBDetailInfo.R8_MP.Trim());
            CtrlHelper.SetText(litR9_BType, YBDetailInfo.R9_BType.Trim() == "1" ? "浏览器重定向" : "服务器点对点通讯");
            CtrlHelper.SetText(litRb_BankId, GetBankName(YBDetailInfo.Rb_BankId.Trim()));
            CtrlHelper.SetText(litRo_BankOrderId, YBDetailInfo.Ro_BankOrderId.Trim());
            CtrlHelper.SetText(litRp_PayDate, GetYbTime(YBDetailInfo.Rp_PayDate.Trim()));
            CtrlHelper.SetText(litRq_CardNo, YBDetailInfo.Rq_CardNo.Trim());
            CtrlHelper.SetText(litRu_Trxtime, GetYbTime(YBDetailInfo.Ru_Trxtime.Trim()));
            CtrlHelper.SetText(litHmac, YBDetailInfo.Hmac.Trim());
            CtrlHelper.SetText(litCollectDate, YBDetailInfo.CollectDate.ToString("yyyy-MM-dd HH:mm:ss"));            
        }

        //获取银行名称
        private string GetBankName(string bankID)
        {
            Dictionary<string, string> bankList = new Dictionary<string, string>();
            string rValue="";
            bankList.Add("1000000-NET", "易宝会员支付");
            bankList.Add("ICBC-NET", "工商银行");
            bankList.Add("ICBC-WAP", "工商银行WAP");
            bankList.Add("CMBCHINA-NET", "招商银行");
            bankList.Add("CMBCHINA-WAP", "招商银行WAP");
            bankList.Add("ABC-NET", "中国农业银行");
            bankList.Add("CCB-NET", "建设银行");
            bankList.Add("CCB-PHONE", "建设银行WAP");
            bankList.Add("BCCB-NET", "北京银行");
            bankList.Add("BOCO-NET", "交通银行");
            bankList.Add("CIB-NET", "兴业银行");
            bankList.Add("NJCB-NET", "南京银行");
            bankList.Add("CMBC-NET", "中国民生银行");
            bankList.Add("CEB-NET", "光大银行");
            bankList.Add("BOC-NET", "中国银行");
            bankList.Add("PAB-NET", "平安银行");
            bankList.Add("CBHB-NET", "渤海银行");
            bankList.Add("HKBEA-NET", "东亚银行");
            bankList.Add("NBCB-NET", "宁波银行");
            bankList.Add("ECITIC-NET", "中信银行");
            bankList.Add("SDB-NET", "深圳发展银行");
            bankList.Add("GDB-NET", "广东发展银行");
            bankList.Add("SPDB-NET", "上海浦东发展银行");
            bankList.Add("POST-NET", "中国邮政");
            bankList.Add("BJRCB-NET", "北京农村商业银行");

            if (bankList.ContainsKey(bankID))
            {
                bankList.TryGetValue(bankID, out rValue);
            }
            else
            {
                rValue = "未知";
            }
            return rValue;
        }

        //格式化易宝时间
        private string GetYbTime(string time)
        {
            string rValue = "";
            if (time != "")
            {
                rValue = time.Substring(0, 4) + "-" + time.Substring(4, 2) + "-" + time.Substring(6, 2) + " " + time.Substring(8, 2) + ":" + time.Substring(10, 2) + ":" + time.Substring(12, 2);
            }
            return rValue;
        }
        #endregion

        
    }
}
