using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Utils;
using Game.Web.UI;
using Game.Entity.Accounts;
using Game.Kernel;
using Game.Entity.Treasure;
using Game.Facade;
using System.Data;
using Game.Facade.Facade;


namespace Game.Web.Module.AccountManager
{
    public partial class AccountsScoreInfo : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-积分信息";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
            {
                BindGameInfo( );
                BindData( );
            }
        }
        protected void ddlGame_SelectedIndexChanged( object sender, EventArgs e )
        {
            BindData( );
        }
        #endregion

        #region 数据加载
        private void BindGameInfo( )
        {
            DataSet ds = aidePlatformFacade.GetGameList( );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                ddlGame.DataSource = ds.Tables[0];
                ddlGame.DataTextField = "KindName";
                ddlGame.DataValueField = "KindID";
                ddlGame.DataBind( );
            }
            ddlGame.Items.Insert( 0, new ListItem( "选择游戏", "0" ) );
        }

        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;
            //获取信息
            AccountsInfo model = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            if ( model == null )
            {
                MessageBox( "用户信息不存在" );
                return;
            }

            CtrlHelper.SetText( ltGameID, model.GameID.ToString( ) );
            CtrlHelper.SetText( ltAccounts, model.Accounts.Trim( ) );
            int kindID = int.Parse( ddlGame.SelectedValue );
            if ( kindID <= 0 )
                return;          

            //积分信息
            //GameScoreFacade aideGameScoreFacade = new GameScoreFacade( aidePlatformFacade.GetConn( kindID ) );
            //Game.Entity.GameScore.GameScoreInfo scoreInfo = aideGameScoreFacade.GetGameScoreInfoByUserId( IntParam );
            GameScoreInfo scoreInfo = new TreasureFacade( kindID ).GetGameScoreInfoByUserID( IntParam );
            if ( scoreInfo == null )
            {
                return;
            }
            CtrlHelper.SetText( ltScore, scoreInfo.Score.ToString( ) );

            CtrlHelper.SetText( ltWinCount, scoreInfo.WinCount.ToString( ) );
            CtrlHelper.SetText( ltLostCount, scoreInfo.LostCount.ToString( ) );
            CtrlHelper.SetText( ltDrawCount, scoreInfo.DrawCount.ToString( ) );
            CtrlHelper.SetText( ltFleeCount, scoreInfo.FleeCount.ToString( ) );


            //登录房间、注册信息
            CtrlHelper.SetText( ltGameLogonTimes, scoreInfo.AllLogonTimes.ToString( )+"次" );
            CtrlHelper.SetText( ltLastLogonDate, scoreInfo.LastLogonDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            CtrlHelper.SetText( ltLogonSpacingTime, Fetch.GetTimeSpan( Convert.ToDateTime( scoreInfo.LastLogonDate ), DateTime.Now )+"前" );

            CtrlHelper.SetText( ltLastLogonIP, scoreInfo.LastLogonIP.ToString( ) );
            CtrlHelper.SetText( ltLogonIPInfo, IPQuery.GetAddressWithIP( scoreInfo.LastLogonIP.ToString( ) ) );
            CtrlHelper.SetText( ltLastLogonMachine, scoreInfo.LastLogonMachine.ToString( ) );
            CtrlHelper.SetText( ltRegisterDate, scoreInfo.RegisterDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            CtrlHelper.SetText( ltRegisterIP, scoreInfo.RegisterIP.ToString( ) );
            CtrlHelper.SetText( ltRegIPInfo, IPQuery.GetAddressWithIP( scoreInfo.RegisterIP.ToString( ) ) );
            CtrlHelper.SetText( ltRegisterMachine, scoreInfo.RegisterMachine.ToString( ) );
            CtrlHelper.SetText( ltOnLineTimeCount, scoreInfo.OnLineTimeCount.ToString( ) );
            CtrlHelper.SetText( ltPlayTimeCount, scoreInfo.PlayTimeCount.ToString( ) );
        }
        #endregion
    }
}
