using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Web.UI;
using Game.Utils;
using Game.Entity.Accounts;
using Game.Kernel;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class ConfineContenInfo : AdminPage
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
                ShowError("限制用户名不能为空");
                return;
            }
           
            ConfineContent confineContent = new ConfineContent( );
            confineContent.String = strString;
            confineContent.EnjoinOverDate = string.IsNullOrEmpty( CtrlHelper.GetText( txtEnjoinOverDate ) ) ? Convert.ToDateTime("1900-01-01") : Convert.ToDateTime( CtrlHelper.GetText( txtEnjoinOverDate ) );

            Message msg = new Message( );
            if ( string.IsNullOrEmpty( StrParam ) )
            {
                ConfineContent model = aideAccountsFacade.GetConfineContentByString( strString );
                if ( model != null )
                {
                    ShowError( "该限制用户名已经存在" );
                    return;
                }
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                msg = aideAccountsFacade.InsertConfineContent( confineContent );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                confineContent.String = StrParam;
                msg = aideAccountsFacade.UpdateConfineContent( confineContent );
            }

            if ( msg.Success )
            {
                ShowInfo( "操作成功", "ConfineContentList.aspx", 1200 );                
            }
            else
            {
                ShowError( msg.Content, "ConfineContentList.aspx", 1200 );   
               
            }
        }
        #endregion

        #region 数据加载

        private void BindData( )
        {
            if ( string.IsNullOrEmpty( StrParam ) )
                return;

            //获取信息
            ConfineContent model = aideAccountsFacade.GetConfineContentByString( StrParam );
            if ( model == null )
            {
                ShowError( "该限制字符不存在" );
                return;
            }
            CtrlHelper.SetText( ltString, model.String );
            txtString.Visible = false;
            CtrlHelper.SetText( txtEnjoinOverDate , model.EnjoinOverDate == DateTime.Now ? "" : model.EnjoinOverDate.ToString( "yyyy-MM-dd" ) );
        }
        #endregion
    }
}
