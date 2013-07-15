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
    public partial class GamePropertyInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindArea( );
                BindData( );
            }
        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string cash = CtrlHelper.GetText( txtCash );
            GameProperty property = aideTreasureFacade.GetGamePropertyInfo( IntParam );
            if ( property == null )
                return;
            property.Name = CtrlHelper.GetText( txtName );
            property.Cash = decimal.Parse( string.IsNullOrEmpty( cash ) ? "0" : cash );
            property.Gold = CtrlHelper.GetInt( txtGold, 0 );
            property.Discount = short.Parse( CtrlHelper.GetText( txtDiscount ) );
            //发行范围
            int intIssueArea = 0;
            if ( ckbIssueArea.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbIssueArea.Items )
                {
                    if ( item.Selected )
                        intIssueArea |= int.Parse( item.Value );
                }
            }
            //使用范围
            int intServiceArea = 0;
            if ( ckbServiceArea.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbServiceArea.Items )
                {
                    if ( item.Selected )
                        intServiceArea |= int.Parse( item.Value );
                }
            }
            property.IssueArea = ( short ) intIssueArea;
            property.ServiceArea = ( short ) intServiceArea;
            property.SendLoveLiness = CtrlHelper.GetInt( txtSendLoveLiness, 0 );
            property.RecvLoveLiness = CtrlHelper.GetInt( txtRecvLoveLiness, 0 );
            property.RegulationsInfo = CtrlHelper.GetText( txtRegulationsInfo );
            property.Nullity = ( byte ) ( ckbNullity.Checked ? 0 : 1 );
            try
            {
                aideTreasureFacade.UpdateGameProperty( property );
                ShowInfo( "更新成功" );
            }
            catch 
            {
                ShowInfo( "更新失败" );
            }
        }
        #endregion

        #region 数据加载
        private void BindArea( )
        {
            //发行范围
            IList<EnumDescription> arrIssueArea = IssueAreaHelper.GetIssueAreaList( typeof( IssueArea ) );
            ckbIssueArea.DataSource = arrIssueArea;
            ckbIssueArea.DataValueField = "EnumValue";
            ckbIssueArea.DataTextField = "Description";
            ckbIssueArea.DataBind( );

            //使用范围
            IList<EnumDescription> arrServiceArea = ServiceAreaHelper.GetServiceAreaList( typeof( ServiceArea ) );
            ckbServiceArea.DataSource = arrServiceArea;
            ckbServiceArea.DataValueField = "EnumValue";
            ckbServiceArea.DataTextField = "Description";
            ckbServiceArea.DataBind( );
        }       
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;

            GameProperty property = aideTreasureFacade.GetGamePropertyInfo( IntParam );
            if ( property == null )
                return;

            //发行范围
            int intIssueArea = property.IssueArea;
            if ( ckbIssueArea.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbIssueArea.Items )
                {
                    item.Selected = int.Parse( item.Value ) == ( intIssueArea & int.Parse( item.Value ) );
                }
            }
            //使用范围
            int intServiceArea = property.ServiceArea;
            if ( ckbServiceArea.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbServiceArea.Items )
                {
                    item.Selected = int.Parse( item.Value ) == ( intServiceArea & int.Parse( item.Value ) );
                }
            }
            CtrlHelper.SetText( txtName, property.Name.ToString( ) );
            CtrlHelper.SetText( txtCash, property.Cash.ToString( ) );
            CtrlHelper.SetText( txtGold, property.Gold.ToString( ) );

            CtrlHelper.SetText( txtDiscount, property.Discount.ToString( ) );
            CtrlHelper.SetText( txtSendLoveLiness, property.SendLoveLiness.ToString( ) );
            CtrlHelper.SetText( txtRecvLoveLiness, property.RecvLoveLiness.ToString( ) );
            CtrlHelper.SetText( txtRegulationsInfo, property.RegulationsInfo );
            ckbNullity.Checked = property.Nullity == 0;

        }
        #endregion
    }
}
