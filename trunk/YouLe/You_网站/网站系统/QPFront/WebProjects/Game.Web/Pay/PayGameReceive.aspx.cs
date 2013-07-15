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
    public partial class PayGameReceive : Page
    {
        private TreasureFacade treasureFacade = new TreasureFacade( );

        protected void Page_Load( object sender , EventArgs e )
        {
            //初始化结果及地址
            ReturnKQDetailInfo result = new ReturnKQDetailInfo( );

            //获取充值卡网关账户号
            String merchantAcctId = Request[ "merchantAcctId" ].ToString( ).Trim( );
            result.MerchantAcctID = merchantAcctId;

            //设置充值卡网关密钥
            //区分大小写
            String key = ApplicationSettings.Get( "keyValueGame" );

            //获取处理结果
            ///支付结果0为成功，3为失败
            string payResult = Request[ "payResult" ].ToString( ).Trim( );
            result.PayResult = payResult;

            //获取快钱交易号 快钱多卡种订单号
            ///获取该交易的交易号
            String dealId = Request[ "dealId" ].ToString( ).Trim( );
            result.DealID = dealId;


            //获取商户订单号商户请求支付提交的订单号
            String orderId = Request[ "orderId" ].ToString( ).Trim( );
            result.OrderID = orderId;

            //获取实际支付金额
            ///单位为分
            ///比方 2 ，代表0.02元
            String payAmount = Request[ "payAmount" ].ToString( ).Trim( );
            result.PayAmount = Convert.ToDecimal( payAmount.Trim( ) );

            //获取请求时充值卡卡号

            String cardNumber = Request[ "cardNumber" ].ToString( ).Trim( );
            result.CardNumber = cardNumber.Trim( );

            //获取商户扩展字段1
            String ext1 = Request[ "ext1" ].ToString( ).Trim( );
            result.Ext1 = ext1.Trim( );

            //获取商户扩展字段2

         	String ext2 = Request[ "ext2" ].ToString( ).Trim( );
            if( !string.IsNullOrEmpty( ext2 ) )
            {
                result.Ext2 = ext2.Trim( ).Split( '/' )[ 0 ];

                //订单金额
                result.OrderAmount = Convert.ToDecimal( ext2.Trim( ).Split( '/' )[ 1 ] );
            }
            else
            {
                result.Ext2 = "";
            }

            //获取错误信息返回
            String errInfo = Request[ "errInfo" ].ToString( ).Trim( );
            result.ErrCode = errInfo;

            //获取加密签名串
            String signMsg = Request[ "signMsg" ].ToString( ).Trim( );
            result.SignMsg = signMsg;

            //生成加密串。必须保持如下顺序。
            String merchantSignMsgVal = "";
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "payResult" , payResult.ToString( ) );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "dealId" , dealId );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "merchantAcctId" , merchantAcctId );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "orderId" , orderId );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "payAmount" , payAmount );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "cardNumber" , cardNumber );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "ext1" , HttpUtility.UrlEncode( ext1 , Encoding.GetEncoding( "gb2312" ) ).Trim( ) );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "ext2" , HttpUtility.UrlEncode( ext2 , Encoding.GetEncoding( "gb2312" ) ).Trim( ) );
            merchantSignMsgVal = AppendParam( merchantSignMsgVal , "key" , key );

            String merchantSignMsg = TextEncrypt.EncryptPassword( merchantSignMsgVal ).ToUpper( );

            //订单提交时间
            result.OrderTime = DateTime.Now;

            //快钱交易时间
            result.DealTime = DateTime.Now;

            //快钱支付结果入库
            treasureFacade.WriteReturnKQDetail( result );

            //支付金额小于订单金额不做任何处理
            //if( result.PayAmount != result.OrderAmount )
            //{
            //    Response.Write( "OK" );
            //    Response.End( );
            //}

            //商家进行数据处理，并跳转会商家显示支付结果的页面
            ///首先进行签名字符串验证
            if( signMsg.ToUpper( ) == merchantSignMsg.ToUpper( ) )
            {
                switch( payResult )
                {
                    case "0":
                        /*  
                        // 商户网站逻辑处理，比方更新订单支付状态为成功
                        // 特别注意：只有signMsg.ToUpper() == merchantSignMsg.ToUpper()，且payResult=10，才表示支付成功！
                        */

                        //报告给快钱处理结果，并提供将要重定向的地址。
                        ShareDetialInfo detailInfo = new ShareDetialInfo( );
                        detailInfo.OrderID = result.OrderID;
                        detailInfo.PayAmount = result.PayAmount;
                        detailInfo.IPAddress = Utility.UserIP;

                        //写充值记录
                        Message msg = treasureFacade.FilliedOnline( detailInfo , 0 );
                        Response.Write( "OK" );
                        break;     
                    default:
                        Response.Write( "OK" );
                        break;
                }
            }
            else
            {
                Response.Write( "OK" );
            }
        }

        //功能函数。将变量值不为空的参数组成字符串
        private String AppendParam( String returnStr , String paramId , String paramValue )
        {
            if( returnStr != "" )
            {
                if( paramValue != "" )
                {
                    returnStr += "&" + paramId + "=" + paramValue;
                }
            }
            else
            {
                if( paramValue != "" )
                {
                    returnStr = paramId + "=" + paramValue;
                }
            }

            return returnStr;
        }

        /// <summary>
        /// 将所有参数组成字符串返回
        /// </summary>
        /// <param name="returnStr"></param>
        /// <param name="paramId"></param>
        /// <param name="paramValue"></param>
        /// <returns></returns>
        private String AppendAllParam( String returnStr , String paramId , String paramValue )
        {
            if( returnStr != "" )
            {
                returnStr += "&" + paramId + "=" + paramValue;
            }
            else
            {
                returnStr = paramId + "=" + paramValue;
            }

            return returnStr;
        }
    }
}
