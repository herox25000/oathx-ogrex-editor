using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using Game.Kernel;
using Game.Entity.NativeWeb;


namespace Game.IData
{
    /// <summary>
    /// 后台数据层接口
    /// </summary>
    public interface INativeWebDataProvider //: IProvider
    {

        #region 新闻部分

        /// <summary>
        /// 获取新闻列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetNewsList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取新闻实体
        /// </summary>
        /// <param name="newsID"></param>
        /// <returns></returns>
        News GetNewsInfo(int newsID);

        /// <summary>
        /// 新增新闻
        /// </summary>
        /// <param name="news"></param>
        void InsertNews(News news);

        /// <summary>
        /// 更新新闻
        /// </summary>
        /// <param name="news"></param>
        void UpdateNews(News news);
        
        /// <summary>
        /// 删除新闻
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteNews(string sqlQuery);
        #endregion

        #region 规则部分

        /// <summary>
        /// 获取规则列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGameRulesList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取规则实体
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        GameRulesInfo GetGameRulesInfo(int kindID);

        /// <summary>
        /// 新增规则
        /// </summary>
        /// <param name="gameRules"></param>
        void InsertGameRules(GameRulesInfo gameRules);

        /// <summary>
        /// 更新规则
        /// </summary>
        /// <param name="gameRules">规则实体</param>
        /// <param name="kindID">需要更新规则的游戏</param>
        void UpdateGameRules(GameRulesInfo gameRules,int kindID);

        /// <summary>
        /// 删除规则
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameRules(string sqlQuery);

        /// <summary>
        /// 判断规则是否存在
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        bool JudgeRulesIsExistence( int kindID );

        #endregion

        #region 常见问题部分

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGameIssueList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取问题实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <returns></returns>
        GameIssueInfo GetGameIssueInfo(int issueID);

        /// <summary>
        /// 新增问题
        /// </summary>
        /// <param name="gameIssue"></param>
        void InsertGameIssue(GameIssueInfo gameIssue);

        /// <summary>
        /// 更新问题
        /// </summary>
        /// <param name="gameIssue"></param>
        void UpdateGameIssue(GameIssueInfo gameIssue);

        /// <summary>
        /// 删除问题
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameIssue(string sqlQuery);
        #endregion

        #region 反馈管理

        /// <summary>
        /// 获取反馈列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGameFeedbackList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取反馈实体
        /// </summary>
        /// <param name="feedbackID"></param>
        /// <returns></returns>
        GameFeedbackInfo GetGameFeedbackInfo(int feedbackID);

        /// <summary>
        /// 回复反馈
        /// </summary>
        /// <param name="gameFeedback"></param>
        void RevertGameFeedback(GameFeedbackInfo gameFeedback);

        /// <summary>
        /// 删除反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameFeedback(string sqlQuery);

        /// <summary>
        /// 禁用反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetFeedbackDisbale( string sqlQuery );
        /// <summary>
        /// 启用反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetFeedbackEnbale( string sqlQuery );
        #endregion

        #region 公告部分

        /// <summary>
        /// 获取公告列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetNoticeList(int pageIndex, int pageSize, string condition, string orderby);

        /// <summary>
        /// 获取公告实体
        /// </summary>
        /// <param name="noticeID"></param>
        /// <returns></returns>
        Notice GetNoticeInfo(int noticeID);

        /// <summary>
        /// 新增公告
        /// </summary>
        /// <param name="notice"></param>
        void InsertNotice(Notice notice);

        /// <summary>
        /// 更新公告
        /// </summary>
        /// <param name="notice"></param>
        void UpdateNotice(Notice notice);

        /// <summary>
        /// 删除公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteNotice(string sqlQuery);
        /// <summary>
        /// 禁用公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetNoticeDisbale( string sqlQuery );
        /// <summary>
        /// 启用公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetNoticeEnbale( string sqlQuery );
        #endregion

        #region 比赛管理

        /// <summary>
        /// 获取比赛列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGameMatchInfoList( int pageIndex, int pageSize, string condition, string orderby );

        /// <summary>
        /// 获取比赛实体
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        GameMatchInfo GetGameMatchInfo( int matchID );

        /// <summary>
        /// 新增比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        void InsertGameMatchInfo( GameMatchInfo gameMatch );

        /// <summary>
        /// 更新比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        void UpdateGameMatchInfo( GameMatchInfo gameMatch );

        /// <summary>
        /// 删除比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        void DeleteGameMatchInfo( string sqlQuery );
        /// <summary>
        /// 禁用比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetMatchDisbale( string sqlQuery );
        /// <summary>
        /// 启用比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetMatchEnbale( string sqlQuery );

        /// <summary>
        /// 获取参赛用户列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        PagerSet GetGameMatchUserInfoList( int pageIndex, int pageSize, string condition, string orderby );
        /// <summary>
        /// 禁用参赛用户
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetUserMatchDisbale( string sqlQuery );
        /// <summary>
        /// 启用参赛用户
        /// </summary>
        /// <param name="sqlQuery"></param>
        void SetUserMatchEnbale( string sqlQuery );
        #endregion
    }
}
