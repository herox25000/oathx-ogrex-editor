using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Treasure;
using System.Data;

namespace Game.IData
{
    /// <summary>
    /// 金币库数据层接口
    /// </summary>
    public interface ITreasureDataProvider //: IProvider
    {
        #region 充值相关
        /// <summary>
        /// 获取实卡类型记录列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGlobalLivcardList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取实卡类型实体
        /// </summary>
        /// <param name="cardTypeID"></param>
        /// <returns></returns>
        GlobalLivcard GetGlobalLivcardInfo( int cardTypeID );
        /// <summary>
        /// 新增实卡类型
        /// </summary>
        /// <param name="globalLivcard"></param>
        void InsertGlobalLivcard( GlobalLivcard globalLivcard );
        /// <summary>
        /// 更新实卡类型
        /// </summary>
        /// <param name="globalLivcard"></param>
        void UpdateGlobalLivcard( GlobalLivcard globalLivcard );
        /// <summary>
        /// 删除实卡类型
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGlobalLivcard( string sqlQuery );

        /// <summary>
        /// 获取实卡批次记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetLivcardBuildStreamList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取实卡批次实体
        /// </summary>
        /// <param name="buildID"></param>
        /// <returns></returns>
        LivcardBuildStream GetLivcardBuildStreamInfo( int buildID );
        /// <summary>
        /// 插入实卡批次记录
        /// </summary>
        /// <param name="livcardBuildStream"></param>
        /// <returns></returns>
        int InsertLivcardBuildStream( LivcardBuildStream livcardBuildStream );
        /// <summary>
        /// 更新实卡批次记录
        /// </summary>
        /// <param name="livcardBuildStream"></param>
        void UpdateLivcardBuildStream( LivcardBuildStream livcardBuildStream );
        /// <summary>
        /// 更新实卡批次导出次数
        /// </summary>
        /// <param name="buildID"></param>
        void UpdateLivcardBuildStream( int buildID );

        /// <summary>
        /// 获取实卡记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetLivcardAssociatorList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取实卡实体,根据CardID
        /// </summary>
        /// <param name="cardID"></param>
        /// <returns></returns>
        LivcardAssociator GetLivcardAssociatorInfo( int cardID );
        /// <summary>
        /// 获取实卡实体,根据SerialID
        /// </summary>
        /// <param name="serialID"></param>
        /// <returns></returns>
        LivcardAssociator GetLivcardAssociatorInfo( string serialID );
        /// <summary>
        /// 获取实卡充值记录,根据SerialID
        /// </summary>
        /// <param name="serialID"></param>
        /// <returns></returns>
        ShareDetailInfo GetShareDetailInfo( string serialID );
        /// <summary>
        /// 获取实卡的销售商名称，根据批号
        /// </summary>
        /// <param name="buildID"></param>
        /// <returns></returns>
        string GetSalesperson( int buildID );
        /// <summary>
        /// 禁用实卡
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetCardDisbale( string sqlQuery );

        /// <summary>
        /// 启用实卡
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetCardEnbale( string sqlQuery );
        /// <summary>
        /// 插入实卡记录
        /// </summary>
        /// <param name="livcardAssociator"></param>
        /// <returns></returns>
        void InsertLivcardAssociator( LivcardAssociator livcardAssociator , string[,] list );
        /// <summary>
        /// 实卡库存统计
        /// </summary>
        /// <returns></returns>
        DataSet GetLivcardStat( );
        /// <summary>
        /// 实卡库存统计
        /// </summary>
        /// <returns></returns>
        DataSet GetLivcardStatByBuildID( int buildID );
        
        /// <summary>
        /// 获取订单记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetOnLineOrderList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取订单信息实体
        /// </summary>
        /// <param name="orderID"></param>
        /// <returns></returns>
        OnLineOrder GetOnLineOrderInfo(string orderID);

        /// <summary>
        /// 删除订单
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteOnlineOrder(string sqlQuery);

        /// <summary>
        /// 获取快钱返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetKQDetailList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取快钱返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        ReturnKQDetailInfo GetKQDetailInfo(int detailID);

        /// <summary>
        /// 删除快钱返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteKQDetail(string sqlQuery);

        /// <summary>
        /// 获取天天付返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetDayDetailList( int pageIndex , int pageSize , string condition , string orderby );

        /// <summary>
        /// 获取天天付返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        ReturnDayDetailInfo GetDayDetailInfo( int detailID );

        /// <summary>
        /// 删除天天付返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteDayDetail( string sqlQuery );

        /// <summary>
        /// 获取易宝返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetYPDetailList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取易宝返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        ReturnYPDetailInfo GetYPDetailInfo( int detailID );

        /// <summary>
        /// 删除易宝返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteYPDetail( string sqlQuery );

        /// <summary>
        /// 获取VB返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetVBDetailList( int pageIndex , int pageSize , string condition , string orderby );

        /// <summary>
        /// 获取VB返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        ReturnVBDetailInfo GetVBDetailInfo( int detailID );

        /// <summary>
        /// 删除VB返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteVBDetail( string sqlQuery );

        /// <summary>
        /// 获取充值记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetShareDetailList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取充值服务类型
        /// </summary>
        /// <param name="shareID"></param>
        /// <returns></returns>
        GlobalShareInfo GetGlobalShareByShareID(int shareID);

        /// <summary>
        /// 获取充值服务列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGlobalShareList(int pageIndex, int pageSize, string condition, string orderby);

       
       
        #endregion

        #region 用户金币信息
        /// <summary>
        /// 分页获取金币列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetGameScoreInfoList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取用户金币信息
        /// </summary>
        /// <param name="UserID"></param>
        /// <returns></returns>
        GameScoreInfo GetGameScoreInfoByUserID(int UserID);
        /// <summary>
        /// 获取用户的银行金币
        /// </summary>
        /// <param name="UserID">用户标识 </param>
        /// <returns></returns>
        decimal GetGameScoreByUserID( int UserID );
        /// <summary>
        /// 更新用户银行金币
        /// </summary>
        /// <param name="gameScoreInfo"></param>
        void UpdateInsureScore( GameScoreInfo gameScoreInfo );
        /// <summary>
        /// 批量赠送金币
        /// </summary>       
        /// <param name="strUserIdList">赠送对象</param>
        /// <param name="intGold">赠送金额</param>
        /// <param name="intMasterID">操作者ID</param>
        /// <param name="strReason">赠送原因</param>
        /// <param name="strIP">IP地址</param>
        /// <returns></returns>
        Message GrantTreasure( string strUserIdList, int intGold, int intMasterID, string strReason, string strIP );
        /// <summary>
        /// 赠送积分
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="kindID"></param>
        /// <param name="score"></param>
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        Message GrantScore( int userID, int kindID, int score, int masterID, string strReason, string strIP );
        /// <summary>
        /// 清零积分
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="kindID"></param>      
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        Message GrantClearScore( int userID, int kindID, int masterID, string strReason, string strIP );
        /// <summary>
        /// 清零逃率
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="kindID"></param>      
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        Message GrantFlee( int userID, int kindID, int masterID, string strReason, string strIP );
        #endregion

        #region 游戏记录
        /// <summary>
        /// 分页获取游戏记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetRecordDrawInfoList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取玩家游戏记录
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetRecordDrawScoreList( int pageIndex, int pageSize, string condition, string orderby );
        #endregion

        #region 用户卡线记录
        /// <summary>
        /// 分页获取卡线记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetGameScoreLockerList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 删除卡线记录
        /// </summary>
        /// <param name="userID"></param>
        void DeleteGameScoreLockerByUserID( int userID );

        /// <summary>
        /// 删除卡线记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameScoreLocker( string sqlQuery );

        /// <summary>
        /// 获取用户卡线信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        GameScoreLocker GetGameScoreLockerByUserID( int userID );

        #endregion
        
        #region 机器人管理

        /// <summary>
        /// 获取机器人列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetAndroidList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取机器人实体
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        AndroidManager GetAndroidInfo(int userID);

        /// <summary>
        /// 新增机器人
        /// </summary>
        /// <param name="android"></param>
        void InsertAndroid(AndroidManager android);

        /// <summary>
        /// 更新机器人
        /// </summary>
        /// <param name="awardType"></param>
        void UpdateAndroid(AndroidManager android);

        /// <summary>
        /// 删除机器人
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteAndroid(string sqlQuery);

        /// <summary>
        /// 冻结或解冻机器人
        /// </summary>
        /// <param name="nullity"></param>
        /// <param name="sqlQuery"></param>
        void NullityAndroid(byte nullity, string sqlQuery);
        #endregion

        #region 用户进出记录

        /// <summary>
        /// 获取进出记录列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetRecordUserInoutList(int pageIndex, int pageSize, string condition, string orderby);
        #endregion

        #region 用户银行记录

        /// <summary>
        /// 获取用户银行记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetRecordInsureList(int pageIndex, int pageSize, string condition, string orderby);
        #endregion

        #region 推广管理
        /// <summary>
        /// 获取推广配置信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        GlobalSpreadInfo GetGlobalSpreadInfo( int id );
        /// <summary>
        /// 更新推广配置信息
        /// </summary>
        /// <param name="spreadinfo"></param>
        void UpdateGlobalSpreadInfo( GlobalSpreadInfo spreadinfo );

        /// <summary>
        /// 获取推广财务列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetRecordSpreadInfoList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取推广员的推广总收入金币
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        int GetSpreadScore( int userID );
        #endregion

        #region 道具管理
        /// <summary>
        /// 获取道具列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGamePropertyList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 获取道具实体
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        GameProperty GetGamePropertyInfo( int id );
        /// <summary>
        /// 更新道具
        /// </summary>
        /// <param name="property"></param>
        void UpdateGameProperty( GameProperty property );

        /// <summary>
        /// 删除道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameProperty( string sqlQuery );
        /// <summary>
        /// 禁用道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetPropertyDisbale( string sqlQuery );

        /// <summary>
        /// 启用道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetPropertyEnbale( string sqlQuery );
        #endregion  

        #region 汇总统计
        /// <summary>
        /// 获取统计信息
        /// </summary>
        /// <returns></returns>
        DataSet GetStatInfo( );
        /// <summary>
        /// 获取每个游戏税收
        /// </summary>
        /// <returns></returns>
        DataTable GetGameRevenue( );
        /// <summary>
        /// 获取每个房间税收
        /// </summary>
        /// <returns></returns>
        DataTable GetRoomRevenue( );
        /// <summary>
        /// 获取每个游戏损耗
        /// </summary>
        /// <returns></returns>
        DataTable GetGameWaste( );
        /// <summary>
        /// 获取每个房间损耗
        /// </summary>
        /// <returns></returns>
        DataTable GetRoomWaste( );
        #endregion

        #region 公共

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        int ExecuteSql( string sql );

        /// <summary>
        ///  执行sql返回DataSet
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        DataSet GetDataSetBySql( string sql );

        /// <summary>
        /// 执行SQL语句返回一个值
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        string GetScalarBySql( string sql );
        
        #endregion
    }
}
