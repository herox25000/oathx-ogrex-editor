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
    public partial class Index : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade( );
        private GameMatchFacade gameMatchFacade = new GameMatchFacade( );

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindMatchData();
            }
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "比赛中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("比赛中心 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 绑定比赛信息
        /// </summary>
        private void BindMatchData()
        {
            this.rptMatchList.DataSource = gameMatchFacade.GetAllList( MatchInfo.Tablename , "ORDER BY CollectDate Desc" , "" ).PageSet;
            this.rptMatchList.DataBind();
        }
    }
}
