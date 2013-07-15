using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Accounts;
using System.Data;
using Game.Entity.Treasure;
using System.Data.Common;

namespace Game.IData
{
    /// <summary>
    /// 金币库数据层接口
    /// </summary>
    public interface ITreasureDataProvider //: IProvider
    {
        #region 在线充值

        /// <summary>
        /// 生成订单
        /// </summary>
        /// <param name="orderInfo"></param>
        /// <returns></returns>
        Message RequestOrder( OnLineOrder orderInfo );

        /// <summary>
        /// 写天天付返回记录
        /// </summary>
        /// <param name="returnKQ"></param>
        void WriteReturnDayDetail( ReturnDayDetailInfo returnDay );

        /// <summary>
        /// 写快钱返回记录
        /// </summary>
        /// <param name="returnKQ"></param>
        void WriteReturnKQDetail( ReturnKQDetailInfo returnKQ );

        /// <summary>
        /// 写电话充值返回记录
        /// </summary>
        /// <param name="returnKQ"></param>
        Message WriteReturnVBDetail( ReturnVBDetailInfo returnVB );

        // <summary>
        /// 写易宝返回记录
        /// </summary>
        /// <param name="returnYB"></param>
        Message WriteReturnYBDetail( ReturnYPDetailInfo returnYB );

        /// <summary>
        /// 在线充值
        /// </summary>
        /// <param name="olDetial"></param>
        /// <returns></returns>
        Message FilliedOnline( ShareDetialInfo olDetial , int isVB );

        /// <summary>
        /// 苹果充值
        /// </summary>
        /// <param name="olDetial"></param>
        /// <returns></returns>
        Message FilliedApp( ShareDetialInfo olDetial );

        /// <summary>
        /// 实卡充值
        /// </summary>
        /// <param name="associator"></param>
        /// <param name="operUserID"></param>
        /// <param name="accounts"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        Message FilledLivcard( ShareDetialInfo detialInfo , string password );

        /// <summary>
        /// 获取订单信息
        /// </summary>
        /// <param name="orderID"></param>
        /// <returns></returns>
        OnLineOrder GetOnlineOrder( string orderID );

        #endregion

        #region 充值记录

        /// <summary>
        /// 充值记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetPayRecord( string whereQuery , int pageIndex , int pageSize );

        #endregion

        #region 推广中心

        /// <summary>
        /// 获取用户推广信息
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        Message GetUserSpreadInfo( int userID );

        /// <summary>
        /// 用户推广结算
        /// </summary>
        /// <param name="balance"></param>
        /// <param name="userID"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        Message GetUserSpreadBalance( int balance , int userID , string ip );

        /// <summary>
        /// 推广记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetSpreaderRecord( string whereQuery , int pageIndex , int pageSize );

        /// <summary>
        /// 单个用户下所有被推荐人的推广信息
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        DataSet GetUserSpreaderList( int userID , int pageIndex , int pageSize );

        /// <summary>
        /// 获取单个结算总额
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        long GetUserSpreaderTotal( string sWhere );

        /// <summary>
        /// 获取推广配置实体
        /// </summary>
        /// <returns></returns>
        GlobalSpreadInfo GetGlobalSpreadInfo( );

        #endregion

        #region 银行操作

        /// <summary>
        /// 金币存入
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="TradeScore"></param>
        /// <param name="minTradeScore"></param>
        /// <param name="clientIP"></param>
        /// <param name="note"></param>
        /// <returns></returns>
        Message InsureIn( int userID , int TradeScore , int minTradeScore , string clientIP , string note );


        /// <summary>
        /// 金币取出
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="insurePass"></param>
        /// <param name="TradeScore"></param>
        /// <param name="minTradeScore"></param>
        /// <param name="clientIP"></param>
        /// <param name="note"></param>
        /// <returns></returns>
        Message InsureOut( int userID , string insurePass , int TradeScore , int minTradeScore , string clientIP , string note );

        /// <summary>
        /// 金币转账
        /// </summary>
        /// <param name="srcUserID"></param>
        /// <param name="insurePass"></param>
        /// <param name="dstUserID"></param>
        /// <param name="TradeScore"></param>
        /// <param name="minTradeScore"></param>
        /// <param name="clientIP"></param>
        /// <param name="note"></param>
        /// <returns></returns>
        Message InsureTransfer( int srcUserID , string insurePass , int dstUserID , int TradeScore , int minTradeScore , string clientIP , string note );

        /// <summary>
        /// 游戏记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetInsureTradeRecord( string whereQuery , int pageIndex , int pageSize );

        #endregion

        #region 获取金币信息

        /// <summary>
        /// 根据用户ID得到金币信息
        /// </summary>
        /// <param name="UserID"></param>
        /// <returns></returns>
        GameScoreInfo GetTreasureInfo2( int UserID );

        #endregion

        #region 财富排名

        /// <summary>
        /// 财富排名
        /// </summary>
        /// <returns></returns>
        IList<GameScoreInfo> GetGameScoreInfoOrderByScore( );

        /// <summary>
        /// 财富排名
        /// </summary>
        /// <returns></returns>
        DataSet GetScoreRanking( int num );
        #endregion

        #region 会员操作

        /// <summary>
        /// 负分清零
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        Message ClearGameScore( int userID , string ip );

        /// <summary>
        /// 逃跑清零
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        Message ClearGameFlee( int userID , string ip );

        #endregion

        #region 游戏记录

        /// <summary>
        /// 每桌游戏记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetDrawInfoRecord( string whereQuery , int pageIndex , int pageSize );

        /// <summary>
        /// 每桌详细记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetDrawScoreRecord( string whereQuery , int pageIndex , int pageSize );

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
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery );

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        /// <param name="whereQuery">字段</param>
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery ,string[] fields);

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

        #endregion
    }
}
