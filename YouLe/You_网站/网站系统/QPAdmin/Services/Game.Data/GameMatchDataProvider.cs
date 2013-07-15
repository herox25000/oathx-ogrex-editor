using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Entity;
using Game.Kernel;

using Game.IData;
using System.Data;
using System.Data.Common;
using Game.Entity.GameMatch;

namespace Game.Data
{
    public class GameMatchDataProvider : BaseDataProvider,IGameMatchProvider
    {
        #region 构造方法

        private ITableProvider aideMatchInfoProvider;

        public GameMatchDataProvider( string connString )
            : base(connString)
        {
            aideMatchInfoProvider = GetTableProvider( MatchInfo.Tablename );
        }

        #endregion

        #region 公共

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
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery )
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
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey )
        {
            PagerParameters pager = new PagerParameters( tableName , pkey , pageIndex , pageSize );
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
        public T GetEntity<T>( string commandText )
        {
            return Database.ExecuteObject<T>( commandText );
        }

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        public int ExecuteSql( string sql )
        {
            return Database.ExecuteNonQuery( sql );
        }


        #endregion

        #region 比赛相关

        /// <summary>
        /// 新增比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void InsertMatchInfo( MatchInfo gameMatch )
        {
            DataRow dr = aideMatchInfoProvider.NewRow( );

            dr[MatchInfo._MatchID] = gameMatch.MatchID;
            dr[MatchInfo._MatchName] = gameMatch.MatchName;
            dr[MatchInfo._MatchSummary] = gameMatch.MatchSummary;
            dr[MatchInfo._MatchContent] = gameMatch.MatchContent;
            dr[MatchInfo._MatchDate] = gameMatch.MatchDate;
            dr[MatchInfo._MatchStatus] = gameMatch.MatchStatus;
            dr[MatchInfo._Nullity] = gameMatch.Nullity;
            dr[MatchInfo._CollectDate] = gameMatch.CollectDate;

            aideMatchInfoProvider.Insert( dr );
        }

        /// <summary>
        /// 更新比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void UpdateMatchInfo( MatchInfo gameMatch )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE MatchInfo SET " )
                    .Append( "MatchName=@MatchName ," )
                    .Append( "MatchSummary=@MatchSummary," )
                    .Append( "MatchContent= @MatchContent ," )
                    .Append( "MatchDate= @MatchDate," )
                    .Append( "MatchStatus=@MatchStatus," )
                    .Append( "Nullity= @Nullity " )
                    .Append( "WHERE MatchID= @MatchID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "MatchName" , gameMatch.MatchName ) );
            prams.Add( Database.MakeInParam( "MatchSummary" , gameMatch.MatchSummary ) );
            prams.Add( Database.MakeInParam( "MatchContent" , gameMatch.MatchContent ) );
            prams.Add( Database.MakeInParam( "MatchDate" , gameMatch.MatchDate ) );
            prams.Add( Database.MakeInParam( "MatchStatus" , gameMatch.MatchStatus ) );
            prams.Add( Database.MakeInParam( "Nullity" , gameMatch.Nullity ) );
            prams.Add( Database.MakeInParam( "MatchID" , gameMatch.MatchID ) );

            Database.ExecuteNonQuery( CommandType.Text , sqlQuery.ToString( ) , prams.ToArray( ) );
        }

        #endregion
    }
}
