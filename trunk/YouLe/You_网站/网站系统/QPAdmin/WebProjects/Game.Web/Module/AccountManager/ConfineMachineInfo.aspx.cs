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
    public partial class ConfineMachineInfo : AdminPage
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
            if ( string.IsNullOrEmpty( StrParam ) && string.IsNullOrEmpty( strString ) )
            {
                ShowError( "限制机器码不能为空" );
                return;
            }
            ConfineMachine machine = new ConfineMachine( );
            machine.MachineSerial = strString;
            machine.EnjoinLogon = ckbEnjoinLogon.Checked;
            machine.EnjoinRegister = ckbEnjoinRegister.Checked;
            machine.EnjoinOverDate = string.IsNullOrEmpty( CtrlHelper.GetText( txtEnjoinOverDate ) ) ? Convert.ToDateTime( "1900-01-01" ) : Convert.ToDateTime( CtrlHelper.GetText( txtEnjoinOverDate ) );
            machine.CollectNote = TextFilter.FilterAll( CtrlHelper.GetText( txtCollectNote ) );
            Message msg = new Message( );
            if ( string.IsNullOrEmpty( StrParam ) )
            {
                ConfineMachine model = aideAccountsFacade.GetConfineMachineBySerial( strString );
                if ( model != null )
                {
                    ShowError( "该限制机器码已经存在" );
                    return;
                }
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                msg = aideAccountsFacade.InsertConfineMachine( machine );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                machine.MachineSerial = StrParam;
                msg = aideAccountsFacade.UpdateConfineMachine( machine );
            }

            if ( msg.Success )
            {
                ShowInfo( "操作成功", "ConfineMachineList.aspx", 1200 );
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
            ConfineMachine model = aideAccountsFacade.GetConfineMachineBySerial( StrParam );
            if ( model == null )
            {
                ShowError( "该限制机器码不存在" );
                return;
            }
            CtrlHelper.SetText( ltString, model.MachineSerial );
            txtString.Visible = false;
            ckbEnjoinLogon.Checked = model.EnjoinLogon;
            ckbEnjoinRegister.Checked = model.EnjoinRegister;
            CtrlHelper.SetText( txtEnjoinOverDate , model.EnjoinOverDate == DateTime.Now ? "" : model.EnjoinOverDate.ToString( "yyyy-MM-dd" ) );
            CtrlHelper.SetText( txtCollectNote, model.CollectNote );

        }
        #endregion
    }
}
