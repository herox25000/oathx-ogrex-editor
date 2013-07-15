using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Record;

namespace Game.IData
{
    /// <summary>
    /// 记录库数据层接口
    /// </summary>
    public interface IRecordDataProvider //: IProvider
    {
        #region 历史修改用户名记录
        /// <summary>
        /// 分页获取历史修改用户名记录列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        PagerSet GetRecordAccountsExpendList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 新增一条记录
        /// </summary>
        /// <param name="actExpend"></param>
        void InsertRecordAccountsExpend( RecordAccountsExpend actExpend );
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
        PagerSet GetRecordPasswdExpendList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 新增一条记录
        /// </summary>
        /// <param name="pwExpend"></param>
        void InsertRecordPasswdExpend( RecordPasswdExpend pwExpend );
          /// <summary>
        /// 获取密码修改记录
        /// </summary>
        /// <param name="rid">记录ID</param>
        /// <returns></returns>
        RecordPasswdExpend GetRecordPasswdExpendByRid( int rid );
         /// <summary>
        /// 确认密码
        /// </summary>
        /// <param name="rid">记录ID</param>
        /// <param name="password">需要确认的密码（密文）</param>
        /// <param name="type">密码类型，0为登录密码，1为银行密码</param>
        /// <returns></returns>
        bool ConfirmPass( int rid, string password, int type );
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
        PagerSet GetRecordGrantTreasureList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 新增一条赠送金币记录
        /// </summary>
        /// <param name="grantTreasure"></param>
        void InsertRecordGrantTreasure( RecordGrantTreasure grantTreasure );


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
        PagerSet GetRecordGrantMemberList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 新增一条赠送会员记录
        /// </summary>
        /// <param name="grantMember"></param>
        void InsertRecordGrantMember( RecordGrantMember grantMember );
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
        Message GrantMember( int userID, int memberOrder, int days, int masterID, string strReason, string strIP );
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
        PagerSet GetRecordGrantExperienceList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 新增一条赠送经验记录
        /// </summary>
        /// <param name="grantExperience"></param>
        void InsertRecordGrantExperience( RecordGrantExperience grantExperience );
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
        PagerSet GetRecordGrantGameScoreList( int pageIndex, int pageSize, string condition, string orderby );
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
        PagerSet GetRecordGrantClearScoreList( int pageIndex, int pageSize, string condition, string orderby );
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
        PagerSet GetRecordGrantClearFleeList( int pageIndex, int pageSize, string condition, string orderby );
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
        PagerSet GetRecordConvertPresentList( int pageIndex, int pageSize, string condition, string orderby );
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
        PagerSet GetRecordGrantGameIDList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 赠送靓号
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="gameID"></param>
        /// <param name="masterID"></param>
        /// <param name="strReason"></param>
        /// <param name="strIP"></param>
        /// <returns></returns>
        Message GrantGameID( int userID, int gameID, int masterID, string strReason, string strIP );
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
        PagerSet GetList( string tableName , int pageIndex , int pageSize , string condition , string orderby );

        #endregion
    }
}
