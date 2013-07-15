using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Accounts;
using System.Data;
using System.Data.Common;

namespace Game.IData
{
    public interface IGameMatchProvider
    {
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
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery , string[] fields , string[] fieldAlias );

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
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery , string[] fields );

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery );

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey );

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        PagerSet GetList( string tableName , int pageIndex , int pageSize ); 

        /// <summary>
        /// 获取全部数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">排序或分组</param>
        /// <param name="pageSize">页大小</param>
        PagerSet GetAllList( string tableName , string pkey , string whereQuery );

        /// <summary>
        /// 获取全部数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">排序或分组</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pageSize">查询的数量</param>
        PagerSet GetNumberList( string tableName , string whereQuery , string pkey , int number );

        /// <summary>
        /// 根据sql语句获取数据
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        DataSet GetDataSetByWhere( string sqlQuery );

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        T GetEntity<T>( string commandText , List<DbParameter> parms );

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        T GetEntity<T>( string commandText );
    }
}
