using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Kernel;
using System.Text;
using Game.Utils;
using Game.Entity.Accounts;
using Game.Entity;
using Game.Entity.Enum;

namespace Game.Web.Module.AccountManager
{
    public partial class AccountsList : AdminPage
    {

        #region 窗口事件
        protected void Page_Load( object sender , EventArgs e )
        {
            if( !IsPostBack )
            {
                AccountsDataBind( );
            }
        }
        protected void anpPage_PageChanged( object sender , EventArgs e )
        {
            AccountsDataBind( );
        }
        /// <summary>
        /// 查询
        /// </summary>
        protected void btnQuery_Click( object sender , EventArgs e )
        {

            ViewState[ "SearchItems" ] = GetQueryString( );// condition.ToString( );

            AccountsDataBind( );
        }
        // 高级查询
        protected void btnHightQuery_Click( object sender , EventArgs e )
        {
            StringBuilder where = new StringBuilder( );
            string regStartDate = CtrlHelper.GetText( txtStartDate );
            string regEndDate = CtrlHelper.GetText( txtEndDate );
            string loStartDate = CtrlHelper.GetText( txtLoStartDate );
            string loEndDate = CtrlHelper.GetText( txtLoEndDate );
            string regIP = CtrlHelper.GetText( txtRegIP );
            string regMachine = CtrlHelper.GetText( txtRegMachine );
            string logIP = CtrlHelper.GetText( txtLogIP );
            string logMachine = CtrlHelper.GetText( txtLogMachine );
            where.Append( GetQueryString( ) );
            if( ckbProtect.Checked )
                where.Append( " AND ProtectID > 0" );
            if( ckbMember.Checked )
                where.Append( " AND MemberOrder > 0" );
            if( ckbNullity.Checked )
                where.Append( " AND Nullity=1" );
            if( ckbIsAndroid.Checked )
                where.Append( " AND IsAndroid=1" );

            if( !string.IsNullOrEmpty( regStartDate ) )
                where.AppendFormat( " AND RegisterDate >= '{0} 00:00:00'" , regStartDate );
            if( !string.IsNullOrEmpty( regEndDate ) )
                where.AppendFormat( " AND RegisterDate <= '{0} 23:59:59'" , regEndDate );
            if( !string.IsNullOrEmpty( loStartDate ) )
                where.AppendFormat( " AND LastLogonDate >= '{0} 00:00:00'" , loStartDate );
            if( !string.IsNullOrEmpty( loEndDate ) )
                where.AppendFormat( " AND LastLogonDate <= '{0} 23:59:59'" , loEndDate );

            if( !string.IsNullOrEmpty( regIP ) )
                where.AppendFormat( " AND RegisterIP = '{0}'" , regIP );
            if( !string.IsNullOrEmpty( regMachine ) )
                where.AppendFormat( " AND RegisterMachine = '{0}'" , regMachine );
            if( !string.IsNullOrEmpty( logIP ) )
                where.AppendFormat( " AND LastLogonIP = '{0}'" , logIP );
            if( !string.IsNullOrEmpty( logMachine ) )
                where.AppendFormat( " AND LastLogonMachine = '{0}'" , logMachine );

            ViewState[ "SearchItems" ] = where.ToString( );
            AccountsDataBind( );
        }
        /// <summary>
        /// 获取查询串
        /// </summary>
        /// <returns></returns>
        protected string GetQueryString( )
        {
            string queryContent = txtSearch.Text.Trim( );
            StringBuilder condition = new StringBuilder( );

            if( !string.IsNullOrEmpty( queryContent ) )
            {
                if( ckbIsLike.Checked )
                {
                    condition.AppendFormat( " AND (UserID LIKE '%{0}%' OR GameID LIKE '%{0}%' OR Accounts LIKE '%{0}%' OR NickName LIKE '%{0}%')" , queryContent );
                }
                else
                {
                    if( Utils.Validate.IsPositiveInt( queryContent ) )
                        condition.AppendFormat( " AND (Accounts='{0}' OR NickName='{0}' OR UserID='{0}' OR GameID='{0}')" , queryContent );
                    else
                        condition.AppendFormat( " AND (Accounts='{0}' OR NickName='{0}')" , queryContent );
                }
            }
            return condition.ToString( );
        }
        /// <summary>
        /// 刷新
        /// </summary>
        protected void btnRefresh_Click( object sender , EventArgs e )
        {
            ViewState[ "SearchItems" ] = null;
            txtSearch.Text = "";
            ckbIsLike.Checked = false;
            AccountsDataBind( );
        }
        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click( object sender , EventArgs e )
        {

        }
        /// <summary>
        /// 批量冻结玩家
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDongjie_Click( object sender , EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Enable );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideAccountsFacade.DongjieAccount( strQuery );
                ShowInfo( "冻结成功" );
            }
            catch
            {
                ShowError( "冻结失败" );
            }
            AccountsDataBind( );
        }
        /// <summary>
        /// 批量解冻玩家
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnJiedong_Click( object sender , EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Enable );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideAccountsFacade.JieDongAccount( strQuery );
                ShowInfo( "解冻成功" );
            }
            catch
            {
                ShowError( "解冻失败" );
            }
            AccountsDataBind( );
        }


        /// <summary>
        /// 批量设置机器人
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnSetting_Click( object sender , EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.IsRobot );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = " WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideAccountsFacade.SettingAndroid( strQuery );
                ShowInfo( "设置成功" );
            }
            catch
            {
                ShowError( "设置失败" );
            }
            AccountsDataBind( );
        }
        /// <summary>
        /// 批量取消机器人
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnCancle_Click( object sender , EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.IsRobot );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = " WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aideAccountsFacade.CancleAndroid( strQuery );
                ShowInfo( "操作成功" );
            }
            catch
            {
                ShowError( "操作失败" );
            }
            AccountsDataBind( );
        }
        #endregion

        #region 数据绑定

        //绑定数据      
        private void AccountsDataBind( )
        {
            PagerSet pagerSet = aideAccountsFacade.GetAccountsList( anpPage.CurrentPageIndex , anpPage.PageSize , SearchItems , Orderby );
            anpPage.RecordCount = pagerSet.RecordCount;
            //anpPage.CurrentPageIndex = PageIndex;
            if( pagerSet.PageSet.Tables[ 0 ].Rows.Count > 0 )
            {
                rptDataList.DataSource = pagerSet.PageSet;
                rptDataList.DataBind( );
                rptDataList.Visible = true;
                litNoData.Visible = false;
            }
            else
            {
                rptDataList.Visible = false;
                litNoData.Visible = true;
            }
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if( ViewState[ "SearchItems" ] == null )
                {
                    StringBuilder condition = new StringBuilder( );
                    condition.Append( " WHERE 1=1 " );
                    ViewState[ "SearchItems" ] = condition.ToString( );
                }

                return ( string )ViewState[ "SearchItems" ];
            }

            set
            {
                ViewState[ "SearchItems" ] = value;
            }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if( ViewState[ "Orderby" ] == null )
                {
                    ViewState[ "Orderby" ] = "ORDER BY RegisterDate DESC";
                }

                return ( string )ViewState[ "Orderby" ];
            }

            set
            {
                ViewState[ "Orderby" ] = value;
            }
        }

        #endregion

    }
}
