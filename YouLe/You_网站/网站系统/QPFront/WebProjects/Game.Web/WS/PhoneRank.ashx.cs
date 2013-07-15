using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Text;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using System.Data;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace Game.Web.WS
{
    /// <summary>
    /// Summary description for $codebehindclassname$
    /// </summary>
    [WebService( Namespace = "http://tempuri.org/" )]
    [WebServiceBinding( ConformsTo = WsiProfiles.BasicProfile1_1 )]
    public class PhoneRank : IHttpHandler
    {
        private TreasureFacade treasureFacade = new TreasureFacade( );

        public void ProcessRequest( HttpContext context )
        {
            context.Response.ContentType = "text/plain";
            context.Response.ContentType = "text/plain";
            string action = GameRequest.GetQueryString( "action" );
            switch( action )
            {
                case "getscorerank":
                    GetScoreRank( context );
                    break;
                default:
                    break;
            }
        }

        //获取金币排行榜，前50
        protected void GetScoreRank( HttpContext context )
        {
            StringBuilder msg = new StringBuilder( );
            int pageIndex = GameRequest.GetInt( "pageindex" , 1 );
            int pageSize = GameRequest.GetInt( "pagesize" , 10 );
            if( pageIndex <= 0 )
            {
                pageIndex = 1;
            }
            if( pageSize <= 0 )
            {
                pageSize = 10;
            }
            if( pageSize > 50 )
            {
                pageSize = 50;
            }
            DataSet ds = treasureFacade.GetList( "GameScoreInfo" , pageIndex , pageSize , " ORDER BY Score DESC" , " WHERE UserID IN(SELECT UserID FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo)" , "UserID,Score" ).PageSet;
            if( ds.Tables[ 0 ].Rows.Count > 0 )
            {
                msg.Append( "[" );
                foreach( DataRow dr in ds.Tables[ 0 ].Rows )
                {
                    msg.Append( "{\"NickName\":\"" + Fetch.GetNickNameByUserID( Convert.ToInt32( dr[ "UserID" ] ) ) + "\",\"Score\":" + dr[ "Score" ] + "}," );
                }
                msg.Remove( msg.Length - 1 , 1 );
                msg.Append( "]" );
            }
            else
            {
                msg.Append( "{}" );
            }
            context.Response.Write( msg.ToString( ) );
        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
    }
}
