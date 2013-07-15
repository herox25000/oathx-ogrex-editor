using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Utils;
using Game.Web.UI;
using Game.Entity.Treasure;
using Game.Kernel;
using Game.Entity.Record;
using System.Text;
using System.Data;

namespace Game.Web.Module.FilledManager
{
    public partial class LivcardEdit : AdminPage
    {
        #region 窗口事件
        
        protected void Page_Load( object sender , EventArgs e )
        {

        }

        protected void btnSave_Click( object sender , EventArgs e )
        {
            //更新充值卡表
            string date = CtrlHelper.GetText( txtEnjoinOverDate );
            string password = CtrlHelper.GetText( txtPassword );
            int buildId = Convert.ToInt32( GameRequest.GetString( "buildId" ).Trim( ));
            if ( date == "" && password == "" )
            {
                MessageBox( "请输入密码或者有效期" );
                return;
            }
            StringBuilder sqlQuery=new StringBuilder();
            if ( date != "" && password != "" )
            {
                sqlQuery.AppendFormat( "update {0} set ValidDate='{1}',PassWord='{2}' where CardID in ({3})" , LivcardAssociator.Tablename , date , Utility.MD5( password ) , StrParamsList );
            }
            else
            {
                if ( date != "" )
                {
                    sqlQuery.AppendFormat( "update {0} set ValidDate='{1}' where CardID in ({2})" , LivcardAssociator.Tablename , date , StrParamsList );
                }
                else
                {
                    sqlQuery.AppendFormat( "update {0} set PassWord='{1}' where CardID in ({2})" , LivcardAssociator.Tablename , Utility.MD5( password ) , StrParamsList );
                }
            }
            int results = aideTreasureFacade.ExecuteSql( sqlQuery.ToString() );
            LivcardBuildStream LivcardBuild = aideTreasureFacade.GetLivcardBuildStreamInfo( buildId );

            //更新批次表
            string byteList = UnicodeEncoding.Default.GetString( LivcardBuild.BuildCardPacket );
            StringBuilder sqlQueryCard = new StringBuilder( );
            sqlQueryCard.AppendFormat( "SELECT SerialID FROM {0} WHERE CardID in ({1})" , LivcardAssociator.Tablename , StrParamsList );
            DataSet ds = aideTreasureFacade.GetDataSetBySql( sqlQueryCard.ToString( ) );
            foreach ( DataRow row in ds.Tables[0].Rows )
            {
                string serialID = row["SerialID"].ToString( );
                int number1 = byteList.IndexOf( serialID );
                string prefix = byteList.Substring( 0 , number1 + serialID.Length + 1 );
                int number2 = byteList.IndexOf( "/" , number1 + serialID.Length + 1 );
                string profix = byteList.Substring( number2 );
                byteList = prefix + password + profix;
            }
            LivcardBuild.BuildCardPacket = UnicodeEncoding.Default.GetBytes( byteList );
            aideTreasureFacade.UpdateLivcardBuildStream( LivcardBuild );
            if ( results > 0 )
            {
                MessageBoxClose( "成功更新" + results + "条记录" );
                
            }
            else
            {
                MessageBoxClose( "没有符合的数据更新" );
            }
        }

        #endregion
    }
}
