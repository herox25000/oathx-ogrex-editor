using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Kernel;
using Game.Entity.Enum;

namespace Game.Web.Module.FilledManager
{
    public partial class GlobalLivcardInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindMemberOrder( );
                BindRight( );
                if ( IntParam <= 0 )
                    return;

                BindData( );
            }
        }

        //保存
        protected void btnSave_Click( object sender, EventArgs e )
        {
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

            GlobalLivcard cardType;
            if ( IntParam <= 0 )
            {
                cardType = new GlobalLivcard( );

            }
            else
            {
                cardType = aideTreasureFacade.GetGlobalLivcardInfo( IntParam );

            }
            cardType.CardName = CtrlHelper.GetText( txtCardTypeName );
            cardType.CardPrice = Utils.Validate.IsDouble( txtCardPrice.Text.Trim( ) ) ? decimal.Parse( txtCardPrice.Text.Trim( ) ) : 0;
            cardType.CardGold = CtrlHelper.GetInt( txtCardGold, 0 );
            cardType.MemberOrder = byte.Parse( string.IsNullOrEmpty( rdoMemberOrder.SelectedValue ) ? "0" : rdoMemberOrder.SelectedValue );
            cardType.MemberDays = CtrlHelper.GetInt( txtMemberDays, 0 );
            cardType.UserRight = intUserRight;
            if ( IntParam <= 0 )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                aideTreasureFacade.InsertGlobalLivcard( cardType );
                ShowInfo( "新增成功", "GlobalLivcardList.aspx", 1200 );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                aideTreasureFacade.UpdateGlobalLivcard( cardType );
                ShowInfo( "更新成功", "GlobalLivcardList.aspx", 1200 );
            }

        }
        #endregion

        #region 数据加载
        //会员等级
        private void BindMemberOrder( )
        {
            IList<EnumDescription> arrMemberOrder = MemberOrderHelper.GetMemberOrderStatusList( typeof( MemberOrderStatus ) );
            rdoMemberOrder.DataSource = arrMemberOrder;
            rdoMemberOrder.DataValueField = "EnumValue";
            rdoMemberOrder.DataTextField = "Description";
            rdoMemberOrder.DataBind( );
        }
        //用户权限
        private void BindRight( )
        {
            IList<EnumDescription> arrUserRight = UserRightHelper.GetUserRightList( typeof( UserRightStatus ) );
            List<EnumDescription> list = new List<EnumDescription>( );
            foreach ( EnumDescription d in arrUserRight )
            {
                if ( d.EnumValue == 256 || d.EnumValue == 512 || d.EnumValue == 268435456 )
                {
                    list.Add( d );
                }
            }
            ckbUserRight.DataSource = list;
            ckbUserRight.DataValueField = "EnumValue";
            ckbUserRight.DataTextField = "Description";
            ckbUserRight.DataBind( );
        }
        private void BindData( )
        {
            GlobalLivcard cardType = aideTreasureFacade.GetGlobalLivcardInfo( IntParam );
            if ( cardType == null )
                return;

            CtrlHelper.SetText( txtCardTypeName, cardType.CardName );
            CtrlHelper.SetText( txtCardPrice, cardType.CardPrice.ToString( ) );
            CtrlHelper.SetText( txtCardGold, cardType.CardGold.ToString( ) );
            if ( rdoMemberOrder.Items.Count > 0 )
            {
                foreach ( ListItem item in rdoMemberOrder.Items )
                {
                    item.Selected = item.Value == cardType.MemberOrder.ToString( );
                }
            }
            //用户权限
            int intUserRight = cardType.UserRight;
            if ( ckbUserRight.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbUserRight.Items )
                {
                    item.Selected = int.Parse( item.Value ) == ( intUserRight & int.Parse( item.Value ) );
                }
            }
            CtrlHelper.SetText( txtMemberDays, cardType.MemberDays.ToString( ) );

        }
        #endregion

    }
}
