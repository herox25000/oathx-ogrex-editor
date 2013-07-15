using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.IData;
using Game.Data.Factory;
using Game.Kernel;
using Game.Entity.Treasure;
using System.Data;

namespace Game.Facade
{
    /// <summary>
    /// 金币库外观
    /// </summary>
    public class TreasureFacade
    {
        #region Fields

        private ITreasureDataProvider aideTreasureData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public TreasureFacade( )
        {
            aideTreasureData = ClassFactory.GetITreasureDataProvider( );
        }
        public TreasureFacade( int kindID )
        {
            aideTreasureData = ClassFactory.GetITreasureDataProvider( kindID );
        }
        #endregion

        #region 充值相关
        /// <summary>
        /// 获取实卡类型记录列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGlobalLivcardList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetGlobalLivcardList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取实卡类型实体
        /// </summary>
        /// <param name="cardTypeID"></param>
        /// <returns></returns>
        public GlobalLivcard GetGlobalLivcardInfo( int cardTypeID )
        {
            return aideTreasureData.GetGlobalLivcardInfo( cardTypeID );
        }
        /// <summary>
        /// 新增实卡类型
        /// </summary>
        /// <param name="globalLivcard"></param>
        public Message InsertGlobalLivcard( GlobalLivcard globalLivcard )
        {
            aideTreasureData.InsertGlobalLivcard( globalLivcard );
            return new Message( true );
        }
        /// <summary>
        /// 更新实卡类型
        /// </summary>
        /// <param name="globalLivcard"></param>
        public Message UpdateGlobalLivcard( GlobalLivcard globalLivcard )
        {
            aideTreasureData.UpdateGlobalLivcard( globalLivcard );
            return new Message( true );
        }
        /// <summary>
        /// 删除实卡类型
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGlobalLivcard( string sqlQuery )
        {
            aideTreasureData.DeleteGlobalLivcard( sqlQuery );
        }

        /// <summary>
        /// 获取实卡批次记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetLivcardBuildStreamList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetLivcardBuildStreamList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取实卡批次实体
        /// </summary>
        /// <param name="buildID"></param>
        /// <returns></returns>
        public LivcardBuildStream GetLivcardBuildStreamInfo( int buildID )
        {
            return aideTreasureData.GetLivcardBuildStreamInfo( buildID );
        }
        /// <summary>
        /// 插入实卡批次记录
        /// </summary>
        /// <param name="livcardBuildStream"></param>
        /// <returns></returns>
        public int InsertLivcardBuildStream( LivcardBuildStream livcardBuildStream )
        {
            return aideTreasureData.InsertLivcardBuildStream( livcardBuildStream );
        }
        /// <summary>
        /// 更新实卡批次记录
        /// </summary>
        /// <param name="livcardBuildStream"></param>
        public void UpdateLivcardBuildStream( LivcardBuildStream livcardBuildStream )
        {
            aideTreasureData.UpdateLivcardBuildStream( livcardBuildStream );
        }
        /// <summary>
        /// 更新实卡批次导出次数
        /// </summary>
        /// <param name="buildID"></param>
        public void UpdateLivcardBuildStream( int buildID )
        {
            aideTreasureData.UpdateLivcardBuildStream( buildID );
        }

        /// <summary>
        /// 获取实卡记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetLivcardAssociatorList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetLivcardAssociatorList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取实卡实体,根据CardID
        /// </summary>
        /// <param name="cardID"></param>
        /// <returns></returns>
        public LivcardAssociator GetLivcardAssociatorInfo( int cardID )
        {
            return aideTreasureData.GetLivcardAssociatorInfo( cardID );
        }
        /// <summary>
        /// 获取实卡实体,根据SerialID
        /// </summary>
        /// <param name="serialID"></param>
        /// <returns></returns>
        public LivcardAssociator GetLivcardAssociatorInfo( string serialID )
        {
            return aideTreasureData.GetLivcardAssociatorInfo( serialID );
        }
        /// <summary>
        /// 获取实卡充值记录,根据SerialID
        /// </summary>
        /// <param name="serialID"></param>
        /// <returns></returns>
        public ShareDetailInfo GetShareDetailInfo( string serialID )
        {
            return aideTreasureData.GetShareDetailInfo( serialID );
        }
        /// <summary>
        /// 获取实卡的销售商名称，根据批号
        /// </summary>
        /// <param name="buildID"></param>
        /// <returns></returns>
        public string GetSalesperson( int buildID )
        {
            return aideTreasureData.GetSalesperson( buildID );
        }
        /// <summary>
        /// 禁用实卡
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetCardDisbale( string sqlQuery )
        {
            aideTreasureData.SetCardDisbale( sqlQuery );
        }

        /// <summary>
        /// 启用实卡
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetCardEnbale( string sqlQuery )
        {
            aideTreasureData.SetCardEnbale( sqlQuery );
        }
        /// <summary>
        /// 插入实卡记录
        /// </summary>
        /// <param name="livcardAssociator"></param>
        /// <returns></returns>
        public void InsertLivcardAssociator( LivcardAssociator livcardAssociator , string[,] list )
        {
            aideTreasureData.InsertLivcardAssociator( livcardAssociator , list );
        }
        /// <summary>
        /// 实卡库存统计
        /// </summary>
        /// <returns></returns>
        public DataSet GetLivcardStat( )
        {
            return aideTreasureData.GetLivcardStat( );
        }
        /// <summary>
        /// 实卡库存统计
        /// </summary>
        /// <returns></returns>
        public DataSet GetLivcardStatByBuildID( int buildID )
        {
            return aideTreasureData.GetLivcardStatByBuildID( buildID );
        }
        /// <summary>
        /// 获取订单记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetOnLineOrderList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetOnLineOrderList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取订单信息实体
        /// </summary>
        /// <param name="orderID"></param>
        /// <returns></returns>
        public OnLineOrder GetOnLineOrderInfo( string orderID )
        {
            return aideTreasureData.GetOnLineOrderInfo( orderID );
        }

        /// <summary>
        /// 删除订单
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteOnlineOrder( string sqlQuery )
        {
            aideTreasureData.DeleteOnlineOrder( sqlQuery );
        }

        /// <summary>
        /// 获取快钱返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetKQDetailList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetKQDetailList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取快钱返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnKQDetailInfo GetKQDetailInfo( int detailID )
        {
            return aideTreasureData.GetKQDetailInfo( detailID );
        }

        /// <summary>
        /// 删除快钱返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteKQDetail( string sqlQuery )
        {
            aideTreasureData.DeleteKQDetail( sqlQuery );
        }

        /// <summary>
        /// 获取易宝返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetYPDetailList( int pageIndex , int pageSize , string condition , string orderby )
        {
            return aideTreasureData.GetYPDetailList( pageIndex , pageSize , condition , orderby );
        }

        /// <summary>
        /// 获取易宝返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnYPDetailInfo GetYPDetailInfo( int detailID )
        {
            return aideTreasureData.GetYPDetailInfo( detailID );
        }

        /// <summary>
        /// 删除易宝返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteYPDetail( string sqlQuery )
        {
            aideTreasureData.DeleteYPDetail( sqlQuery );
        }

        /// <summary>
        /// 获取VB返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetVBDetailList( int pageIndex , int pageSize , string condition , string orderby )
        {
            return aideTreasureData.GetVBDetailList( pageIndex , pageSize , condition , orderby );
        }

        /// <summary>
        /// 获取VB返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnVBDetailInfo GetVBDetailInfo( int detailID )
        {
            return aideTreasureData.GetVBDetailInfo( detailID );
        }

        /// <summary>
        /// 删除VB返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteVBDetail( string sqlQuery )
        {
            aideTreasureData.DeleteVBDetail( sqlQuery );
        }


        /// <summary>
        /// 获取天天付返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetDayDetailList( int pageIndex , int pageSize , string condition , string orderby )
        {
            return aideTreasureData.GetDayDetailList( pageIndex , pageSize , condition , orderby );
        }

        /// <summary>
        /// 获取天天付返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnDayDetailInfo GetDayDetailInfo( int detailID )
        {
            return aideTreasureData.GetDayDetailInfo( detailID );
        }

        /// <summary>
        /// 删除天天付返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteDayDetail( string sqlQuery )
        {
            aideTreasureData.DeleteDayDetail( sqlQuery );
        }

        /// <summary>
        /// 获取充值记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetShareDetailList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetShareDetailList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取充值服务类型
        /// </summary>
        /// <param name="shareID"></param>
        /// <returns></returns>
        public GlobalShareInfo GetGlobalShareByShareID( int shareID )
        {
            return aideTreasureData.GetGlobalShareByShareID( shareID );
        }

        /// <summary>
        /// 获取充值服务列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGlobalShareList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetGlobalShareList( pageIndex, pageSize, condition, orderby );
        }

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
        public PagerSet GetGameScoreInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetGameScoreInfoList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取用户金币信息
        /// </summary>
        /// <param name="UserID"></param>
        /// <returns></returns>
        public GameScoreInfo GetGameScoreInfoByUserID( int UserID )
        {
            return aideTreasureData.GetGameScoreInfoByUserID( UserID );
        }
        /// <summary>
        /// 获取用户的银行金币
        /// </summary>
        /// <param name="UserID">用户标识 </param>
        /// <returns></returns>
        public decimal GetGameScoreByUserID( int UserID )
        {
            return aideTreasureData.GetGameScoreByUserID( UserID );
        }
        /// <summary>
        /// 更新用户银行金币
        /// </summary>
        /// <param name="gameScoreInfo"></param>
        public void UpdateInsureScore( GameScoreInfo gameScoreInfo )
        {
            aideTreasureData.UpdateInsureScore( gameScoreInfo );
        }
        /// <summary>
        /// 批量赠送金币
        /// </summary>      
        /// <param name="strUserIdList">赠送对象</param>
        /// <param name="intGold">赠送金额</param>
        /// <param name="intMasterID">操作者ID</param>
        /// <param name="strReason">赠送原因</param>
        /// <param name="strIP">IP地址</param>
        /// <returns></returns>
        public Message GrantTreasure( string strUserIdList, int intGold, int intMasterID, string strReason, string strIP )
        {
            return aideTreasureData.GrantTreasure( strUserIdList, intGold, intMasterID, strReason, strIP );
        }
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
        public Message GrantScore( int userID, int kindID, int score, int masterID, string strReason, string strIP )
        {
            return aideTreasureData.GrantScore( userID, kindID, score, masterID, strReason, strIP );
        }
        /// <summary>
        /// 清零积分
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="kindID"></param>      
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        public Message GrantClearScore( int userID, int kindID, int masterID, string strReason, string strIP )
        {
            return aideTreasureData.GrantClearScore( userID, kindID, masterID, strReason, strIP );
        }
        /// <summary>
        /// 清零逃率
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="kindID"></param>      
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        public Message GrantFlee( int userID, int kindID, int masterID, string strReason, string strIP )
        {
            return aideTreasureData.GrantFlee( userID, kindID, masterID, strReason, strIP );
        }
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
        public PagerSet GetRecordDrawInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetRecordDrawInfoList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取玩家游戏记录
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordDrawScoreList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetRecordDrawScoreList( pageIndex, pageSize, condition, orderby );
        }

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
        public PagerSet GetGameScoreLockerList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetGameScoreLockerList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 删除卡线记录
        /// </summary>
        /// <param name="userID"></param>
        public void DeleteGameScoreLockerByUserID( int userID )
        {
            aideTreasureData.DeleteGameScoreLockerByUserID( userID );
        }

        /// <summary>
        /// 删除卡线记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameScoreLocker( string sqlQuery )
        {
            aideTreasureData.DeleteGameScoreLocker( sqlQuery );
        }

        /// <summary>
        /// 获取用户卡线信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public GameScoreLocker GetGameScoreLockerByUserID( int userID )
        {
            return aideTreasureData.GetGameScoreLockerByUserID( userID );
        }
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
        public PagerSet GetAndroidList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetAndroidList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取机器人实体
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public AndroidManager GetAndroidInfo( int userID )
        {
            return aideTreasureData.GetAndroidInfo( userID );
        }

        /// <summary>
        /// 新增机器人
        /// </summary>
        /// <param name="android"></param>
        public Message InsertAndroid( AndroidManager android )
        {
            aideTreasureData.InsertAndroid( android );
            return new Message( true );
        }

        /// <summary>
        /// 更新机器人
        /// </summary>
        /// <param name="awardType"></param>
        public Message UpdateAndroid( AndroidManager android )
        {
            aideTreasureData.UpdateAndroid( android );
            return new Message( true );
        }

        /// <summary>
        /// 删除机器人
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteAndroid( string sqlQuery )
        {
            aideTreasureData.DeleteAndroid( sqlQuery );
        }

        /// <summary>
        /// 冻结或解冻机器人
        /// </summary>
        /// <param name="nullity"></param>
        /// <param name="sqlQuery"></param>
        public void NullityAndroid( byte nullity, string sqlQuery )
        {
            aideTreasureData.NullityAndroid( nullity, sqlQuery );
        }
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
        public PagerSet GetRecordUserInoutList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetRecordUserInoutList( pageIndex, pageSize, condition, orderby );
        }
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
        public PagerSet GetRecordInsureList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetRecordInsureList( pageIndex, pageSize, condition, orderby );
        }
        #endregion

        #region 推广管理
        /// <summary>
        /// 获取推广配置信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public GlobalSpreadInfo GetGlobalSpreadInfo( int id )
        {
            return aideTreasureData.GetGlobalSpreadInfo( id );
        }
        /// <summary>
        /// 更新推广配置信息
        /// </summary>
        /// <param name="spreadinfo"></param>
        public void UpdateGlobalSpreadInfo( GlobalSpreadInfo spreadinfo )
        {
            aideTreasureData.UpdateGlobalSpreadInfo( spreadinfo );
        }

        /// <summary>
        /// 获取推广财务列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetRecordSpreadInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetRecordSpreadInfoList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取推广员的推广总收入金币
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public int GetSpreadScore( int userID )
        {
            return aideTreasureData.GetSpreadScore( userID );
        }
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
        public PagerSet GetGamePropertyList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideTreasureData.GetGamePropertyList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 获取道具实体
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public GameProperty GetGamePropertyInfo( int id )
        {
            return aideTreasureData.GetGamePropertyInfo( id );
        }
        /// <summary>
        /// 更新道具
        /// </summary>
        /// <param name="property"></param>
        public void UpdateGameProperty( GameProperty property )
        {
            aideTreasureData.UpdateGameProperty( property );
        }

        /// <summary>
        /// 删除道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameProperty( string sqlQuery )
        {
            aideTreasureData.DeleteGameProperty( sqlQuery );
        }
        /// <summary>
        /// 禁用道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetPropertyDisbale( string sqlQuery )
        {
            aideTreasureData.SetPropertyDisbale( sqlQuery );
        }

        /// <summary>
        /// 启用道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetPropertyEnbale( string sqlQuery )
        {
            aideTreasureData.SetPropertyEnbale( sqlQuery );
        }
        #endregion

        #region 汇总统计
        /// <summary>
        /// 获取统计信息
        /// </summary>
        /// <returns></returns>
        public DataSet GetStatInfo( )
        {
            return aideTreasureData.GetStatInfo( );
        }
        /// <summary>
        /// 获取每个游戏税收
        /// </summary>
        /// <returns></returns>
        public DataTable GetGameRevenue( )
        {
            return aideTreasureData.GetGameRevenue( );
        }
        /// <summary>
        /// 获取每个房间税收
        /// </summary>
        /// <returns></returns>
        public DataTable GetRoomRevenue( )
        {
            return aideTreasureData.GetRoomRevenue( );
        }
        /// <summary>
        /// 获取每个游戏损耗
        /// </summary>
        /// <returns></returns>
        public DataTable GetGameWaste( )
        {
            return aideTreasureData.GetGameWaste( );
        }
        /// <summary>
        /// 获取每个房间损耗
        /// </summary>
        /// <returns></returns>
        public DataTable GetRoomWaste( )
        {
            return aideTreasureData.GetRoomWaste( );
        }
        #endregion

        #region 公共

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        public int ExecuteSql( string sql )
        {
            return aideTreasureData.ExecuteSql( sql );
        }

        /// <summary>
        ///  执行sql返回DataSet
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        public DataSet GetDataSetBySql( string sql )
        {
            return aideTreasureData.GetDataSetBySql( sql );
        }

        /// <summary>
        /// 执行SQL语句返回一个值
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        public string GetScalarBySql( string sql )
        {
            return aideTreasureData.GetScalarBySql( sql );
        }

        #endregion
    }
}
