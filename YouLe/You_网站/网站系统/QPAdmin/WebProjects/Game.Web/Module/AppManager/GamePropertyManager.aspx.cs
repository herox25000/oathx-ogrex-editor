using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using Game.Entity.Enum;
using System.Web.UI.MobileControls;
using System.Data;

namespace Game.Web.Module.AppManager
{
    public partial class GamePropertyManager : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                BindData( );               
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            BindData( );
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE ID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.DeleteGameProperty( strQuery );
                ShowInfo( "删除成功" );
            }
            catch
            {
                ShowError( "删除失败" );
            }
            BindData( );
        }
        //批量禁用
        protected void btnDisable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE ID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.SetPropertyDisbale( strQuery );
                MessageBox( "禁用成功" );
            }
            catch
            {
                MessageBox( "禁用失败" );
            }
            BindData( );
        }
        //批量启用
        protected void btnEnable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE ID in (" + Checkbox_Value + ")";
            try
            {
                aideTreasureFacade.SetPropertyEnbale( strQuery );
                MessageBox( "启用成功" );
            }
            catch
            {
                MessageBox( "启用失败" );
            }
            BindData( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void BindData( )
        {
            PagerSet pagerSet = aideTreasureFacade.GetGamePropertyList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptDataList.DataSource = pagerSet.PageSet;
            rptDataList.DataBind( );
            anpNews.RecordCount = pagerSet.RecordCount;
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if ( ViewState["SearchItems"] == null )
                {
                    StringBuilder condition = new StringBuilder( );
                    condition.Append( " WHERE 1=1 " );

                    ViewState["SearchItems"] = condition.ToString( );
                }

                return ( string ) ViewState["SearchItems"];
            }

            set
            {
                ViewState["SearchItems"] = value;
            }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if ( ViewState["Orderby"] == null )
                {
                    ViewState["Orderby"] = "ORDER BY ID ASC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        //道具发行范围
        protected string GetIssueArea( int intIssueArea )
        {
            StringBuilder sb = new StringBuilder( );
            IList<EnumDescription> arrIssueArea = IssueAreaHelper.GetIssueAreaList( typeof( IssueArea ) );

            foreach ( EnumDescription v in arrIssueArea )
            {
                if ( v.EnumValue == ( intIssueArea & v.EnumValue ) )
                    sb.AppendFormat( "{0},", IssueAreaHelper.GetIssueAreaDes( ( IssueArea ) v.EnumValue ) );
            }

            return sb.ToString( ).TrimEnd( new char[ ] { ',' } );
        }
        //道具使用范围
        protected string GetServiceArea( int intServiceArea )
        {
            StringBuilder sb = new StringBuilder( );
            IList<EnumDescription> arrServiceArea = ServiceAreaHelper.GetServiceAreaList( typeof( ServiceArea ) );

            foreach ( EnumDescription v in arrServiceArea )
            {
                if ( v.EnumValue == ( intServiceArea & v.EnumValue ) )
                    sb.AppendFormat( "{0},", ServiceAreaHelper.GetServiceAreaDes( ( ServiceArea ) v.EnumValue ) );
            }

            return sb.ToString( ).TrimEnd( new char[ ] { ',' } );
        }      

        #endregion
    }
}
