using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using System.Data;

namespace Game.Web.Module.FilledManager
{
    public partial class LivcardStat : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindData( );
            }
        }       

        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            DataSet ds = aideTreasureFacade.GetLivcardStat( );
            if ( ds.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
                rptDataList.DataSource = ds.Tables[0];
                rptDataList.DataBind( );
            }
            else
            {
                litNoData.Visible = true;
            }            
        }    

        #endregion
    }
}
