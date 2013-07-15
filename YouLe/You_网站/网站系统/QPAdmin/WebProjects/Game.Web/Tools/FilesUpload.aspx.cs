using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Utils;
using Game.Facade.Files;
using Game.Facade;
using Game.Entity;
using Game.Entity.PlatformManager;

namespace Game.Web.Tools
{
    public partial class FilesUpload : System.Web.UI.Page
    {
        #region Fields

        protected string clientPath = GameRequest.GetQueryString( "path" );   //相对路径
        protected string inImgUrl = GameRequest.GetQueryString( "inImgUrl" ); //保存图片路径的字段

        protected StringBuilder builder = new StringBuilder( );

        #endregion

        #region 事件处理

        protected void Page_Load( object sender , EventArgs e )
        {
            //验证
            Base_Users userExt = AdminCookie.GetUserFromCookie( );
            if( userExt == null || userExt.UserID <= 0 )
            {
                return;
            }

            //路径处理
            if( TextUtility.EmptyTrimOrNull( clientPath ) || clientPath == "/" || !clientPath.StartsWith( "/upload" ) )
            {
                clientPath = "/upload";
            }

            //操作处理
            HttpFileManager fileManage = new HttpFileManager( Request.QueryString[ "act" ] );
            builder.Append( fileManage.Value );
            if( builder.Length > 0 )
            {
                SetUploadFilePath( builder.ToString( ).Replace( "'" , "\\'" ).Replace( "\r\n" , "" ) , fileManage.UploadFilePath );
            }
        }

        protected void SetUploadFilePath( string msg , string uploadPath )
        {
            Page.ClientScript.RegisterStartupScript( typeof( Page ) , "" ,
                string.Format( "showInfo(\"{2}\");setUploadFilePath(\"{0}\",\"{1}\");" , inImgUrl , uploadPath , msg ) , true );
        }

        #endregion
    }
}
