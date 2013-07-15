using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Web.UI;
using Game.Entity.Accounts;
using Game.Kernel;
using Game.Utils;
using Game.Entity.Enum;
using Game.Entity.Platform;


namespace Game.Web.Module.AccountManager
{
    public partial class AddAccount : AdminPage
    {
        #region Fields

        private string _strTitle;
        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return _strTitle;
            }
            set
            {
                _strTitle = value;
            }
        }
        //头像ID
        protected string strFaceID = string.Empty;
        #endregion
        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Add );
            if ( !IsPostBack )
            {
                if ( Header != null )
                    Title = "添加新用户-用户管理";
                BindMemberOrder( );
                BindRight( );
            }
        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            #region 验证
            string strAccount = TextFilter.FilterAll( CtrlHelper.GetText( txtAccount ) );
            string strNickName = TextFilter.FilterAll( CtrlHelper.GetText( txtNickName ) );
            string strLogonPass = CtrlHelper.GetText( txtLogonPass );
            string strLogonPass2 = CtrlHelper.GetText( txtLogonPass2 );

            if ( string.IsNullOrEmpty( strAccount ) )
            {
                MessageBox( "用户名不能为空！" );
                return;
            }
            if ( string.IsNullOrEmpty( strLogonPass ) )
            {
                MessageBox( "登录密码不能为空！" );
                return;
            }
            if ( !strLogonPass.Equals( strLogonPass2 ) )
            {
                MessageBox( "两次输入的登录密码不一样！" );
                return;
            }
            if ( string.IsNullOrEmpty( strNickName ) )
                strNickName = strAccount;


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
            AccountsInfo account = new AccountsInfo( );
            IndividualDatum datum = new IndividualDatum( );

            account.Accounts = strAccount;
            account.NickName = strNickName;
            account.LogonPass = Utility.MD5( strLogonPass );
            account.InsurePass = string.IsNullOrEmpty( CtrlHelper.GetText( txtInsurePass ) ) ? Utility.MD5( strLogonPass ) : Utility.MD5( CtrlHelper.GetText( txtInsurePass ) );
            account.UnderWrite = TextFilter.FilterAll( CtrlHelper.GetText( txtUnderWrite ) );

            account.Present = CtrlHelper.GetInt( txtPresent, 0 );
            account.LoveLiness = CtrlHelper.GetInt( txtLoveLiness, 0 );
            account.Experience = CtrlHelper.GetInt( txtExperience, 0 );
            account.Gender = byte.Parse( ddlGender.SelectedValue );
            account.FaceID = ( short ) GameRequest.GetFormInt( "inFaceID", 0 );
            account.Nullity = ( byte ) ( ckbNullity.Checked ? 1 : 0 );
            account.StunDown = ( byte ) ( ckbStunDown.Checked ? 1 : 0 );
            account.MoorMachine = byte.Parse( rdoMoorMachine.SelectedValue );

            account.IsAndroid = ( byte ) ( chkIsAndroid.Checked ? 1 : 0 );
            account.UserRight = intUserRight;
            account.MasterRight = intMasterRight;
            account.MasterOrder = Convert.ToByte( ddlMasterOrder.SelectedValue.Trim( ) );

            account.Compellation = TextFilter.FilterAll( CtrlHelper.GetText( txtCompellation ) );
            account.MemberOrder = byte.Parse( ddlMemberOrder.SelectedValue );
            account.MemberOverDate = string.IsNullOrEmpty( CtrlHelper.GetText( txtMemberOverDate ) ) ? Convert.ToDateTime( "1980-01-01" ) : Convert.ToDateTime( CtrlHelper.GetText( txtMemberOverDate ) );
            account.MemberSwitchDate = string.IsNullOrEmpty( CtrlHelper.GetText( txtMemberOverDate ) ) ? Convert.ToDateTime( "1980-01-01" ) : Convert.ToDateTime( CtrlHelper.GetText( txtMemberOverDate ) );
            account.RegisterIP = GameRequest.GetUserIP( );

            datum.QQ = TextFilter.FilterAll( CtrlHelper.GetText( txtQQ ) );
            datum.EMail = TextFilter.FilterAll( CtrlHelper.GetText( txtEMail ) );
            datum.SeatPhone = TextFilter.FilterAll( CtrlHelper.GetText( txtSeatPhone ) );
            datum.MobilePhone = TextFilter.FilterAll( CtrlHelper.GetText( txtMobilePhone ) );
            datum.PostalCode = TextFilter.FilterAll( CtrlHelper.GetText( txtPostalCode ) );
            datum.DwellingPlace = TextFilter.FilterAll( CtrlHelper.GetText( txtDwellingPlace ) );
            datum.UserNote = TextFilter.FilterAll( CtrlHelper.GetText( txtUserNote ) );


            Message msg = aideAccountsFacade.AddAccount( account, datum );
            if ( msg.Success )
            {
                //MessageBox( "添加成功" );
                Page.ClientScript.RegisterStartupScript( typeof( Page ), "", string.Format( "alert(\"{0}\");location.href='{1}';", "添加成功", Request.Url.AbsoluteUri ), true );
                //Redirect( Request.Url.AbsoluteUri );
            }
            else
            {
                string strMessage = "";
                int intMsgID = msg.MessageID;
                switch ( intMsgID )
                {

                    case -5:
                        strMessage = "帐号已存在，请重新输入！";//您所输入的帐号名含有限制字符串
                        break;
                    case -4:
                        strMessage = "昵称已存在，请重新输入！";
                        break;
                    case -3:
                        strMessage = "帐号已存在，请重新输入！";
                        break;
                    case -2:
                        strMessage = "参数有误！";
                        break;
                    case -1:
                        strMessage = "抱歉，未知服务器错误！";
                        break;
                    case 1:
                        strMessage = "用户添加成功，但未成功获取游戏 ID 号码！";
                        break;
                    default:
                        strMessage = "抱歉，未知服务器错误！";
                        break;
                }

                MessageBox( strMessage );
            }
        }

        #endregion

        #region 数据加载
        //会员等级
        private void BindMemberOrder( )
        {
            IList<EnumDescription> arrMemberOrder = MemberOrderHelper.GetMemberOrderStatusList( typeof( MemberOrderStatus ) );
            ddlMemberOrder.DataSource = arrMemberOrder;
            ddlMemberOrder.DataValueField = "EnumValue";
            ddlMemberOrder.DataTextField = "Description";
            ddlMemberOrder.DataBind( );
        }
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
        #endregion
    }
}
