using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Utils;
using Game.Web.UI;
using System.Text;

using Game.Entity.Accounts;
using Game.Kernel;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class AccountsGoldInfo : AdminPage
    {
        #region Fields       

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-财富信息";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
                BindData( );
            BindDataOnline( );
        }


        #region 按钮事件

        //Button_ClearUserOnline
        protected void Button_ClearUserOnline( object sender , EventArgs e )
        {
            AuthUserOperationPermission( Permission.Enable );
            aideTreasureFacade.DeleteGameScoreLockerByUserID( IntParam );
            MessageBox( "清除成功" , "AccountsGoldInfo.aspx?param=" + IntParam );
        }

        #endregion

        #endregion

        #region 数据加载
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

            CtrlHelper.SetText( ltGameID,  model.GameID.ToString( )  );
            CtrlHelper.SetText( ltAccounts, model.Accounts.Trim( ) );

            //金币信息
            GameScoreInfo scoreInfo = aideTreasureFacade.GetGameScoreInfoByUserID( IntParam );
            if ( scoreInfo == null )
            {
                return;
            }
            CtrlHelper.SetText( ltScore, scoreInfo.Score.ToString( ) );
            CtrlHelper.SetText( ltInsureScore, scoreInfo.InsureScore.ToString( ) );
            CtrlHelper.SetText( ltWinCount, scoreInfo.WinCount.ToString( ) );
            CtrlHelper.SetText( ltLostCount, scoreInfo.LostCount.ToString( ) );
            CtrlHelper.SetText( ltDrawCount, scoreInfo.DrawCount.ToString( ) );
            CtrlHelper.SetText( ltFleeCount, scoreInfo.FleeCount.ToString( ) );
            CtrlHelper.SetText( ltRevenue, scoreInfo.Revenue.ToString( ) );

            //登录房间、注册信息
            CtrlHelper.SetText( ltGameLogonTimes, scoreInfo.AllLogonTimes.ToString( ) );
            CtrlHelper.SetText( ltLastLogonDate, scoreInfo.LastLogonDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            CtrlHelper.SetText( ltLogonSpacingTime, Fetch.GetTimeSpan( Convert.ToDateTime( scoreInfo.LastLogonDate ), DateTime.Now ) );

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

        protected void BindDataOnline( )
        {
            //用户卡线记录
            StringBuilder where = new StringBuilder( );
            where.AppendFormat( "Where UserID={0}" , IntParam );
            string order = "ORDER BY CollectDate DESC";
            PagerSet pg = aideTreasureFacade.GetGameScoreLockerList( 1 , 100 , where.ToString( ) , order );
            if ( pg.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptLocker.DataSource = pg.PageSet;
                rptLocker.DataBind( );
            }
            else
            {
                rptLocker.Visible = false;
                plMsg.Visible = true;
                Button1.Visible = false;
            }
        }
        #endregion

    }
}
