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
    public partial class ApplyPasswordCard : UCPageBase
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
                if ( accountsFacade.userIsBindPasswordCard( Fetch.GetUserCookie( ).UserID ) )
                {
                    Panel1.Visible = false;
                    return;
                }
                else
                {
                    Panel2.Visible = false;
                }
                PasswordCard pc = new PasswordCard( );
                pc.CreateSerialNumber( );
                lbSerialNumber.Text = pc.AddSpace( );
                lbA1.Text = pc.GetNumberByCoordinate( "A1" );
                lbA2.Text = pc.GetNumberByCoordinate( "A2" );
                lbA3.Text = pc.GetNumberByCoordinate( "A3" );
                lbA4.Text = pc.GetNumberByCoordinate( "A4" );
                lbB1.Text = pc.GetNumberByCoordinate( "B1" );
                lbB2.Text = pc.GetNumberByCoordinate( "B2" );
                lbB3.Text = pc.GetNumberByCoordinate( "B3" );
                lbB4.Text = pc.GetNumberByCoordinate( "B4" );
                lbC1.Text = pc.GetNumberByCoordinate( "C1" );
                lbC2.Text = pc.GetNumberByCoordinate( "C2" );
                lbC3.Text = pc.GetNumberByCoordinate( "C3" );
                lbC4.Text = pc.GetNumberByCoordinate( "C4" );
                lbD1.Text = pc.GetNumberByCoordinate( "D1" );
                lbD2.Text = pc.GetNumberByCoordinate( "D2" );
                lbD3.Text = pc.GetNumberByCoordinate( "D3" );
                lbD4.Text = pc.GetNumberByCoordinate( "D4" );
                lbE1.Text = pc.GetNumberByCoordinate( "E1" );
                lbE2.Text = pc.GetNumberByCoordinate( "E2" );
                lbE3.Text = pc.GetNumberByCoordinate( "E3" );
                lbE4.Text = pc.GetNumberByCoordinate( "E4" );
                lbF1.Text = pc.GetNumberByCoordinate( "F1" );
                lbF2.Text = pc.GetNumberByCoordinate( "F2" );
                lbF3.Text = pc.GetNumberByCoordinate( "F3" );
                lbF4.Text = pc.GetNumberByCoordinate( "F4" );

                string[] number = pc.RandomString( );
                lbNumber1.Text = number[0];
                lbNumber2.Text = number[1];
                lbNumber3.Text = number[2];
            }
        }

        //输出图片
        protected void DownloadImg( object sender , EventArgs e )
        {
            PasswordCard pc = new PasswordCard( );
            pc.SerialNumber = Convert.ToInt32( lbSerialNumber.Text.Replace(" ","") );
            string path = Server.MapPath( "/img/PasswordBlack.jpg" );
            byte[] bs = pc.WritePasswordCardImg( path );
            Response.Clear( );
            Response.ContentType = "image/jpg";
            Response.AddHeader( "Content-Disposition" , "attachment;  filename=" + HttpUtility.UrlEncode( "密保卡.jpg" , System.Text.Encoding.UTF8 ) );
            Response.BinaryWrite( bs );
            Response.End( );
        }

        //绑定密保卡
        protected void BindPasswordCard( object sender , EventArgs e )
        {
            PasswordCard pc = new PasswordCard( );
            pc.SerialNumber = Convert.ToInt32( lbSerialNumber.Text.Replace(" ","") );
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
            bool resutl = accountsFacade.UpdateUserPasswordCardID( Fetch.GetUserCookie( ).UserID , pc.SerialNumber );
            if ( resutl )
            {
                ShowAndRedirect( "绑定成功" , "ApplyPasswordCard.aspx" );
            }
            else
            {
                Show( "绑定失败，请联系客服人员" );
                return;
            }
        }
    }
}
