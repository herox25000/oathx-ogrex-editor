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
using Game.Entity.Record;
using System.Text;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class GrantMember : AdminPage
    {
        #region Fields


        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-赠送会员";
            }
        }
        #endregion
        #region 窗口事件
        protected void Page_Load( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.GrantMember );
            if ( !IsPostBack )
            {
                if ( Header != null )
                    Title = StrTitle;
                BindMemberOrder( );
            }

        }
        protected void btnSave_Click( object sender, EventArgs e )
        {
            string strReason = CtrlHelper.GetText( txtReason );
            int intDays = CtrlHelper.GetInt( txtMemberDays, 0 );
            if ( intDays <= 0 )
            {
                MessageBox( "赠送天数必须为大于零的正整数！");
                return;
            }
            if ( string.IsNullOrEmpty( strReason ) )
            {
                MessageBox( "赠送原因不能为空！" );
                return;
            }
           
            AccountsInfo modelAccountInfo = new AccountsInfo( );
            /*RecordGrantMember grantMember = new RecordGrantMember( );
            grantMember.ClientIP = GameRequest.GetUserIP( );
            grantMember.MasterID = userExt.UserID;
            grantMember.GrantCardType = int.Parse( ddlMemberType.SelectedValue );
            grantMember.MemberDays = intDays;
            grantMember.Reason = strReason;
            */
            string[ ] arrUserIDList = StrParamsList.Split( new char[ ] { ',' } );
            foreach ( string strid in arrUserIDList )
            {
                if ( Utils.Validate.IsPositiveInt( strid ) )
                {
                    modelAccountInfo = aideAccountsFacade.GetAccountInfoByUserID( int.Parse( strid ) );
                    if ( modelAccountInfo == null )
                        continue;

                    aideRecordFacade.GrantMember( int.Parse( strid ), CtrlHelper.GetSelectValue( ddlMemberType, 0 ), intDays, userExt.UserID, strReason, GameRequest.GetUserIP( ) );

                    /*grantMember.UserID = int.Parse( strid );
                    modelAccountInfo.MemberOrder = CtrlHelper.GetSelectValue( ddlMemberType,0 );

                    aideAccountsFacade.UpdateAccount( modelAccountInfo );           //更新会员信息
                    aideRecordFacade.InsertRecordGrantMember( grantMember );        //插入赠送会员日志*/
                }
            }
            MessageBox( "确认成功" );
        }
        #endregion
        #region 绑定数据
        //会员等级
        private void BindMemberOrder( )
        {
            IList<EnumDescription> arrMemberOrder = MemberOrderHelper.GetMemberOrderStatusList( typeof( MemberOrderStatus ) );
            ddlMemberType.DataSource = arrMemberOrder;
            ddlMemberType.DataValueField = "EnumValue";
            ddlMemberType.DataTextField = "Description";
            ddlMemberType.DataBind( );
            ddlMemberType.Items.RemoveAt( 0 );
        }
        #endregion
    }
}
