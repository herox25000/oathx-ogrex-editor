using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using Game.Entity.Accounts;
using System.Data.Common;

namespace Game.Data
{
    /// <summary>
    /// 用户数据访问层
    /// </summary>
    public class AccountsDataProvider : BaseDataProvider , IAccountsDataProvider
    {
        #region 构造方法

        public AccountsDataProvider( string connString )
            : base( connString )
        {

        }
        #endregion

        #region 用户登录、注册

        /// <summary>
        /// 用户登录
        /// </summary>
        /// <param name="names">用户信息</param>
        /// <returns></returns>
        public Message Login( UserInfo user )
        {
            List<DbParameter> prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "strAccounts" , user.Accounts ) );
            prams.Add( Database.MakeInParam( "strPassword" , user.LogonPass ) );
            prams.Add( Database.MakeInParam( "strClientIP" , user.LastLogonIP ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessageForObject<UserInfo>( Database , "NET_PW_EfficacyAccounts" , prams );
        }

        /// <summary>
        /// 用户注册
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        public Message Register( UserInfo user , string parentAccount )
        {
            List<DbParameter> prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "strSpreader" , parentAccount ) );
            prams.Add( Database.MakeInParam( "strAccounts" , user.Accounts ) );
            prams.Add( Database.MakeInParam( "strNickname" , user.NickName ) );

            prams.Add( Database.MakeInParam( "strLogonPass" , user.LogonPass ) );
            prams.Add( Database.MakeInParam( "strInsurePass" , user.InsurePass ) );

            prams.Add( Database.MakeInParam( "strCompellation" , user.Compellation ) );
            prams.Add( Database.MakeInParam( "strPassPortID" , user.PassPortID ) );

            prams.Add( Database.MakeInParam( "dwFaceID" , user.FaceID ) );
            prams.Add( Database.MakeInParam( "dwGender" , user.Gender ) );

            prams.Add( Database.MakeInParam( "strClientIP" , user.RegisterIP ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessageForObject<UserInfo>( Database , "NET_PW_RegisterAccounts" , prams );
        }

        /// <summary>
        /// 判断用户名是否存在
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        public Message IsAccountsExist( string accounts )
        {
            List<DbParameter> prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "strAccounts" , accounts ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_IsAccountsExists" , prams );
        }

        /// <summary>
        /// 判断昵称是否存在
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        public bool IsNickNameExist( string nickName )
        {
            string sqlQuery = "SELECT NickName, UserID FROM AccountsInfo(NOLOCK) WHERE NickName=@NickName";
            List<DbParameter> prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "NickName" , nickName ) );
            UserInfo user = Database.ExecuteObject<UserInfo>( sqlQuery , prams );
            if( user != null )
            {
                return true;
            }
            return false;
        }

        #endregion

        #region 获取用户信息

        /// <summary>
        /// 根据用户昵称获取用户ID
        /// </summary>
        /// <param name="nickName"></param>
        /// <returns></returns>
        public int GetUserIDByNickName( string nickName )
        {
            string sqlQuery = string.Format( "SELECT NickName, UserID FROM AccountsInfo(NOLOCK) WHERE NickName='{0}'" , nickName );
            UserInfo user = Database.ExecuteObject<UserInfo>( sqlQuery );
            return user == null ? 0 : user.UserID;
        }

        /// <summary>
        /// 获取基本用户信息
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public UserInfo GetUserBaseInfoByUserID( int userID )
        {
            List<DbParameter> prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "dwUserID" , userID ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return Database.RunProcObject<UserInfo>( "NET_PW_GetUserBaseInfo" , prams );
        }

        /// <summary>
        /// 获取指定用户联系信息
        /// </summary>
        /// <param name="user">用户</param>
        /// <returns></returns> 		
        public IndividualDatum GetUserContactInfoByUserID( int userID )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return Database.RunProcObject<IndividualDatum>( "NET_PW_GetUserContactInfo" , parms );
        }

        /// <summary>
        /// 获取用户全局信息
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="gameID"></param>
        /// <param name="Accounts"></param>
        /// <returns></returns>
        public Message GetUserGlobalInfo( int userID , int gameID , String Accounts )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );
            parms.Add( Database.MakeInParam( "dwGameID" , gameID ) );
            parms.Add( Database.MakeInParam( "strAccounts" , Accounts ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessageForObject<UserInfo>( Database , "NET_PW_GetUserGlobalsInfo" , parms );
        }

        /// <summary>
        /// 获取密保卡序列号
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns></returns>
        public string GetPasswordCardByUserID( int userId )
        {
            string sqlQuery = string.Format( "SELECT PasswordID FROM AccountsInfo(NOLOCK) WHERE UserID={0}" , userId );
            return Database.ExecuteScalarToStr( System.Data.CommandType.Text , sqlQuery );
        }

        #endregion

        #region	 密码管理

        /// <summary>
        /// 重置登录密码
        /// </summary>
        /// <param name="sInfo">密保信息</param>       
        /// <returns></returns>
        public Message ResetLogonPasswd( AccountsProtect sInfo )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , sInfo.UserID ) );
            parms.Add( Database.MakeInParam( "strPassword" , sInfo.LogonPass ) );

            parms.Add( Database.MakeInParam( "strResponse1" , sInfo.Response1 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , sInfo.Response2 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , sInfo.Response3 ) );

            parms.Add( Database.MakeInParam( "strClientIP" , sInfo.LastLogonIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ResetLogonPasswd" , parms );
        }

        /// <summary>
        /// 重置银行密码
        /// </summary>
        /// <param name="sInfo">密保信息</param>       
        /// <returns></returns>
        public Message ResetInsurePasswd( AccountsProtect sInfo )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , sInfo.UserID ) );
            parms.Add( Database.MakeInParam( "strInsurePass" , sInfo.InsurePass ) );

            parms.Add( Database.MakeInParam( "strResponse1" , sInfo.Response1 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , sInfo.Response2 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , sInfo.Response3 ) );

            parms.Add( Database.MakeInParam( "strClientIP" , sInfo.LastLogonIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ResetInsurePasswd" , parms );
        }

        /// <summary>
        /// 修改登录密码
        /// </summary>
        /// <param name="userID">玩家标识</param>
        /// <param name="srcPassword">旧密码</param>
        /// <param name="dstPassword">新密码</param>
        /// <param name="ip">连接地址</param>
        /// <returns></returns>
        public Message ModifyLogonPasswd( int userID , string srcPassword , string dstPassword , string ip )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );
            parms.Add( Database.MakeInParam( "strSrcPassword" , srcPassword ) );
            parms.Add( Database.MakeInParam( "strDesPassword" , dstPassword ) );

            parms.Add( Database.MakeInParam( "strClientIP" , ip ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ModifyLogonPass" , parms );
        }

        /// <summary>
        /// 修改银行密码
        /// </summary>
        /// <param name="userID">玩家标识</param>
        /// <param name="srcPassword">旧密码</param>
        /// <param name="dstPassword">新密码</param>
        /// <param name="ip">连接地址</param>
        /// <returns></returns>
        public Message ModifyInsurePasswd( int userID , string srcPassword , string dstPassword , string ip )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );
            parms.Add( Database.MakeInParam( "strSrcPassword" , srcPassword ) );
            parms.Add( Database.MakeInParam( "strDesPassword" , dstPassword ) );

            parms.Add( Database.MakeInParam( "strClientIP" , ip ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ModifyInsurePass" , parms );
        }

        #endregion

        #region  密码保护管理

        /// <summary>
        /// 申请帐号保护
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        public Message ApplyUserSecurity( AccountsProtect sInfo )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , sInfo.UserID ) );

            parms.Add( Database.MakeInParam( "strQuestion1" , sInfo.Question1 ) );
            parms.Add( Database.MakeInParam( "strResponse1" , sInfo.Response1 ) );
            parms.Add( Database.MakeInParam( "strQuestion2" , sInfo.Question2 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , sInfo.Response2 ) );
            parms.Add( Database.MakeInParam( "strQuestion3" , sInfo.Question3 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , sInfo.Response3 ) );

            parms.Add( Database.MakeInParam( "dwPassportType" , ( byte )sInfo.PassportType ) );
            parms.Add( Database.MakeInParam( "strPassportID" , sInfo.PassportID ) );
            parms.Add( Database.MakeInParam( "strSafeEmail" , sInfo.SafeEmail ) );

            parms.Add( Database.MakeInParam( "strClientIP" , sInfo.CreateIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_AddAccountProtect" , parms );
        }

        /// <summary>
        /// 修改帐号保护
        /// </summary>
        /// <param name="oldInfo">旧密保信息</param>
        /// <param name="newInfo">新密保信息</param>
        /// <returns></returns>
        public Message ModifyUserSecurity( AccountsProtect newInfo )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , newInfo.UserID ) );

            parms.Add( Database.MakeInParam( "strQuestion1" , newInfo.Question1 ) );
            parms.Add( Database.MakeInParam( "strResponse1" , newInfo.Response1 ) );
            parms.Add( Database.MakeInParam( "strQuestion2" , newInfo.Question2 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , newInfo.Response2 ) );
            parms.Add( Database.MakeInParam( "strQuestion3" , newInfo.Question3 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , newInfo.Response3 ) );

            parms.Add( Database.MakeInParam( "strSafeEmail" , newInfo.SafeEmail ) );

            parms.Add( Database.MakeInParam( "strClientIP" , newInfo.ModifyIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ModifyAccountProtect" , parms );
        }

        /// <summary>
        /// 获取密保信息 (userID)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSecurityByUserID( int userID )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );

            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessageForObject<AccountsProtect>( Database , "NET_PW_GetAccountProtectByUserID" , parms );
        }

        /// <summary>
        /// 获取密保信息 (gameID)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSecurityByGameID( int gameID )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwGameID" , gameID ) );

            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessageForObject<AccountsProtect>( Database , "NET_PW_GetAccountProtectByGameID" , parms );
        }

        /// <summary>
        /// 获取密保信息 (Accounts)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSecurityByAccounts( string accounts )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "strAccounts" , accounts ) );

            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessageForObject<AccountsProtect>( Database , "NET_PW_GetAccountProtectByAccounts" , parms );
        }

        /// <summary>
        /// 密保确认
        /// </summary>
        /// <param name="info"></param>
        /// <returns></returns>
        public Message ConfirmUserSecurity( AccountsProtect info )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , info.UserID ) );

            parms.Add( Database.MakeInParam( "strResponse1" , info.Response1 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , info.Response2 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , info.Response3 ) );

            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ConfirmAccountProtect" , parms );
        }

        #endregion

        #region 安全管理

        #region 固定机器

        /// <summary>
        /// 申请机器绑定
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        public Message ApplyUserMoorMachine( AccountsProtect sInfo )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , sInfo.UserID ) );

            parms.Add( Database.MakeInParam( "strResponse1" , sInfo.Response1 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , sInfo.Response2 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , sInfo.Response3 ) );

            parms.Add( Database.MakeInParam( "strClientIP" , sInfo.LastLogonIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ApplyMoorMachine" , parms );
        }

        /// <summary>
        /// 解除机器绑定
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        public Message RescindUserMoorMachine( AccountsProtect sInfo )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , sInfo.UserID ) );

            parms.Add( Database.MakeInParam( "strResponse1" , sInfo.Response1 ) );
            parms.Add( Database.MakeInParam( "strResponse2" , sInfo.Response2 ) );
            parms.Add( Database.MakeInParam( "strResponse3" , sInfo.Response3 ) );

            parms.Add( Database.MakeInParam( "strClientIP" , sInfo.LastLogonIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_CancelMoorMachine" , parms );
        }

        #endregion 固定机器结束

        #endregion

        #region 资料管理

        /// <summary>
        /// 更新个人资料
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        public Message ModifyUserIndividual( IndividualDatum user )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , user.UserID ) );

            parms.Add( Database.MakeInParam( "dwGender" , ( byte )user.Gender ) );
            parms.Add( Database.MakeInParam( "strUnderWrite" , user.UnderWrite ) );

            parms.Add( Database.MakeInParam( "strCompellation" , user.Compellation ) );
            parms.Add( Database.MakeInParam( "strQQ" , user.QQ ) );
            parms.Add( Database.MakeInParam( "strEmail" , user.EMail ) );
            parms.Add( Database.MakeInParam( "strSeatPhone" , user.SeatPhone ) );
            parms.Add( Database.MakeInParam( "strMobilePhone" , user.MobilePhone ) );
            parms.Add( Database.MakeInParam( "strDwellingPlace" , user.DwellingPlace ) );
            parms.Add( Database.MakeInParam( "strUserNote" , user.UserNote ) );

            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ModifyUserInfo" , parms );
        }

        /// <summary>
        /// 更新用户头像
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="faceID"></param>
        /// <returns></returns>
        public Message ModifyUserFace( int userID , int faceID )
        {
            List<DbParameter> prams = new List<DbParameter>( );

            prams.Add( Database.MakeInParam( "dwUserID" , userID ) );
            prams.Add( Database.MakeInParam( "dwFaceID" , faceID ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ModifyUserFace" , prams );
        }

        /// <summary>
        /// 更新用户昵称
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="faceID"></param>
        /// <returns></returns>
        public Message ModifyUserNickname( int userID , string nickName , string ip )
        {
            List<DbParameter> prams = new List<DbParameter>( );

            prams.Add( Database.MakeInParam( "dwUserID" , userID ) );
            prams.Add( Database.MakeInParam( "strNickName" , nickName ) );
            prams.Add( Database.MakeInParam( "clientIP" , ip ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ModifyUserNickName" , prams );
        }

        #endregion

        #region 魅力兑换

        public Message UserConvertPresent( int userID , int present , int rate , string ip )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );
            parms.Add( Database.MakeInParam( "dwPresent" , present ) );
            parms.Add( Database.MakeInParam( "dwConvertRate" , rate ) );
            parms.Add( Database.MakeInParam( "strClientIP" , ip ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ConvertPresent" , parms );
        }

        /// <summary>
        /// 根据用户魅力排名(前10名)
        /// </summary>
        /// <returns></returns>
        public IList<UserInfo> GetUserInfoOrderByLoves( )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "SELECT TOP 10 Accounts, NickName,GameID, LoveLiness, Present " )
                    .Append( "FROM AccountsInfo " )
                    .Append( "WHERE Nullity=0 " )
                    .Append( " ORDER By LoveLiness DESC,UserID ASC" );
            return Database.ExecuteObjectList<UserInfo>( sqlQuery.ToString( ) );
        }

        #endregion

        #region 奖牌兑换

        public Message UserConvertMedal( int userID , int medals , int rate , string ip )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwUserID" , userID ) );
            parms.Add( Database.MakeInParam( "dwMedals" , medals ) );
            parms.Add( Database.MakeInParam( "dwConvertRate" , rate ) );
            parms.Add( Database.MakeInParam( "strClientIP" , ip ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe" , typeof( string ) , 127 ) );

            return MessageHelper.GetMessage( Database , "NET_PW_ConvertMedal" , parms );
        }

        #endregion

        #region 电子密保卡

        /// <summary>
        /// 检测密保卡序列号是否存在
        /// </summary>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        public bool PasswordIDIsEnable( string serialNumber )
        {
            string sqlQuery = string.Format( "SELECT UserID FROM AccountsInfo(NOLOCK) WHERE PasswordID='{0}'" , serialNumber );
            AccountsInfo user = Database.ExecuteObject<AccountsInfo>( sqlQuery );
            if( user == null )
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// 检测用户是否绑定了密保卡
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        public bool userIsBindPasswordCard( int userId )
        {
            string sqlQuery = string.Format( "SELECT UserID FROM AccountsInfo(NOLOCK) WHERE PasswordID<>0 and userID={0}" , userId );
            AccountsInfo user = Database.ExecuteObject<AccountsInfo>( sqlQuery );
            if( user == null )
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// 更新用户密保卡序列号
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        public bool UpdateUserPasswordCardID( int userId , int serialNumber )
        {
            string sqlQuery = string.Format( "UPDATE AccountsInfo SET PasswordID={0} WHERE UserID={1}" , serialNumber , userId );
            int resutl = Database.ExecuteNonQuery( sqlQuery );
            if( resutl > 0 )
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// 取消密保卡绑定
        /// </summary>
        /// <param name="userId"></param>
        /// <returns></returns>
        public bool ClearUserPasswordCardID( int userId )
        {
            string sqlQuery = string.Format( "UPDATE AccountsInfo SET PasswordID=0 WHERE UserID={0}" , userId );
            int resutl = Database.ExecuteNonQuery( sqlQuery );
            if( resutl > 0 )
            {
                return true;
            }
            return false;
        }

        #endregion

        #region 公共

        /// <summary>
        /// 根据SQL语句查询一个值
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        public object GetObjectBySql( string sqlQuery )
        {
            return Database.ExecuteScalar( System.Data.CommandType.Text , sqlQuery );
        }

        #endregion
    }
}
