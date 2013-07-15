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
using Game.Facade;
using Game.Utils;
using System.Text;
using System.Collections.Generic;
using Game.Kernel;

namespace Game.Web.WS
{
    /// <summary>
    /// WSAccount 的摘要说明
    /// </summary>
    [WebService( Namespace = "http://tempuri.org/" )]
    [WebServiceBinding( ConformsTo = WsiProfiles.BasicProfile1_1 )]
    [ToolboxItem( false )]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    [System.Web.Script.Services.ScriptService]
    public class WSAccount : System.Web.Services.WebService
    {
        private AccountsFacade accountFacade = new AccountsFacade( );
        /// <summary>
        /// 用户登录
        /// </summary>
        /// <param name="userName"></param>
        /// <param name="userPass"></param>
        /// <param name="code"></param>
        /// <returns></returns>
        [WebMethod]
        public string Logon( string userName , string userPass , string code )
        {
            string msg = "";

            if( TextUtility.EmptyTrimOrNull( userName ) || TextUtility.EmptyTrimOrNull( userPass ) )
            {
                msg = "抱歉！您输入的用户名或密码错误了。";
                return "{success:'error',msg:'" + msg + "'}";
            }

            //验证码错误
            if( !code.Equals( Fetch.GetVerifyCode( ) , StringComparison.InvariantCultureIgnoreCase ) )
            {
                msg = "抱歉！您输入的验证码错误了。";
                return "{success:'error',msg:'" + msg + "'}";
            }

            Message umsg = accountFacade.Logon( userName , userPass );
            if( umsg.Success )
            {
                UserInfo ui = umsg.EntityList[ 0 ] as UserInfo;
                ui.LogonPass = TextEncrypt.EncryptPassword( userPass );

                Fetch.SetUserCookie( ui.ToUserTicketInfo( ) );
                string mOrder = ui.MemberOrder == 0 ? "普通会员" : ui.MemberOrder == 1 ? "蓝钻会员" : ui.MemberOrder == 2 ? "黄钻会员" : ui.MemberOrder == 3 ? "白钻会员" : "红钻会员";
                msg = "{success:'success',account:'" + ui.Accounts + "',gid:'" + ui.GameID + "',loves:'" + ui.LoveLiness + "',morder:'" + mOrder + "',fid:'" + ui.FaceID + "'}";
            }
            else
            {
                msg = "{success:'error',msg:'" + umsg.Content + "'}";
            }
            return msg;
        }

        /// <summary>
        /// 获取用户登录信息
        /// </summary>
        /// <returns></returns>
        [WebMethod]
        public string GetUserInfo( )
        {
            UserTicketInfo userTick = Fetch.GetUserCookie( );
            if( userTick == null ) return "{}";
            Message umsg = accountFacade.GetUserGlobalInfo( userTick.UserID , 0 , "" );
            if( umsg.Success )
            {
                UserInfo ui = umsg.EntityList[ 0 ] as UserInfo;
                string mOrder = ui.MemberOrder == 0 ? "普通会员" : ui.MemberOrder == 1 ? "蓝钻会员" : ui.MemberOrder == 2 ? "黄钻会员" : ui.MemberOrder == 3 ? "白钻会员" : "红钻会员";
                return "{success:'success',account:'" + ui.Accounts + "',gid:'" + ui.GameID + "',loves:'" + ui.LoveLiness + "',morder:'" + mOrder + "',fid:'" + ui.FaceID + "'}";
            }
            return "{}";
        }

        /// <summary>
        /// 检测用户名
        /// </summary>
        /// <param name="userName"></param>
        /// <returns></returns>
        [WebMethod]
        public string CheckName( string userName )
        {
            Message umsg = accountFacade.IsAccountsExist( userName );
            if( umsg.Success )
            {
                return "{success:'success'}";
            }
            return "{success:'error',msg:'" + umsg.Content + "'}";
        }

        /// <summary>
        /// 检测昵称
        /// </summary>
        /// <param name="userName"></param>
        /// <returns></returns>
        [WebMethod]
        public string CheckNickName( string nickName )
        {
            if( accountFacade.IsNickNameExist( nickName ) )
            {
                return "{success:'success'}";
            }
            return "{success:'error'}";
        }

        /// <summary>
        /// 用户魅力排名
        /// </summary>
        /// <returns></returns>
        [WebMethod]
        public string GetUserLoves( )
        {
            StringBuilder msg = new StringBuilder( );
            IList<UserInfo> users = accountFacade.GetUserInfoOrderByLoves( );
            if( users == null ) return "{}";
            msg.Append( "[" );
            foreach( UserInfo user in users )
            {
                msg.Append( "{userName:'" + user.NickName + "',loves:'" + user.LoveLiness + "'}," );
            }
            msg.Remove( msg.Length - 1 , 1 );
            msg.Append( "]" );
            return msg.ToString( );
        }
    }
}
