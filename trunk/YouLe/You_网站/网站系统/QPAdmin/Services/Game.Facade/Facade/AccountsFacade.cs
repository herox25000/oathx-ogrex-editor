using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Game.IData;
using Game.Data.Factory;
using Game.Kernel;
using Game.Entity.Accounts;
using System.Data;

namespace Game.Facade
{
    /// <summary>
    /// 帐号库外观
    /// </summary>
    public class AccountsFacade
    {
        #region Fields

        private IAccountsDataProvider aideAccountsData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public AccountsFacade( )
        {
            aideAccountsData = ClassFactory.IAccountsDataProvider( );
        }
        #endregion

        #region 用户基本信息管理
        /// <summary>
        /// 分页获取所有玩家列表
        /// </summary>
        /// <returns></returns>
        public PagerSet GetAccountsList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideAccountsData.GetAccountsList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 冻结玩家
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DongjieAccount( string sqlQuery )
        {
            aideAccountsData.DongjieAccount( sqlQuery );
        }

        /// <summary>
        /// 解冻玩家
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void JieDongAccount( string sqlQuery )
        {
            aideAccountsData.JieDongAccount( sqlQuery );
        }
        /// <summary>
        /// 设为机器人
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        public void SettingAndroid( string sqlQuery )
        {
            aideAccountsData.SettingAndroid( sqlQuery );
        }
        /// <summary>
        /// 取消机器人
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        public void CancleAndroid( string sqlQuery )
        {
            aideAccountsData.CancleAndroid( sqlQuery );
        }
        /// <summary>
        /// 获取用户基本信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public AccountsInfo GetAccountInfoByUserID( int userID )
        {
            return aideAccountsData.GetAccountInfoByUserID( userID );
        }
        /// <summary>
        /// 获取用户名
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public string GetAccountByUserID( int userID )
        {
            return aideAccountsData.GetAccountByUserID( userID );
        }
        /// <summary>
        /// 获取用户基本信息
        /// </summary>
        /// <param name="account">用户帐号</param>
        /// <returns></returns>
        public AccountsInfo GetAccountInfoByAccount( string account )
        {
            return aideAccountsData.GetAccountInfoByAccount( account );
        }
        /// <summary>
        /// 获得用户经验值
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public int GetExperienceByUserID( int userID )
        {
            return aideAccountsData.GetExperienceByUserID( userID );
        }      
        /// <summary>
        /// 更新用户基本信息
        /// </summary>
        /// <param name="account">AccountsInfo实体</param>
        /// <returns></returns>
        public Message UpdateAccount( AccountsInfo account )
        {
            aideAccountsData.UpdateAccount( account );
            return new Message( true );
        }
        /// <summary>
        /// 添加玩家信息
        /// </summary>
        /// <param name="account">AccountsInfo实体</param>
        /// <param name="datum">IndividualDatum实体</param>
        /// <returns></returns>
        public Message AddAccount( AccountsInfo account, IndividualDatum datum )
        {
            return aideAccountsData.AddAccount( account, datum );
        }

        #endregion        

        #region 用户详细信息管理
        /// <summary>
        /// 获取用户详细信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public IndividualDatum GetAccountDetailByUserID( int userID )
        {
            return aideAccountsData.GetAccountDetailByUserID( userID );
        }

        /// <summary>
        /// 新增详细信息
        /// </summary>
        /// <param name="accountDetail"></param>
        /// <returns></returns>
        public Message InsertAccountDetail(IndividualDatum accountDetail)
        {
            aideAccountsData.InsertAccountDetail(accountDetail);
            return new Message(true);
        }

        /// <summary>
        /// 更新用户详细信息
        /// </summary>
        /// <param name="accountDetail">IndividualDatum实体</param>
        /// <returns></returns>
        public Message UpdateAccountDetail( IndividualDatum accountDetail )
        {
            aideAccountsData.UpdateAccountDetail( accountDetail );
            return new Message( true );
        }
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
        public PagerSet GetConfineContentList( int pageIndex, int pageSize, string condition, string orderby )
        {

            return aideAccountsData.GetConfineContentList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取限制字符
        /// </summary>
        /// <param name="pid">限制字符表主健</param>
        /// <returns></returns>
        public ConfineContent GetConfineContentByString( string strString )
        {
            return aideAccountsData.GetConfineContentByString( strString );
        }
        /// <summary>
        /// 新增一条限制字符信息
        /// </summary>
        /// <param name="content"></param>
        public Message InsertConfineContent( ConfineContent content )
        {
            aideAccountsData.InsertConfineContent( content );
            return new Message( true );
        }
        /// <summary>
        ///  更新限制字符信息
        /// </summary>
        /// <param name="content"></param>
        public Message UpdateConfineContent( ConfineContent content )
        {
            aideAccountsData.UpdateConfineContent( content );
            return new Message( true );
        }
        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="pid"></param>
        public void DeleteConfineContentByString( string strString )
        {
            aideAccountsData.DeleteConfineContentByString( strString );
        }

        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteConfineContent( string sqlQuery )
        {
            aideAccountsData.DeleteConfineContent( sqlQuery );
        }
        #endregion

        #region 用户密保信息管理
        /// <summary>
        /// 获取用户密保信息
        /// </summary>
        /// <param name="pid">密保ProtectID</param>
        /// <returns></returns>
        public AccountsProtect GetAccountsProtectByPID( int pid )
        {
            return aideAccountsData.GetAccountsProtectByPID( pid );
        }
        /// <summary>
        /// 获取用户密保信息
        /// </summary>
        /// <param name="uid">用户标识</param>
        /// <returns></returns>
        public AccountsProtect GetAccountsProtectByUserID( int uid )
        {
            return aideAccountsData.GetAccountsProtectByUserID( uid );
        }
        /// <summary>
        /// 更新用户密保信息
        /// </summary>
        /// <param name="accountProtect"></param>
        public Message UpdateAccountsProtect( AccountsProtect accountProtect )
        {
            aideAccountsData.UpdateAccountsProtect( accountProtect );
            return new Message( true );
        }


        /// <summary>
        /// 删除用户密保信息
        /// </summary>
        /// <param name="pid">密保ProtectID</param>
        public void DeleteAccountsProtect( int pid )
        {
            aideAccountsData.DeleteAccountsProtect( pid );
        }

        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteAccountsProtect( string sqlQuery )
        {
            aideAccountsData.DeleteAccountsProtect( sqlQuery );
        }

        #endregion

        #region 靓号信息
        /// <summary>
        /// 随机取出10个靓号
        /// </summary>
        /// <returns></returns>
        public DataSet GetReserveIdentifierList( )
        {
            return aideAccountsData.GetReserveIdentifierList( );

        }
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
        public PagerSet GetConfineAddressList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideAccountsData.GetConfineAddressList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取限制地址
        /// </summary>
        /// <param name="strString">限制地址表主健</param>
        /// <returns></returns>
        public ConfineAddress GetConfineAddressByAddress( string strAddress )
        {
            return aideAccountsData.GetConfineAddressByAddress( strAddress );
        }
        /// <summary>
        /// 新增一条限制地址信息
        /// </summary>
        /// <param name="address"></param>
        public Message InsertConfineAddress( ConfineAddress address )
        {
            aideAccountsData.InsertConfineAddress( address );
            return new Message( true );
        }
        /// <summary>
        ///  更新限制地址信息
        /// </summary>
        /// <param name="address"></param>
        public Message UpdateConfineAddress( ConfineAddress address )
        {
            aideAccountsData.UpdateConfineAddress( address );
            return new Message( true );
        }
        /// <summary>
        /// 删除限制地址信息
        /// </summary>
        /// <param name="strAddress"></param>
        public void DeleteConfineAddressByAddress( string strAddress )
        {
            aideAccountsData.DeleteConfineAddressByAddress( strAddress );
        }

        /// <summary>
        /// 删除限制地址信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteConfineAddress( string sqlQuery )
        {
            aideAccountsData.DeleteConfineAddress( sqlQuery );
        }
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
        public PagerSet GetConfineMachineList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideAccountsData.GetConfineMachineList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取限制机器码
        /// </summary>
        /// <param name="strSerial">限制机器码表主健</param>
        /// <returns></returns>
        public ConfineMachine GetConfineMachineBySerial( string strSerial )
        {
            return aideAccountsData.GetConfineMachineBySerial( strSerial );
        }
        /// <summary>
        /// 新增一条限制机器码信息
        /// </summary>
        /// <param name="machine"></param>
        public Message InsertConfineMachine( ConfineMachine machine )
        {
            aideAccountsData.InsertConfineMachine( machine );
            return new Message( true );
        }
        /// <summary>
        ///  更新限制机器码信息
        /// </summary>
        /// <param name="machine"></param>
        public Message UpdateConfineMachine( ConfineMachine machine )
        {
            aideAccountsData.UpdateConfineMachine( machine );
            return new Message( true );
        }
        /// <summary>
        /// 删除限制机器码信息
        /// </summary>
        /// <param name="strSerial"></param>
        public void DeleteConfineMachineBySerial( string strSerial )
        {
            aideAccountsData.DeleteConfineMachineBySerial( strSerial );
        }

        /// <summary>
        /// 删除限制机器码信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteConfineMachine( string sqlQuery )
        {
            aideAccountsData.DeleteConfineMachine( sqlQuery );
        }
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
        public PagerSet GetSystemStatusInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideAccountsData.GetSystemStatusInfoList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取配置信息实体
        /// </summary>
        /// <param name="statusName"></param>
        /// <returns></returns>
        public SystemStatusInfo GetSystemStatusInfo( string statusName )
        {
            return aideAccountsData.GetSystemStatusInfo( statusName );
        }
        /// <summary>
        /// 更新配置信息
        /// </summary>
        /// <param name="systemStatusInfo"></param>
        public Message UpdateSystemStatusInfo( SystemStatusInfo systemStatusInfo )
        {
            aideAccountsData.UpdateSystemStatusInfo( systemStatusInfo );
            return new Message( true );
        }
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
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string condition , string orderby )
        {
            return aideAccountsData.GetList( tableName , pageIndex , pageSize , condition , orderby );
        }

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        public int ExecuteSql( string sql )
        {
            return aideAccountsData.ExecuteSql( sql );
        }

        /// <summary>
        ///  执行sql返回DataSet
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        public DataSet GetDataSetBySql( string sql )
        {
            return aideAccountsData.GetDataSetBySql( sql );
        }

        /// <summary>
        /// 执行SQL语句返回一个值
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        public string GetScalarBySql( string sql )
        {
            return aideAccountsData.GetScalarBySql( sql );
        }

        #endregion
    }
}
