using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.Common;

using Game.Kernel;
using Game.IData;
using Game.Entity.Treasure;

namespace Game.Data
{
    /// <summary>
    /// 金币库数据层
    /// </summary>
    public class TreasureDataProvider : BaseDataProvider, ITreasureDataProvider
    {
        #region Fields

        private ITableProvider aideShareDetialProvider;
        private ITableProvider aideGlobalShareProvider;
        private ITableProvider aideOnLineOrderProvider;
        private ITableProvider aideDayDetailProvider;
        private ITableProvider aideKQDetailProvider;
        private ITableProvider aideYPDetailProvider;

        private ITableProvider aideGameScoreInfoProvider;
        private ITableProvider aideRecordDrawInfoProvider;
        private ITableProvider aideRecordDrawScoreProvider;
        private ITableProvider aideGameScoreLockerProvider;

        private ITableProvider aideAndroidProvider;
        private ITableProvider aideGlobalLivcardProvider;
        private ITableProvider aideLivcardAssociatorProvider;
        private ITableProvider aideLivcardBuildStreamProvider;
        private ITableProvider aideGlobalSpreadInfoProvider;
        private ITableProvider aideGamePropertyProvider;
        private ITableProvider aideGameScoreLocker;
        private ITableProvider aideVBDetailProvider;

        #endregion

        #region 构造方法

        public TreasureDataProvider( string connString )
            : base( connString )
        {
            aideShareDetialProvider = GetTableProvider( ShareDetailInfo.Tablename );
            aideGlobalShareProvider = GetTableProvider( GlobalShareInfo.Tablename );
            aideOnLineOrderProvider = GetTableProvider( OnLineOrder.Tablename );
            aideDayDetailProvider = GetTableProvider( ReturnDayDetailInfo.Tablename );
            aideKQDetailProvider = GetTableProvider( ReturnKQDetailInfo.Tablename );
            aideYPDetailProvider = GetTableProvider( ReturnYPDetailInfo.Tablename );
            aideVBDetailProvider = GetTableProvider( ReturnVBDetailInfo.Tablename );

            aideGameScoreInfoProvider = GetTableProvider( GameScoreInfo.Tablename );
            aideRecordDrawInfoProvider = GetTableProvider( RecordDrawInfo.Tablename );
            aideRecordDrawScoreProvider = GetTableProvider( RecordDrawScore.Tablename );
            aideGameScoreLockerProvider = GetTableProvider( GameScoreLocker.Tablename );

            aideAndroidProvider = GetTableProvider( AndroidManager.Tablename );
            aideGlobalLivcardProvider = GetTableProvider( GlobalLivcard.Tablename );
            aideLivcardAssociatorProvider = GetTableProvider( LivcardAssociator.Tablename );
            aideLivcardBuildStreamProvider = GetTableProvider( LivcardBuildStream.Tablename );

            aideGlobalSpreadInfoProvider = GetTableProvider( GlobalSpreadInfo.Tablename );
            aideGamePropertyProvider = GetTableProvider( GameProperty.Tablename );
            aideGameScoreLocker = GetTableProvider( GameScoreLocker.Tablename );
        }
        #endregion

        #region 充值相关

        #region 实卡类型
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
            PagerParameters pagerPrams = new PagerParameters( GlobalLivcard.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 获取实卡类型实体
        /// </summary>
        /// <param name="cardTypeID"></param>
        /// <returns></returns>
        public GlobalLivcard GetGlobalLivcardInfo( int cardTypeID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE CardTypeID= '{0}'", cardTypeID );
            GlobalLivcard globalLivcard = aideGlobalLivcardProvider.GetObject<GlobalLivcard>( sqlQuery );
            return globalLivcard;
        }
        /// <summary>
        /// 新增实卡类型
        /// </summary>
        /// <param name="globalLivcard"></param>
        public void InsertGlobalLivcard( GlobalLivcard globalLivcard )
        {
            DataRow dr = aideGlobalLivcardProvider.NewRow( );

            dr[GlobalLivcard._CardName] = globalLivcard.CardName;
            dr[GlobalLivcard._CardPrice] = globalLivcard.CardPrice;
            dr[GlobalLivcard._CardGold] = globalLivcard.CardGold;
            dr[GlobalLivcard._MemberOrder] = globalLivcard.MemberOrder;
            dr[GlobalLivcard._MemberDays] = globalLivcard.MemberDays;
            dr[GlobalLivcard._UserRight] = globalLivcard.UserRight;
            dr[GlobalLivcard._ServiceRight] = globalLivcard.ServiceRight;

            aideGlobalLivcardProvider.Insert( dr );
        }
        /// <summary>
        /// 更新实卡类型
        /// </summary>
        /// <param name="globalLivcard"></param>
        public void UpdateGlobalLivcard( GlobalLivcard globalLivcard )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GlobalLivcard SET " )
                    .Append( "CardName=@CardName, " )
                    .Append( "CardPrice=@CardPrice, " )
                    .Append( "CardGold=@CardGold, " )
                    .Append( "MemberOrder=@MemberOrder, " )
                    .Append( "MemberDays=@MemberDays, " )
                    .Append( "UserRight=@UserRight, " )
                    .Append( "ServiceRight=@ServiceRight " )
                    .Append( "WHERE CardTypeID=@CardTypeID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "CardName", globalLivcard.CardName ) );
            prams.Add( Database.MakeInParam( "CardPrice", globalLivcard.CardPrice ) );
            prams.Add( Database.MakeInParam( "CardGold", globalLivcard.CardGold ) );
            prams.Add( Database.MakeInParam( "MemberOrder", globalLivcard.MemberOrder ) );
            prams.Add( Database.MakeInParam( "MemberDays", globalLivcard.MemberDays ) );
            prams.Add( Database.MakeInParam( "UserRight", globalLivcard.UserRight ) );
            prams.Add( Database.MakeInParam( "ServiceRight", globalLivcard.ServiceRight ) );
            prams.Add( Database.MakeInParam( "CardTypeID", globalLivcard.CardTypeID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        /// <summary>
        /// 删除实卡类型
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGlobalLivcard( string sqlQuery )
        {
            aideGlobalLivcardProvider.Delete( sqlQuery );
        }
        #endregion
        #region 实卡批次
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
            PagerParameters pagerPrams = new PagerParameters( LivcardBuildStream.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 获取实卡批次实体
        /// </summary>
        /// <param name="buildID"></param>
        /// <returns></returns>
        public LivcardBuildStream GetLivcardBuildStreamInfo( int buildID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE BuildID= '{0}'", buildID );
            LivcardBuildStream livcardBuildStream = aideLivcardBuildStreamProvider.GetObject<LivcardBuildStream>( sqlQuery );
            return livcardBuildStream;
        }
        /// <summary>
        /// 插入实卡批次记录
        /// </summary>
        /// <param name="livcardBuildStream"></param>
        /// <returns></returns>
        public int InsertLivcardBuildStream( LivcardBuildStream livcardBuildStream )
        {
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "AdminName", livcardBuildStream.AdminName ) );
            prams.Add( Database.MakeInParam( "CardTypeID", livcardBuildStream.CardTypeID ) );
            prams.Add( Database.MakeInParam( "CardPrice", livcardBuildStream.CardPrice ) );
            prams.Add( Database.MakeInParam( "CardGold", livcardBuildStream.CardGold ) );
            prams.Add( Database.MakeInParam( "BuildCount", livcardBuildStream.BuildCount ) );
            prams.Add( Database.MakeInParam( "BuildAddr", livcardBuildStream.BuildAddr ) );
            prams.Add( Database.MakeInParam( "NoteInfo", livcardBuildStream.NoteInfo ) );
            prams.Add( Database.MakeInParam( "BuildCardPacket", livcardBuildStream.BuildCardPacket ) );

            object obj;
            Database.RunProc( "WSP_PM_BuildStreamAdd", prams, out obj );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
        }

        /// <summary>
        /// 更新实卡批次记录
        /// </summary>
        /// <param name="livcardBuildStream"></param>
        public void UpdateLivcardBuildStream( LivcardBuildStream livcardBuildStream )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE LivcardBuildStream SET " )
                    .Append( "BuildCardPacket=@BuildCardPacket " )
                    .Append( "WHERE BuildID=@BuildID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "BuildCardPacket", livcardBuildStream.BuildCardPacket ) );
            prams.Add( Database.MakeInParam( "BuildID", livcardBuildStream.BuildID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        /// <summary>
        /// 更新实卡批次导出次数
        /// </summary>
        /// <param name="buildID"></param>
        public void UpdateLivcardBuildStream( int buildID )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE LivcardBuildStream SET " )
                    .Append( "DownLoadCount=DownLoadCount+1 " )
                    .Append( "WHERE BuildID=@BuildID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "BuildID", buildID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        #endregion

        #region 实卡信息
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
            PagerParameters pagerPrams = new PagerParameters( LivcardAssociator.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 获取实卡实体,根据CardID
        /// </summary>
        /// <param name="cardID"></param>
        /// <returns></returns>
        public LivcardAssociator GetLivcardAssociatorInfo( int cardID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE CardID= '{0}'", cardID );
            LivcardAssociator livcardAssociator = aideLivcardAssociatorProvider.GetObject<LivcardAssociator>( sqlQuery );
            return livcardAssociator;
        }
        /// <summary>
        /// 获取实卡实体,根据SerialID
        /// </summary>
        /// <param name="serialID"></param>
        /// <returns></returns>
        public LivcardAssociator GetLivcardAssociatorInfo( string serialID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE SerialID= '{0}'", serialID );
            LivcardAssociator livcardAssociator = aideLivcardAssociatorProvider.GetObject<LivcardAssociator>( sqlQuery );
            return livcardAssociator;
        }
        /// <summary>
        /// 获取实卡充值记录,根据SerialID
        /// </summary>
        /// <param name="serialID"></param>
        /// <returns></returns>
        public ShareDetailInfo GetShareDetailInfo( string serialID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE SerialID= '{0}'" , serialID );
            ShareDetailInfo shareDetailInfo = aideShareDetialProvider.GetObject<ShareDetailInfo>( sqlQuery );
            return shareDetailInfo;
        }
        /// <summary>
        /// 获取实卡的销售商名称，根据批号
        /// </summary>
        /// <param name="buildID"></param>
        /// <returns></returns>
        public string GetSalesperson( int buildID )
        {
            string sqlQuery = string.Format( "SELECT TOP 1 Salesperson FROM LivcardAssociator(NOLOCK) WHERE BuildID= '{0}'", buildID );
            return Database.ExecuteScalarToStr( CommandType.Text, sqlQuery );
        }
        /// <summary>
        /// 禁用实卡
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetCardDisbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE LivcardAssociator SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }

        /// <summary>
        /// 启用实卡
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetCardEnbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE LivcardAssociator SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }

        /// <summary>
        /// 插入实卡记录
        /// </summary>
        /// <param name="livcardAssociator"></param>
        /// <returns></returns>
        public void InsertLivcardAssociator( LivcardAssociator livcardAssociator,string[,] list )
        {
            for ( int i = 0; i < list.GetLength( 0 ); i++ )
            {
                var prams = new List<DbParameter>( );
                prams.Add( Database.MakeInParam( "SerialID" , list[i , 0] ) );
                prams.Add( Database.MakeInParam( "Password" , list[i , 1] ) );
                prams.Add( Database.MakeInParam( "BuildID" , livcardAssociator.BuildID ) );
                prams.Add( Database.MakeInParam( "CardTypeID" , livcardAssociator.CardTypeID ) );
                prams.Add( Database.MakeInParam( "CardPrice" , livcardAssociator.CardPrice ) );
                prams.Add( Database.MakeInParam( "CardGold" , livcardAssociator.CardGold ) );
                prams.Add( Database.MakeInParam( "MemberOrder" , livcardAssociator.MemberOrder ) );
                prams.Add( Database.MakeInParam( "MemberDays" , livcardAssociator.MemberDays ) );
                prams.Add( Database.MakeInParam( "UserRight" , livcardAssociator.UserRight ) );
                prams.Add( Database.MakeInParam( "ServiceRight" , livcardAssociator.ServiceRight ) );

                prams.Add( Database.MakeInParam( "UseRange" , livcardAssociator.UseRange ) );
                prams.Add( Database.MakeInParam( "SalesPerson" , livcardAssociator.SalesPerson ) );
                prams.Add( Database.MakeInParam( "ValidDate" , livcardAssociator.ValidDate ) );

                Database.RunProc( "WSP_PM_LivcardAdd" , prams );
            }
        }

        /// <summary>
        /// 实卡库存统计
        /// </summary>
        /// <returns></returns>
        public DataSet GetLivcardStat( )
        {
            DataSet ds;
            Database.RunProc( "WSP_PM_LivcardStat", out ds );
            return ds;
        }

        /// <summary>
        /// 实卡库存统计
        /// </summary>
        /// <returns></returns>
        public DataSet GetLivcardStatByBuildID( int buildID )
        {
            DataSet ds;
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "BuildID" , buildID ) );
            Database.RunProc( "NET_PM_LivcardStatByBuildID" , prams , out ds );
            return ds;
        }
        #endregion

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
            PagerParameters pagerPrams = new PagerParameters( OnLineOrder.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取订单信息实体
        /// </summary>
        /// <param name="orderID"></param>
        /// <returns></returns>
        public OnLineOrder GetOnLineOrderInfo( string orderID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE OrderID= '{0}'", orderID );
            OnLineOrder onLineOrder = aideOnLineOrderProvider.GetObject<OnLineOrder>( sqlQuery );
            return onLineOrder;
        }

        /// <summary>
        /// 删除订单
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteOnlineOrder( string sqlQuery )
        {
            aideOnLineOrderProvider.Delete( sqlQuery );
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
            PagerParameters pagerPrams = new PagerParameters( ReturnKQDetailInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取快钱返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnKQDetailInfo GetKQDetailInfo( int detailID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE DetailID= {0}", detailID );
            ReturnKQDetailInfo detailInfo = aideKQDetailProvider.GetObject<ReturnKQDetailInfo>( sqlQuery );
            return detailInfo;
        }

        /// <summary>
        /// 删除快钱返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteKQDetail( string sqlQuery )
        {
            aideKQDetailProvider.Delete( sqlQuery );
        }
        /// <summary>
        /// 获取易宝返回记录
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetYPDetailList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( ReturnYPDetailInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取易宝返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnYPDetailInfo GetYPDetailInfo( int detailID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE DetailID= {0}", detailID );
            ReturnYPDetailInfo detailInfo = aideYPDetailProvider.GetObject<ReturnYPDetailInfo>( sqlQuery );
            return detailInfo;
        }

        /// <summary>
        /// 删除易宝返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteYPDetail( string sqlQuery )
        {
            aideYPDetailProvider.Delete( sqlQuery );
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
            PagerParameters pagerPrams = new PagerParameters( ReturnVBDetailInfo.Tablename , orderby , condition , pageIndex , pageSize );       
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取VB返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnVBDetailInfo GetVBDetailInfo( int detailID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE DetailID= {0}" , detailID );
            ReturnVBDetailInfo detailInfo = aideVBDetailProvider.GetObject<ReturnVBDetailInfo>( sqlQuery );
            return detailInfo;
        }

        /// <summary>
        /// 删除VB返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteVBDetail( string sqlQuery )
        {
            aideVBDetailProvider.Delete( sqlQuery );
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
            PagerParameters pagerPrams = new PagerParameters( ReturnDayDetailInfo.Tablename , orderby , condition , pageIndex , pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取天天付返回记录实体
        /// </summary>
        /// <param name="detailID"></param>
        /// <returns></returns>
        public ReturnDayDetailInfo GetDayDetailInfo( int detailID )
        {
            ReturnDayDetailInfo info = new ReturnDayDetailInfo( );
            return info;
        }

        /// <summary>
        /// 删除天天付返回记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteDayDetail( string sqlQuery )
        {
            aideDayDetailProvider.Delete( sqlQuery );
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
            PagerParameters pagerPrams = new PagerParameters( ShareDetailInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取充值服务类型
        /// </summary>
        /// <param name="shareID"></param>
        /// <returns></returns>
        public GlobalShareInfo GetGlobalShareByShareID( int shareID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE ShareID= N'{0}'", shareID );
            GlobalShareInfo globalShare = aideGlobalShareProvider.GetObject<GlobalShareInfo>( sqlQuery );
            return globalShare;
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
            PagerParameters pagerPrams = new PagerParameters( GlobalShareInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
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
            PagerParameters pagerPrams = new PagerParameters( GameScoreInfo.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 获取用户金币信息
        /// </summary>
        /// <param name="UserID"></param>
        /// <returns></returns>
        public GameScoreInfo GetGameScoreInfoByUserID( int UserID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= N'{0}'", UserID );
            GameScoreInfo gameScoreInfo = aideGameScoreInfoProvider.GetObject<GameScoreInfo>( sqlQuery );
            return gameScoreInfo;
        }
        /// <summary>
        /// 获取用户的银行金币
        /// </summary>
        /// <param name="UserID">用户标识 </param>
        /// <returns></returns>
        public decimal GetGameScoreByUserID( int UserID )
        {
            GameScoreInfo gameScoreInfo = GetGameScoreInfoByUserID( UserID );
            if ( gameScoreInfo == null )
                return 0;
            else
                return gameScoreInfo.InsureScore;
        }
        /// <summary>
        /// 更新用户银行金币
        /// </summary>
        /// <param name="gameScoreInfo"></param>
        public void UpdateInsureScore( GameScoreInfo gameScoreInfo )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameScoreInfo SET " )
                    .Append( "InsureScore=@InsureScore " )
                    .Append( "WHERE UserID=@UserID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "InsureScore", gameScoreInfo.InsureScore ) );
            prams.Add( Database.MakeInParam( "UserID", gameScoreInfo.UserID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
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
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "strUserIDList", strUserIdList ) );
            prams.Add( Database.MakeInParam( "dwAddGold", intGold ) );
            prams.Add( Database.MakeInParam( "dwMasterID", intMasterID ) );
            prams.Add( Database.MakeInParam( "strReason", strReason ) );
            prams.Add( Database.MakeInParam( "strClientIP", strIP ) );

            Message msg = MessageHelper.GetMessage( Database, "NET_PM_GrantTreasure", prams );
            return msg;
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
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "UserID", userID ) );
            prams.Add( Database.MakeInParam( "KindID", kindID ) );
            prams.Add( Database.MakeInParam( "AddScore", score ) );
            prams.Add( Database.MakeInParam( "MasterID", masterID ) );
            prams.Add( Database.MakeInParam( "Reason", strReason ) );
            prams.Add( Database.MakeInParam( "ClientIP", strIP ) );

            Message msg = MessageHelper.GetMessage( Database, "WSP_PM_GrantGameScore", prams );
            return msg;
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
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "UserID", userID ) );
            prams.Add( Database.MakeInParam( "KindID", kindID ) );
            prams.Add( Database.MakeInParam( "MasterID", masterID ) );
            prams.Add( Database.MakeInParam( "Reason", strReason ) );
            prams.Add( Database.MakeInParam( "ClientIP", strIP ) );

            Message msg = MessageHelper.GetMessage( Database, "WSP_PM_GrantClearScore", prams );
            return msg;
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
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "UserID", userID ) );
            prams.Add( Database.MakeInParam( "KindID", kindID ) );
            prams.Add( Database.MakeInParam( "MasterID", masterID ) );
            prams.Add( Database.MakeInParam( "Reason", strReason ) );
            prams.Add( Database.MakeInParam( "ClientIP", strIP ) );

            Message msg = MessageHelper.GetMessage( Database, "WSP_PM_GrantClearFlee", prams );
            return msg;
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
            PagerParameters pagerPrams = new PagerParameters( RecordDrawInfo.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
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
            PagerParameters pagerPrams = new PagerParameters( RecordDrawScore.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
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
            PagerParameters pagerPrams = new PagerParameters( GameScoreLocker.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 删除卡线记录
        /// </summary>
        /// <param name="userID"></param>
        public void DeleteGameScoreLockerByUserID( int userID )
        {
            string sqlQuery = string.Format( "WHERE UserID='{0}'", userID );
            aideGameScoreLockerProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 删除卡线记录
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameScoreLocker( string sqlQuery )
        {
            aideGameScoreLockerProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 获取用户卡线信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public GameScoreLocker GetGameScoreLockerByUserID( int userID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= N'{0}'" , userID );
            GameScoreLocker model = aideGameScoreLocker.GetObject<GameScoreLocker>( sqlQuery );
            return model;
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
            PagerParameters pagerPrams = new PagerParameters( AndroidManager.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取机器人实体
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public AndroidManager GetAndroidInfo( int userID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= {0}", userID );
            AndroidManager android = aideAndroidProvider.GetObject<AndroidManager>( sqlQuery );
            return android;
        }

        /// <summary>
        /// 新增机器人
        /// </summary>
        /// <param name="android"></param>
        public void InsertAndroid( AndroidManager android )
        {
            DataRow dr = aideAndroidProvider.NewRow( );

            dr[AndroidManager._UserID] = android.UserID;
            dr[AndroidManager._ServerID] = android.ServerID;
            dr[AndroidManager._MinPlayDraw] = android.MinPlayDraw;
            dr[AndroidManager._MaxPlayDraw] = android.MaxPlayDraw;
            dr[AndroidManager._MinTakeScore] = android.MinTakeScore;
            dr[AndroidManager._MaxTakeScore] = android.MaxTakeScore;
            dr[AndroidManager._MinReposeTime] = android.MinReposeTime;
            dr[AndroidManager._MaxReposeTime] = android.MaxReposeTime;
            dr[AndroidManager._ServiceGender] = android.ServiceGender;
            dr[AndroidManager._ServiceTime] = android.ServiceTime;
            dr[AndroidManager._AndroidNote] = android.AndroidNote;
            dr[AndroidManager._Nullity] = android.Nullity;
            dr[AndroidManager._CreateDate] = android.CreateDate;

            aideAndroidProvider.Insert( dr );
        }

        /// <summary>
        /// 更新机器人
        /// </summary>
        /// <param name="awardType"></param>
        public void UpdateAndroid( AndroidManager android )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE AndroidManager SET " )
                    .Append( "ServerID=@ServerID ," )
                    .Append( "MinPlayDraw=@MinPlayDraw," )
                    .Append( "MaxPlayDraw=@MaxPlayDraw," )
                    .Append( "MinTakeScore=@MinTakeScore," )
                    .Append( "MaxTakeScore=@MaxTakeScore," )
                    .Append( "MinReposeTime=@MinReposeTime," )
                    .Append( "MaxReposeTime=@MaxReposeTime," )
                    .Append( "ServiceGender=@ServiceGender," )
                    .Append( "ServiceTime=@ServiceTime," )
                    .Append( "AndroidNote=@AndroidNote," )
                    .Append( "Nullity=@Nullity " )
                    .Append( "WHERE UserID= @UserID" );
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "ServerID", android.ServerID ) );
            prams.Add( Database.MakeInParam( "MinPlayDraw", android.MinPlayDraw ) );
            prams.Add( Database.MakeInParam( "MaxPlayDraw", android.MaxPlayDraw ) );
            prams.Add( Database.MakeInParam( "MinTakeScore", android.MinTakeScore ) );
            prams.Add( Database.MakeInParam( "MaxTakeScore", android.MaxTakeScore ) );
            prams.Add( Database.MakeInParam( "MinReposeTime", android.MinReposeTime ) );
            prams.Add( Database.MakeInParam( "MaxReposeTime", android.MaxReposeTime ) );
            prams.Add( Database.MakeInParam( "ServiceGender", android.ServiceGender ) );
            prams.Add( Database.MakeInParam( "ServiceTime", android.ServiceTime ) );
            prams.Add( Database.MakeInParam( "AndroidNote", android.AndroidNote ) );
            prams.Add( Database.MakeInParam( "Nullity", android.Nullity ) );

            prams.Add( Database.MakeInParam( "UserID", android.UserID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除机器人
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteAndroid( string sqlQuery )
        {
            aideAndroidProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 冻结或解冻机器人
        /// </summary>
        /// <param name="nullity"></param>
        /// <param name="sqlQuery"></param>
        public void NullityAndroid( byte nullity, string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE AndroidManager SET Nullity={0} {1}", nullity, sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
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
            PagerParameters pagerPrams = new PagerParameters( RecordUserInout.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
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
            PagerParameters pagerPrams = new PagerParameters( RecordInsure.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
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
            string sqlQuery = string.Format( "(NOLOCK) WHERE ID= {0}", id );
            GlobalSpreadInfo spread = aideGlobalSpreadInfoProvider.GetObject<GlobalSpreadInfo>( sqlQuery );
            return spread;
        }
        /// <summary>
        /// 更新推广配置信息
        /// </summary>
        /// <param name="spreadinfo"></param>
        public void UpdateGlobalSpreadInfo( GlobalSpreadInfo spreadinfo )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GlobalSpreadInfo SET " )
                    .Append( "RegisterGrantScore=@RegisterGrantScore ," )
                    .Append( "PlayTimeCount=@PlayTimeCount," )
                    .Append( "PlayTimeGrantScore=@PlayTimeGrantScore," )
                    .Append( "FillGrantRate=@FillGrantRate," )
                    .Append( "BalanceRate=@BalanceRate," )
                    .Append( "MinBalanceScore=@MinBalanceScore " )
                    .Append( "WHERE ID= @ID" );
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "ID", spreadinfo.ID ) );
            prams.Add( Database.MakeInParam( "RegisterGrantScore", spreadinfo.RegisterGrantScore ) );
            prams.Add( Database.MakeInParam( "PlayTimeCount", spreadinfo.PlayTimeCount ) );
            prams.Add( Database.MakeInParam( "PlayTimeGrantScore", spreadinfo.PlayTimeGrantScore ) );
            prams.Add( Database.MakeInParam( "FillGrantRate", spreadinfo.FillGrantRate ) );
            prams.Add( Database.MakeInParam( "BalanceRate", spreadinfo.BalanceRate ) );
            prams.Add( Database.MakeInParam( "MinBalanceScore", spreadinfo.MinBalanceScore ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
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
            PagerParameters pagerPrams = new PagerParameters( RecordSpreadInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 获取推广员的推广总收入金币
        /// </summary>
        /// <param name="userID"></param>
        /// <returns></returns>
        public int GetSpreadScore( int userID )
        {
            string sqlQuery = string.Format( "SELECT ISNULL(SUM(Score),0) FROM RecordSpreadInfo WHERE Score>0 AND UserID= {0}", userID );
            object obj = Database.ExecuteScalar( CommandType.Text, sqlQuery );
            if ( obj == null || obj.ToString( ).Length <= 0 )
                return 0;
            return int.Parse( obj.ToString( ) );
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
            PagerParameters pagerPrams = new PagerParameters( GameProperty.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 获取道具实体
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public GameProperty GetGamePropertyInfo( int id )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE ID= {0}", id );
            GameProperty property = aideGamePropertyProvider.GetObject<GameProperty>( sqlQuery );
            return property;
        }
        /// <summary>
        /// 更新道具
        /// </summary>
        /// <param name="property"></param>
        public void UpdateGameProperty( GameProperty property )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameProperty SET " )
                    .Append( "Name=@Name ," )
                    .Append( "Cash=@Cash," )
                    .Append( "Gold=@Gold," )
                    .Append( "Discount=@Discount," )
                    .Append( "IssueArea=@IssueArea," )
                    .Append( "ServiceArea=@ServiceArea," )
                    .Append( "SendLoveLiness=@SendLoveLiness," )
                    .Append( "RecvLoveLiness=@RecvLoveLiness," )
                    .Append( "RegulationsInfo=@RegulationsInfo," )
                    .Append( "Nullity=@Nullity " )
                    .Append( "WHERE ID= @ID" );
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "ID", property.ID ) );
            prams.Add( Database.MakeInParam( "Name", property.Name ) );
            prams.Add( Database.MakeInParam( "Cash", property.Cash ) );
            prams.Add( Database.MakeInParam( "Gold", property.Gold ) );
            prams.Add( Database.MakeInParam( "Discount", property.Discount ) );
            prams.Add( Database.MakeInParam( "IssueArea", property.IssueArea ) );
            prams.Add( Database.MakeInParam( "ServiceArea", property.ServiceArea ) );
            prams.Add( Database.MakeInParam( "SendLoveLiness", property.SendLoveLiness ) );
            prams.Add( Database.MakeInParam( "RecvLoveLiness", property.RecvLoveLiness ) );
            prams.Add( Database.MakeInParam( "RegulationsInfo", property.RegulationsInfo ) );
            prams.Add( Database.MakeInParam( "Nullity", property.Nullity ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameProperty( string sqlQuery )
        {
            aideGamePropertyProvider.Delete( sqlQuery );
        }
        /// <summary>
        /// 禁用道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetPropertyDisbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameProperty SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }

        /// <summary>
        /// 启用道具
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetPropertyEnbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameProperty SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        #endregion

        #region 汇总统计
        /// <summary>
        /// 获取统计信息
        /// </summary>
        /// <returns></returns>
        public DataSet GetStatInfo( )
        {
            DataSet ds;
            Database.RunProc( "NET_PM_StatInfo", out ds );
            return ds;
        }

        /// <summary>
        /// 获取每个游戏税收
        /// </summary>
        /// <returns></returns>
        public DataTable GetGameRevenue( )
        {
            string sqlQuery = @"SELECT KindID,SUM(Revenue) AS Revenue FROM RecordUserInout(NOLOCK) GROUP BY KindID";
            DataSet ds;
            ds = Database.ExecuteDataset( CommandType.Text, sqlQuery );
            return ds.Tables[0];
        }

        /// <summary>
        /// 获取每个房间税收
        /// </summary>
        /// <returns></returns>
        public DataTable GetRoomRevenue( )
        {
            string sqlQuery = @"SELECT ServerID,SUM(Revenue) AS Revenue FROM RecordUserInout(NOLOCK) GROUP BY ServerID";
            DataSet ds;
            ds = Database.ExecuteDataset( CommandType.Text, sqlQuery );
            return ds.Tables[0];
        }

        /// <summary>
        /// 获取每个游戏损耗
        /// </summary>
        /// <returns></returns>
        public DataTable GetGameWaste( )
        {
            string sqlQuery = @"SELECT KindID,SUM(Waste) AS Waste FROM RecordDrawInfo(NOLOCK) GROUP BY KindID";
            DataSet ds;
            ds = Database.ExecuteDataset( CommandType.Text, sqlQuery );
            return ds.Tables[0];
        }

        /// <summary>
        /// 获取每个房间损耗
        /// </summary>
        /// <returns></returns>
        public DataTable GetRoomWaste( )
        {
            string sqlQuery = @"SELECT ServerID,SUM(Waste) AS Waste FROM RecordDrawInfo(NOLOCK) GROUP BY ServerID";
            DataSet ds;
            ds = Database.ExecuteDataset( CommandType.Text, sqlQuery );
            return ds.Tables[0];
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

        /// <summary>
        ///  执行SQL语句返回DataSet
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        public DataSet GetDataSetBySql( string sql )
        {
            DataSet ds = Database.ExecuteDataset( sql );
            return ds;
        }

        /// <summary>
        /// 执行SQL语句返回一个值
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        public string GetScalarBySql( string sql )
        {
            return Database.ExecuteScalarToStr( CommandType.Text , sql );
        }

        #endregion

    }
}
