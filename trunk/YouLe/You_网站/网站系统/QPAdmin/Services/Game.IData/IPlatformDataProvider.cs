using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

using Game.Kernel;
using Game.Entity.Platform;

namespace Game.IData
{
    /// <summary>
    /// 平台库数据层接口
    /// </summary>
    public interface IPlatformDataProvider //: IProvider
    {
        

        #region 机器管理

        /// <summary>
        /// 获取机器列表
        /// </summary>
        /// <returns></returns>
        PagerSet GetDataBaseList(int pageIndex, int pageSize, string condition, string orderby);        

        /// <summary>
        /// 获取机器实体
        /// </summary>
        /// <param name="dBAddr"></param>
        /// <returns></returns>
        DataBaseInfo GetDataBaseInfo(int dBInfoID);

        /// <summary>
        /// 获取机器实体
        /// </summary>
        /// <param name="dBAddr"></param>
        /// <returns></returns>
        DataBaseInfo GetDataBaseInfo( string dBAddr );

        /// <summary>
        /// 新增机器信息
        /// </summary>
        /// <param name="station"></param>
        void InsertDataBase(DataBaseInfo dataBase);        

        /// <summary>
        ///  更新机器信息
        /// </summary>
        /// <param name="station"></param>
        void UpdateDataBase(DataBaseInfo dataBase);

        /// <summary>
        /// 删除机器
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteDataBase(string sqlQuery);
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
        PagerSet GetGameGameItemList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取模块实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        GameGameItem GetGameGameItemInfo(int gameID);

        /// <summary>
        /// 获取游戏模块标识的最大值
        /// </summary>
        /// <returns></returns>
        int GetMaxGameGameID( );

        /// <summary>
        /// 新增模块
        /// </summary>
        /// <param name="gameGameItem"></param>
        void InsertGameGameItem(GameGameItem gameGameItem);

        /// <summary>
        /// 更新模块
        /// </summary>
        /// <param name="gameGameItem"></param>
        void UpdateGameGameItem(GameGameItem gameGameItem);        

        /// <summary>
        /// 删除模块
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameGameItem(string sqlQuery);        
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
        PagerSet GetGameTypeItemList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取游戏类型实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        GameTypeItem GetGameTypeItemInfo(int typeID);
        /// <summary>
        /// 获取游戏类型ID的最大值
        /// </summary>
        /// <returns></returns>
        int GetMaxGameTypeID( );
        /// <summary>
        /// 新增游戏类型
        /// </summary>
        /// <param name="gameGameItem"></param>
        void InsertGameTypeItem(GameTypeItem gameTypeItem);

        /// <summary>
        /// 更新游戏类型
        /// </summary>
        /// <param name="gameGameItem"></param>
        void UpdateGameTypeItem(GameTypeItem gameTypeItem);

        /// <summary>
        /// 删除游戏类型
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameTypeItem(string sqlQuery);

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
        PagerSet GetGameNodeItemList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取游戏节点实体
        /// </summary>
        /// <param name="nodeID"></param>
        /// <returns></returns>
        GameNodeItem GetGameNodeItemInfo( int nodeID );
        /// <summary>
        /// 获取游戏节点ID的最大值
        /// </summary>
        /// <returns></returns>
        int GetMaxGameNodeID( );
        /// <summary>
        /// 新增游戏节点
        /// </summary>
        /// <param name="gameNodeItem"></param>
        void InsertGameNodeItem( GameNodeItem gameNodeItem );

        /// <summary>
        /// 更新游戏节点
        /// </summary>
        /// <param name="gameNodeItem"></param>
        void UpdateGameNodeItem( GameNodeItem gameNodeItem );

        /// <summary>
        /// 删除游戏节点
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameNodeItem( string sqlQuery );
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
        PagerSet GetGamePageItemList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取自定义页实体
        /// </summary>
        /// <param name="pageID"></param>
        /// <returns></returns>
        GamePageItem GetGamePageItemInfo( int pageID );
        /// <summary>
        /// 获取页面ID的最大值
        /// </summary>
        /// <returns></returns>
        int GetMaxGamePageID( );
        /// <summary>
        /// 新增自定义页
        /// </summary>
        /// <param name="gamePageItem"></param>
        void InsertGamePageItem( GamePageItem gamePageItem );

        /// <summary>
        /// 更新自定义页
        /// </summary>
        /// <param name="gamePageItem"></param>
        void UpdateGamePageItem( GamePageItem gamePageItem );

        /// <summary>
        /// 删除自定义页
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGamePageItem( string sqlQuery );
        #endregion

        #region 游戏
        /// <summary>
        /// 获取积分游戏列表
        /// </summary>
        /// <returns></returns>
        DataSet GetGameList( );
        /// <summary>
        /// 获取游戏列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGameKindItemList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取游戏实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        GameKindItem GetGameKindItemInfo(int kindID);
        
        /// <summary>
        /// 获取游戏标识KindID的最大值
        /// </summary>
        /// <returns></returns>
        int GetMaxGameKindID( );

        /// <summary>
        /// 新增游戏
        /// </summary>
        /// <param name="gameGameItem"></param>
        void InsertGameKindItem(GameKindItem gameKindItem);

        /// <summary>
        /// 更新游戏
        /// </summary>
        /// <param name="gameGameItem"></param>
        void UpdateGameKindItem(GameKindItem gameKindItem);

        /// <summary>
        /// 删除游戏
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameKindItem(string sqlQuery);
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
        PagerSet GetGameRoomInfoList(int pageIndex, int pageSize, string condition, string orderby); 

        /// <summary>
        /// 获取游戏房间实体
        /// </summary>
        /// <param name="gameID"></param>
        /// <returns></returns>
        GameRoomInfo GetGameRoomInfoInfo(int serverID);

        /// <summary>
        /// 新增游戏房间
        /// </summary>
        /// <param name="gameGameItem"></param>
        void InsertGameRoomInfo(GameRoomInfo gameRoomInfo);

        /// <summary>
        /// 更新游戏房间
        /// </summary>
        /// <param name="gameGameItem"></param>
        void UpdateGameRoomInfo(GameRoomInfo gameRoomInfo);

        /// <summary>
        /// 删除游戏房间
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameRoomInfo(string sqlQuery);
        #endregion

        #region 在线统计

        /// <summary>
        /// 根据查询条件获得在线人数统计信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        DataSet GetOnLineStreamInfoList(string sqlQuery);

        /// <summary>
        /// 获取在线人数列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetOnLineStreamInfoList(int pageIndex, int pageSize, string condition, string orderby);
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
        PagerSet GetSystemMessageList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取消息实体
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        SystemMessage GetSystemMessageInfo(int id);

        /// <summary>
        /// 新增游戏
        /// </summary>
        /// <param name="gameGameItem"></param>
        void InsertSystemMessage(SystemMessage systemMessage);

        /// <summary>
        /// 更新游戏
        /// </summary>
        /// <param name="gameGameItem"></param>
        void UpdateSystemMessage(SystemMessage systemMessage);

        /// <summary>
        /// 删除系统消息
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteSystemMessage(string sqlQuery);

        #endregion

        #region 泡点管理

        /// <summary>
        /// 获取泡点规则列表
        /// </summary>
        /// <returns></returns>
        PagerSet GetGlobalPlayPresentList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取泡点规则实体
        /// </summary>
        /// <param name="serverID"></param>
        /// <returns></returns>
        GlobalPlayPresent GetGlobalPlayPresentInfo( int serverID );

        /// <summary>
        /// 新增泡点规则信息
        /// </summary>
        /// <param name="globalPlayPresent"></param>
        void InsertGlobalPlayPresent( GlobalPlayPresent globalPlayPresent );

        /// <summary>
        ///  更新泡点规则信息
        /// </summary>
        /// <param name="globalPlayPresent"></param>
        void UpdateGlobalPlayPresent( GlobalPlayPresent globalPlayPresent );

        /// <summary>
        /// 删除泡点规则
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGlobalPlayPresent( string sqlQuery );
        #endregion

        #region 积分库

        /// <summary>
        /// 获取积分库连接字符串
        /// </summary>
        /// <param name="kindID"></param>
        string GetConn( int kindID );
		 
	    #endregion

        #region 公共

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        int ExecuteSql( string sql );
 
        #endregion
       
    }
}
