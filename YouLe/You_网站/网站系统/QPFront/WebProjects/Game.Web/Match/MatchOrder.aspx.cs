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

using Game.Entity.GameMatch;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Match
{
    public partial class MatchOrder : UCPageBase
    {
        private GameMatchFacade gameMatchGacade = new GameMatchFacade( );

        public string matchID = "";
        protected int number = 1;

        private int XID = GameRequest.GetQueryInt("XID", 0);

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            matchID = XID.ToString( );
            BindRankData( );
            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "比赛中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("比赛排名 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 绑定数据
        /// </summary>
        protected void BindRankData( )
        {
            /*string tag = "MatchRank" + XID.ToString();
            object ob = HttpContext.Current.Application.Get( tag );
            if ( ob == null )
            {
                string sqlQuery = "SELECT  TOP 100 UserID,SUM(MatchScore) AS Score FROM dbo.StreamMatchHistory WHERE  MatchID=" + matchID + " GROUP BY UserID ORDER BY Score DESC ";
                DataSet ds = gameMatchGacade.GetDataSetByWhere( sqlQuery );
                if ( ds.Tables[0].Rows.Count > 0 )
                {
                    rptRank.DataSource = ds;
                    rptRank.DataBind( );
                    HttpContext.Current.Application.Add( tag , ds );
                }
                else
                {
                    plData.Visible = false;
                    plMessage.Visible = true;
                }
            }
            else
            {
                DataSet ds = ( DataSet )ob;
                if ( ds.Tables[0].Rows.Count > 0 )
                {
                    rptRank.DataSource = ds;
                    rptRank.DataBind( );
                }
                else
                {
                    plData.Visible = false;
                    plMessage.Visible = true;
                }
            }*/

            string sqlQuery = "SELECT  TOP 100 UserID,SUM(MatchScore) AS Score FROM dbo.StreamMatchHistory WHERE  MatchID=" + matchID + " GROUP BY UserID ORDER BY Score DESC ";
            DataSet ds = gameMatchGacade.GetDataSetByWhere( sqlQuery );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                rptRank.DataSource = ds;
                rptRank.DataBind( );
            }
            else
            {
                plData.Visible = false;
                plMessage.Visible = true;
            }
        }
    }
}
