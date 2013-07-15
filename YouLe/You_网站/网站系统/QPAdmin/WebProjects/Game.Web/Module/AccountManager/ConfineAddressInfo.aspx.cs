using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Web.UI;
using System.Text.RegularExpressions;

using Game.Utils;
using Game.Entity.Accounts;
using Game.Kernel;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class ConfineAddressInfo : AdminPage
    {

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Read );
            if ( !IsPostBack )
                BindData( );
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            string strString = CtrlHelper.GetText( txtString );

            //验证数据
            if ( string.IsNullOrEmpty( StrParam ) && string.IsNullOrEmpty( strString ) )
            {
                ShowError( "限制IP地址不能为空" );
                return;
            }
            
            ConfineAddress address = new ConfineAddress( );
            address.AddrString = strString;
            address.EnjoinLogon = ckbEnjoinLogon.Checked;
            address.EnjoinRegister = ckbEnjoinRegister.Checked;
            address.EnjoinOverDate = string.IsNullOrEmpty( CtrlHelper.GetText( txtEnjoinOverDate ) ) ? Convert.ToDateTime( "1900-01-01" ) : Convert.ToDateTime( CtrlHelper.GetText( txtEnjoinOverDate ) );
            address.CollectNote = TextFilter.FilterAll( CtrlHelper.GetText( txtCollectNote ) );
            Message msg = new Message( );
            if ( string.IsNullOrEmpty( StrParam ) )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( !Utils.Validate.IsIP( strString ) )
                {
                    ShowError( "该限制IP地址格式不正确" );
                    return;
                }
                ConfineAddress model = aideAccountsFacade.GetConfineAddressByAddress( strString );
                if ( model != null )
                {
                    ShowError( "该限制IP地址已经存在" );
                    return;
                }
                msg = aideAccountsFacade.InsertConfineAddress( address );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                address.AddrString = StrParam;
                msg = aideAccountsFacade.UpdateConfineAddress( address );
            }

            if ( msg.Success )
            {  
                ShowInfo( "操作成功", "ConfineAddressList.aspx", 1200 );//Server.UrlDecode( GameRequest.GetQueryString("reurl"))
            }
            else
            {
                ShowError( msg.Content );
            }
        }
        #endregion

        #region 数据加载

        private void BindData( )
        {
            if ( string.IsNullOrEmpty( StrParam ) )
                return;

            //获取信息
            ConfineAddress model = aideAccountsFacade.GetConfineAddressByAddress( StrParam );
            if ( model == null )
            {
                ShowError( "该限制IP地址不存在" );
                return;
            }
            CtrlHelper.SetText( ltString, model.AddrString );
            txtString.Visible = false;
            ckbEnjoinLogon.Checked = model.EnjoinLogon;
            ckbEnjoinRegister.Checked = model.EnjoinRegister;
            CtrlHelper.SetText( txtEnjoinOverDate , model.EnjoinOverDate == DateTime.Now ? "" : model.EnjoinOverDate.ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtCollectNote, model.CollectNote );

        }
        #endregion
    }
}
