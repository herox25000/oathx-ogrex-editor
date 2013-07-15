using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.Common;

using Game.Kernel;
using Game.IData;
using Game.Entity.Platform;

namespace Game.Data
{
    /// <summary>
    /// 平台库数据层
    /// </summary>
    public class PlatformDataProvider : BaseDataProvider, IPlatformDataProvider
    {
        #region Fields

        private ITableProvider aideDataBaseInfoProvider;
        private ITableProvider aideGameGameItemProvider;
        private ITableProvider aideGameTypeItemProvider;
        private ITableProvider aideGameKindItemProvider;
        private ITableProvider aideGameNodeItemProvider;
        private ITableProvider aideGamePageItemProvider;
        private ITableProvider aideGameRoomInfoProvider;
        private ITableProvider aideSystemMessageProvider;
        private ITableProvider aideGlobalPlayPresentProvider;


        #endregion

        #region 构造方法

        public PlatformDataProvider( string connString )
            : base( connString )
        {
            aideDataBaseInfoProvider = GetTableProvider( DataBaseInfo.Tablename );
            aideGameGameItemProvider = GetTableProvider( GameGameItem.Tablename );
            aideGameTypeItemProvider = GetTableProvider( GameTypeItem.Tablename );
            aideGameKindItemProvider = GetTableProvider( GameKindItem.Tablename );
            aideGameNodeItemProvider = GetTableProvider( GameNodeItem.Tablename );
            aideGamePageItemProvider = GetTableProvider( GamePageItem.Tablename );
            aideGameRoomInfoProvider = GetTableProvider( GameRoomInfo.Tablename );
            aideSystemMessageProvider = GetTableProvider( SystemMessage.Tablename );
            aideGlobalPlayPresentProvider = GetTableProvider( GlobalPlayPresent.Tablename );
        }
        #endregion

        #region  数据库连接串
        /// <summary>
        /// 获取积分库的连接串
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public string GetConn( int kindID )
        {
            StringBuilder sb = new StringBuilder( );
            GameKindItem gamekind = GetGameKindItemInfo( kindID );
            if ( gamekind == null )
                return "";
            GameGameItem game = GetGameGameItemInfo( gamekind.GameID );
            if ( game == null )
                return "";
            DataBaseInfo database = GetDataBaseInfo( game.DataBaseAddr );
            if ( database == null )
                return "";
            string userID = Utils.CWHEncryptNet.XorCrevasse( database.DBUser );
            string password = Utils.CWHEncryptNet.XorCrevasse( database.DBPassword );
            sb.AppendFormat( "Data Source={0}; Initial Catalog={1}; User ID={2}; Password={3}; Pooling=true", game.DataBaseAddr + ( string.IsNullOrEmpty( database.DBPort.ToString( ) ) ? "" : ( "," + database.DBPort.ToString( ) ) ), game.DataBaseName, userID, password );
            return sb.ToString( );
        }
        #endregion

        #region 机器管理

        /// <summary>
        /// 获取机器列表
        /// </summary>
        /// <returns></returns>
        public PagerSet GetDataBaseList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( DataBaseInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取机器实体
        /// </summary>
        /// <param name="dBInfoID"></param>
        /// <returns></returns>
        public DataBaseInfo GetDataBaseInfo( int dBInfoID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE DBInfoID= {0}", dBInfoID );
            DataBaseInfo dataBase = aideDataBaseInfoProvider.GetObject<DataBaseInfo>( sqlQuery );
            return dataBase;
        }
        /// <summary>
        /// 获取机器实体
        /// </summary>
        /// <param name="dBAddr"></param>
        /// <returns></returns>
        public DataBaseInfo GetDataBaseInfo( string dBAddr )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE DBAddr= '{0}'", dBAddr );
            DataBaseInfo dataBase = aideDataBaseInfoProvider.GetObject<DataBaseInfo>( sqlQuery );
            return dataBase;
        }
        /// <summary>
        /// 新增机器信息
        /// </summary>
        /// <param name="station"></param>
        public void InsertDataBase( DataBaseInfo dataBase )
        {
            DataRow dr = aideDataBaseInfoProvider.NewRow( );

            dr[DataBaseInfo._DBAddr] = dataBase.DBAddr;
            dr[DataBaseInfo._DBPort] = dataBase.DBPort;
            dr[DataBaseInfo._DBUser] = dataBase.DBUser;
            dr[DataBaseInfo._DBPassword] = dataBase.DBPassword;
            dr[DataBaseInfo._MachineID] = dataBase.MachineID;
            dr[DataBaseInfo._Information] = dataBase.Information;

            aideDataBaseInfoProvider.Insert( dr );
        }

        /// <summary>
        ///  更新机器信息
        /// </summary>
        /// <param name="station"></param>
        public void UpdateDataBase( DataBaseInfo dataBase )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE DataBaseInfo SET " )
                    .Append( "DBAddr=@DBAddr, " )
                    .Append( "DBPort=@DBPort, " )
                    .Append( "DBUser=@DBUser, " )
                    .Append( "DBPassword=@DBPassword, " )
                    .Append( "MachineID=@MachineID, " )
                    .Append( "Information=@Information " )
                    .Append( "WHERE DBInfoID=@DBInfoID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "DBAddr", dataBase.DBAddr ) );
            prams.Add( Database.MakeInParam( "DBPort", dataBase.DBPort ) );
            prams.Add( Database.MakeInParam( "DBUser", dataBase.DBUser ) );
            prams.Add( Database.MakeInParam( "DBPassword", dataBase.DBPassword ) );
            prams.Add( Database.MakeInParam( "MachineID", dataBase.MachineID ) );
            prams.Add( Database.MakeInParam( "Information", dataBase.Information ) );
            prams.Add( Database.MakeInParam( "DBInfoID", dataBase.DBInfoID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除机器
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteDataBase( string sqlQuery )
        {
            aideDataBaseInfoProvider.Delete( sqlQuery );
        }
        #endregion

        #region 游戏模块管理

        /// <summary>
        /// 获取模板列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGameGameItemList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameGameItem.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取模块实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        public GameGameItem GetGameGameItemInfo( int gameID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE GameID= {0}", gameID );
            GameGameItem gameGameItem = aideGameGameItemProvider.GetObject<GameGameItem>( sqlQuery );
            return gameGameItem;
        }

        /// <summary>
        /// 获取游戏模块标识的最大值
        /// </summary>
        /// <returns></returns>
        public int GetMaxGameGameID( )
        {
            string sqlQuery = "SELECT MAX(GameID) FROM GameGameItem(NOLOCK)";
            object obj = Database.ExecuteScalar( CommandType.Text, sqlQuery );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
        }

        /// <summary>
        /// 新增模块
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void InsertGameGameItem( GameGameItem gameGameItem )
        {
            DataRow dr = aideGameGameItemProvider.NewRow( );

            dr[GameGameItem._GameID] = gameGameItem.GameID;
            dr[GameGameItem._GameName] = gameGameItem.GameName;
            dr[GameGameItem._SuporType] = gameGameItem.SuporType;
            dr[GameGameItem._DataBaseAddr] = gameGameItem.DataBaseAddr;
            dr[GameGameItem._DataBaseName] = gameGameItem.DataBaseName;
            dr[GameGameItem._ServerVersion] = gameGameItem.ServerVersion;
            dr[GameGameItem._ClientVersion] = gameGameItem.ClientVersion;
            dr[GameGameItem._ServerDLLName] = gameGameItem.ServerDLLName;
            dr[GameGameItem._ClientExeName] = gameGameItem.ClientExeName;

            aideGameGameItemProvider.Insert( dr );
        }

        /// <summary>
        /// 更新模块
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void UpdateGameGameItem( GameGameItem gameGameItem )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameGameItem SET " )
                    .Append( "GameName=@GameName, " )
                    .Append( "SuporType=@SuporType, " )
                    .Append( "DataBaseAddr=@DataBaseAddr, " )
                    .Append( "DataBaseName=@DataBaseName, " )
                    .Append( "ServerVersion=@ServerVersion, " )
                    .Append( "ClientVersion=@ClientVersion, " )
                    .Append( "ServerDLLName=@ServerDLLName, " )
                    .Append( "ClientExeName=@ClientExeName " )
                    .Append( "WHERE GameID=@GameID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "GameName", gameGameItem.GameName ) );
            prams.Add( Database.MakeInParam( "SuporType", gameGameItem.SuporType ) );
            prams.Add( Database.MakeInParam( "DataBaseAddr", gameGameItem.DataBaseAddr ) );
            prams.Add( Database.MakeInParam( "DataBaseName", gameGameItem.DataBaseName ) );
            prams.Add( Database.MakeInParam( "ServerVersion", gameGameItem.ServerVersion ) );
            prams.Add( Database.MakeInParam( "ClientVersion", gameGameItem.ClientVersion ) );
            prams.Add( Database.MakeInParam( "ServerDLLName", gameGameItem.ServerDLLName ) );
            prams.Add( Database.MakeInParam( "ClientExeName", gameGameItem.ClientExeName ) );
            prams.Add( Database.MakeInParam( "GameID", gameGameItem.GameID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除模块
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameGameItem( string sqlQuery )
        {
            aideGameGameItemProvider.Delete( sqlQuery );
        }
        #endregion

        #region 游戏类型

        /// <summary>
        /// 获取游戏类型列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGameTypeItemList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameTypeItem.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取游戏类型实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        public GameTypeItem GetGameTypeItemInfo( int typeID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE TypeID= {0}", typeID );
            GameTypeItem gameTypeItem = aideGameTypeItemProvider.GetObject<GameTypeItem>( sqlQuery );
            return gameTypeItem;
        }
        /// <summary>
        /// 获取游戏类型ID的最大值
        /// </summary>
        /// <returns></returns>
        public int GetMaxGameTypeID( )
        {
            string sqlQuery = "SELECT MAX(TypeID) FROM GameTypeItem(NOLOCK)";
            object obj = Database.ExecuteScalar( CommandType.Text, sqlQuery );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
        }
        /// <summary>
        /// 新增游戏类型
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void InsertGameTypeItem( GameTypeItem gameTypeItem )
        {
            DataRow dr = aideGameTypeItemProvider.NewRow( );

            dr[GameTypeItem._TypeID] = gameTypeItem.TypeID;
            dr[GameTypeItem._SortID] = gameTypeItem.SortID;
            dr[GameTypeItem._TypeName] = gameTypeItem.TypeName;
            dr[GameTypeItem._JoinID] = gameTypeItem.JoinID;
            dr[GameTypeItem._Nullity] = gameTypeItem.Nullity;

            aideGameTypeItemProvider.Insert( dr );
        }

        /// <summary>
        /// 更新游戏类型
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void UpdateGameTypeItem( GameTypeItem gameTypeItem )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameTypeItem SET " )
                    .Append( "SortID=@SortID, " )
                    .Append( "TypeName=@TypeName, " )
                    .Append( "JoinID=@JoinID, " )
                    .Append( "Nullity=@Nullity " )
                    .Append( "WHERE TypeID=@TypeID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "TypeID", gameTypeItem.TypeID ) );
            prams.Add( Database.MakeInParam( "SortID", gameTypeItem.SortID ) );
            prams.Add( Database.MakeInParam( "TypeName", gameTypeItem.TypeName ) );
            prams.Add( Database.MakeInParam( "JoinID", gameTypeItem.JoinID ) );
            prams.Add( Database.MakeInParam( "Nullity", gameTypeItem.Nullity ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除游戏类型
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameTypeItem( string sqlQuery )
        {
            aideGameTypeItemProvider.Delete( sqlQuery );
        }
        #endregion

        #region 节点

        /// <summary>
        /// 获取游戏节点列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGameNodeItemList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameNodeItem.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取游戏节点实体
        /// </summary>
        /// <param name="nodeID"></param>
        /// <returns></returns>
        public GameNodeItem GetGameNodeItemInfo( int nodeID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE NodeID= {0}", nodeID );
            GameNodeItem gameNodeItem = aideGameNodeItemProvider.GetObject<GameNodeItem>( sqlQuery );
            return gameNodeItem;
        }

        /// <summary>
        /// 获取游戏节点ID的最大值
        /// </summary>
        /// <returns></returns>
        public int GetMaxGameNodeID( )
        {
            string sqlQuery = "SELECT MAX(NodeID) FROM GameNodeItem(NOLOCK)";
            object obj = Database.ExecuteScalar( CommandType.Text, sqlQuery );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
        }
        /// <summary>
        /// 新增游戏节点
        /// </summary>
        /// <param name="gameNodeItem"></param>
        public void InsertGameNodeItem( GameNodeItem gameNodeItem )
        {
            DataRow dr = aideGameNodeItemProvider.NewRow( );

            dr[GameNodeItem._NodeID] = gameNodeItem.NodeID;
            dr[GameNodeItem._KindID] = gameNodeItem.KindID;
            dr[GameNodeItem._JoinID] = gameNodeItem.JoinID;
            dr[GameNodeItem._SortID] = gameNodeItem.SortID;
            dr[GameNodeItem._NodeName] = gameNodeItem.NodeName;
            dr[GameNodeItem._Nullity] = gameNodeItem.Nullity;

            aideGameNodeItemProvider.Insert( dr );
        }

        /// <summary>
        /// 更新游戏节点
        /// </summary>
        /// <param name="gameNodeItem"></param>
        public void UpdateGameNodeItem( GameNodeItem gameNodeItem )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameNodeItem SET " )
                    .Append( "KindID=@KindID, " )
                    .Append( "JoinID=@JoinID, " )
                    .Append( "SortID=@SortID, " )
                    .Append( "NodeName=@NodeName, " )
                    .Append( "Nullity=@Nullity " )
                    .Append( "WHERE NodeID=@NodeID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "NodeID", gameNodeItem.NodeID ) );
            prams.Add( Database.MakeInParam( "KindID", gameNodeItem.KindID ) );
            prams.Add( Database.MakeInParam( "JoinID", gameNodeItem.JoinID ) );
            prams.Add( Database.MakeInParam( "SortID", gameNodeItem.SortID ) );
            prams.Add( Database.MakeInParam( "NodeName", gameNodeItem.NodeName ) );
            prams.Add( Database.MakeInParam( "Nullity", gameNodeItem.Nullity ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除游戏节点
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameNodeItem( string sqlQuery )
        {
            aideGameNodeItemProvider.Delete( sqlQuery );
        }
        #endregion

        #region 自定义页

        /// <summary>
        /// 获取自定义页列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGamePageItemList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GamePageItem.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取自定义页实体
        /// </summary>
        /// <param name="pageID"></param>
        /// <returns></returns>
        public GamePageItem GetGamePageItemInfo( int pageID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE PageID= {0}", pageID );
            GamePageItem gamePageItem = aideGamePageItemProvider.GetObject<GamePageItem>( sqlQuery );
            return gamePageItem;
        }

        /// <summary>
        /// 获取页面ID的最大值
        /// </summary>
        /// <returns></returns>
        public int GetMaxGamePageID( )
        {
            string sqlQuery = "SELECT MAX(PageID) FROM GamePageItem(NOLOCK)";
            object obj = Database.ExecuteScalar( CommandType.Text, sqlQuery );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
        }

        /// <summary>
        /// 新增自定义页
        /// </summary>
        /// <param name="gamePageItem"></param>
        public void InsertGamePageItem( GamePageItem gamePageItem )
        {
            DataRow dr = aideGamePageItemProvider.NewRow( );
            dr[GamePageItem._PageID] = gamePageItem.PageID;
            dr[GamePageItem._NodeID] = gamePageItem.NodeID;
            dr[GamePageItem._KindID] = gamePageItem.KindID;
            dr[GamePageItem._SortID] = gamePageItem.SortID;
            dr[GamePageItem._OperateType] = gamePageItem.OperateType;
            dr[GamePageItem._DisplayName] = gamePageItem.DisplayName;
            dr[GamePageItem._ResponseUrl] = gamePageItem.ResponseUrl;
            dr[GamePageItem._Nullity] = gamePageItem.Nullity;

            aideGamePageItemProvider.Insert( dr );
        }

        /// <summary>
        /// 更新自定义页
        /// </summary>
        /// <param name="gamePageItem"></param>
        public void UpdateGamePageItem( GamePageItem gamePageItem )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GamePageItem SET " )
                    .Append( "NodeID=@NodeID, " )
                    .Append( "KindID=@KindID, " )
                    .Append( "SortID=@SortID, " )
                    .Append( "OperateType=@OperateType, " )
                    .Append( "DisplayName=@DisplayName, " )
                    .Append( "ResponseUrl=@ResponseUrl, " )
                    .Append( "Nullity=@Nullity " )
                    .Append( "WHERE PageID=@PageID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "PageID", gamePageItem.PageID ) );
            prams.Add( Database.MakeInParam( "NodeID", gamePageItem.NodeID ) );
            prams.Add( Database.MakeInParam( "KindID", gamePageItem.KindID ) );        
            prams.Add( Database.MakeInParam( "SortID", gamePageItem.SortID ) );
            prams.Add( Database.MakeInParam( "OperateType", gamePageItem.OperateType ) );
            prams.Add( Database.MakeInParam( "DisplayName", gamePageItem.DisplayName ) );
            prams.Add( Database.MakeInParam( "ResponseUrl", gamePageItem.ResponseUrl ) );
            prams.Add( Database.MakeInParam( "Nullity", gamePageItem.Nullity ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除自定义页
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGamePageItem( string sqlQuery )
        {
            aideGamePageItemProvider.Delete( sqlQuery );
        }
        #endregion

        #region 游戏
        /// <summary>
        /// 获取积分游戏列表
        /// </summary>
        /// <returns></returns>
        public DataSet GetGameList( )
        {
            string sqlCommandText = @" SELECT a.KindID,a.KindName FROM GameKindItem a INNER JOIN GameGameItem b ON a.GameID=b.GameID
                                WHERE b.DataBaseName<>'QPTreasureDB' ORDER BY KindID ASC";
            DataSet ds = Database.ExecuteDataset( CommandType.Text, sqlCommandText );
            return ds;

        }

        /// <summary>
        /// 获取游戏列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGameKindItemList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameKindItem.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取游戏实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        public GameKindItem GetGameKindItemInfo( int kindID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE KindID= {0}", kindID );
            GameKindItem gameKindItem = aideGameKindItemProvider.GetObject<GameKindItem>( sqlQuery );
            return gameKindItem;
        }

        /// <summary>
        /// 获取游戏标识KindID的最大值
        /// </summary>
        /// <returns></returns>
        public int GetMaxGameKindID( )
        {
            string sqlQuery = "SELECT MAX(KindID) FROM GameKindItem(NOLOCK)";
            object obj = Database.ExecuteScalar( CommandType.Text, sqlQuery );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
        }

        /// <summary>
        /// 新增游戏
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void InsertGameKindItem( GameKindItem gameKindItem )
        {
            DataRow dr = aideGameKindItemProvider.NewRow( );

            dr[GameKindItem._KindID] = gameKindItem.KindID;
            dr[GameKindItem._GameID] = gameKindItem.GameID;
            dr[GameKindItem._TypeID] = gameKindItem.TypeID;
            dr[GameKindItem._SortID] = gameKindItem.SortID;
            dr[GameKindItem._KindName] = gameKindItem.KindName;
            dr[GameKindItem._JoinID] = gameKindItem.JoinID;
            dr[GameKindItem._ProcessName] = gameKindItem.ProcessName;
            dr[GameKindItem._GameRuleUrl] = gameKindItem.GameRuleUrl;
            dr[GameKindItem._DownLoadUrl] = gameKindItem.DownLoadUrl;
            dr[GameKindItem._Nullity] = gameKindItem.Nullity;

            aideGameKindItemProvider.Insert( dr );
        }

        /// <summary>
        /// 更新游戏
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void UpdateGameKindItem( GameKindItem gameKindItem )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameKindItem SET " )
                    .Append( "GameID=@GameID, " )
                    .Append( "TypeID=@TypeID, " )
                    .Append( "SortID=@SortID, " )
                    .Append( "KindName=@KindName, " )
                    .Append( "JoinID=@JoinID, " )
                    .Append( "ProcessName=@ProcessName, " )
                    .Append( "GameRuleUrl=@GameRuleUrl, " )
                    .Append( "DownLoadUrl=@DownLoadUrl, " )
                    .Append( "Nullity=@Nullity " )
                    .Append( "WHERE KindID=@KindID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "GameID", gameKindItem.GameID ) );
            prams.Add( Database.MakeInParam( "TypeID", gameKindItem.TypeID ) );
            prams.Add( Database.MakeInParam( "SortID", gameKindItem.SortID ) );
            prams.Add( Database.MakeInParam( "KindName", gameKindItem.KindName ) );
            prams.Add( Database.MakeInParam( "JoinID", gameKindItem.JoinID ) );
            prams.Add( Database.MakeInParam( "ProcessName", gameKindItem.ProcessName ) );
            prams.Add( Database.MakeInParam( "GameRuleUrl", gameKindItem.GameRuleUrl ) );
            prams.Add( Database.MakeInParam( "DownLoadUrl", gameKindItem.DownLoadUrl ) );
            prams.Add( Database.MakeInParam( "Nullity", gameKindItem.Nullity ) );
            prams.Add( Database.MakeInParam( "KindID", gameKindItem.KindID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除游戏
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameKindItem( string sqlQuery )
        {
            aideGameKindItemProvider.Delete( sqlQuery );
        }
        #endregion

        #region 游戏房间

        /// <summary>
        /// 获取游戏房间列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGameRoomInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameRoomInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取游戏房间实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        public GameRoomInfo GetGameRoomInfoInfo( int serverID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE ServerID= {0}", serverID );
            GameRoomInfo gameRoomInfo = aideGameRoomInfoProvider.GetObject<GameRoomInfo>( sqlQuery );
            return gameRoomInfo;
        }

        /// <summary>
        /// 新增游戏房间
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void InsertGameRoomInfo( GameRoomInfo gameRoomInfo )
        {
            DataRow dr = aideGameRoomInfoProvider.NewRow( );

            dr[GameRoomInfo._ServerID] = gameRoomInfo.ServerID;
            dr[GameRoomInfo._ServerName] = gameRoomInfo.ServerName;
            dr[GameRoomInfo._KindID] = gameRoomInfo.KindID;
            dr[GameRoomInfo._SortID] = gameRoomInfo.SortID;
            dr[GameRoomInfo._NodeID] = gameRoomInfo.NodeID;
            dr[GameRoomInfo._GameID] = gameRoomInfo.GameID;
            dr[GameRoomInfo._TableCount] = gameRoomInfo.TableCount;
            dr[GameRoomInfo._ServerType] = gameRoomInfo.ServerType;
            dr[GameRoomInfo._ServerPort] = gameRoomInfo.ServerPort;
            dr[GameRoomInfo._DataBaseName] = gameRoomInfo.DataBaseName;
            dr[GameRoomInfo._DataBaseAddr] = gameRoomInfo.DataBaseAddr;
            dr[GameRoomInfo._CellScore] = gameRoomInfo.CellScore;
            dr[GameRoomInfo._RevenueRatio] = gameRoomInfo.RevenueRatio;
            dr[GameRoomInfo._RestrictScore] = gameRoomInfo.RestrictScore;
            dr[GameRoomInfo._MinTableScore] = gameRoomInfo.MinTableScore;
            dr[GameRoomInfo._MinEnterScore] = gameRoomInfo.MinEnterScore;
            dr[GameRoomInfo._MaxEnterScore] = gameRoomInfo.MaxEnterScore;
            dr[GameRoomInfo._MinEnterMember] = gameRoomInfo.MinEnterMember;
            dr[GameRoomInfo._MaxEnterMember] = gameRoomInfo.MaxEnterMember;
            dr[GameRoomInfo._MaxPlayer] = gameRoomInfo.MaxPlayer;
            dr[GameRoomInfo._ServerRule] = gameRoomInfo.ServerRule;
            dr[GameRoomInfo._DistributeRule] = gameRoomInfo.DistributeRule;
            dr[GameRoomInfo._MinDistributeUser] = gameRoomInfo.MinDistributeUser;
            dr[GameRoomInfo._MaxDistributeUser] = gameRoomInfo.MaxDistributeUser;
            dr[GameRoomInfo._DistributeTimeSpace] = gameRoomInfo.DistributeTimeSpace;
            dr[GameRoomInfo._DistributeDrawCount] = gameRoomInfo.DistributeDrawCount;
            dr[GameRoomInfo._DistributeStartDelay] = gameRoomInfo.DistributeStartDelay;
            dr[GameRoomInfo._AttachUserRight] = gameRoomInfo.AttachUserRight;
            dr[GameRoomInfo._ServiceMachine] = gameRoomInfo.ServiceMachine;
            dr[GameRoomInfo._CustomRule] = gameRoomInfo.CustomRule;
            dr[GameRoomInfo._Nullity] = gameRoomInfo.Nullity;
            dr[GameRoomInfo._ServerNote] = gameRoomInfo.ServerNote;
            dr[GameRoomInfo._CreateDateTime] = gameRoomInfo.CreateDateTime;
            dr[GameRoomInfo._ModifyDateTime] = gameRoomInfo.ModifyDateTime;
            dr[GameRoomInfo._ServiceScore] = gameRoomInfo.ServiceScore;


            aideGameRoomInfoProvider.Insert( dr );
        }

        /// <summary>
        /// 更新游戏房间
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void UpdateGameRoomInfo( GameRoomInfo gameRoomInfo )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameRoomInfo SET " )
                    .Append( "ServerName=@ServerName, " )
                    .Append( "KindID=@KindID, " )
                    .Append( "NodeID=@NodeID, " )
                    .Append( "SortID=@SortID, " )
                    .Append( "GameID=@GameID, " )
                    .Append( "TableCount=@TableCount, " )
                    .Append( "ServerType=@ServerType, " )
                    .Append( "ServerPort=@ServerPort, " )
                    .Append( "DataBaseName=@DataBaseName, " )
                    .Append( "DataBaseAddr=@DataBaseAddr, " )
                    .Append( "CellScore=@CellScore, " )
                    .Append( "RevenueRatio=@RevenueRatio, " )
                    .Append( "RestrictScore=@RestrictScore, " )
                    .Append( "MinTableScore=@MinTableScore, " )
                    .Append( "MinEnterScore=@MinEnterScore, " )
                    .Append( "MaxEnterScore=@MaxEnterScore, " )
                    .Append( "MinEnterMember=@MinEnterMember, " )
                    .Append( "MaxEnterMember=@MaxEnterMember, " )
                    .Append( "MaxPlayer=@MaxPlayer, " )
                    .Append( "ServerRule=@ServerRule, " )
                    .Append( "DistributeRule=@DistributeRule, " )
                    .Append( "MinDistributeUser=@MinDistributeUser, " )
                    .Append( "MaxDistributeUser=@MaxDistributeUser, " )
                    .Append( "DistributeTimeSpace=@DistributeTimeSpace, " )
                    .Append( "DistributeDrawCount=@DistributeDrawCount, " )
                    .Append( "DistributeStartDelay=@DistributeStartDelay, " )
                    .Append( "AttachUserRight=@AttachUserRight, " )
                    .Append( "ServiceMachine=@ServiceMachine, " )
                    .Append( "CustomRule=@CustomRule, " )
                    .Append( "Nullity=@Nullity, " )
                    .Append( "ServerNote=@ServerNote, " )
                    .Append( "ModifyDateTime=@ModifyDateTime " )
                    .Append( "WHERE ServerID=@ServerID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "ServerName", gameRoomInfo.ServerName ) );
            prams.Add( Database.MakeInParam( "KindID", gameRoomInfo.KindID ) );
            prams.Add( Database.MakeInParam( "NodeID", gameRoomInfo.NodeID ) );
            prams.Add( Database.MakeInParam( "SortID", gameRoomInfo.SortID ) );
            prams.Add( Database.MakeInParam( "GameID", gameRoomInfo.GameID ) );
            prams.Add( Database.MakeInParam( "TableCount", gameRoomInfo.TableCount ) );
            prams.Add( Database.MakeInParam( "ServerType", gameRoomInfo.ServerType ) );
            prams.Add( Database.MakeInParam( "ServerPort", gameRoomInfo.ServerPort ) );
            prams.Add( Database.MakeInParam( "DataBaseName", gameRoomInfo.DataBaseName ) );
            prams.Add( Database.MakeInParam( "DataBaseAddr", gameRoomInfo.DataBaseAddr ) );
            prams.Add( Database.MakeInParam( "CellScore", gameRoomInfo.CellScore ) );
            prams.Add( Database.MakeInParam( "RevenueRatio", gameRoomInfo.RevenueRatio ) );
            prams.Add( Database.MakeInParam( "RestrictScore", gameRoomInfo.RestrictScore ) );
            prams.Add( Database.MakeInParam( "MinTableScore", gameRoomInfo.MinTableScore ) );
            prams.Add( Database.MakeInParam( "MinEnterScore", gameRoomInfo.MinEnterScore ) );
            prams.Add( Database.MakeInParam( "MaxEnterScore", gameRoomInfo.MaxEnterScore ) );
            prams.Add( Database.MakeInParam( "MinEnterMember", gameRoomInfo.MinEnterMember ) );
            prams.Add( Database.MakeInParam( "MaxEnterMember", gameRoomInfo.MaxEnterMember ) );
            prams.Add( Database.MakeInParam( "MaxPlayer", gameRoomInfo.MaxPlayer ) );
            prams.Add( Database.MakeInParam( "ServerRule", gameRoomInfo.ServerRule ) );
            prams.Add( Database.MakeInParam( "DistributeRule", gameRoomInfo.DistributeRule ) );
            prams.Add( Database.MakeInParam( "MinDistributeUser", gameRoomInfo.MinDistributeUser ) );
            prams.Add( Database.MakeInParam( "MaxDistributeUser", gameRoomInfo.MaxDistributeUser ) );
            prams.Add( Database.MakeInParam( "DistributeTimeSpace", gameRoomInfo.DistributeTimeSpace ) );
            prams.Add( Database.MakeInParam( "DistributeDrawCount", gameRoomInfo.DistributeDrawCount ) );
            prams.Add( Database.MakeInParam( "DistributeStartDelay", gameRoomInfo.DistributeStartDelay ) );
            prams.Add( Database.MakeInParam( "AttachUserRight", gameRoomInfo.AttachUserRight ) );
            prams.Add( Database.MakeInParam( "ServiceMachine", gameRoomInfo.ServiceMachine ) );
            prams.Add( Database.MakeInParam( "CustomRule", gameRoomInfo.CustomRule ) );
            prams.Add( Database.MakeInParam( "Nullity", gameRoomInfo.Nullity ) );
            prams.Add( Database.MakeInParam( "ServerNote", gameRoomInfo.ServerNote ) );
            prams.Add( Database.MakeInParam( "ModifyDateTime", gameRoomInfo.ModifyDateTime ) );
            prams.Add( Database.MakeInParam( "ServerID", gameRoomInfo.ServerID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除游戏房间
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameRoomInfo( string sqlQuery )
        {
            aideGameRoomInfoProvider.Delete( sqlQuery );
        }
        #endregion

        #region 在线统计

        /// <summary>
        /// 根据查询条件获得在线人数统计信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        public DataSet GetOnLineStreamInfoList( string sqlQuery )
        {
            return Database.ExecuteDataset( CommandType.Text, sqlQuery );
        }

        /// <summary>
        /// 获取在线人数列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetOnLineStreamInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( OnLineStreamInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        #endregion

        #region 系统消息

        /// <summary>
        /// 获取系统消息列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetSystemMessageList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( SystemMessage.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取消息实体
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public SystemMessage GetSystemMessageInfo( int id )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE ID= {0}", id );
            SystemMessage systemMessage = aideSystemMessageProvider.GetObject<SystemMessage>( sqlQuery );
            return systemMessage;
        }

        /// <summary>
        /// 新增
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void InsertSystemMessage( SystemMessage systemMessage )
        {
             DataRow dr = aideSystemMessageProvider.NewRow( );

             dr[SystemMessage._MessageType] = systemMessage.MessageType;
             dr[SystemMessage._ServerRange] = systemMessage.ServerRange;
             dr[SystemMessage._MessageString] = systemMessage.MessageString;
             dr[SystemMessage._StartTime] = systemMessage.StartTime;
             dr[SystemMessage._ConcludeTime] = systemMessage.ConcludeTime;
             dr[SystemMessage._TimeRate] = systemMessage.TimeRate;
             dr[SystemMessage._Nullity] = systemMessage.Nullity;
             dr[SystemMessage._CreateDate] = systemMessage.CreateDate;
             dr[SystemMessage._CreateMasterID] = systemMessage.CreateMasterID;
             dr[SystemMessage._UpdateDate] = systemMessage.UpdateDate;
             dr[SystemMessage._UpdateMasterID] = systemMessage.UpdateMasterID;
             dr[SystemMessage._UpdateCount] = systemMessage.UpdateCount;
             dr[SystemMessage._CollectNote] = systemMessage.CollectNote;

             aideSystemMessageProvider.Insert( dr );
        }

        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="gameGameItem"></param>
        public void UpdateSystemMessage( SystemMessage systemMessage )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE SystemMessage SET " )
                    .Append( "MessageType=@MessageType, " )
                    .Append( "ServerRange=@ServerRange, " )
                    .Append( "MessageString=@MessageString, " )
                    .Append( "StartTime=@StartTime, " )
                    .Append( "ConcludeTime=@ConcludeTime, " )
                    .Append( "TimeRate=@TimeRate, " )
                    .Append( "Nullity=@Nullity, " )
                    .Append( "UpdateDate=@UpdateDate, " )
                    .Append( "UpdateMasterID=@UpdateMasterID, " )
                    .Append( "UpdateCount=@UpdateCount, " )
                    .Append( "CollectNote=@CollectNote " )
                    .Append( "WHERE ID=@ID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "MessageType", systemMessage.MessageType ) );
            prams.Add( Database.MakeInParam( "ServerRange", systemMessage.ServerRange ) );
            prams.Add( Database.MakeInParam( "MessageString", systemMessage.MessageString ) );
            prams.Add( Database.MakeInParam( "StartTime", systemMessage.StartTime ) );
            prams.Add( Database.MakeInParam( "ConcludeTime", systemMessage.ConcludeTime ) );
            prams.Add( Database.MakeInParam( "TimeRate", systemMessage.TimeRate ) );
            prams.Add( Database.MakeInParam( "Nullity", systemMessage.Nullity ) );
            prams.Add( Database.MakeInParam( "UpdateDate", systemMessage.UpdateDate ) );
            prams.Add( Database.MakeInParam( "UpdateMasterID", systemMessage.UpdateMasterID ) );
            prams.Add( Database.MakeInParam( "UpdateCount", systemMessage.UpdateCount ) );
            prams.Add( Database.MakeInParam( "CollectNote", systemMessage.CollectNote ) );
            prams.Add( Database.MakeInParam( "ID", systemMessage.ID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除系统消息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteSystemMessage( string sqlQuery )
        {
            aideSystemMessageProvider.Delete( sqlQuery );
        }


        #endregion

        #region 泡点管理

        /// <summary>
        /// 获取泡点规则列表
        /// </summary>
        /// <returns></returns>
        public PagerSet GetGlobalPlayPresentList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GlobalPlayPresent.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取泡点规则实体
        /// </summary>
        /// <param name="serverID"></param>
        /// <returns></returns>
        public GlobalPlayPresent GetGlobalPlayPresentInfo( int serverID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE ServerID= {0}", serverID );
            GlobalPlayPresent globalPlayPresent = aideGlobalPlayPresentProvider.GetObject<GlobalPlayPresent>( sqlQuery );
            return globalPlayPresent;
        }

        /// <summary>
        /// 新增泡点规则信息
        /// </summary>
        /// <param name="globalPlayPresent"></param>
        public void InsertGlobalPlayPresent( GlobalPlayPresent globalPlayPresent )
        {
            DataRow dr = aideGlobalPlayPresentProvider.NewRow( );

            dr[GlobalPlayPresent._ServerID] = globalPlayPresent.ServerID;
            dr[GlobalPlayPresent._PresentMember] = globalPlayPresent.PresentMember;
            dr[GlobalPlayPresent._MaxDatePresent] = globalPlayPresent.MaxDatePresent;
            dr[GlobalPlayPresent._MaxPresent] = globalPlayPresent.MaxPresent;
            dr[GlobalPlayPresent._CellPlayPresnet] = globalPlayPresent.CellPlayPresnet;
            dr[GlobalPlayPresent._CellPlayTime] = globalPlayPresent.CellPlayTime;

            dr[GlobalPlayPresent._StartPlayTime] = globalPlayPresent.StartPlayTime;
            dr[GlobalPlayPresent._CellOnlinePresent] = globalPlayPresent.CellOnlinePresent;
            dr[GlobalPlayPresent._CellOnlineTime] = globalPlayPresent.CellOnlineTime;
            dr[GlobalPlayPresent._StartOnlineTime] = globalPlayPresent.StartOnlineTime;

            dr[GlobalPlayPresent._IsPlayPresent] = globalPlayPresent.IsPlayPresent;
            dr[GlobalPlayPresent._IsOnlinePresent] = globalPlayPresent.IsOnlinePresent;
            dr[GlobalPlayPresent._CollectDate] = globalPlayPresent.CollectDate;

            aideGlobalPlayPresentProvider.Insert( dr );
        }

        /// <summary>
        ///  更新泡点规则信息
        /// </summary>
        /// <param name="globalPlayPresent"></param>
        public void UpdateGlobalPlayPresent( GlobalPlayPresent globalPlayPresent )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GlobalPlayPresent SET " )
                    .Append( "PresentMember=@PresentMember, " )
                    .Append( "MaxDatePresent=@MaxDatePresent, " )
                    .Append( "MaxPresent=@MaxPresent, " )
                    .Append( "CellPlayPresnet=@CellPlayPresnet, " )

                    .Append( "CellPlayTime=@CellPlayTime, " )
                    .Append( "StartPlayTime=@StartPlayTime, " )
                    .Append( "CellOnlinePresent=@CellOnlinePresent, " )
                    .Append( "CellOnlineTime=@CellOnlineTime, " )

                    .Append( "StartOnlineTime=@StartOnlineTime, " )
                    .Append( "IsPlayPresent=@IsPlayPresent, " )
                    .Append( "IsOnlinePresent=@IsOnlinePresent, " )
                    .Append( "CollectDate=@CollectDate " )
                    .Append( "WHERE ServerID=@ServerID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "PresentMember", globalPlayPresent.PresentMember ) );
            prams.Add( Database.MakeInParam( "MaxDatePresent", globalPlayPresent.MaxDatePresent ) );
            prams.Add( Database.MakeInParam( "MaxPresent", globalPlayPresent.MaxPresent ) );
            prams.Add( Database.MakeInParam( "CellPlayPresnet", globalPlayPresent.CellPlayPresnet ) );
            prams.Add( Database.MakeInParam( "CellPlayTime", globalPlayPresent.CellPlayTime ) );

            prams.Add( Database.MakeInParam( "StartPlayTime", globalPlayPresent.StartPlayTime ) );
            prams.Add( Database.MakeInParam( "CellOnlinePresent", globalPlayPresent.CellOnlinePresent ) );
            prams.Add( Database.MakeInParam( "CellOnlineTime", globalPlayPresent.CellOnlineTime ) );
            prams.Add( Database.MakeInParam( "StartOnlineTime", globalPlayPresent.StartOnlineTime ) );
            prams.Add( Database.MakeInParam( "IsPlayPresent", globalPlayPresent.IsPlayPresent ) );
            prams.Add( Database.MakeInParam( "IsOnlinePresent", globalPlayPresent.IsOnlinePresent ) );
            prams.Add( Database.MakeInParam( "CollectDate", globalPlayPresent.CollectDate ) );
            prams.Add( Database.MakeInParam( "ServerID", globalPlayPresent.ServerID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除泡点规则
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGlobalPlayPresent( string sqlQuery )
        {
            aideGlobalPlayPresentProvider.Delete( sqlQuery );
        }
        #endregion

        #region 公共

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        public int ExecuteSql( string sql )
        {
            return Database.ExecuteNonQuery( sql );
        }

        #endregion
    }
}
