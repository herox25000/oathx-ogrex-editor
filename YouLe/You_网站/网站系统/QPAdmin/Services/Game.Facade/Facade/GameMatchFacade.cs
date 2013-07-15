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
using System.Data.Common;
using Game.Entity.GameMatch;

namespace Game.Facade
{
    /// <summary>
    /// 网站外观
    /// </summary>
    public class GameMatchFacade
    {
        #region Fields

        private IGameMatchProvider gameMatchData;

        #endregion

        #region 公共

        /// <summary>
        /// 构造函数
        /// </summary>
        public GameMatchFacade( )
        {
            gameMatchData = ClassFactory.GetIGameMatchProvider( );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        /// <param name="fields">查询字段</param>
        /// <param name="fieldAlias"></param>
        /// <returns></returns>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery , string[] fields , string[] fieldAlias )
        {
            return gameMatchData.GetList( tableName , pageIndex , pageSize , pkey , whereQuery , fields , fieldAlias );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        /// <param name="fields">查询字段</param>
        /// <returns></returns>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery , string[] fields )
        {
            return gameMatchData.GetList( tableName , pageIndex , pageSize , pkey , whereQuery , fields );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery )
        {
            return gameMatchData.GetList( tableName , pageIndex , pageSize , pkey , whereQuery );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey )
        {
            return gameMatchData.GetList( tableName , pageIndex , pageSize , pkey );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize )
        {
            return gameMatchData.GetList( tableName , pageIndex , pageSize );
        }

        /// <summary>
        /// 获取全部数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">排序或分组</param>
        /// <param name="pageSize">页大小</param>
        public PagerSet GetAllList( string tableName , string pkey , string whereQuery )
        {
            return gameMatchData.GetAllList( tableName , pkey , whereQuery );
        }

        /// <summary>
        /// 获取全部数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">排序或分组</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pageSize">查询的数量</param>
        public PagerSet GetNumberList( string tableName , string whereQuery , string pkey , int number )
        {
            return gameMatchData.GetNumberList( tableName , whereQuery , pkey , number );
        }

        /// <summary>
        /// 根据sql语句获取数据
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        public DataSet GetDataSetByWhere( string sqlQuery )
        {
            return gameMatchData.GetDataSetByWhere( sqlQuery );
        }

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public T GetEntity<T>( string commandText , List<DbParameter> parms )
        {
            return gameMatchData.GetEntity<T>( commandText , parms );
        }

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public T GetEntity<T>( string commandText )
        {
            return gameMatchData.GetEntity<T>( commandText );
        }

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        public int ExecuteSql( string sql )
        {
            return gameMatchData.ExecuteSql( sql );
        }

        #endregion

        #region 比赛相关

        /// <summary>
        /// 新增比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void InsertMatchInfo( MatchInfo gameMatch )
        {
            gameMatchData.InsertMatchInfo( gameMatch );
        }

        /// <summary>
        /// 更新比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void UpdateMatchInfo( MatchInfo gameMatch )
        {
            gameMatchData.UpdateMatchInfo( gameMatch );
        }

        #endregion
    }
}
