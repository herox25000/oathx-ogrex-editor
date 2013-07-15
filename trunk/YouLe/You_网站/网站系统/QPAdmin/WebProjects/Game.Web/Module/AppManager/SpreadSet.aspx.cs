using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Facade;
using Game.Kernel;
using System.Collections;
using System.Text;
using Game.Entity.Treasure;
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class SpreadSet : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindData( );
            }
        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            double FillGrantRate = CtrlHelper.GetInt( txtFillGrantRate, 0 );
            double BalanceRate = CtrlHelper.GetInt( txtBalanceRate, 0 );
            GlobalSpreadInfo spread = aideTreasureFacade.GetGlobalSpreadInfo( 1 );
            spread.RegisterGrantScore = CtrlHelper.GetInt( txtRegGrantScore, 0 );
            spread.PlayTimeCount = CtrlHelper.GetInt( txtPlayTimeCount, 0 );
            spread.PlayTimeGrantScore = CtrlHelper.GetInt( txtPlayTimeGrantScore, 0 );
            spread.FillGrantRate = ( decimal ) ( FillGrantRate / 100 );
            spread.BalanceRate = ( decimal ) ( BalanceRate / 100 );
            spread.MinBalanceScore = CtrlHelper.GetInt( txtMinBalanceScore, 0 );

            try
            {
                aideTreasureFacade.UpdateGlobalSpreadInfo( spread );
                ShowInfo( "更新成功" );
            }
            catch 
            {
                ShowError( "更新失败" );
            }

        }
        #endregion

        #region 数据加载

        private void BindData( )
        {
            GlobalSpreadInfo spreadinfo = aideTreasureFacade.GetGlobalSpreadInfo( 1 );
            if ( spreadinfo == null )
                return;
            CtrlHelper.SetText( txtRegGrantScore, spreadinfo.RegisterGrantScore.ToString( ) );
            CtrlHelper.SetText( txtPlayTimeCount, spreadinfo.PlayTimeCount.ToString( ) );
            CtrlHelper.SetText( txtPlayTimeGrantScore, spreadinfo.PlayTimeGrantScore.ToString( ) );
            CtrlHelper.SetText( txtFillGrantRate, (Convert.ToInt32( spreadinfo.FillGrantRate * 100 )).ToString( ) );
            CtrlHelper.SetText( txtBalanceRate, ( Convert.ToInt32(spreadinfo.BalanceRate * 100 )).ToString( ) );
            CtrlHelper.SetText( txtMinBalanceScore, spreadinfo.MinBalanceScore.ToString( ) );
        }
        #endregion
    }
}
