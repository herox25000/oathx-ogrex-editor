using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Data.Factory;
using Game.IData;
using Game.Kernel;
using Game.Utils;
using Game.Entity.Accounts;
using System.Data;

namespace Game.Facade
{
    /// <summary>
    /// 用户外观
    /// </summary>
    public class AccountsFacade
    {
        #region Fields

        private IAccountsDataProvider accountsData;
        private ITreasureDataProvider treasureData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public AccountsFacade()
        {
            accountsData = ClassFactory.GetIAccountsDataProvider();
            treasureData = ClassFactory.GetITreasureDataProvider();
        }
        #endregion

        #region 用户登录、注册

        /// <summary>
        /// 用户登录
        /// </summary>
        public Message Logon(UserInfo user, bool isEncryptPasswd)
        {
            Message umsg;
            if (!isEncryptPasswd)
            {
                user.LogonPass = TextEncrypt.EncryptPassword(user.LogonPass);
            }

            umsg = accountsData.Login(user);
            return umsg;
        }

        /// <summary>
        /// 用户登录，登录密码必须是密文。并且验证登录参数
        /// </summary>
        /// <param name="stationID">站点标识</param>
        /// <param name="accounts">用户名</param>
        /// <param name="logonPasswd">密文密码</param>
        /// <param name="ip">登录地址</param>
        /// <returns>返回网站消息，若登录成功将携带用户对象</returns>
        public Message Logon(string accounts, string logonPasswd)
        {
            UserInfo suInfo = new UserInfo(0, accounts, 0, logonPasswd);
            suInfo.LastLogonIP = GameRequest.GetUserIP();

            return Logon(suInfo, false);
        }

        /// <summary>
        /// 用户注册
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        public Message Register(UserInfo user, string parentAccount)
        {
            return accountsData.Register(user, parentAccount);
        }

        /// <summary>
        /// 判断用户名是否存在
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        public Message IsAccountsExist(string accounts)
        {
            return accountsData.IsAccountsExist(accounts);
        }

        /// <summary>
        /// 判断昵称是否存在
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        public bool IsNickNameExist ( string nickName )
        {
            return accountsData.IsNickNameExist( nickName );
        }

        #endregion

        #region 获取用户信息

        /// <summary>
        /// 根据用户昵称获取用户ID
        /// </summary>
        /// <param name="nickName"></param>
        /// <returns></returns>
        public int GetUserIDByNickName(string nickName)
        {
            return accountsData.GetUserIDByNickName(nickName);
        }

        /// <summary>
        /// 获取基本用户信息
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public UserInfo GetUserBaseInfoByUserID(int userID)
        {
            return accountsData.GetUserBaseInfoByUserID(userID);
        }

        /// <summary>
        /// 获取指定用户联系信息
        /// </summary>
        /// <param name="user">用户</param>
        /// <returns></returns> 		
        public IndividualDatum GetUserContactInfoByUserID(int userID)
        {
            return accountsData.GetUserContactInfoByUserID(userID);
        }

        /// <summary>
        /// 获取用户全局信息
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="gameID"></param>
        /// <param name="Accounts"></param>
        /// <returns></returns>
        public Message GetUserGlobalInfo(int userID, int gameID, String Accounts)
        {
            return accountsData.GetUserGlobalInfo(userID, gameID, Accounts);
        }

        /// <summary>
        /// 获取密保卡序列号
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns></returns>
        public string GetPasswordCardByUserID( int userId )
        {
            return accountsData.GetPasswordCardByUserID( userId );
        }

        #endregion

        #region	 密码管理

        /// <summary>
        /// 重置登录密码
        /// </summary>
        /// <param name="sInfo">密保信息</param>       
        /// <returns></returns>
        public Message ResetLogonPasswd(AccountsProtect sInfo)
        {
            return accountsData.ResetLogonPasswd(sInfo);
        }

        /// <summary>
        /// 重置银行密码
        /// </summary>
        /// <param name="sInfo">密保信息</param>       
        /// <returns></returns>
        public Message ResetInsurePasswd(AccountsProtect sInfo)
        {
            return accountsData.ResetInsurePasswd(sInfo);
        }

        /// <summary>
        /// 修改登录密码
        /// </summary>
        /// <param name="userID">玩家标识</param>
        /// <param name="srcPassword">旧密码</param>
        /// <param name="dstPassword">新密码</param>
        /// <param name="ip">连接地址</param>
        /// <returns></returns>
        public Message ModifyLogonPasswd(int userID, string srcPassword, string dstPassword, string ip)
        {
            return accountsData.ModifyLogonPasswd(userID, srcPassword, dstPassword, ip);
        }

        /// <summary>
        /// 修改银行密码
        /// </summary>
        /// <param name="userID">玩家标识</param>
        /// <param name="srcPassword">旧密码</param>
        /// <param name="dstPassword">新密码</param>
        /// <param name="ip">连接地址</param>
        /// <returns></returns>
        public Message ModifyInsurePasswd(int userID, string srcPassword, string dstPassword, string ip)
        {
            return accountsData.ModifyInsurePasswd(userID, srcPassword, dstPassword, ip);
        }

        #endregion

        #region  密码保护管理

        /// <summary>
        /// 申请帐号保护
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        public Message ApplyUserSecurity(AccountsProtect sInfo)
        {
            return accountsData.ApplyUserSecurity(sInfo);
        }

        /// <summary>
        /// 修改帐号保护
        /// </summary>
        /// <param name="oldInfo">旧密保信息</param>
        /// <param name="newInfo">新密保信息</param>
        /// <returns></returns>
        public Message ModifyUserSecurity(AccountsProtect newInfo)
        {
            return accountsData.ModifyUserSecurity(newInfo);
        }

        /// <summary>
        /// 获取密保信息 (userID)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSecurityByUserID(int userID)
        {
            return accountsData.GetUserSecurityByUserID(userID);
        }

        /// <summary>
        /// 获取密保信息 (gameID)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSecurityByGameID(int gameID)
        {
            return accountsData.GetUserSecurityByGameID(gameID);
        }

        /// <summary>
        /// 获取密保信息 (Accounts)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSecurityByAccounts(string accounts)
        {
            return accountsData.GetUserSecurityByAccounts(accounts);
        }

        /// <summary>
        /// 密保确认
        /// </summary>
        /// <param name="info"></param>
        /// <returns></returns>
        public Message ConfirmUserSecurity(AccountsProtect info)
        {
            return accountsData.ConfirmUserSecurity(info);
        }

        #endregion

        #region 安全管理

        #region 固定机器

        /// <summary>
        /// 申请机器绑定
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        public Message ApplyUserMoorMachine(AccountsProtect sInfo)
        {
            return accountsData.ApplyUserMoorMachine(sInfo);
        }

        /// <summary>
        /// 解除机器绑定
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        public Message RescindUserMoorMachine(AccountsProtect sInfo)
        {
            return accountsData.RescindUserMoorMachine(sInfo);
        }

        #endregion 固定机器结束

        #endregion

        #region 资料管理

        /// <summary>
        /// 更新个人资料
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        public Message ModifyUserIndividual(IndividualDatum user)
        {
            return accountsData.ModifyUserIndividual(user);
        }

        /// <summary>
        /// 更新用户头像
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="faceID"></param>
        /// <returns></returns>
        public Message ModifyUserFace(int userID, int faceID)
        {
            return accountsData.ModifyUserFace(userID, faceID);
        }

        /// <summary>
        /// 更新用户昵称
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="faceID"></param>
        /// <returns></returns>
        public Message ModifyUserNickname(int userID, string nickName, string ip)
        {
            return accountsData.ModifyUserNickname( userID , nickName , ip );
        }

        #endregion

        #region 魅力兑换

        public Message UserConvertPresent(int userID, int present, int rate, string ip)
        {
            return accountsData.UserConvertPresent(userID, present, rate, ip);
        }

        /// <summary>
        /// 根据用户魅力排名(前10名)
        /// </summary>
        /// <returns></returns>
        public IList<UserInfo> GetUserInfoOrderByLoves()
        {
            return accountsData.GetUserInfoOrderByLoves();
        }

        #endregion

        #region 奖牌兑换 

        public Message UserConvertMedal( int userID , int medals , int rate , string ip )
        {
            return accountsData.UserConvertMedal( userID , medals , rate , ip );
        }

        #endregion

        #region 密保卡

        /// <summary>
        /// 检测密保卡序列号是否存在
        /// </summary>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        public bool PasswordIDIsEnable( string serialNumber )
        {
            return accountsData.PasswordIDIsEnable( serialNumber );
        }

        /// <summary>
        /// 检测用户是否绑定了密保卡
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        public bool userIsBindPasswordCard( int userId )
        {
            return accountsData.userIsBindPasswordCard( userId );
        }


        /// <summary>
        /// 更新用户密保卡序列号
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        public bool UpdateUserPasswordCardID( int userId , int serialNumber )
        {
            return accountsData.UpdateUserPasswordCardID( userId , serialNumber );
        }

        /// <summary>
        /// 取消密保卡绑定
        /// </summary>
        /// <param name="userId"></param>
        /// <returns></returns>
        public bool ClearUserPasswordCardID( int userId )
        {
            return accountsData.ClearUserPasswordCardID( userId );
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
            return accountsData.GetObjectBySql( sqlQuery );
        }

        #endregion
    }
}
