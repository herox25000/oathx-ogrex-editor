using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Game.Kernel;
using Game.IData;
using Game.Entity.PlatformManager;
using System.Data;
using System.Data.Common;

namespace Game.Data
{
    /// <summary>
    /// 后台数据层
    /// </summary>
    public class PlatformManagerDataProvider : BaseDataProvider, IPlatformManagerDataProvider
    {
        #region Fields
        private ITableProvider aideUserProvider;
        private ITableProvider aideRoleProvider;
        private ITableProvider aideRolePermissionProvider;
        private ITableProvider aideQPAdminSiteInfoProvider;
        #endregion

        #region 构造方法
        /// <summary>
        /// 构造函数
        /// </summary>
        public PlatformManagerDataProvider( string connString )
            : base( connString )
        {
            aideUserProvider = GetTableProvider( Base_Users.Tablename );
            aideRoleProvider = GetTableProvider( Base_Roles.Tablename );
            aideRolePermissionProvider = GetTableProvider( Base_RolePermission.Tablename );
            aideQPAdminSiteInfoProvider = GetTableProvider( QPAdminSiteInfo.Tablename );
        }
        #endregion

        #region 管理员管理
        /// <summary>
        /// 管理员登录
        /// </summary>
        /// <param name="user"></param>
        /// <returns></returns>
        public Message UserLogon( Base_Users user )
        {
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "strUserName", user.Username ) );
            prams.Add( Database.MakeInParam( "strPassword", user.Password ) );
            prams.Add( Database.MakeInParam( "strClientIP", user.LastLoginIP ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe", typeof( string ), 127 ) );

            Message msg = MessageHelper.GetMessageForObject<Base_Users>( Database, "NET_PM_UserLogon", prams );
            return msg;
        }

        /// <summary>
        /// 添加管理员用户
        /// </summary>
        /// <param name="user"></param>
        public void Register( Base_Users user )
        {
            DataRow dr = aideUserProvider.NewRow( );

            dr[Base_Users._Username] = user.Username;
            dr[Base_Users._Password] = user.Password;
            dr[Base_Users._RoleID] = user.RoleID;
            dr[Base_Users._Nullity] = user.Nullity;
            dr[Base_Users._PreLoginIP] = user.PreLoginIP;
            dr[Base_Users._PreLogintime] = user.PreLogintime;
            dr[Base_Users._LastLoginIP] = user.LastLoginIP;
            dr[Base_Users._LastLogintime] = user.LastLogintime;
            dr[Base_Users._LoginTimes] = user.LoginTimes;
            dr[Base_Users._IsBand] = user.IsBand;
            dr[Base_Users._BandIP] = user.BandIP;

            aideUserProvider.Insert( dr );
        }

        /// <summary>
        /// 删除用户
        /// </summary>
        /// <param name="userIDList"></param>
        public void DeleteUser( string userIDList )
        {
            aideUserProvider.Delete( string.Format( "WHERE UserID in ({0})", userIDList ) );
        }

        /// <summary>
        /// 修改密码
        /// </summary>
        /// <param name="user"></param>
        /// <param name="newLogonPass"></param>
        public void ModifyUserLogonPass( Base_Users user, string newLogonPass )
        {
            string sqlQuery = "UPDATE Base_Users SET Password = @Password WHERE UserID= @UserID";

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "UserID", user.UserID ) );
            prams.Add( Database.MakeInParam( "Password", newLogonPass ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery, prams.ToArray( ) );
        }

        /// <summary>
        /// 封停帐号
        /// </summary>
        /// <param name="userIDList"></param>
        /// <param name="nullity"></param>
        public void ModifyUserNullity( string userIDList, bool nullity )
        {
            string sqlQuery = string.Format( "UPDATE Base_Users SET Nullity = @Nullity WHERE UserID IN ({0})", userIDList );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "Nullity", nullity ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery, prams.ToArray( ) );
        }

        /// <summary>
        /// 修改资料
        /// </summary>
        /// <param name="userExt"></param>
        public void ModifyUserInfo( Base_Users user )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE Base_Users SET " )
                    .Append( "Password=@Password, " )
                    .Append( "RoleID=@RoleID, " )
                    .Append( "Nullity=@Nullity, " )
                    .Append( "IsBand=@IsBand, " )
                    .Append( "BandIP=@BandIP " )
                    .Append( "WHERE UserID=@UserID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "Password", user.Password ) );
            prams.Add( Database.MakeInParam( "RoleID", user.RoleID ) );
            prams.Add( Database.MakeInParam( "Nullity", user.Nullity ) );
            prams.Add( Database.MakeInParam( "IsBand", user.IsBand ) );
            prams.Add( Database.MakeInParam( "BandIP", user.BandIP ) );
            prams.Add( Database.MakeInParam( "UserID", user.UserID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 获取用户对象 by userName
        /// </summary>
        /// <param name="accounts"></param>
        /// <returns></returns>
        public Base_Users GetUserByAccounts( string userName )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserName= N'{0}'", userName );
            Base_Users user = aideUserProvider.GetObject<Base_Users>( sqlQuery );
            return user;
        }

        /// <summary>
        /// 获取用户对象 by userID
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Base_Users GetUserByUserID( int userID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID={0}", userID );
            Base_Users user = aideUserProvider.GetObject<Base_Users>( sqlQuery );
            return user;
        }

        /// <summary>
        /// 获取用户列表 by roleID
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        public DataSet GetUserListByRoleID( int roleID )
        {
            return aideUserProvider.Get( string.Format( "(NOLOCK) WHERE RoleID={0}", roleID ) );
        }

        /// <summary>
        /// 获取用户列表
        /// </summary>
        /// <returns></returns>
        public DataSet GetUserList( )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.AppendFormat( @"SELECT UserID, RoleID" )
            .AppendFormat( @"      ,Rolename=" )
            .AppendFormat( @"         CASE UserID" )
            .AppendFormat( @"             WHEN 1 THEN N'超级管理员'" )
            .AppendFormat( @"             ELSE (SELECT RoleName FROM Base_Roles(NOLOCK) WHERE RoleID=u.RoleID)" )
            .AppendFormat( @"         END" )
            .AppendFormat( @"      ,UserName,PreLogintime,PreLoginIP,LastLogintime,LastLoginIP" )
            .AppendFormat( @"      ,LoginTimes,IsBand,BandIP" )
            .AppendFormat( @"  FROM Base_Users(NOLOCK) AS u" )
            .Append( @" WHERE UserID>1" );

            return Database.ExecuteDataset( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 获取用户列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetUserList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( Base_Users.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
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
        public PagerSet GetRoleList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( Base_Roles.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取角色实体
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        public Base_Roles GetRoleInfo( int roleID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE RoleID= {0}", roleID );
            Base_Roles role = aideRoleProvider.GetObject<Base_Roles>( sqlQuery );
            return role;
        }

        /// <summary>
        /// 获得角色名称
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        public string GetRolenameByRoleID( int roleID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE RoleID={0}", roleID );
            Base_Roles userRolesInfo = aideRoleProvider.GetObject<Base_Roles>( sqlQuery );
            if ( userRolesInfo == null )
                return "";
            return userRolesInfo.RoleName;
        }

        /// <summary>
        /// 新增角色
        /// </summary>
        /// <param name="role"></param>
        public void InsertRole( Base_Roles role )
        {
            DataRow dr = aideRoleProvider.NewRow( );

            dr[Base_Roles._RoleID] = role.RoleID;
            dr[Base_Roles._RoleName] = role.RoleName;
            dr[Base_Roles._Description] = role.Description;

            aideRoleProvider.Insert( dr );
        }

        /// <summary>
        /// 更新角色
        /// </summary>
        /// <param name="role"></param>
        public void UpdateRole( Base_Roles role )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE Base_Roles SET " )
                    .Append( "RoleName=@RoleName ," )
                    .Append( "Description=@Description " )

                    .Append( "WHERE RoleID= @RoleID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "RoleName", role.RoleName ) );
            prams.Add( Database.MakeInParam( "Description", role.Description ) );
            prams.Add( Database.MakeInParam( "RoleID", role.RoleID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除角色
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteRole( string sqlQuery )
        {
            aideRoleProvider.Delete( sqlQuery );
        }
        #endregion

        #region 菜单列表

        /// <summary>
        /// 获取菜单 by userID
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public DataSet GetMenuByUserID( int userID )
        {
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "dwUserID", userID ) );

            DataSet ds;
            Database.RunProc( "NET_PM_GetMenuByUserID", prams, out ds );
            return ds;
        }

        /// <summary>
        /// 获取权限 by userID
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public DataSet GetPermissionByUserID( int userID )
        {
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "dwUserID", userID ) );

            DataSet ds;
            Database.RunProc( "NET_PM_GetPermissionByUserID", prams, out ds );
            return ds;
        }

        /// <summary>
        /// 获取父模块
        /// </summary>
        /// <returns></returns>
        public DataSet GetModuleParentList( )
        {
            string sqlQuery = "SELECT * FROM Base_Module WHERE ParentID=0 ORDER BY OrderNo";

            return Database.ExecuteDataset( CommandType.Text, sqlQuery );
        }

        /// <summary>
        /// 获取子模块
        /// </summary>
        /// <param name="moduleID"></param>
        /// <returns></returns>
        public DataSet GetModuleListByModuleID( int moduleID )
        {
            string sqlQuery = string.Format( "SELECT * FROM Base_Module WHERE ParentID={0} ORDER BY OrderNo", moduleID );

            return Database.ExecuteDataset( CommandType.Text, sqlQuery );
        }

        /// <summary>
        /// 获取模块权限列表
        /// </summary>
        /// <param name="moduleID"></param>
        /// <returns></returns>
        public DataSet GetModulePermissionList( int moduleID )
        {
            string sqlQuery = string.Format( "SELECT * FROM Base_ModulePermission WHERE ModuleID={0}", moduleID );

            return Database.ExecuteDataset( CommandType.Text, sqlQuery );
        }

        /// <summary>
        /// 获取角色权限列表
        /// </summary>
        /// <param name="roleID"></param>
        /// <returns></returns>
        public DataSet GetRolePermissionList( int roleID )
        {
            string sqlQuery = string.Format( "SELECT * FROM Base_RolePermission WHERE RoleID={0}", roleID );

            return Database.ExecuteDataset( CommandType.Text, sqlQuery );
        }

        /// <summary>
        /// 新增角色权限
        /// </summary>
        /// <param name="rolePermission"></param>
        public void InsertRolePermission( Base_RolePermission rolePermission )
        {
            DataRow dr = aideRolePermissionProvider.NewRow( );

            dr[Base_RolePermission._RoleID] = rolePermission.RoleID;
            dr[Base_RolePermission._ModuleID] = rolePermission.ModuleID;
            dr[Base_RolePermission._ManagerPermission] = rolePermission.ManagerPermission;
            dr[Base_RolePermission._OperationPermission] = rolePermission.OperationPermission;
            dr[Base_RolePermission._StateFlag] = rolePermission.StateFlag;

            aideRolePermissionProvider.Insert( dr );
        }

        /// <summary>
        /// 删除角色权限
        /// </summary>
        /// <param name="roleID"></param>
        public void DeleteRolePermission( int roleID )
        {
            aideRolePermissionProvider.Delete( string.Format( "WHERE RoleID = ({0})", roleID ) );
        }

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
        public PagerSet GetSystemSecurityList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( SystemSecurity.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        #endregion

        #region 系统配置
        /// <summary>
        /// 获取系统配置信息
        /// </summary>
        /// <param name="siteID"></param>
        /// <returns></returns>
        public QPAdminSiteInfo GetQPAdminSiteInfo( int siteID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE SiteID= {0}", siteID );
            QPAdminSiteInfo site = aideQPAdminSiteInfoProvider.GetObject<QPAdminSiteInfo>( sqlQuery );
            return site;
        }
        /// <summary>
        /// 更新配置
        /// </summary>
        /// <param name="site"></param>
        public void UpdateQPAdminSiteInfo( QPAdminSiteInfo site )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE QPAdminSiteInfo SET " )
                    .Append( "SiteName=@SiteName ," )
                    .Append( "PageSize=@PageSize ," )
                    .Append( "CopyRight=@CopyRight " )
                    .Append( "WHERE SiteID= @SiteID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "SiteName", site.SiteName ) );
            prams.Add( Database.MakeInParam( "PageSize", site.PageSize ) );
            prams.Add( Database.MakeInParam( "CopyRight", site.CopyRight ) );
            prams.Add( Database.MakeInParam( "SiteID", site.SiteID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        #endregion
    }
}
