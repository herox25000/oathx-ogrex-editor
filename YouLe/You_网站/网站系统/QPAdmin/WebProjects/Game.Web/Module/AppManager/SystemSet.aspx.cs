using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using System.Text;
using Game.Entity.Platform;
using Game.Entity.Accounts;
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class SystemSet : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindData( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            ProcessData( );
        }
        #endregion

        #region 数据加载

        private void BindData( )
        {
            PagerSet pagerSet = aideAccountsFacade.GetSystemStatusInfoList( 1, 10000, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                rptDataList.DataSource = pagerSet.PageSet;
                rptDataList.DataBind( );
            }

            SystemStatusInfo config = aideAccountsFacade.GetSystemStatusInfo( string.IsNullOrEmpty( StrParam ) ? "EnjoinInsure" : StrParam );
            if ( config == null )
                return;

            CtrlHelper.SetText( txtStatusName, config.StatusName );
            CtrlHelper.SetText( txtStatusValue, config.StatusValue.ToString( ) );
            CtrlHelper.SetText( txtStatusTip, config.StatusTip );
            CtrlHelper.SetText( txtStatusString, config.StatusString );
            CtrlHelper.SetText( txtStatusDescription, config.StatusDescription );


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
                    ViewState["Orderby"] = "ORDER BY StatusName ASC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            if ( string.IsNullOrEmpty( txtStatusName.Text.Trim( ) ) )
                return;

            SystemStatusInfo config = new SystemStatusInfo( );

            config.StatusName = CtrlHelper.GetText( txtStatusName );
            config.StatusValue = CtrlHelper.GetInt( txtStatusValue, 0 );
            config.StatusString = CtrlHelper.GetText( txtStatusString );
            config.StatusTip = CtrlHelper.GetText( txtStatusTip );
            config.StatusDescription = CtrlHelper.GetText( txtStatusDescription );

            Message msg = new Message( );            
            msg = aideAccountsFacade.UpdateSystemStatusInfo( config );

            if ( msg.Success )
            {
                ShowInfo( "修改成功" );
            }
            else
            {
                ShowError( msg.Content );
            }
        }
        #endregion
    }
}
