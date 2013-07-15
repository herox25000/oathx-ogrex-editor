using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Pay
{
    public partial class PayShow : UCPageBase
    {
        private TreasureFacade treasureFacade = new TreasureFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                InitStart();
            }
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "充值中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("充值订单信息 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 获取信息
        /// </summary>
        private void InitStart()
        {
            //查询订单编号
            string orderID = GameRequest.GetString("OrderID");

            OnLineOrder onlineOrder = treasureFacade.GetOnlineOrder(orderID);
            if ( onlineOrder != null )
            {
                lblOrderID.Text = onlineOrder.OrderID.ToString();
                lblAccounts.Text = onlineOrder.Accounts.ToString();
                lblGameID.Text = onlineOrder.GameID.ToString();
                lblCardName.Text = Convert.ToInt32(onlineOrder.OrderAmount) < 30 ? "蓝钻会员卡" : Convert.ToInt32(onlineOrder.OrderAmount) < 60 ? "黄钻会员卡" : Convert.ToInt32(onlineOrder.OrderAmount) < 120 ? "白钻会员卡" : "红钻会员卡";
                lblMemberMonth.Text = onlineOrder.OrderAmount / 10 + " 个月";
                lblPresentScore.Text = ( onlineOrder.CardGold * onlineOrder.OrderAmount / ( onlineOrder.CardPrice ) ).ToString( "N" );
                lblOrderAmount.Text = onlineOrder.OrderAmount.ToString( "N" );
            }

            string msg = "0";
            if (!String.IsNullOrEmpty(GameRequest.GetString("msg")))
            {
                msg = Request[ "msg" ].ToString( ).Trim( );
            }
            else
            {
                if (Request.QueryString["payResult"] == null)
                {
                    msg = "1";
                }
                else
                {
                    if (Request.QueryString["payResult"].ToString() != "10")
                    {
                        msg = "3";
                    }
                }
            }

            this.lblResults.Text = GetBillMessage(msg);
        }

        #region 公共方法

        private static string GetBillMessage(string msg)
        {
            if (msg == "1")
                return "在线支付成功，用户数据更新完成";
            if (msg == "2")
                return "在线支付成功，用户数据正在更新中";
            if (msg == "3")
                return "在线支付失败";
            else
                return "未知错误";
        }
        #endregion
    }
}
