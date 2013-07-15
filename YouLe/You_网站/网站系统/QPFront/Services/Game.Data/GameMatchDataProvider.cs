using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Entity;
using Game.Kernel;

using Game.IData;
using System.Data;
using System.Data.Common;

namespace Game.Data
{
    public class GameMatchDataProvider : BaseDataProvider,IGameMatchProvider
    {
        #region 构造方法

        public GameMatchDataProvider( string connString )
            : base(connString)
        {

        }

        #endregion

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
            PagerParameters pager = new PagerParameters( tableName , pkey , whereQuery , pageIndex , pageSize , fields , fieldAlias );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
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
            PagerParameters pager = new PagerParameters( tableName , pkey , whereQuery , pageIndex , pageSize , fields );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize, string pkey ,string whereQuery )
        {
            PagerParameters pager = new PagerParameters( tableName , pkey , whereQuery , pageIndex , pageSize );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        public PagerSet GetList( string tableName ,int pageIndex , int pageSize, string pkey )
        {
            PagerParameters pager = new PagerParameters( tableName , pkey  , pageIndex , pageSize );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize )
        {
            PagerParameters pager = new PagerParameters( tableName , "" , pageIndex , pageSize );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取全部数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">排序或分组</param>
        /// <param name="pageSize">页大小</param>
        public PagerSet GetAllList( string tableName , string pkey , string whereQuery )
        {
            PagerParameters pager = new PagerParameters( tableName , pkey , whereQuery , 1 , Int32.MaxValue );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
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
            PagerParameters pager = new PagerParameters( tableName , pkey , whereQuery , 1 , number );
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 根据sql语句获取数据
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        public DataSet GetDataSetByWhere( string sqlQuery )
        {
           return Database.ExecuteDataset( sqlQuery );
        }

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public T GetEntity<T>( string commandText , List<DbParameter> parms )
        {
            return Database.ExecuteObject<T>( commandText , parms );
        }

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public T GetEntity<T>( string commandText  )
        {
            return Database.ExecuteObject<T>( commandText );
        }
    }
}
