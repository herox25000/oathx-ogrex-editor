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
    public partial class PayVBReceive : UCPageBase
    {
        private TreasureFacade treasureFacade = new TreasureFacade();

        protected void Page_Load(object sender, EventArgs e)
        {
            BindData( );
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

        //更新数据
        private void BindData()
        {
            ReturnVBDetailInfo result = new ReturnVBDetailInfo();

            string spid = ApplicationSettings.Get("spId"); //'sp号码
            string sppwd = ApplicationSettings.Get("spKeyValue");//'sp18位密码

            //'接受服务器url get参数                            
            string rtmd5 = Request.QueryString["v1"]; //   '服务器MD5 
            result.Rtmd5 = rtmd5;

            string trka = Request.QueryString["v2"];  //  'V币号码15位
            result.Rtka = trka;

            string rtmi = Request.QueryString["v3"]; //   '密码'V币密码6位 （可能为空 老V币没有密码）
            result.Rtmi = rtmi;

            string rtmz = Request.QueryString["v4"];    //  '面值1-999 整数
            result.Rtmz = Convert.ToInt32(rtmz);

            string rtlx = Request.QueryString["v5"];    //  '卡的类型  1 2 3 
            result.Rtlx = Convert.ToInt32(rtlx);

            string rtoid = Request.QueryString["v6"]; // '网盈一号通服务器端订单 
            result.Rtoid = rtoid;

            string rtcoid = Request.QueryString["v7"];  //  '商户自己订单
            result.OrderID = rtcoid;

            string rtuserid = Request.QueryString["v8"];// '商户的用户ID 
            result.Rtuserid = rtuserid;

            string rtcustom = Request.QueryString["v9"]; //'商户自己定义数据
            result.Rtcustom = rtcustom;

            string rtflag = Request.QueryString["v10"]; // '返回状态. 1正常发送 2补单发送
            result.Rtflag = Convert.ToInt32(rtflag);

            string get_key = trka + rtmi + rtoid + spid + sppwd + rtcoid + rtflag + rtmz;
            result.EcryptStr = get_key;
            //'卡+密+网盈一号通服务器端订单+ 5位spid+ 18位SP密码+商户订单+rtflag返回类型1或2 +面值
            //'LCase函数是将字符转换为小写; Ucase函数是将字符转换为大写
            //'全国声讯支付联盟全国声讯电话支付接口对MD5值只认大写字符串，所以小写的MD5值得转换为大写
            string md5password = TextEncrypt.EncryptPassword(get_key).ToUpper();  //  '先MD5 32 然后转大写
            result.SignMsg = md5password;

            //'流程 第1次访问此页面 是盈华讯方服务器调用此页面1次 ，你先判断订单（订单包含金额，面值，状态等消息）
            //'如果订单是没有使用状态并金额一致就MD5校验，校验通过 你发送“header("Data-Received:ok_vpay8"); ”
            //'给盈华讯方服务器，服务器接收到这个头 后判断（ 你已经给用户加点了)，然后就把本页面转向给你
            //，此时转发的数据和第一次服务器直接调用的一致 此次你只需要根据订单，给用户提示冲值成功就可以了。
            //如果你没有发送头或网络中断，我就会给用户提示补单的消息（他可以自己点击，也可以我方服务器自动
            //补发，补发数据的MD5和第一发送的不一样，里面的“$_GET['v10']”'返回状态. 1为正常发送回来 2为补单发送回来）
            // 做好加点后一定要把订单 状态改变。！并注意安全处理。  
            //关于订单安全做法 如有不明请电话：0755-82126136 徐先生 

            //此页面不要使用SEESION cooke  请用数据库管理你的订单 */
            //////////此处请商户自己编写求出订单状态代码 以备下方条件判断用！

            //写VB返回记录

            if (rtmd5 == "" || rtmd5 == null)
            {
                litMsg.Text = "没有此订单信息";
                return;
            }
            treasureFacade.WriteReturnVBDetail( result );

            //'步骤1  :包含A和B
            //'A步骤,盈华讯方服务器第一次探测商户服务器状态.并给该订单充值 
            //'B步骤,检查该订单如果订单使用了 就把该订单的充值记录给用户打印.
            if (rtflag == "1")
            {
                if (md5password == rtmd5)
                {
                    //'校验商户订单号码状态 
                    string orderID = rtcoid.Trim();
                    OnLineOrder order = treasureFacade.GetOnlineOrder(orderID);
                    if (order != null)
                    {
                        if (order.OrderStatus == 0)
                        {
                            //充值
                            ShareDetialInfo detailInfo = new ShareDetialInfo();
                            detailInfo.OrderID = orderID;
                            detailInfo.PayAmount = Convert.ToDecimal( rtmz );
                            detailInfo.IPAddress = Utility.UserIP;
                            Message msg = treasureFacade.FilliedOnline(detailInfo, 1);
                            if (msg.Success)
                            {
                                BindText( order );
                            }
                        }
                        else
                        {
                            BindText( order );
                        }
                    }
                }
            }

            //'步骤2  :包含A补单
            //'A补单：如果由于网络服务器中断或加点失败,会在5分钟内开始给用户补发数据.持续200次 24个小时
            if (rtflag == "2")
            {
                if (md5password == rtmd5)
                {
                    //'校验商户订单号码状态 
                    string orderID = rtcoid.Trim();
                    OnLineOrder order = treasureFacade.GetOnlineOrder( orderID );
                    if (order != null)
                    {
                        if (order.OrderStatus == 0)
                        {
                            //充值
                            ShareDetialInfo detailInfo = new ShareDetialInfo( );
                            detailInfo.OrderID = orderID;
                            detailInfo.PayAmount = Convert.ToDecimal( rtmz );
                            detailInfo.IPAddress = Utility.UserIP;
                            Message msg = treasureFacade.FilliedOnline( detailInfo , 1 );
                            if (msg.Success)
                            {
                               BindText( order );
                            }
                        }
                        else
                        {
                            BindText( order );
                        }
                    }
                }
            }
        }

        //绑定数据
        private void BindText( OnLineOrder order )
        {
            litMsg.Text = "在线支付成功，用户数据更新完成";
            lblOrderID.Text = order.OrderID.ToString( );
            lblAccounts.Text = order.Accounts.ToString( );
            lblGameID.Text = order.GameID.ToString( );
            lblCardName.Text = Convert.ToInt32( order.OrderAmount ) < 30 ? "蓝钻会员卡" : Convert.ToInt32( order.OrderAmount ) < 60 ? "黄钻会员卡" : Convert.ToInt32( order.OrderAmount ) < 120 ? "白钻会员卡" : "红钻会员卡";
            lblMemberMonth.Text = order.OrderAmount / 10 + " 个月";
            lblPresentScore.Text = ( order.CardGold * order.OrderAmount / ( order.CardPrice * 2 ) ).ToString( "N" );
            lblOrderAmount.Text = order.OrderAmount.ToString( "N" );

            Response.AddHeader( "Data-Received" , "ok_vpay8" );// '此句不能删除也不能修改，作为探测成功之用
        }

    }
}
