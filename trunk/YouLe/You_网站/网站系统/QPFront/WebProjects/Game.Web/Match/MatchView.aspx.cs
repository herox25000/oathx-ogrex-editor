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
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;
using System.Data.Common;
using System.Collections.Generic;
using Game.Entity.GameMatch;

namespace Game.Web.Match
{
    public partial class MatchView : UCPageBase
    {
        public string matchID = "";
        public string content = "";

        private AccountsFacade accountsFacade = new AccountsFacade( );
        private GameMatchFacade gameMatchFacade = new GameMatchFacade( );

        private int XID = GameRequest.GetQueryInt( "XID", 0 );

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                if ( Model != null )
                {
                    matchID = Model.MatchID.ToString( );
                    content = Model.MatchContent;
                }
            }
            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header ) this.FindControl( "sHeader" );
            sHeader.title = "比赛中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle( )
        {
            if ( Model != null )
            {
                AddMetaTitle( Model.MatchName + " - " + ApplicationSettings.Get( "title" ) );
            }
            AddMetaKeywords( ApplicationSettings.Get( "keywords" ) );
            AddMetaDescription( ApplicationSettings.Get( "description" ) );
        }

        protected MatchInfo Model
        {
            get
            {
                StringBuilder sql = new StringBuilder( );
                sql.AppendFormat( "select * from MatchInfo where MatchID={0}" , XID );
                return gameMatchFacade.GetEntity<MatchInfo>( sql.ToString( ) );
            }
        }
    }
}
