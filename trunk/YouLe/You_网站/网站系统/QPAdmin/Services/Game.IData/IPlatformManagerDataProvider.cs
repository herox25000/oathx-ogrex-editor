using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Game.Kernel;
using Game.Entity.PlatformManager;
using System.Data;

namespace Game.IData
{
    /// <summary>
    /// 后台数据层接口
    /// </summary>
    public interface IPlatformManagerDataProvider //: IProvider
    {
        #region 管理员管理
        /// <summary>
        /// 管理员登录
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        Message UserLogon( Base_Users user );

        /// <summary>
        /// 添加管理员用户
        /// </summary>
        /// <param name="user"></param>
        void Register( Base_Users user );

        /// <summary>
        /// 删除用户
        /// </summary>
        /// <param name="userIDList"></param>
        void DeleteUser( string userIDList );

        /// <summary>
        /// 修改密码
        /// </summary>
        /// <param name="user"></param>
        /// <param name="newLogonPass"></param>
        void ModifyUserLogonPass( Base_Users user, string newLogonPass );

        /// <summary>
        /// 封停帐号
        /// </summary>
        /// <param name="userIDList"></param>
        /// <param name="nullity"></param>
        void ModifyUserNullity( string userIDList, bool nullity );

        /// <summary>
        /// 修改资料
        /// </summary>
        /// <param name="userExt"></param>
        void ModifyUserInfo( Base_Users user );

        /// <summary>
        /// 获取用户对象 by userName
        /// </summary>
        /// <param name="userName"></param>
        /// <returns></returns>
        Base_Users GetUserByAccounts( string userName );       

        /// <summary>
        /// 获取用户对象 by userID
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        Base_Users GetUserByUserID( int userID );

        /// <summary>
        /// 获取用户列表 by roleID
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        DataSet GetUserListByRoleID( int roleID );

        /// <summary>
        /// 获取用户列表
        /// </summary>
        /// <returns></returns>
        DataSet GetUserList( );

        /// <summary>
        /// 获取用户列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetUserList( int pageIndex, int pageSize, string condition, string orderby );
        #endregion

        #region 角色管理
        /// <summary>
        /// 获取角色列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetRoleList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取角色实体
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        Base_Roles GetRoleInfo( int roleID );

        /// <summary>
        /// 获得角色名称
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        string GetRolenameByRoleID( int roleID );

        /// <summary>
        /// 新增角色
        /// </summary>
        /// <param name="role"></param>
        void InsertRole( Base_Roles role );

        /// <summary>
        /// 更新角色
        /// </summary>
        /// <param name="role"></param>
        void UpdateRole( Base_Roles role );

        /// <summary>
        /// 删除角色
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteRole( string sqlQuery );
        #endregion

        #region 菜单管理

        /// <summary>
        /// 获取菜单 by userID
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        DataSet GetMenuByUserID( int userID );

        /// <summary>
        /// 获取权限 by userID
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        DataSet GetPermissionByUserID( int userID );      

        /// <summary>
        /// 获取父模块
        /// </summary>
        /// <returns></returns>
        DataSet GetModuleParentList( );

        /// <summary>
        /// 获取子模块
        /// </summary>
        /// <param name="moduleID"></param>
        /// <returns></returns>
        DataSet GetModuleListByModuleID( int moduleID );

        /// <summary>
        /// 获取模块权限列表
        /// </summary>
        /// <param name="moduleID"></param>
        /// <returns></returns>
        DataSet GetModulePermissionList( int moduleID );

        /// <summary>
        /// 获取角色权限列表
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        DataSet GetRolePermissionList( int roleID );

        /// <summary>
        /// 新增角色权限
        /// </summary>
        /// <param name="rolePermission"></param>
        void InsertRolePermission( Base_RolePermission rolePermission );

        /// <summary>
        /// 删除角色权限
        /// </summary>
        /// <param name="roleID"></param>
        void DeleteRolePermission( int roleID );

        #endregion
        #region 安全日志列表
        /// <summary>
        /// 获取安全日志列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetSystemSecurityList( int pageIndex, int pageSize, string condition, string orderby );
        #endregion
        #region 系统配置
        /// <summary>
        /// 获取系统配置信息
        /// </summary>
        /// <param name="siteID"></param>
        /// <returns></returns>
        QPAdminSiteInfo GetQPAdminSiteInfo( int siteID );
        /// <summary>
        /// 更新配置
        /// </summary>
        /// <param name="site"></param>
        void UpdateQPAdminSiteInfo( QPAdminSiteInfo site );
        #endregion
    }
   
}
