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
using Game.Kernel;
using System.Text;
using Game.Entity.Enum;
using System.Data;

namespace Game.Web.Module.FilledManager
{
    public partial class LivcardCreate : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                txtValidDate.Text = DateTime.Now.AddMonths( 1 ).ToString( "yyyy-MM-dd" );
                txtRemark.Text = string.Format( "管理员【{0}】 于 {1} 生成", userExt.Username, DateTime.Now.ToString( "yyyy-MM-dd" ) );
                BindCardType( );
                BindData( );
            }
        }
        protected void ddlCardType_SelectedIndexChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        //重置
        protected void btnReset_Click( object sender, EventArgs e )
        {
            txtCount.Text = "";
        }
        //生成实卡
        protected void btnCreate_Click( object sender, EventArgs e )
        {
            #region 验证
            //判断权限
            AuthUserOperationPermission( Permission.CreateCard );
            int cardCount = CtrlHelper.GetInt( txtCount, 0 );
            int cardTypeID = string.IsNullOrEmpty( ddlCardType.SelectedValue ) ? 0 : int.Parse( ddlCardType.SelectedValue );
            if ( cardTypeID <= 0 )
            {
                ShowError( "请先添加实卡类型" );
                return;
            }
            if ( cardCount <= 0 )
            {
                ShowError( "生成实卡的数量必须大于零的整数" );
                return;
            }
            if ( cardCount > 10000 )
            {
                ShowError( "生成实卡的数量一次最多10000张" );
                return;
            }
            // 卡号规则
            int cardLen = CtrlHelper.GetInt( txtCardNumLen, 0 );
            if ( cardLen < 15 || cardLen > 32 )
            {
                ShowError( "卡号长度必须大于等于15小于32 " );
                return;
            }
            //卡密规则
            int passwordLen = CtrlHelper.GetInt( txtPassLen, 0 );
            if ( passwordLen < 8 || passwordLen > 32 )
            {
                ShowError( "密码长度必须大于等于8小于33 " );
                return;
            }
            #endregion

            GlobalLivcard cardType = aideTreasureFacade.GetGlobalLivcardInfo( cardTypeID );
            if ( cardType == null )
            {
                ShowError( "实卡类型不存在" );
                return;
            }
            byte[ ] bytes = Encoding.Default.GetBytes( "" );
            LivcardBuildStream cardBuild = new LivcardBuildStream( );
            cardBuild.AdminName = userExt.Username;
            cardBuild.BuildAddr = GameRequest.GetUserIP( );
            cardBuild.BuildCardPacket = bytes;
            cardBuild.BuildCount = cardCount;
            cardBuild.BuildDate = DateTime.Now;
            cardBuild.CardGold = cardType.CardGold;
            cardBuild.CardPrice = cardType.CardPrice;
            cardBuild.CardTypeID = cardTypeID;
            cardBuild.DownLoadCount = 0;
            cardBuild.NoteInfo = CtrlHelper.GetText( txtRemark );
            int buildID = aideTreasureFacade.InsertLivcardBuildStream( cardBuild );
            if ( buildID <= 0 )
            {
                ShowError( "添加实卡批次失败" );
                return;
            }
            //实卡信息
            LivcardAssociator card = new LivcardAssociator( );
            card.BuildID = buildID;
            card.CardTypeID = cardType.CardTypeID;
            card.CardPrice = cardType.CardPrice;
            card.CardGold = CtrlHelper.GetInt( txtCardGold , 0 );
            card.MemberOrder = cardType.MemberOrder;
            card.MemberDays = CtrlHelper.GetInt( txtMemberDays , 0 );
            card.UserRight = cardType.UserRight;
            card.ServiceRight = cardType.ServiceRight;
            card.UseRange = int.Parse( ddlUseRange.SelectedValue );
            card.SalesPerson = CtrlHelper.GetText( txtSalesPerson );
            card.ValidDate = Convert.ToDateTime( txtValidDate.Text.Trim( ) );
            
            StringBuilder sb = new StringBuilder( );
            string[,] list = new string[cardCount , 2];
            int i=0;
            Random rand = new Random( );
            while ( cardCount > 0 )
            {
                string serialID = GetSerialID( cardLen , cardType.CardTypeID , rand );//卡号
                bool isRepeat = false;
                for ( int j = i; j > 0; j-- )
                {
                    if ( list[j , 0] == serialID )
                    {
                        isRepeat = true;
                        break;
                    }
                }
                if ( isRepeat )
                {
                    isRepeat = false;
                    continue;
                }
                string password = GetPassword( passwordLen,rand );//卡密
                sb.AppendFormat( "{0},{1}/" , serialID , password );
                list[i , 0] = serialID;
                list[i , 1] = Utility.MD5( password );
                cardCount--;
                i++;
            }
            aideTreasureFacade.InsertLivcardAssociator( card , list);
            bytes = Encoding.Default.GetBytes( sb.ToString( ) );
            cardBuild.BuildID = buildID;
            cardBuild.BuildCardPacket = bytes;
            try
            {
                aideTreasureFacade.UpdateLivcardBuildStream( cardBuild );
                txtCount.Text = "0";
                ShowInfo( "生成会员卡成功" );
            }
            catch 
            {
                ShowError( "生成会员卡失败" );
            }

        }
        private static bool ExistsSerialID( string[] s )
        {
            return true;
        }
        //生成卡号：前缀+日期(yyyyMM)+随机数字串
        private string GetSerialID( int length,int cardType , Random rand)
        {
            string tempID = "";
            if ( !string.IsNullOrEmpty( txtInitial.Text.Trim( ) ) )
                tempID = txtInitial.Text.Trim( );
            StringBuilder builder = new StringBuilder( );
            for ( int i = length; i > 0; i-- )
            {
                builder.Append( rand.Next( 0 , 9 ).ToString( ) );
            }
            tempID = tempID + DateTime.Now.ToString( "yyMMdd" ) + DateTime.Now.Minute.ToString( ) + cardType.ToString( ) + builder.ToString( );
            return tempID.Substring( 0, length );
        }
        //生成实卡密码
        private string GetPassword( int length, Random rand )
        {
            string tempPassNum = "";
            bool isDigit = ckbDigit.Checked;
            bool isLower = ckbLower.Checked;
            bool isUpper = ckbUpper.Checked;
            if( isDigit && isLower && isUpper )//数字+小写字母+大写字母
                tempPassNum = Fetch.GetRandomNumericAndEn( 32 , rand );
            else if( isDigit && !isLower && !isUpper )//纯数字
            {
                StringBuilder builder = new StringBuilder( );
                for( int i = length; i > 0; i-- )
                {
                    builder.Append( rand.Next( 0 , 9 ).ToString( ) );
                }
                tempPassNum = builder.ToString( );
            }
            else if( !isDigit && isLower && !isUpper )//纯小写字母
                tempPassNum = Fetch.GetRandomStr( 32 , false , rand ).ToLower( );
            else if( !isDigit && !isLower && isUpper )//纯大写字母
                tempPassNum = Fetch.GetRandomStr( 32 , false , rand ).ToUpper( );
            else if( isDigit && isLower && !isUpper )//数字+小写字母
                tempPassNum = Fetch.GetRandomNumericAndEn( 32 , rand ).ToLower( );
            else if( isDigit && !isLower && isUpper )//数字+大写字母
                tempPassNum = Fetch.GetRandomNumericAndEn( 32 , rand ).ToUpper( );
            else if( !isDigit && isLower && isUpper )//小写字母+大写字母
                tempPassNum = Fetch.GetRandomStr( 32 , false , rand );
            else
            {
                StringBuilder builder = new StringBuilder( );
                for( int i = length; i > 0; i-- )
                {
                    builder.Append( rand.Next( 0 , 9 ).ToString( ) );
                }
                tempPassNum = builder.ToString( );
            }
            return tempPassNum.Substring( 0, length );
        }

        #endregion

        #region 数据加载
        //实卡类型
        private void BindCardType( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGlobalLivcardList( 1, 1000, "", "ORDER BY CardTypeID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlCardType.DataSource = pagerSet.PageSet;
                ddlCardType.DataTextField = "CardName";
                ddlCardType.DataValueField = "CardTypeID";
                ddlCardType.DataBind( );
            }
        }
        private void BindData( )
        {
            int cardTypeID = string.IsNullOrEmpty( ddlCardType.SelectedValue ) ? 0 : int.Parse( ddlCardType.SelectedValue );
            if ( cardTypeID <= 0 )
                return;
            GlobalLivcard cardType = aideTreasureFacade.GetGlobalLivcardInfo( cardTypeID );
            if ( cardType == null )
                return;

            CtrlHelper.SetText( ltCardPrice, cardType.CardPrice.ToString( ) );
            CtrlHelper.SetText( txtCardGold, cardType.CardGold.ToString( ) );
            CtrlHelper.SetText( ltMemberOrder, GetMemberName( cardType.MemberOrder ) );
            CtrlHelper.SetText( txtMemberDays, cardType.MemberDays.ToString( ) );

        }
        #endregion

    }
}
