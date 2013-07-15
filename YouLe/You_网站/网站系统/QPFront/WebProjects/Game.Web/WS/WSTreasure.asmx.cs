using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Xml.Linq;

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using System.Text;
using System.Collections.Generic;

namespace Game.Web.WS
{
    /// <summary>
    /// WSTreasure 的摘要说明
    /// </summary>
    [WebService( Namespace = "http://tempuri.org/" )]
    [WebServiceBinding( ConformsTo = WsiProfiles.BasicProfile1_1 )]
    [ToolboxItem( false )]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    [System.Web.Script.Services.ScriptService]
    public class WSTreasure : System.Web.Services.WebService
    {
        private TreasureFacade treasureFacade = new TreasureFacade( );
        private AccountsFacade accountsFacade = new AccountsFacade( );

        /// <summary>
        /// 财富排名
        /// </summary>
        /// <returns></returns>
        [WebMethod]
        public string GetUserScoroInfo( )
        {
            StringBuilder msg = new StringBuilder( );
            //if ( scoreList == null ) return "{}";
            //msg.Append( "[" );
            //foreach ( GameScoreInfo scoreInfo in scoreList )
            //{
            //    msg.Append( "{userName:'" + Fetch.GetNickNameByUserID( scoreInfo.UserID ) + "',s:'" + scoreInfo.Score + "'}," );
            //}
            //msg.Remove( msg.Length - 1 , 1 );
            //msg.Append( "]" );

            DataSet ds = treasureFacade.GetScoreRanking( 10 );
            if( ds.Tables[ 0 ].Rows.Count > 0 )
            {
                msg.Append( "[" );
                foreach( DataRow dr in ds.Tables[ 0 ].Rows )
                {
                    msg.Append( "{userName:'" + dr[ "NickName" ] + "',s:'" + dr[ "Score" ] + "'}," );
                }
                msg.Remove( msg.Length - 1 , 1 );
                msg.Append( "]" );
            }
            else
            {
                msg.Append( "{}" );
            }
            return msg.ToString( );
        }
    }
}
