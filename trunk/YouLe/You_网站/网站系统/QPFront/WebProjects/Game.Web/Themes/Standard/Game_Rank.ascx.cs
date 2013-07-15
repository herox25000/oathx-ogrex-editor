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

using Game.Entity.Platform;
using Game.Facade;
using Game.Utils;
using Game.Kernel;


namespace Game.Web.Themes.Standard
{
    public partial class Game_Rank : System.Web.UI.UserControl
    {
        private PlatformFacade platformFacade = new PlatformFacade( );

        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindGameTypes( );
            }
        }

        /// <summary>
        /// 绑定游戏类型列表
        /// </summary>
        private void BindGameTypes( )
        {
            this.rptGameTypes.DataSource = platformFacade.GetGmaeTypes( );
            this.rptGameTypes.DataBind( );

            this.TCount.Value = this.rptGameTypes.Items.Count.ToString( );
        }

        /// <summary>
        /// 绑定事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void rptGameTypes_ItemDataBound( object sender , RepeaterItemEventArgs e )
        {
            if ( e.Item.ItemType == ListItemType.Item || e.Item.ItemType == ListItemType.AlternatingItem )
            {

                Repeater rptGameList = ( Repeater )e.Item.FindControl( "rptGameList" );

                //找到分类Repeater关联的数据项 

                GameTypeItem type = ( GameTypeItem )e.Item.DataItem;

                //提取分类ID 

                int typeID = Convert.ToInt32( type.TypeID );

                //根据分类ID查询该分类下的游戏，并绑定游戏Repeater 

                rptGameList.DataSource = platformFacade.GetGameKindsByTypeID( typeID );

                rptGameList.DataBind( );
            }
        }
    }
}