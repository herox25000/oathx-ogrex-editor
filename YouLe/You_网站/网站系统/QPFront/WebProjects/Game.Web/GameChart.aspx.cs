using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;
using System.Data;

namespace Game.Web
{
    public partial class GameChart : UCPageBase
    {
        private int kindID = GameRequest.GetQueryInt( "KindID" , 0 );
        protected int number = 1;

        protected void Page_Load( object sender , EventArgs e )
        {
            if ( kindID == 0 )
            {
                return;
            }
            BindRankData( );
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle( )
        {
            AddMetaTitle( "游戏财富排行 - " + ApplicationSettings.Get( "title" ) );
            AddMetaKeywords( ApplicationSettings.Get( "keywords" ) );
            AddMetaDescription( ApplicationSettings.Get( "description" ) );
        }

        /// <summary>
        /// 绑定数据
        /// </summary>
        protected void BindRankData( )
        {
            string tag = "MatchRank";
            object ob = SessionState.Get( tag );
            if ( SessionState.Get( "MatchRank" ) == null )
            {
                TreasureFacade treasureFacade = new TreasureFacade( kindID );
                string sqlQuery = "Select Top 100 * from GameScoreInfo(nolock) order by Score desc";
                DataSet ds = treasureFacade.GetDataSetByWhere( sqlQuery );
                if ( ds.Tables[0].Rows.Count > 0 )
                {
                    rptRank.DataSource = ds;
                    rptRank.DataBind( );
                }
                SessionState.Set( tag , ob , 10 );
            }
            else
            {
                DataSet ds = ( DataSet )ob;
                if ( ds.Tables[0].Rows.Count > 0 )
                {
                    rptRank.DataSource = ds;
                    rptRank.DataBind( );
                }
            }
        }
    }
}
