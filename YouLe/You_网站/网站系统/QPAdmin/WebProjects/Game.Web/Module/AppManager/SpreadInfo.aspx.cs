using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using System.Collections;
using Game.Facade.Aide;

namespace Game.Web.Module.AppManager
{
    public partial class SpreadInfo : AdminPage
    {
        #region 窗口事件 

        protected void Page_Load( object sender , EventArgs e )
        {
            BindData( );
        }

        protected void anpNews_PageChanged( object sender , EventArgs e )
        {
            BindData( );
            
        }

        #endregion
      
        #region 绑定数据

        protected void BindData( )
        {
            string where = string.Empty;
            if ( IntParam <= 0 )
            {
                return;
            }
            where = "where ChildrenID =" + IntParam;
            PagerSet ps = aideTreasureFacade.GetRecordSpreadInfoList( PageIndex , anpNews.PageSize , where , "Order By CollectDate Desc" );
            if ( ps.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptDataList.DataSource = ps.PageSet;
                rptDataList.DataBind( );
            }
            else
            {
                rptDataList.Visible = false;
                litNoData.Visible = true;
            }
        }

        #endregion
    }
}
