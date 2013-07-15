using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;

using Game.Utils;
using System.Web.Security;
using Game.Entity.PlatformManager;

namespace Game.Facade
{
    /// <summary>
    /// 用户Cookie数据
    /// </summary>
    public class AdminCookie
    {

        /// <summary>
        /// 设置用户 Cookie
        /// </summary>
        /// <param name="user"></param>
        public static void SetUserCookie( Base_Users user )
        {
            Dictionary<string, object> dic = new Dictionary<string, object>( );
            dic.Add( Base_Users._UserID, user.UserID );
            dic.Add( Base_Users._Username, user.Username );
            dic.Add( Base_Users._RoleID, user.RoleID );
            dic.Add( Base_Users._IsBand, user.IsBand );
            Add( dic , 30 );
            /* HttpCookie cookie = new HttpCookie( Fetch.GetCookieName );
             cookie[Base_Users._UserID] = Utility.UrlEncode( user.UserID.ToString( ) );
             cookie[Base_Users._Accounts] = Utility.UrlEncode( user.Accounts );
             cookie[Base_Users._LogonPass] = Utility.UrlEncode( user.LogonPass );
             cookie[Base_Users._RoleID] = Utility.UrlEncode( user.RoleID.ToString( ) );
             cookie[Base_Users._RoleName] = Utility.UrlEncode( user.RoleName );
             cookie[Base_Users._Nullity] = Utility.UrlEncode( user.Nullity.ToString( ) );
             cookie[Base_Users._RealName] = Utility.UrlEncode( user.RealName );
             cookie[Base_Users._LinkEmail] = Utility.UrlEncode( user.LinkEmail );
             cookie[Base_Users._LastLogonDate] = Utility.UrlEncode( user.LastLogonDate.ToString( ) );
             cookie[Base_Users._OwnStation] = user.OwnStation.ToString( );
             #if DEBUG
             cookie.Expires = DateTime.Now.AddDays( 1 );
             #endif
             Cookie.Save( cookie );*/
        }

        /// <summary>
        /// 获取用户对象 by Cookie
        /// </summary>
        /// <returns></returns>
        public static Base_Users GetUserFromCookie( )
        {
            HttpContext context = HttpContext.Current;
            if ( context == null )
                return null;

            Base_Users user = new Base_Users( );
            object objUserID = GetValue( Base_Users._UserID );
            object objAccount = GetValue( Base_Users._Username );
            object objRoleID = GetValue( Base_Users._RoleID );
            object objIsBand = GetValue( Base_Users._IsBand );
            if ( objUserID == null || objAccount == null || objRoleID == null || objIsBand == null )
                return null;
            user.UserID = int.Parse( objUserID.ToString( ) );
            user.Username = objAccount.ToString( );
            user.RoleID = int.Parse( objRoleID.ToString( ) );
            user.IsBand = int.Parse( objIsBand.ToString( ) );

            return user;
            /*
            string cookie = Utility.GetCookie( Fetch.GetCookieName );
            if ( TextUtility.EmptyTrimOrNull( cookie ) )
                return null;

            Base_Users user = new Base_Users( );
            user.UserID = TypeParse.StrToInt( GetCookie( Base_Users._UserID ), 0 );
            user.Accounts = GetCookie( Base_Users._Accounts );
            user.LogonPass = GetCookie( Base_Users._LogonPass );
            user.RoleID = TypeParse.StrToInt( GetCookie( Base_Users._RoleID ), 0 );
            user.RoleName = GetCookie( Base_Users._RoleName );
            user.Nullity = Convert.ToByte( GetCookie( Base_Users._Nullity ) );
            user.RealName = GetCookie( Base_Users._RealName );
            user.LinkEmail = GetCookie( Base_Users._LinkEmail );
            user.LastLogonDate = Convert.ToDateTime( GetCookie( Base_Users._LastLogonDate ) );
            user.OwnStation = GetCookie( Base_Users._OwnStation );

            return user;*/
        }

        /// <summary>
        /// 清理用户Cookie
        /// </summary>
        public static void ClearUserCookie( )
        {
            if ( HttpContext.Current == null )
                return;

            HttpCookie cookie = HttpContext.Current.Request.Cookies[Fetch.GetCookieName];
            cookie.Expires = DateTime.Now.AddYears( -1 );
            HttpContext.Current.Response.Cookies.Add( cookie );
            //Cookie.Remove( cookie );
        }

        /// <summary>
        /// 检查用户登录状态
        /// </summary>
        /// <returns></returns>
        public static bool CheckedUserLogon( )
        {
            Base_Users user = AdminCookie.GetUserFromCookie( );
            if ( user == null || user.UserID <= 0 || user.RoleID <= 0 )
                return false;
            else
                AdminCookie.SetUserCookie( user );

            return true;
        }

        //根据键值获取Cookie值
        private static string GetCookie( string strKey )
        {
            return Utility.UrlDecode( Utility.GetCookie( Fetch.GetCookieName, strKey ) );
        }

        #region Cookie操作
        private static string ValidateKey = "{2EF1D4CB-16BA-471D-9DFC-12C1E4D15253}";
        private static string ValidateName = "VS";
        private static string ExpireTimeStr = "_ETS";
        /// <summary>
        /// Cookie名称
        /// </summary>
        protected static string CookiesName
        {
            get
            {
                string strName = Utility.GetAppSetting( "CookiesName" );
                if ( !string.IsNullOrEmpty( strName ) )
                {
                    return strName;
                }
                else if ( !string.IsNullOrEmpty( Fetch.GetCookieName ) )
                {
                    return Fetch.GetCookieName;
                }
                return "Default";
            }
        }
        /// <summary>
        /// Cookie过期时间(分钟)
        /// </summary>
        protected static DateTime CookiesExpire
        {
            get
            {
                int num;
                if ( !int.TryParse( Utility.GetAppSetting( "CookiesExpireMinutes" ), out num ) )
                {
                    num = 30;
                }
                return DateTime.Now.AddMinutes( ( double ) num );
            }
        }
        /// <summary>
        /// Cookie路径
        /// </summary>
        protected static string CookiesPath
        {
            get
            {
                string strPath = Utility.GetAppSetting( "CookiesPath" );
                if ( !string.IsNullOrEmpty( strPath ) )
                {
                    return strPath;
                }
                return "/";
            }
        }
        /// <summary>
        /// Cookie域
        /// </summary>
        protected static string CookiesDomain
        {
            get
            {
                string strDomain = Utility.GetAppSetting( "CookiesDomain" );
                if ( !string.IsNullOrEmpty( strDomain ) )
                {
                    return strDomain;
                }
                return "";
            }
        }
        /// <summary>
        /// 设置用户Cookie
        /// </summary>
        /// <param name="key">键</param>
        /// <param name="value">值</param>
        /// <param name="timeout">过期时间(分钟)</param>
        public static void Add( string key, object value, int? timeout )
        {
            HttpCookie ck = HttpContext.Current.Request.Cookies[CookiesName];
            if ( ck == null )
            {
                ck = new HttpCookie( CookiesName );
            }
            ck.Expires = DateTime.Now.AddYears( 50 );
            ck.Domain = CookiesDomain;
            ck.Values[key] = HttpUtility.UrlEncode( value.ToString( ) );
            ck.Values[key + ExpireTimeStr] = !timeout.HasValue ? HttpUtility.UrlEncode( CookiesExpire.ToString( "yyyy-MM-dd HH:mm:ss" ) ) : HttpUtility.UrlEncode( DateTime.Now.AddMinutes( ( double ) timeout.Value ).ToString( "yyyy-MM-dd HH:mm:ss" ) );
            ck.Values[ValidateName] = GetValidateStr( ck );
            HttpContext.Current.Response.Cookies.Add( ck );
        }
        /// <summary>
        /// 设置用户Cookie
        /// </summary>
        /// <param name="dic">键值集合</param>
        /// <param name="timeout">过期时间(分钟)</param>
        public static void Add( Dictionary<string, object> dic, int? timeout )
        {
            HttpCookie ck = HttpContext.Current.Request.Cookies[CookiesName];
            if ( ck == null )
            {
                ck = new HttpCookie( CookiesName );
            }
            ck.Expires = DateTime.Now.AddYears( 50 );
            ck.Domain = CookiesDomain;
            foreach ( KeyValuePair<string, object> pair in dic )
            {
                ck.Values[pair.Key] = HttpUtility.UrlEncode( pair.Value.ToString( ) );
                ck.Values[pair.Key + ExpireTimeStr] = !timeout.HasValue ? HttpUtility.UrlEncode( CookiesExpire.ToString( "yyyy-MM-dd HH:mm:ss" ) ) : HttpUtility.UrlEncode( DateTime.Now.AddMinutes( ( double ) timeout.Value ).ToString( "yyyy-MM-dd HH:mm:ss" ) );
            }
            ck.Values[ValidateName] = GetValidateStr( ck );
            HttpContext.Current.Response.Cookies.Add( ck );
        }
        /// <summary>
        /// 根据键名获取Cookie值
        /// </summary>
        /// <param name="key">键</param>
        /// <returns></returns>
        public static object GetValue( string key )
        {
            if ( ( key != null ) && ( key != "" ) )
            {
                DateTime time;
                HttpCookie ck = HttpContext.Current.Request.Cookies[CookiesName];
                if ( ck == null )
                {
                    return null;
                }
                ck.Expires = DateTime.Now.AddYears( 50 );
                ck.Domain = CookiesDomain;
                if ( !ValidateCookies( ck ) )
                {
                    ck.Expires = DateTime.Now.AddYears( -1 );
                    HttpContext.Current.Response.Cookies.Add( ck );
                    return null;
                }
                string str = ck.Values[key + ExpireTimeStr];
                if ( string.IsNullOrEmpty( str ) || !DateTime.TryParse( HttpUtility.UrlDecode( str ), out time ) )
                {
                    ck.Values[key] = "";
                    ck.Values[key + ExpireTimeStr] = "";
                    ck.Values[ValidateName] = GetValidateStr( ck );
                    HttpContext.Current.Response.Cookies.Add( ck );
                    return null;
                }
                DateTime now = DateTime.Now;
                if ( time > now )
                {
                    return HttpUtility.UrlDecode( ck.Values[key] );
                }
                ck.Values[key] = "";
                ck.Values[key + ExpireTimeStr] = "";
                ck.Values[ValidateName] = GetValidateStr( ck );
                HttpContext.Current.Response.Cookies.Add( ck );
            }
            return null;
        }
        /// <summary>
        /// 加密
        /// </summary>
        /// <param name="ck"></param>
        /// <returns></returns>
        private static string GetValidateStr( HttpCookie ck )
        {
            StringBuilder builder = new StringBuilder( );
            foreach ( string str in ck.Values.AllKeys )
            {
                if ( str != ValidateName )
                {
                    builder.Append( ck.Values[str] );
                }
            }
            builder.Append( ValidateKey );
            builder.Append( HttpContext.Current.Request.ServerVariables["LOCAL_ADDR"] );
            builder.Append( HttpContext.Current.Request.ServerVariables["INSTANCE_ID"] );
            builder.Append( HttpContext.Current.Request.ServerVariables["HTTP_USER_AGENT"] );
            return FormsAuthentication.HashPasswordForStoringInConfigFile( builder.ToString( ), "md5" ).ToLower( ).Substring( 8, 0x10 );
        }
        /// <summary>
        ///  验证
        /// </summary>
        /// <param name="ck"></param>
        /// <returns></returns>
        private static bool ValidateCookies( HttpCookie ck )
        {
            string strSourse = ck.Values[ValidateName];
            StringBuilder builder = new StringBuilder( );
            foreach ( string str in ck.Values.AllKeys )
            {
                if ( str != ValidateName )
                {
                    builder.Append( ck.Values[str] );
                }
            }
            builder.Append( ValidateKey );
            builder.Append( HttpContext.Current.Request.ServerVariables["LOCAL_ADDR"] );
            builder.Append( HttpContext.Current.Request.ServerVariables["INSTANCE_ID"] );
            builder.Append( HttpContext.Current.Request.ServerVariables["HTTP_USER_AGENT"] );
            string strValidate = FormsAuthentication.HashPasswordForStoringInConfigFile( builder.ToString( ), "md5" ).ToLower( ).Substring( 8, 0x10 );
            return strSourse.Equals( strValidate );
        }
        #endregion
    }
}
