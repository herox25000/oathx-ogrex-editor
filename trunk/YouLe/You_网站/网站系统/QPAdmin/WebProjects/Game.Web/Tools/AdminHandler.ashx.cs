using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using Game.Utils;
using Game.Facade;
using Game.Entity.PlatformManager;

namespace Game.Web.Tools
{
    /// <summary>
    /// Summary description for $codebehindclassname$
    /// </summary>
    [WebService( Namespace = "http://tempuri.org/" )]
    [WebServiceBinding( ConformsTo = WsiProfiles.BasicProfile1_1 )]
    public class AdminHandler : IHttpHandler
    {
        /// <summary>
        /// 后台外观
        /// </summary>
        protected PlatformManagerFacade aidePlatformManagerFacade = new PlatformManagerFacade( );

        public void ProcessRequest( HttpContext context )
        {
            context.Response.ContentType = "text/plain";
            string Action = GameRequest.GetQueryString( "action" );
            if ( string.IsNullOrEmpty( Action ) )
                return;
            switch ( Action.ToLower( ) )
            {
                case "bindip":
                    if( !CheckPostSource( ) )
                        return;
                    BindIP( context );
                    break;
                case "testinstanceid":
                    TestInstanceID( context );
                    break;
                default:
                    break;
            }
        } 
       
        /// <summary>
        /// 绑定IP
        /// </summary>
        /// <param name="context"></param>
        private void BindIP( HttpContext context )
        {
            Base_Users userExt = AdminCookie.GetUserFromCookie( );          
            int isbind = GameRequest.GetQueryInt( "isbind", 0 );
            if ( isbind >= 0 && userExt.UserID > 0 )
            {
                Base_Users user = aidePlatformManagerFacade.GetUserByUserID( userExt.UserID );
                if ( user == null )
                {
                    context.Response.Write( "-1" );
                    return;
                }
                user.BandIP = GameRequest.GetUserIP( );
                user.IsBand = isbind;
                aidePlatformManagerFacade.ModifyUserInfo( user );
                context.Response.Write( isbind );
                return;
            }
            context.Response.Write( "-1" );
        }

        /// <summary>
        /// 是否同域提交
        /// </summary>
        /// <returns></returns>
        public bool CheckPostSource( )
        {
            string str = "";
            string str2 = "";
            str2 = HttpContext.Current.Request.Url.Host.ToLower( );
            if ( HttpContext.Current.Request.UrlReferrer == null )
            {
                str = "";
            }
            else
            {
                str = HttpContext.Current.Request.UrlReferrer.Host.ToLower( );
            }
            return ( ( str.Length > 0 ) && str.Equals( str2 ) );
        }    
        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
        public void TestInstanceID ( HttpContext context )
        {
            string str = HttpContext.Current.Request.ServerVariables[ "INSTANCE_ID" ];
            context.Response.Write( str );
        }
    }
}
