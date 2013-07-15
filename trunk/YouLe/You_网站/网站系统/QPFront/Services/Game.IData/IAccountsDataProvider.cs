using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Accounts;
using System.Data;

namespace Game.IData
{
    /// <summary>
    ///  用户库数据层接口
    /// </summary>
    public interface IAccountsDataProvider//:IProvider
    {
        #region 用户登录、注册

        /// <summary>
        /// 用户登录
        /// </summary>
        /// <param name="names">用户信息</param>
        /// <returns></returns>
        Message Login(UserInfo user);

        /// <summary>
        /// 用户注册
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        Message Register(UserInfo user, string parentAccount);

        /// <summary>
        /// 判断用户名是否存在
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        Message IsAccountsExist(string accounts);

        /// <summary>
        /// 判断昵称是否存在
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        bool IsNickNameExist ( string nickName );

        #endregion

        #region 获取用户信息

        /// <summary>
        /// 根据用户昵称获取用户ID
        /// </summary>
        /// <param name="nickName"></param>
        /// <returns></returns>
        int GetUserIDByNickName(string nickName);

        /// <summary>
        /// 获取基本用户信息
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        UserInfo GetUserBaseInfoByUserID(int userID);

        /// <summary>
        /// 获取指定用户联系信息
        /// </summary>
        /// <param name="user">用户</param>
        /// <returns></returns> 		
        IndividualDatum GetUserContactInfoByUserID(int userID);

        /// <summary>
        /// 获取用户全局信息
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="gameID"></param>
        /// <param name="Accounts"></param>
        /// <returns></returns>
        Message GetUserGlobalInfo(int userID, int gameID, String Accounts);

        
        /// <summary>
        /// 获取密保卡序列号
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns></returns>
        string GetPasswordCardByUserID( int userId );

        #endregion

        #region	 密码管理

        /// <summary>
        /// 重置登录密码
        /// </summary>
        /// <param name="sInfo">密保信息</param>       
        /// <returns></returns>
        Message ResetLogonPasswd(AccountsProtect sInfo);

        /// <summary>
        /// 重置银行密码
        /// </summary>
        /// <param name="sInfo">密保信息</param>       
        /// <returns></returns>
        Message ResetInsurePasswd(AccountsProtect sInfo);

        /// <summary>
        /// 修改登录密码
        /// </summary>
        /// <param name="userID">玩家标识</param>
        /// <param name="srcPassword">旧密码</param>
        /// <param name="dstPassword">新密码</param>
        /// <param name="ip">连接地址</param>
        /// <returns></returns>
        Message ModifyLogonPasswd(int userID, string srcPassword, string dstPassword, string ip);

        /// <summary>
        /// 修改银行密码
        /// </summary>
        /// <param name="userID">玩家标识</param>
        /// <param name="srcPassword">旧密码</param>
        /// <param name="dstPassword">新密码</param>
        /// <param name="ip">连接地址</param>
        /// <returns></returns>
        Message ModifyInsurePasswd(int userID, string srcPassword, string dstPassword, string ip);

        #endregion

        #region  密码保护管理

        /// <summary>
        /// 申请帐号保护
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        Message ApplyUserSecurity(AccountsProtect sInfo);

        /// <summary>
        /// 修改帐号保护
        /// </summary>
        /// <param name="oldInfo">旧密保信息</param>
        /// <param name="newInfo">新密保信息</param>
        /// <returns></returns>
        Message ModifyUserSecurity(AccountsProtect newInfo);

        /// <summary>
        /// 获取密保信息 (userID)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        Message GetUserSecurityByUserID(int userID);

        /// <summary>
        /// 获取密保信息 (gameID)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        Message GetUserSecurityByGameID(int gameID);

        /// <summary>
        /// 获取密保信息 (Accounts)
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        Message GetUserSecurityByAccounts(string accounts);

        /// <summary>
        /// 密保确认
        /// </summary>
        /// <param name="info"></param>
        /// <returns></returns>
        Message ConfirmUserSecurity(AccountsProtect info);

        #endregion

        #region 安全管理

        #region 固定机器

        /// <summary>
        /// 申请机器绑定
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        Message ApplyUserMoorMachine(AccountsProtect sInfo);

        /// <summary>
        /// 解除机器绑定
        /// </summary>
        /// <param name="sInfo">密保信息</param>
        /// <returns></returns>
        Message RescindUserMoorMachine(AccountsProtect sInfo);

        #endregion 固定机器结束

        #endregion

        #region 资料管理

        /// <summary>
        /// 更新个人资料
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        Message ModifyUserIndividual(IndividualDatum user);

        /// <summary>
        /// 更新用户头像
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="faceID"></param>
        /// <returns></returns>
        Message ModifyUserFace(int userID, int faceID);

        /// <summary>
        /// 更新用户昵称
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="faceID"></param>
        /// <returns></returns>
        Message ModifyUserNickname(int userID, string nickName, string ip);

        #endregion

        #region 魅力兑换

        Message UserConvertPresent(int userID, int medals, int rate, string ip);

        /// <summary>
        /// 根据用户魅力排名(前10名)
        /// </summary>
        /// <returns></returns>
        IList<UserInfo> GetUserInfoOrderByLoves();

        #endregion

        #region 奖牌兑换

        Message UserConvertMedal( int userID , int medals , int rate , string ip );

        #endregion
        #region 密保卡信息

        /// <summary>
        /// 检测密保卡序列号是否存在
        /// </summary>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        bool PasswordIDIsEnable( string serialNumber );

        /// <summary>
        /// 检测用户是否绑定了密保卡
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        bool userIsBindPasswordCard( int userId );

        /// <summary>
        /// 更新用户密保卡序列号
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="serialNumber">密保卡序列号</param>
        /// <returns></returns>
        bool UpdateUserPasswordCardID( int userId , int serialNumber );

        /// <summary>
        /// 取消密保卡绑定
        /// </summary>
        /// <param name="userId"></param>
        /// <returns></returns>
        bool ClearUserPasswordCardID( int userId );

        #endregion

        #region 公共

         /// <summary>
        /// 根据SQL语句查询一个值
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        object GetObjectBySql( string sqlQuery );

        #endregion
    }
}
