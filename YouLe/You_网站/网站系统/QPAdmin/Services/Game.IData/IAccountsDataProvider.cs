using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using System.Data;
using Game.Entity.Accounts;

namespace Game.IData
{
    /// <summary>
    /// 帐号库数据层接口
    /// </summary>
    public interface IAccountsDataProvider //: IProvider
    {

        #region 用户基本信息管理

        /// <summary>
        /// 分页获取玩家列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetAccountsList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获得用户名
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        string GetAccountByUserID( int userID );
        /// <summary>
        /// 获得用户经验值
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        int GetExperienceByUserID( int userID );
      
        /// <summary>
        /// 获取用户基本信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        AccountsInfo GetAccountInfoByUserID( int userID );
        /// <summary>
        /// 获取用户基本信息
        /// </summary>
        /// <param name="account">用户帐号</param>
        /// <returns></returns>
        AccountsInfo GetAccountInfoByAccount( string account );
        /// <summary>
        /// 冻结玩家
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        void DongjieAccount( string sqlQuery );
        /// <summary>
        /// 解冻玩家
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        void JieDongAccount( string sqlQuery );
        /// <summary>
        /// 设为机器人
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        void SettingAndroid( string sqlQuery );
        /// <summary>
        /// 取消机器人
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        void CancleAndroid( string sqlQuery );
        /// <summary>
        ///  更新用户基本信息
        /// </summary>
        /// <param name="account">AccountsInfo实体</param>
        void UpdateAccount( AccountsInfo account );
         /// <summary>
        /// 添加玩家信息
        /// </summary>
        /// <param name="account">AccountsInfo实体</param>
        /// <param name="datum">IndividualDatum实体</param>
        /// <returns></returns>
        Message AddAccount( AccountsInfo account, IndividualDatum datum );
        #endregion        

        #region 用户详细信息管理
        /// <summary>
        /// 获取用户详细信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        IndividualDatum GetAccountDetailByUserID( int userID );

        /// <summary>
        /// 新增详细信息
        /// </summary>
        /// <param name="accountDetail"></param>
        /// <returns></returns>
        void InsertAccountDetail(IndividualDatum accountDetail);

        /// <summary>
        ///  更新用户详细信息
        /// </summary>
        /// <param name="account">IndividualDatum实体</param>
        void UpdateAccountDetail( IndividualDatum accountDetail );
        #endregion        

        #region 用户密保信息管理
        /// <summary>
        /// 获取用户密保信息
        /// </summary>
        /// <param name="pid">密保ProtectID</param>
        /// <returns></returns>
        AccountsProtect GetAccountsProtectByPID( int pid );
        /// <summary>
        /// 获取用户密保信息
        /// </summary>
        /// <param name="uid">用户标识</param>
        /// <returns></returns>
        AccountsProtect GetAccountsProtectByUserID( int uid );
        /// <summary>
        /// 更新用户密保信息
        /// </summary>
        /// <param name="accountProtect"></param>
        void UpdateAccountsProtect( AccountsProtect accountProtect );


        /// <summary>
        /// 删除用户密保信息
        /// </summary>
        /// <param name="pid">密保ProtectID</param>
        void DeleteAccountsProtect( int pid );

        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteAccountsProtect( string sqlQuery );

        #endregion

        #region 靓号信息
        /// <summary>
        /// 随机取出10个靓号
        /// </summary>
        /// <returns></returns>
        DataSet GetReserveIdentifierList( );
        #endregion

        #region 限制字符管理

        /// <summary>
        /// 分页获取限制字符列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetConfineContentList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取限制字符
        /// </summary>
        /// <param name="strString">限制字符表主健</param>
        /// <returns></returns>
        ConfineContent GetConfineContentByString( string strString );
        /// <summary>
        /// 新增一条限制字符信息
        /// </summary>
        /// <param name="content"></param>
        void InsertConfineContent( ConfineContent content );
        /// <summary>
        ///  更新限制字符信息
        /// </summary>
        /// <param name="content"></param>
        void UpdateConfineContent( ConfineContent content );
        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="strString"></param>
        void DeleteConfineContentByString( string strString );

        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteConfineContent( string sqlQuery );
        #endregion

        #region 限制地址管理

        /// <summary>
        /// 分页获取限制地址列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetConfineAddressList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取限制地址
        /// </summary>
        /// <param name="strAddress">限制地址表主健</param>
        /// <returns></returns>
        ConfineAddress GetConfineAddressByAddress( string strAddress );
        /// <summary>
        /// 新增一条限制地址信息
        /// </summary>
        /// <param name="address"></param>
        void InsertConfineAddress( ConfineAddress address );
        /// <summary>
        ///  更新限制地址信息
        /// </summary>
        /// <param name="address"></param>
        void UpdateConfineAddress( ConfineAddress address );
        /// <summary>
        /// 删除限制地址信息
        /// </summary>
        /// <param name="strAddress"></param>
        void DeleteConfineAddressByAddress( string strAddress );
        /// <summary>
        /// 删除限制地址信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteConfineAddress( string sqlQuery );
        #endregion

        #region 限制机器码管理

        /// <summary>
        /// 分页获取限制机器码列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetConfineMachineList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取限制机器码
        /// </summary>
        /// <param name="strSerial">限制机器码表主健</param>
        /// <returns></returns>
        ConfineMachine GetConfineMachineBySerial( string strSerial );
        /// <summary>
        /// 新增一条限制机器码信息
        /// </summary>
        /// <param name="machine"></param>
        void InsertConfineMachine( ConfineMachine machine );
        /// <summary>
        ///  更新限制机器码信息
        /// </summary>
        /// <param name="machine"></param>
        void UpdateConfineMachine( ConfineMachine machine );
        /// <summary>
        /// 删除限制机器码信息
        /// </summary>
        /// <param name="strSerial"></param>
        void DeleteConfineMachineBySerial( string strSerial );
        /// <summary>
        /// 删除限制机器码信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteConfineMachine( string sqlQuery );
        #endregion

        #region 系统参数配置
        /// <summary>
        /// 获取配置列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetSystemStatusInfoList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取配置信息实体
        /// </summary>
        /// <param name="statusName"></param>
        /// <returns></returns>
        SystemStatusInfo GetSystemStatusInfo( string statusName );
        /// <summary>
        /// 更新配置信息
        /// </summary>
        /// <param name="systemStatusInfo"></param>
        void UpdateSystemStatusInfo( SystemStatusInfo systemStatusInfo );
        #endregion

        #region 公共

        /// <summary>
        /// 分页获取数据列表
        /// </summary>
        /// <param name="tableName"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string condition , string orderby );

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        int ExecuteSql( string sql );

        /// <summary>
        ///  执行sql返回DataSet
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        DataSet GetDataSetBySql( string sql );

        /// <summary>
        /// 执行SQL语句返回一个值
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        string GetScalarBySql( string sql );

        #endregion
    }
}
