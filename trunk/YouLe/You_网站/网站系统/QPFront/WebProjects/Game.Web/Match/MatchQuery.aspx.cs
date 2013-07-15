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
using Game.Entity.GameMatch;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Match
{
    public partial class MatchQuery : UCPageBase
    {
        private GameMatchFacade gameMatchGacade = new GameMatchFacade( );

        public string matchID = "";

        #region 继承属性

        protected override bool IsAuthenticatedUser
        {
            get
            {
                return true;
            }
        }

        #endregion

        private int XID = GameRequest.GetQueryInt("XID", 0);

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            matchID = XID.ToString();
            BindData( );
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "比赛中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("得奖查询 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        private void BindData( )
        {
            StringBuilder sWhere = new StringBuilder( );
            sWhere.AppendFormat( " WHERE UserID = {0} and MatchID = {1}" , Fetch.GetUserCookie( ).UserID ,matchID);
            sWhere.AppendFormat( " AND RecordDate > '{0}'" , DateTime.Now.Year.ToString( ) + "-" + DateTime.Now.Month + "-" + DateTime.Now.Day );
            int sPageIndex = anpPage.CurrentPageIndex;
            int sPageSize = anpPage.PageSize; 
            string orderQuery = "Order By RecordDate Desc";
            PagerSet ps = gameMatchGacade.GetList( StreamMatchHistory.Tablename , sPageIndex , sPageSize , orderQuery , sWhere.ToString( ) );
            if ( ps.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptRank.DataSource = ps.PageSet;
                rptRank.DataBind( );
                anpPage.RecordCount = ps.PageSet.Tables[0].Rows.Count;
            }
            else
            {
                plData.Visible = false;
                plMessage.Visible = true;
            }
        }

        protected void anpPage_PageChanging( object src , Wuqi.Webdiyer.PageChangingEventArgs e )
        {
            anpPage.CurrentPageIndex = e.NewPageIndex;
            BindData( );
        }
    }
}
