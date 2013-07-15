using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.IData;
using Game.Data.Factory;
using Game.Kernel;
using Game.Entity.Record;

namespace Game.Facade
{
    /// <summary>
    /// 记录库外观
    /// </summary>
    public class RecordFacade
    {
        #region Fields

        private IRecordDataProvider aideRecordData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public RecordFacade( )
        {
            aideRecordData = ClassFactory.GetIRecordDataProvider( );
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
            return aideRecordData.GetRecordAccountsExpendList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 新增一条记录
        /// </summary>
        /// <param name="actExpend"></param>
        public void InsertRecordAccountsExpend( RecordAccountsExpend actExpend )
        {
            aideRecordData.InsertRecordAccountsExpend( actExpend );
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
            return aideRecordData.GetRecordPasswdExpendList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 新增一条记录
        /// </summary>
        /// <param name="pwExpend"></param>
        public void InsertRecordPasswdExpend( RecordPasswdExpend pwExpend )
        {
            aideRecordData.InsertRecordPasswdExpend( pwExpend );

        }
        /// <summary>
        /// 获取密码修改记录
        /// </summary>
        /// <param name="rid">记录ID</param>
        /// <returns></returns>
        public RecordPasswdExpend GetRecordPasswdExpendByRid( int rid )
        {
            return aideRecordData.GetRecordPasswdExpendByRid( rid );
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
            return aideRecordData.ConfirmPass( rid, password, type );
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
            return aideRecordData.GetRecordGrantTreasureList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 新增一条赠送金币记录
        /// </summary>
        /// <param name="grantTreasure"></param>
        public void InsertRecordGrantTreasure( RecordGrantTreasure grantTreasure )
        {
            aideRecordData.InsertRecordGrantTreasure( grantTreasure );
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
            return aideRecordData.GetRecordGrantMemberList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 新增一条赠送会员记录
        /// </summary>
        /// <param name="grantMember"></param>
        public void InsertRecordGrantMember( RecordGrantMember grantMember )
        {
            aideRecordData.InsertRecordGrantMember( grantMember );
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
        public void GrantMember( int userID, int memberOrder, int days, int masterID, string strReason, string strIP )
        {
             aideRecordData.GrantMember( userID, memberOrder, days, masterID, strReason, strIP );
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
           return aideRecordData.GetRecordGrantExperienceList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 新增一条赠送经验记录
        /// </summary>
        /// <param name="grantExperience"></param>
        public void InsertRecordGrantExperience( RecordGrantExperience grantExperience )
        {
            aideRecordData.InsertRecordGrantExperience( grantExperience );
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
            return aideRecordData.GetRecordGrantGameScoreList( pageIndex, pageSize, condition, orderby );
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
            return aideRecordData.GetRecordGrantClearScoreList( pageIndex, pageSize, condition, orderby );
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
            return aideRecordData.GetRecordGrantClearFleeList( pageIndex, pageSize, condition, orderby );
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
            return aideRecordData.GetRecordConvertPresentList( pageIndex, pageSize, condition, orderby );
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
            return aideRecordData.GetRecordGrantGameIDList( pageIndex, pageSize, condition, orderby );
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
            return aideRecordData.GrantGameID( userID, gameID, masterID, strReason, strIP );
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
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string condition , string orderby )
        {
            return aideRecordData.GetList( tableName , pageIndex , pageSize , condition , orderby );
        }

        #endregion
    }
}
