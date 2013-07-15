using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Data.Factory;
using Game.IData;
using Game.Kernel;
using Game.Utils;
using Game.Entity.Treasure;
using System.Data;
using Game.Data;
using System.Data.Common;

namespace Game.Facade
{
    /// <summary>
    /// 金币库外观
    /// </summary>
    public class TreasureFacade
    {
        #region Fields

        private ITreasureDataProvider treasureData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public TreasureFacade( )
        {
            treasureData = ClassFactory.GetITreasureDataProvider( );
        }

        /// <summary>
        /// 带参构造函数
        /// </summary>
        /// <param name="kindID"></param>
        public TreasureFacade( int kindID )
        {
            if( new AppConfig( ).GetDBlink( kindID ) == "" )
                treasureData = null;
            else
                treasureData = ProxyFactory.CreateInstance<TreasureDataProvider>( new AppConfig( ).GetDBlink( kindID ) );
        }
        #endregion

        #region 在线充值

        /// <summary>
        /// 生成订单
        /// </summary>
        /// <param name="orderInfo"></param>
        /// <returns></returns>
        public Message RequestOrder( OnLineOrder orderInfo )
        {
            return treasureData.RequestOrder( orderInfo );
        }

        /// <summary>
        /// 写天天付返回记录
        /// </summary>
        /// <param name="returnKQ"></param>
        public void WriteReturnDayDetail( ReturnDayDetailInfo returnDay )
        {
            treasureData.WriteReturnDayDetail( returnDay );
        }

        /// <summary>
        /// 写快钱返回记录
        /// </summary>
        /// <param name="returnKQ"></param>
        public void WriteReturnKQDetail( ReturnKQDetailInfo returnKQ )
        {
            treasureData.WriteReturnKQDetail( returnKQ );
        }

        /// <summary>
        /// 写电话充值返回记录
        /// </summary>
        /// <param name="returnKQ"></param>
        public Message WriteReturnVBDetail( ReturnVBDetailInfo returnVB )
        {
            return treasureData.WriteReturnVBDetail( returnVB );
        }

        /// <summary>
        /// 写易宝返回记录
        /// </summary>
        /// <param name="returnYB"></param>
        public Message WriteReturnYBDetail( ReturnYPDetailInfo returnYB )
        {
            return treasureData.WriteReturnYBDetail( returnYB );
        }

        /// <summary>
        /// 在线充值
        /// </summary>
        /// <param name="olDetial"></param>
        /// <returns></returns>
        public Message FilliedOnline( ShareDetialInfo olDetial , int isVB )
        {
            return treasureData.FilliedOnline( olDetial , isVB );
        }

        /// <summary>
        /// 苹果充值
        /// </summary>
        /// <param name="olDetial"></param>
        /// <returns></returns>
        public Message FilliedApp( ShareDetialInfo olDetial )
        {
            return treasureData.FilliedApp( olDetial );
        }

        /// <summary>
        /// 实卡充值
        /// </summary>
        /// <param name="associator"></param>
        /// <param name="operUserID"></param>
        /// <param name="accounts"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        public Message FilledLivcard( ShareDetialInfo detialInfo , string password )
        {
            return treasureData.FilledLivcard( detialInfo , password );
        }

        /// <summary>
        /// 获取订单信息
        /// </summary>
        /// <param name="orderID"></param>
        /// <returns></returns>
        public OnLineOrder GetOnlineOrder( string orderID )
        {
            return treasureData.GetOnlineOrder( orderID );
        }

        #endregion

        #region 充值记录

        /// <summary>
        /// 充值记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetPayRecord( string whereQuery , int pageIndex , int pageSize )
        {
            return treasureData.GetPayRecord( whereQuery , pageIndex , pageSize );
        }

        #endregion

        #region 推广中心

        /// <summary>
        /// 获取用户推广信息
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public Message GetUserSpreadInfo( int userID )
        {
            return treasureData.GetUserSpreadInfo( userID );
        }

        /// <summary>
        /// 用户推广结算信息
        /// </summary>
        /// <param name="balance"></param>
        /// <param name="userID"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        public Message GetUserSpreadBalance( int balance , int userID , string ip )
        {
            return treasureData.GetUserSpreadBalance( balance , userID , ip );
        }

        /// <summary>
        /// 推广记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetSpreaderRecord( string whereQuery , int pageIndex , int pageSize )
        {
            return treasureData.GetSpreaderRecord( whereQuery , pageIndex , pageSize );
        }

        /// <summary>
        /// 单个用户下所有被推荐人的推广信息
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public DataSet GetUserSpreaderList( int userID , int pageIndex , int pageSize )
        {
            return treasureData.GetUserSpreaderList( userID , pageIndex , pageSize );
        }

        /// <summary>
        /// 获取单个结算总额
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public long GetUserSpreaderTotal( string sWhere )
        {
            return treasureData.GetUserSpreaderTotal( sWhere );
        }

        /// <summary>
        /// 获取推广配置实体
        /// </summary>
        /// <returns></returns>
        public GlobalSpreadInfo GetGlobalSpreadInfo( )
        {
            return treasureData.GetGlobalSpreadInfo( );
        }

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
        public Message InsureIn( int userID , int TradeScore , int minTradeScore , string clientIP , string note )
        {
            return treasureData.InsureIn( userID , TradeScore , minTradeScore , clientIP , note );
        }


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
        public Message InsureOut( int userID , string insurePass , int TradeScore , int minTradeScore , string clientIP , string note )
        {
            return treasureData.InsureOut( userID , insurePass , TradeScore , minTradeScore , clientIP , note );
        }

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
        public Message InsureTransfer( int srcUserID , string insurePass , int dstUserID , int TradeScore , int minTradeScore , string clientIP , string note )
        {
            return treasureData.InsureTransfer( srcUserID , insurePass , dstUserID , TradeScore , minTradeScore , clientIP , note );
        }

        /// <summary>
        /// 游戏记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetInsureTradeRecord( string whereQuery , int pageIndex , int pageSize )
        {
            return treasureData.GetInsureTradeRecord( whereQuery , pageIndex , pageSize );
        }

        #endregion

        #region 获取金币信息

        /// <summary>
        /// 根据用户ID得到金币信息
        /// </summary>
        /// <param name="UserID"></param>
        /// <returns></returns>
        public GameScoreInfo GetTreasureInfo2( int UserID )
        {
            if( treasureData == null ) return null;
            return treasureData.GetTreasureInfo2( UserID );
        }

        #endregion

        #region 财富排名

        /// <summary>
        /// 财富排名
        /// </summary>
        /// <returns></returns>
        public IList<GameScoreInfo> GetGameScoreInfoOrderByScore( )
        {
            return treasureData.GetGameScoreInfoOrderByScore( );
        }

        /// <summary>
        /// 财富排名
        /// </summary>
        /// <returns></returns>
        public DataSet GetScoreRanking( int num )
        {
            return treasureData.GetScoreRanking( num );
        }

        #endregion

        #region 会员操作

        /// <summary>
        /// 负分清零
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        public Message ClearGameScore( int userID , string ip )
        {
            return treasureData.ClearGameScore( userID , ip );
        }

        /// <summary>
        /// 逃跑清零
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="ip"></param>
        /// <returns></returns>
        public Message ClearGameFlee( int userID , string ip )
        {
            return treasureData.ClearGameFlee( userID , ip );
        }

        #endregion

        #region 游戏记录

        /// <summary>
        /// 每桌游戏记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetDrawInfoRecord( string whereQuery , int pageIndex , int pageSize )
        {
            return treasureData.GetDrawInfoRecord( whereQuery , pageIndex , pageSize );
        }

        /// <summary>
        /// 每桌详细记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetDrawScoreRecord( string whereQuery , int pageIndex , int pageSize )
        {
            return treasureData.GetDrawScoreRecord( whereQuery , pageIndex , pageSize );
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
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery )
        {
            return treasureData.GetList( tableName , pageIndex , pageSize , pkey , whereQuery );
        }

        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <param name="pkey">排序或分组</param>
        /// <param name="whereQuery">查询条件</param>
        /// <param name="whereQuery">字段</param>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string pkey , string whereQuery , string fieldsList )
        {
            string[ ] fileds = fieldsList.Split( ',' );
            return treasureData.GetList( tableName , pageIndex , pageSize , pkey , whereQuery , fileds );
        }

        /// <summary>
        /// 根据sql语句获取数据
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns></returns>
        public DataSet GetDataSetByWhere( string sqlQuery )
        {
            return treasureData.GetDataSetByWhere( sqlQuery );
        }

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public T GetEntity<T>( string commandText , List<DbParameter> parms )
        {
            return treasureData.GetEntity<T>( commandText , parms );
        }

        /// <summary>
        /// 根据sql获取实体
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public T GetEntity<T>( string commandText )
        {
            return treasureData.GetEntity<T>( commandText );
        }

        #endregion
    }
}
