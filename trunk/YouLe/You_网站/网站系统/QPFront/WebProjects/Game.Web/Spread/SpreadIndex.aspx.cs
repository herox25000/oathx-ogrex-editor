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
using Game.Entity.NativeWeb;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Spread
{
    public partial class SpreadIndex : UCPageBase
    {
        TreasureFacade aideTreasureFacade = new TreasureFacade( );

        protected int gameTime = 1800;     //一次性赠送需要游戏时长
        protected int presentGold = 200000;  //一次性赠送金币
        protected decimal balanceRate = 0.1M;   //推广分成
        protected int registerGold = 5000; //推广赠送金币

        protected void Page_Load( object sender , EventArgs e )
        {
            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "推广系统";
            DatasBind( );
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle( )
        {
            AddMetaTitle( "推广首页 - " + ApplicationSettings.Get( "title" ) );
            AddMetaKeywords( ApplicationSettings.Get( "keywords" ) );
            AddMetaDescription( ApplicationSettings.Get( "description" ) );
        }

        protected void DatasBind( )
        {
            GlobalSpreadInfo model = new GlobalSpreadInfo( );
            model = aideTreasureFacade.GetGlobalSpreadInfo( );
            if( model != null )
            {
                gameTime = model.PlayTimeCount / 60;
                presentGold = model.PlayTimeGrantScore;
                balanceRate = model.BalanceRate;
                registerGold = model.RegisterGrantScore;
            }
        }
    }
}
