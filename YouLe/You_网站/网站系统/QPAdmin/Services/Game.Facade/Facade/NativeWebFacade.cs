using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

using Game.Kernel;
using Game.IData;
using Game.Data.Factory;
using Game.Entity;
using Game.Utils;
using Game.Entity.NativeWeb;

namespace Game.Facade
{
    /// <summary>
    /// 后台外观
    /// </summary>
    public class NativeWebFacade //: BaseFacadeProvider
    {
        #region Fields

        private INativeWebDataProvider aideNativeWebData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public NativeWebFacade( )
        {
            aideNativeWebData = ClassFactory.GetINativeWebDataProvider();
        }
        #endregion   

        #region 新闻部分

        /// <summary>
        /// 获取新闻列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetNewsList(int pageIndex, int pageSize, string condition, string orderby)
        {
            return aideNativeWebData.GetNewsList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取新闻实体
        /// </summary>
        /// <param name="newsID"></param>
        /// <returns></returns>
        public News GetNewsInfo(int newsID)
        {
            return aideNativeWebData.GetNewsInfo(newsID);
        }

        /// <summary>
        /// 新增新闻
        /// </summary>
        /// <param name="news"></param>
        public Message InsertNews(News news)
        {
            aideNativeWebData.InsertNews(news);
            return new Message(true);
        }

        /// <summary>
        /// 更新新闻
        /// </summary>
        /// <param name="news"></param>
        public Message UpdateNews(News news)
        {
            aideNativeWebData.UpdateNews(news);
            return new Message(true);
        }

        /// <summary>
        /// 删除新闻
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteNews(string sqlQuery)
        {
            aideNativeWebData.DeleteNews(sqlQuery);
        }
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
        public PagerSet GetGameRulesList(int pageIndex, int pageSize, string condition, string orderby)
        {
            return aideNativeWebData.GetGameRulesList(pageIndex, pageSize, condition, orderby);
        }

        /// <summary>
        /// 获取规则实体
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public GameRulesInfo GetGameRulesInfo(int kindID)
        {
            return aideNativeWebData.GetGameRulesInfo(kindID);
        }

        /// <summary>
        /// 新增规则
        /// </summary>
        /// <param name="gameRules"></param>
        public Message InsertGameRules(GameRulesInfo gameRules)
        {
            aideNativeWebData.InsertGameRules(gameRules);
            return new Message(true);
        }

        /// <summary>
        /// 更新规则
        /// </summary>
        /// <param name="gameRules"></param>
        public Message UpdateGameRules(GameRulesInfo gameRules,int kindID)
        {
            aideNativeWebData.UpdateGameRules( gameRules , kindID );
            return new Message(true);
        }

        /// <summary>
        /// 删除规则
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameRules(string sqlQuery)
        {
            aideNativeWebData.DeleteGameRules(sqlQuery);
        }

        /// <summary>
        /// 判断游戏规则是否存在
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public bool JudgeRulesIsExistence( int kindID )
        {
            return aideNativeWebData.JudgeRulesIsExistence( kindID );
        }
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
        public PagerSet GetGameIssueList(int pageIndex, int pageSize, string condition, string orderby)
        {
            return aideNativeWebData.GetGameIssueList(pageIndex, pageSize, condition, orderby);
        }

        /// <summary>
        /// 获取问题实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <returns></returns>
        public GameIssueInfo GetGameIssueInfo(int issueID)
        {
            return aideNativeWebData.GetGameIssueInfo(issueID);
        }

        /// <summary>
        /// 新增问题
        /// </summary>
        /// <param name="gameIssue"></param>
        public Message InsertGameIssue(GameIssueInfo gameIssue)
        {
            aideNativeWebData.InsertGameIssue(gameIssue);
            return new Message(true);
        }

        /// <summary>
        /// 更新问题
        /// </summary>
        /// <param name="gameIssue"></param>
        public Message UpdateGameIssue(GameIssueInfo gameIssue)
        {
            aideNativeWebData.UpdateGameIssue(gameIssue);
            return new Message(true);
        }

        /// <summary>
        /// 删除问题
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameIssue(string sqlQuery)
        {
            aideNativeWebData.DeleteGameIssue(sqlQuery);
        }
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
        public PagerSet GetGameFeedbackList(int pageIndex, int pageSize, string condition, string orderby)
        {
            return aideNativeWebData.GetGameFeedbackList(pageIndex, pageSize, condition, orderby);
        }

        /// <summary>
        /// 获取反馈实体
        /// </summary>
        /// <param name="feedbackID"></param>
        /// <returns></returns>
        public GameFeedbackInfo GetGameFeedbackInfo(int feedbackID)
        {
            return aideNativeWebData.GetGameFeedbackInfo(feedbackID);
        }

        /// <summary>
        /// 回复反馈
        /// </summary>
        /// <param name="gameFeedback"></param>
        public Message RevertGameFeedback(GameFeedbackInfo gameFeedback)
        {
            aideNativeWebData.RevertGameFeedback(gameFeedback);
            return new Message(true);
        }

        /// <summary>
        /// 删除反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameFeedback(string sqlQuery)
        {
            aideNativeWebData.DeleteGameFeedback(sqlQuery);
        }

        /// <summary>
        /// 禁用反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetFeedbackDisbale( string sqlQuery )
        {
            aideNativeWebData.SetFeedbackDisbale( sqlQuery );
        }
        /// <summary>
        /// 启用反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetFeedbackEnbale( string sqlQuery )
        {
            aideNativeWebData.SetFeedbackEnbale( sqlQuery );
        }
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
        public PagerSet GetNoticeList(int pageIndex, int pageSize, string condition, string orderby)
        {
            return aideNativeWebData.GetNoticeList(pageIndex, pageSize, condition, orderby);
        }

        /// <summary>
        /// 获取公告实体
        /// </summary>
        /// <param name="noticeID"></param>
        /// <returns></returns>
        public Notice GetNoticeInfo(int noticeID)
        {
            return aideNativeWebData.GetNoticeInfo(noticeID);
        }

        /// <summary>
        /// 新增公告
        /// </summary>
        /// <param name="notice"></param>
        public Message InsertNotice(Notice notice)
        {
            aideNativeWebData.InsertNotice(notice);
            return new Message(true);
        }

        /// <summary>
        /// 更新公告
        /// </summary>
        /// <param name="notice"></param>
        public Message UpdateNotice(Notice notice)
        {
            aideNativeWebData.UpdateNotice(notice);
            return new Message(true);
        }

        /// <summary>
        /// 删除公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteNotice(string sqlQuery)
        {
            aideNativeWebData.DeleteNotice(sqlQuery);
        }
        /// <summary>
        /// 禁用公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetNoticeDisbale( string sqlQuery )
        {
            aideNativeWebData.SetNoticeDisbale( sqlQuery );
        }
        /// <summary>
        /// 启用公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetNoticeEnbale( string sqlQuery )
        {
            aideNativeWebData.SetNoticeEnbale( sqlQuery );
        }
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
        public PagerSet GetGameMatchInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideNativeWebData.GetGameMatchInfoList( pageIndex, pageSize, condition, orderby );
        }

        /// <summary>
        /// 获取比赛实体
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        public GameMatchInfo GetGameMatchInfo( int matchID )
        {
            return aideNativeWebData.GetGameMatchInfo( matchID );
        }

        /// <summary>
        /// 新增比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void InsertGameMatchInfo( GameMatchInfo gameMatch )
        {
            aideNativeWebData.InsertGameMatchInfo( gameMatch );
        }

        /// <summary>
        /// 更新比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void UpdateGameMatchInfo( GameMatchInfo gameMatch )
        {
            aideNativeWebData.UpdateGameMatchInfo( gameMatch );
        }

        /// <summary>
        /// 删除比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameMatchInfo( string sqlQuery )
        {
            aideNativeWebData.DeleteGameMatchInfo( sqlQuery );
        }
        /// <summary>
        /// 禁用比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetMatchDisbale( string sqlQuery )
        {
            aideNativeWebData.SetMatchDisbale( sqlQuery );
        }
        /// <summary>
        /// 启用比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetMatchEnbale( string sqlQuery )
        {
            aideNativeWebData.SetMatchEnbale( sqlQuery );
        }

        /// <summary>
        /// 获取参赛用户列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetGameMatchUserInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            return aideNativeWebData.GetGameMatchUserInfoList( pageIndex, pageSize, condition, orderby );
        }
        /// <summary>
        /// 禁用参赛用户
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetUserMatchDisbale( string sqlQuery )
        {
            aideNativeWebData.SetUserMatchDisbale( sqlQuery );
        }
        /// <summary>
        /// 启用参赛用户
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetUserMatchEnbale( string sqlQuery )
        {
            aideNativeWebData.SetUserMatchEnbale( sqlQuery );
        }
        #endregion
    }
}
