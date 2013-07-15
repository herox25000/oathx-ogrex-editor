using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;

namespace Game.Web.Member
{
    public partial class ExitPasswordCard : UCPageBase
    {

        #region 继承属性

        protected override bool IsAuthenticatedUser
        {
            get
            {
                return true;
            }
        }

        #endregion

        private AccountsFacade accountsFacade = new AccountsFacade( );

        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                string serialNumber = accountsFacade.GetPasswordCardByUserID( Fetch.GetUserCookie( ).UserID );
                if ( serialNumber == "0" )
                {
                    Panel1.Visible = false;
                    return;
                }
                else
                {
                    Panel2.Visible = false;
                }
                PasswordCard pc = new PasswordCard( );
                pc.SerialNumber = Convert.ToInt32( serialNumber );
                lbSerialNumber.Text = pc.AddSpace( );
                string[] coordinate = pc.RandomString( );
                lbNumber1.Text = coordinate[0];
                lbNumber2.Text = coordinate[1];
                lbNumber3.Text = coordinate[2];
            }  
        }

        //取消绑定
        protected void ClearPasswordCard( object sender , EventArgs e )
        {
            PasswordCard pc = new PasswordCard( );
            pc.SerialNumber = Convert.ToInt32( lbSerialNumber.Text.Replace( " " , "" ) );
            string numberOne = CtrlHelper.GetText( txtNumber1 );
            string numberTwo = CtrlHelper.GetText( txtNumber2 );
            string numberThree = CtrlHelper.GetText( txtNumber3 );
            if ( string.IsNullOrEmpty( numberOne ) || string.IsNullOrEmpty( numberTwo ) || string.IsNullOrEmpty( numberThree ) )
            {
                Show( "请填写坐标码" );
                return;
            }
            string lbNumberOne = pc.GetNumberByCoordinate( CtrlHelper.GetText( lbNumber1 ) );
            string lbNumberTwo = pc.GetNumberByCoordinate( CtrlHelper.GetText( lbNumber2 ) );
            string lbNumberThree = pc.GetNumberByCoordinate( CtrlHelper.GetText( lbNumber3 ) );
            if ( numberOne != lbNumberOne || numberTwo != lbNumberTwo || numberThree != lbNumberThree )
            {
                Show( "坐标码填写错误" );
                return;
            }
            bool resutl = accountsFacade.ClearUserPasswordCardID( Fetch.GetUserCookie( ).UserID );
            if ( resutl )
            {
                ShowAndRedirect( "取消绑定成功" , "ExitPasswordCard.aspx" );
            }
            else
            {
                Show( "取消绑定失败，请联系客服人员" );
                return;
            }
        }
    }
}
