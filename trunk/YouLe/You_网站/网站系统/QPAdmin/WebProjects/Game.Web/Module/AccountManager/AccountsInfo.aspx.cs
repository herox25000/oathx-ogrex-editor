using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Utils;
using Game.Web.UI;
using Game.Entity.Accounts;

using Game.Kernel;
using Game.Entity.Platform;
using Game.Entity.Enum;
using System.Collections;
using Game.Entity.Record;
using Game.Facade;


namespace Game.Web.Module.AccountManager
{
    public partial class AccountInfo : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-" + GetAccounts( IntParam ) + "-基本信息";
            }
        }
        //头像ID
        protected string strFaceID = string.Empty;
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Read );
            if ( Header != null )
                Title = StrTitle;
            if ( !IsPostBack )
            {
                BindRight( );
                BindData( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            #region 验证
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string strAccount = TextFilter.FilterAll( CtrlHelper.GetText( txtAccount ) );   //用户名
            string strNickName = TextFilter.FilterAll( CtrlHelper.GetText( txtNickName ) ); //昵称

            if ( string.IsNullOrEmpty( strAccount ) )
            {
                MessageBox( "用户名不能为空！" );
                return;
            }
            if ( string.IsNullOrEmpty( strNickName ) )
            {
                strNickName = strAccount;
            }


            //计算用户权限
            int intUserRight = 0;
            if ( ckbUserRight.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbUserRight.Items )
                {
                    if ( item.Selected )
                    {
                        intUserRight |= int.Parse( item.Value );
                    }
                }
            }
            //计算管理权限         
            int intMasterRight = 0;
            if ( ckbMasterRight.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbMasterRight.Items )
                {
                    if ( item.Selected )
                        intMasterRight |= int.Parse( item.Value );
                }
            }
            #endregion

            AccountsInfo model = new AccountsInfo( );
            model = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            if ( model == null )
                return;
            string strOldAccounts = model.Accounts;     //原用户名
            string strOldNickName = model.NickName;     //原昵称
            string strOldLogonPass = model.LogonPass;   //原登录密码
            string strOldInsurePass = model.InsurePass; //原银行密码

            model.UserID = IntParam;
            model.Accounts = strAccount;
            model.NickName = strNickName;
            model.LogonPass = string.IsNullOrEmpty( CtrlHelper.GetText( txtLogonPass ) ) ? model.LogonPass : Utility.MD5( CtrlHelper.GetText( txtLogonPass ) );
            model.InsurePass = string.IsNullOrEmpty( CtrlHelper.GetText( txtInsurePass ) ) ? model.InsurePass : Utility.MD5( CtrlHelper.GetText( txtInsurePass ) );
            model.UnderWrite = CtrlHelper.GetText( txtUnderWrite );
            model.Experience = CtrlHelper.GetInt( txtExperience, 0 );
            model.Present = CtrlHelper.GetInt( txtPresent, 0 );
            model.LoveLiness = CtrlHelper.GetInt( txtLoveLiness, 0 );
            model.Gender = byte.Parse( ddlGender.SelectedValue );
            model.FaceID = ( short ) GameRequest.GetFormInt( "inFaceID", 0 );
            model.Nullity = ( byte ) ( ckbNullity.Checked ? 1 : 0 );
            model.StunDown = ( byte ) ( ckbStunDown.Checked ? 1 : 0 );
            model.MoorMachine = byte.Parse( rdoMoorMachine.SelectedValue );

            model.IsAndroid = ( byte ) ( chkIsAndroid.Checked ? 1 : 0 );
            model.UserRight = intUserRight;
            model.MasterRight = intMasterRight;
            model.MasterOrder = Convert.ToByte( ddlMasterOrder.SelectedValue.Trim( ) );

            Message msg = new Message( );
            msg = aideAccountsFacade.UpdateAccount( model );

            if ( msg.Success )
            {
                MessageBox( "信息修改成功" );
                //判断是否有修改昵称，若修改则写入日志表
                if ( !strOldNickName.Equals( model.NickName ) )
                {
                    RecordAccountsExpend actExend = new RecordAccountsExpend( );
                    actExend.OperMasterID = userExt.UserID;
                    actExend.ReAccounts = model.NickName;
                    actExend.UserID = model.UserID;
                    actExend.ClientIP = GameRequest.GetUserIP( );
                    aideRecordFacade.InsertRecordAccountsExpend( actExend );
                }
                //判断是否有修改登录密码或银行密码，若修改则写入日志表
                if ( !strOldLogonPass.Equals( model.LogonPass ) || !strOldInsurePass.Equals( model.InsurePass ) )
                {
                    RecordPasswdExpend pwExend = new RecordPasswdExpend( );
                    pwExend.OperMasterID = userExt.UserID;
                    pwExend.UserID = model.UserID;
                    pwExend.ReLogonPasswd = string.IsNullOrEmpty( CtrlHelper.GetText( txtLogonPass ) ) ? "" : model.LogonPass;
                    pwExend.ReInsurePasswd = string.IsNullOrEmpty( CtrlHelper.GetText( txtInsurePass ) ) ? "" : model.InsurePass;
                    pwExend.ClientIP = GameRequest.GetUserIP( );
                    aideRecordFacade.InsertRecordPasswdExpend( pwExend );
                }
                MessageBox( "操作成功！" );
                Redirect( Request.Url.AbsoluteUri );
            }
            else
            {
                MessageBox( msg.Content );
            }

        }
        #endregion

        #region 数据加载
        private void BindRight( )
        {
            //用户权限
            IList<EnumDescription> arrUserRight = UserRightHelper.GetUserRightList( typeof( UserRightStatus ) );
            ckbUserRight.DataSource = arrUserRight;
            ckbUserRight.DataValueField = "EnumValue";
            ckbUserRight.DataTextField = "Description";
            ckbUserRight.DataBind( );
            //用户管理权限
            IList<EnumDescription> arrMasterRight = MasterRightHelper.GetMasterRightList( typeof( MasterRightStatus ) );
            ckbMasterRight.DataSource = arrMasterRight;
            ckbMasterRight.DataValueField = "EnumValue";
            ckbMasterRight.DataTextField = "Description";
            ckbMasterRight.DataBind( );

        }
        private void BindData( )
        {
            if ( IntParam <= 0 )
                return;

            //获取信息
            AccountsInfo model = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            if ( model == null )
            {
                MessageBox( "用户信息不存在" );
                return;
            }
            //CtrlHelper.SetText( ltUserID, model.UserID.ToString( ) );
            CtrlHelper.SetText( ltGameID, model.GameID.ToString( ) );
            CtrlHelper.SetText( ltRegAccounts, model.RegAccounts.Trim( ) );
            CtrlHelper.SetText( txtAccount, model.Accounts.Trim( ) );
            CtrlHelper.SetText( txtNickName, model.NickName.Trim( ) );
            CtrlHelper.SetText( litCompellation, model.Compellation );
            //CtrlHelper.SetText(litUserMedal, model.UserMedal.ToString());

            CtrlHelper.SetText( txtUnderWrite, model.UnderWrite.Trim( ) );
            CtrlHelper.SetCheckBoxValue( ckbNullity, model.Nullity );
            CtrlHelper.SetCheckBoxValue( ckbStunDown, model.StunDown );
            CtrlHelper.SetText( txtExperience, model.Experience.ToString( ).Trim( ) );
            CtrlHelper.SetText( txtPresent, model.Present.ToString( ).Trim( ) );
            CtrlHelper.SetText( txtLoveLiness, model.LoveLiness.ToString( ).Trim( ) );
            CtrlHelper.SetText( ltProtectID, model.ProtectID > 0 ? "<span style=\"font-weight: bold;\">已申请</span>&nbsp;<a href=\"javascript:openWindow('AccountsProtectInfo.aspx?param=" + model.ProtectID + "',580,320)\" class=\"l1\">点击查看</a>" : "未申请" );
            CtrlHelper.SetText( ltMemberInfo, GetMemberName( model.MemberOrder ) + ( model.MemberOrder == 0 ? "" : "&nbsp;&nbsp;&nbsp;&nbsp;到期时间：" + model.MemberSwitchDate.ToString( "yyyy-MM-dd mm:HH:ss" ) ) );
            if ( model.MemberOrder != 0 )
            {
                plMemberList.Visible = true;
            }
            strFaceID = model.FaceID.ToString( );
            ddlGender.SelectedValue = model.Gender.ToString( );
            rdoMoorMachine.SelectedValue = model.MoorMachine.ToString( );
            //用户权限
            int intUserRight = model.UserRight;
            if ( ckbUserRight.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbUserRight.Items )
                {
                    item.Selected = int.Parse( item.Value ) == ( intUserRight & int.Parse( item.Value ) );
                }
            }
            //玩家身份
            ddlMasterOrder.SelectedValue = model.MasterOrder.ToString( ).Trim( );
            //用户管理权限
            int intMasterRight = model.MasterRight;
            if ( ckbMasterRight.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbMasterRight.Items )
                {
                    item.Selected = int.Parse( item.Value ) == ( intMasterRight & int.Parse( item.Value ) );
                }
            }
            //机器人
            CtrlHelper.SetCheckBoxValue( chkIsAndroid, model.IsAndroid );

            //登录、注册信息
            CtrlHelper.SetText( ltWebLogonTimes, model.WebLogonTimes.ToString( ) );
            CtrlHelper.SetText( ltGameLogonTimes, model.GameLogonTimes.ToString( ) );
            CtrlHelper.SetText( ltLastLogonDate, model.LastLogonDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            CtrlHelper.SetText( ltLogonSpacingTime, Fetch.GetTimeSpan( Convert.ToDateTime( model.LastLogonDate ), DateTime.Now ) );
            CtrlHelper.SetText( ltLastLogonIP, model.LastLogonIP.ToString( ) );
            CtrlHelper.SetText( ltLogonIPInfo, IPQuery.GetAddressWithIP( model.LastLogonIP.ToString( ) ) );
            CtrlHelper.SetText( ltLastLogonMachine, model.LastLogonMachine.ToString( ) );
            CtrlHelper.SetText( ltRegisterDate, model.RegisterDate.ToString( "yyyy-MM-dd HH:mm:ss" ) );
            CtrlHelper.SetText( ltRegisterIP, model.RegisterIP.ToString( ) );
            CtrlHelper.SetText( ltRegIPInfo, IPQuery.GetAddressWithIP( model.RegisterIP.ToString( ) ) );
            CtrlHelper.SetText( ltRegisterMachine, model.RegisterMachine.ToString( ) );
            CtrlHelper.SetText( ltOnLineTimeCount, Fetch.ConverTimeToDHMS( model.OnLineTimeCount ) );
            CtrlHelper.SetText( ltPlayTimeCount, Fetch.ConverTimeToDHMS( model.PlayTimeCount ) );

            //密保卡信息
            //PasswordCard pc = new PasswordCard( );
            if ( model.PasswordID != 0 )
            {
                LiteralPasswordCard.Text = "<span style=\"font-weight: bold;\">已绑定</span>";  
                spanPasswordCard.Visible = true;
            }
           

        }
        #endregion
    }
}
