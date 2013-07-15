using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

using Game.Kernel;
using Game.IData;
using Game.Entity.Platform;

namespace Game.Data
{
    /// <summary>
    /// 平台数据访问层
    /// </summary>
    public class PlatformDataProvider : BaseDataProvider, IPlatformDataProvider
    {
        #region 构造方法

        public PlatformDataProvider(string connString)
            : base(connString)
        {

        }
        #endregion

        /// <summary>
        /// 根据服务器地址获取数据库信息
        /// </summary>
        /// <param name="addrString"></param>
        /// <returns></returns>
        public DataBaseInfo GetDatabaseInfo(string addrString)
        {
            string sqlQuery = string.Format("SELECT * FROM DataBaseInfo(NOLOCK) WHERE DBAddr='{0}'", addrString);
            DataBaseInfo dbInfo = Database.ExecuteObject<DataBaseInfo>(sqlQuery);

            return dbInfo;
        }

        /// <summary>
        /// 根据游戏ID获取服务器地址信息
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public GameGameItem GetDBAddString(int kindID)
        {
            string sqlQuery = string.Format("SELECT GameName, DataBaseAddr, DataBaseName, ServerVersion, ClientVersion, ServerDLLName, ClientExeName FROM GameGameItem g,GameKindItem k WHERE KindID={0} AND g.GameID=k.GameID", kindID);
            GameGameItem game = Database.ExecuteObject<GameGameItem>(sqlQuery);

            return game;
        }

        /// <summary>
        /// 获取游戏类型列表
        /// </summary>
        /// <returns></returns>
        public IList<GameTypeItem> GetGmaeTypes()
        {
            StringBuilder sqlQuery = new StringBuilder();
            sqlQuery.Append("SELECT TypeID,TypeName ")
                    .Append("FROM GameTypeItem ")
                    .Append("WHERE Nullity=0")
                    .Append(" ORDER By SortID ASC,TypeID ASC");

            return Database.ExecuteObjectList<GameTypeItem>(sqlQuery.ToString());
        }

        /// <summary>
        /// 根据类型ID获取游戏列表
        /// </summary>
        /// <param name="typeID"></param>
        /// <returns></returns>
        public IList<GameKindItem> GetGameKindsByTypeID(int typeID)
        {
            StringBuilder sqlQuery = new StringBuilder();
            sqlQuery.Append("SELECT KindID, GameID, TypeID, SortID, KindName, ProcessName, GameRuleUrl, DownLoadUrl, Nullity ")
                    .Append("FROM GameKindItem ")
                    .AppendFormat("WHERE Nullity=0 AND TypeID={0} ", typeID)
                    .Append(" ORDER By SortID ASC,KindID ASC");
            return Database.ExecuteObjectList<GameKindItem>(sqlQuery.ToString());
        }

        /// <summary>
        /// 获取热门游戏
        /// </summary>
        /// <param name="top"></param>
        /// <returns></returns>
        public IList<GameKindItem> GetHotGame(int top)
        {
            StringBuilder sqlQuery = new StringBuilder();
            sqlQuery.Append("SELECT top " + top + " KindID, KindName, GameRuleUrl ")
                    .Append("FROM GameKindItem ")
                    .Append("WHERE Nullity=0")
                    .Append(" ORDER By SortID ASC,KindID ASC");

            return Database.ExecuteObjectList<GameKindItem>(sqlQuery.ToString());
        }

        /// <summary>
        /// 得到所有的游戏
        /// </summary>
        /// <returns></returns>
        public IList<GameKindItem> GetAllKinds()
        {
            StringBuilder sqlQuery = new StringBuilder();
            sqlQuery.Append("SELECT KindID, GameID, TypeID, SortID, KindName, ProcessName, GameRuleUrl, DownLoadUrl, Nullity ")
                    .Append("FROM GameKindItem ")
                    .AppendFormat( "WHERE Nullity=0 " )
                    .Append(" ORDER By SortID ASC,KindID ASC ");
            return Database.ExecuteObjectList<GameKindItem>(sqlQuery.ToString());
        }

        /// <summary>
        /// 得到积分游戏
        /// </summary>
        /// <returns></returns>
        public IList<GameKindItem> GetIntegralKinds( )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "SELECT KindID, GameID, TypeID, SortID, KindName, ProcessName, GameRuleUrl, DownLoadUrl, Nullity " )
                    .Append( "FROM GameKindItem " )
                    .AppendFormat( "WHERE Nullity=0 AND GameID NOT IN( SELECT GameID FROM GameGameItem WHERE DataBaseName = 'QPTreasureDB' )" )
                    .Append( " ORDER By SortID ASC,KindID ASC " );
            return Database.ExecuteObjectList<GameKindItem>( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 得到游戏列表
        /// </summary>
        /// <returns></returns>
        public IList<GameGameItem> GetGameList()
        {
            StringBuilder sqlQuery = new StringBuilder();
            sqlQuery.Append("SELECT a.KindID,a.KindName,b.DataBaseAddr,b.DataBaseName ")
                    .Append(" FROM GameKindItem a,GameGameItem b ")
                    .Append("WHERE a.GameID = b.GameID ORDER BY SortID");
            return Database.ExecuteObjectList<GameGameItem>(sqlQuery.ToString());
        }

        #region 公共

        /// <summary>
        /// 根据SQL语句查询一个值
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        public object GetObjectBySql( string sqlQuery )
        {
            return Database.ExecuteScalar( System.Data.CommandType.Text , sqlQuery );
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

        #endregion
    }
}
