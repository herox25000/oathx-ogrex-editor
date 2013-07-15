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
using Game.Facade;

namespace Game.Web.Module.AccountManager
{
    public partial class AccountPasswordCard : AdminPage
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
        #endregion

        #region 窗口事件
        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                if ( Header != null )
                    Title = StrTitle;
                BindData( );
            }
        }
        
        //取消绑定
        protected void btn_ClearPasswordCard( object sender , EventArgs e )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.AppendFormat( "UPDATE {0} SET PasswordID = '0' WHERE PasswordID != '0' AND UserID = {1}" , AccountsInfo.Tablename , IntParam );
            int result = aideAccountsFacade.ExecuteSql( sqlQuery.ToString( ) );
            if ( result > 0 )
            {
                //MessageBox(  );
                MessageBoxClose( "取消密保卡绑定成功" );
            }
            else
            {
                MessageBox( "取消失败" );
            }
        }
        
        #endregion

        #region 绑定数据

        protected void BindData( )
        {
            //密保卡信息
            AccountsInfo model = aideAccountsFacade.GetAccountInfoByUserID( IntParam );
            PasswordCard pc = new PasswordCard( );
            if ( model.PasswordID != 0 )
            {
                lbSerialNumber.Text = model.PasswordID.ToString( );
                pc.SerialNumber = model.PasswordID;
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
            }
        }

        #endregion
    }
}
