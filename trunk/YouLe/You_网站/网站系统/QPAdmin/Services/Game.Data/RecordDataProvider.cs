using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using Game.Entity.Record;
using System.Data;
using Game.Entity.Treasure;
using System.Data.Common;

namespace Game.Data
{
    /// <summary>
    /// 记录库数据层
    /// </summary>
    public class RecordDataProvider : BaseDataProvider, IRecordDataProvider
    {
        #region Fields

        private ITableProvider aideRecordAccountsExpendProvider;
        private ITableProvider aideRecordPasswdExpendProvider;
        private ITableProvider aideRecordGrantTreasureProvider;
        private ITableProvider aideRecordGrantMemberProvider;
        private ITableProvider aideRecordGrantExperienceProvider;
        private ITableProvider aideRecordGrantGameScoreProvider;
        private ITableProvider aideRecordGrantClearScoreProvider;
        private ITableProvider aideRecordGrantClearFleeProvider;
        private ITableProvider aideRecordConvertPresentProvider;

        #endregion

        #region 构造方法

        public RecordDataProvider( string connString )
            : base( connString )
        {
            aideRecordAccountsExpendProvider = GetTableProvider( RecordAccountsExpend.Tablename );
            aideRecordPasswdExpendProvider = GetTableProvider( RecordPasswdExpend.Tablename );
            aideRecordGrantTreasureProvider = GetTableProvider( RecordGrantTreasure.Tablename );
            aideRecordGrantMemberProvider = GetTableProvider( RecordGrantMember.Tablename );
            aideRecordGrantExperienceProvider = GetTableProvider( RecordGrantExperience.Tablename );
            aideRecordGrantGameScoreProvider = GetTableProvider( RecordGrantGameScore.Tablename );
            aideRecordGrantClearScoreProvider = GetTableProvider( RecordGrantClearScore.Tablename );
            aideRecordGrantClearFleeProvider = GetTableProvider( RecordGrantClearFlee.Tablename );
            aideRecordConvertPresentProvider = GetTableProvider( RecordConvertPresent.Tablename );

        }

        #endregion

        #region 历史修改用户名记录
        /// <summary>
        /// 分页获取历史修改用户名记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordAccountsExpendList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordAccountsExpend.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 新增一条记录
        /// </summary>
        /// <param name="actExpend"></param>
        public void InsertRecordAccountsExpend( RecordAccountsExpend actExpend )
        {
            DataRow dr = aideRecordAccountsExpendProvider.NewRow( );

            dr[RecordAccountsExpend._ReAccounts] = actExpend.ReAccounts;
            dr[RecordAccountsExpend._UserID] = actExpend.UserID;
            dr[RecordAccountsExpend._ClientIP] = actExpend.ClientIP;
            dr[RecordAccountsExpend._OperMasterID] = actExpend.OperMasterID;
            dr[RecordAccountsExpend._CollectDate] = DateTime.Now;
            aideRecordAccountsExpendProvider.Insert( dr );
        }
        #endregion

        #region 历史修改密码记录
        /// <summary>
        /// 分页获取历史修改密码记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordPasswdExpendList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordPasswdExpend.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 新增一条记录
        /// </summary>
        /// <param name="pwExpend"></param>
        public void InsertRecordPasswdExpend( RecordPasswdExpend pwExpend )
        {
            DataRow dr = aideRecordPasswdExpendProvider.NewRow( );

            dr[RecordPasswdExpend._ReLogonPasswd] = pwExpend.ReLogonPasswd;
            dr[RecordPasswdExpend._ReInsurePasswd] = pwExpend.ReInsurePasswd;
            dr[RecordPasswdExpend._UserID] = pwExpend.UserID;
            dr[RecordPasswdExpend._ClientIP] = pwExpend.ClientIP;
            dr[RecordPasswdExpend._OperMasterID] = pwExpend.OperMasterID;
            dr[RecordPasswdExpend._CollectDate] = DateTime.Now;
            aideRecordPasswdExpendProvider.Insert( dr );
        }

        /// <summary>
        /// 获取密码修改记录
        /// </summary>
        /// <param name="rid">记录ID</param>
        /// <returns></returns>
        public RecordPasswdExpend GetRecordPasswdExpendByRid( int rid )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE RecordID= N'{0}'", rid );
            RecordPasswdExpend model = aideRecordPasswdExpendProvider.GetObject<RecordPasswdExpend>( sqlQuery );
            return model;
        }
        /// <summary>
        /// 确认密码
        /// </summary>
        /// <param name="rid">记录ID</param>
        /// <param name="password">需要确认的密码（密文）</param>
        /// <param name="type">密码类型，0为登录密码，1为银行密码</param>
        /// <returns></returns>
        public bool ConfirmPass( int rid, string password, int type )
        {
            string sqlWhere = string.Empty;
            if ( type == 0 )
                sqlWhere = string.Format( "WHERE RecordID={0} AND ReLogonPasswd='{1}'", rid, password );
            else
                sqlWhere = string.Format( "WHERE RecordID={0} AND ReInsurePasswd='{1}'", rid, password );
            int count = aideRecordPasswdExpendProvider.GetRecordsCount( sqlWhere );
            if ( count > 0 )
                return true;
            else
                return false;
        }
        #endregion

        #region 赠送金币记录
        /// <summary>
        /// 分页获取赠送金币记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantTreasureList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantTreasure.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 新增一条赠送金币记录
        /// </summary>
        /// <param name="grantTreasure"></param>
        public void InsertRecordGrantTreasure( RecordGrantTreasure grantTreasure )
        {
            DataRow dr = aideRecordGrantTreasureProvider.NewRow( );

            dr[RecordGrantTreasure._MasterID] = grantTreasure.MasterID;
            dr[RecordGrantTreasure._CurGold] = grantTreasure.CurGold;
            dr[RecordGrantTreasure._UserID] = grantTreasure.UserID;
            dr[RecordGrantTreasure._ClientIP] = grantTreasure.ClientIP;
            dr[RecordGrantTreasure._AddGold] = grantTreasure.AddGold;
            dr[RecordGrantTreasure._Reason] = grantTreasure.Reason;
            dr[RecordGrantTreasure._CollectDate] = DateTime.Now;
            aideRecordGrantTreasureProvider.Insert( dr );
        }




        #endregion
        #region 赠送会员记录
        /// <summary>
        /// 分页获取赠送会员记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantMemberList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantMember.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 新增一条赠送会员记录
        /// </summary>
        /// <param name="grantMember"></param>
        public void InsertRecordGrantMember( RecordGrantMember grantMember )
        {
            DataRow dr = aideRecordGrantMemberProvider.NewRow( );

            dr[RecordGrantMember._MasterID] = grantMember.MasterID;
            dr[RecordGrantMember._GrantCardType] = grantMember.GrantCardType;
            dr[RecordGrantMember._UserID] = grantMember.UserID;
            dr[RecordGrantMember._ClientIP] = grantMember.ClientIP;
            dr[RecordGrantMember._MemberDays] = grantMember.MemberDays;
            dr[RecordGrantMember._Reason] = grantMember.Reason;
            dr[RecordGrantMember._CollectDate] = DateTime.Now;
            aideRecordGrantMemberProvider.Insert( dr );
        }
        /// <summary>
        /// 赠送会员
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="memberOrder"></param>
        /// <param name="days"></param>
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        public Message GrantMember( int userID, int memberOrder, int days, int masterID, string strReason, string strIP )
        {
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "UserID", userID ) );
            prams.Add( Database.MakeInParam( "MemberOrder", memberOrder ) );
            prams.Add( Database.MakeInParam( "MemberDays", days ) );
            prams.Add( Database.MakeInParam( "MasterID", masterID ) );
            prams.Add( Database.MakeInParam( "Reason", strReason ) );
            prams.Add( Database.MakeInParam( "ClientIP", strIP ) );

            Message msg = MessageHelper.GetMessage( Database, "WSP_PM_GrantMember", prams );
            return msg;
        }
        #endregion
        #region 赠送经验记录
        /// <summary>
        /// 分页获取赠送经验记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantExperienceList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantExperience.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 新增一条赠送经验记录
        /// </summary>
        /// <param name="grantExperience"></param>
        public void InsertRecordGrantExperience( RecordGrantExperience grantExperience )
        {
            DataRow dr = aideRecordGrantExperienceProvider.NewRow( );

            dr[RecordGrantExperience._MasterID] = grantExperience.MasterID;
            dr[RecordGrantExperience._CurExperience] = grantExperience.CurExperience;
            dr[RecordGrantExperience._UserID] = grantExperience.UserID;
            dr[RecordGrantExperience._ClientIP] = grantExperience.ClientIP;
            dr[RecordGrantExperience._AddExperience] = grantExperience.AddExperience;
            dr[RecordGrantExperience._Reason] = grantExperience.Reason;
            dr[RecordGrantExperience._CollectDate] = DateTime.Now;
            aideRecordGrantExperienceProvider.Insert( dr );
        }
        #endregion
        #region 赠送积分记录
        /// <summary>
        /// 分页获取赠送积分记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantGameScoreList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantGameScore.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        #endregion
        #region 清零积分记录
        /// <summary>
        /// 分页获取清零积分记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantClearScoreList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantClearScore.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        #endregion
        #region 清零逃率记录
        /// <summary>
        /// 分页获取清零逃率记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantClearFleeList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantClearFlee.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        #endregion

        #region 魅力兑换记录
        /// <summary>
        /// 分页获取魅力兑换记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordConvertPresentList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordConvertPresent.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        #endregion

        #region 赠送靓号记录
        /// <summary>
        /// 分页获取赠送靓号记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetRecordGrantGameIDList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( RecordGrantGameID.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 赠送靓号
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="gameID"></param>
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        public Message GrantGameID( int userID, int gameID, int masterID, string strReason, string strIP )
        {
            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "UserID", userID ) );
            prams.Add( Database.MakeInParam( "ReGameID", gameID ) );
            prams.Add( Database.MakeInParam( "MasterID", masterID ) );
            prams.Add( Database.MakeInParam( "Reason", strReason ) );
            prams.Add( Database.MakeInParam( "ClientIP", strIP ) );

            Message msg = MessageHelper.GetMessage( Database, "WSP_PM_GrantGameID", prams );
            return msg;
        }
        #endregion

        #region 公共

        /// <summary>
        /// 分页获取数据列表
        /// </summary>
        /// <param name="tableName"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetList(string tableName, int pageIndex , int pageSize , string condition , string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( tableName , orderby , condition , pageIndex , pageSize );
            return GetPagerSet2( pagerPrams );
        }

        #endregion
    }
}
