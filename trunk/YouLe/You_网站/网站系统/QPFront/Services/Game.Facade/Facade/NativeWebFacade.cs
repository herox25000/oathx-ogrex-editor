using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Data.Factory;
using Game.IData;
using Game.Kernel;
using Game.Utils;
using Game.Entity.NativeWeb;
using System.Data;

namespace Game.Facade
{
    /// <summary>
    /// 网站外观
    /// </summary>
    public class NativeWebFacade
    {
        #region Fields

        private INativeWebDataProvider webData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public NativeWebFacade()
        {
            webData = ClassFactory.GetINativeWebDataProvider();
        }
        #endregion

        #region 网站新闻

        /// <summary>
        /// 获取置顶新闻列表
        /// </summary>
        /// <param name="newsType"></param>
        /// <param name="hot"></param>
        /// <param name="elite"></param>
        /// <param name="top"></param>
        /// <returns></returns>
        public IList<News> GetTopNewsList(int typeID, int hot, int elite, int top)
        {
            return webData.GetTopNewsList(typeID, hot, elite, top);
        }

        /// <summary>
        /// 获取新闻列表
        /// </summary>
        /// <returns></returns>
        public IList<News> GetNewsList()
        {
            return webData.GetNewsList();
        }

        /// <summary>
        /// 获取分页新闻列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetNewsList(int pageIndex, int pageSize)
        {
            return webData.GetNewsList(pageIndex, pageSize);
        }

        /// <summary>
        /// 获取新闻 by newsID
        /// </summary>
        /// <param name="newsID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        public News GetNewsByNewsID(int newsID, byte mode)
        {
            return webData.GetNewsByNewsID(newsID, mode);
        }

        /// <summary>
        /// 获取公告
        /// </summary>
        /// <param name="noticeID"></param>
        /// <returns></returns>
        public Notice GetNotice(int noticeID)
        {
            return webData.GetNotice(noticeID);
        }

        #endregion

        #region 网站问题

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <param name="issueType"></param>
        /// <param name="top"></param>
        /// <returns></returns>
        public IList<GameIssueInfo> GetTopIssueList(int top)
        {
            return webData.GetTopIssueList(top);
        }

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <returns></returns>
        public IList<GameIssueInfo> GetIssueList()
        {
            return webData.GetIssueList();
        }

        /// <summary>
        /// 获取分页问题列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetIssueList(int pageIndex, int pageSize)
        {
            return webData.GetIssueList(pageIndex, pageSize);
        }

        /// <summary>
        /// 获取问题实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        public GameIssueInfo GetIssueByIssueID(int issueID, byte mode)
        {
            return webData.GetIssueByIssueID(issueID, mode);
        }
        #endregion

        #region 反馈意见

        /// <summary>
        /// 获取分页反馈意见列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetFeedbacklist(int pageIndex, int pageSize)
        {
            return webData.GetFeedbacklist(pageIndex, pageSize);
        }

        /// <summary>
        /// 获取反馈意见实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        public GameFeedbackInfo GetGameFeedBackInfo(int feedID, byte mode)
        {
            return webData.GetGameFeedBackInfo(feedID, mode);
        }

        /// <summary>
        /// 更新浏览量
        /// </summary>
        /// <param name="feedID"></param>
        public void UpdateFeedbackViewCount(int feedID)
        {
            webData.UpdateFeedbackViewCount(feedID);
        }

        /// <summary>
        /// 发表留言
        /// </summary>
        /// <returns></returns>
        public Message PublishFeedback(GameFeedbackInfo info)
        {
            return webData.PublishFeedback(info);
        }

        #endregion

        #region 游戏帮助数据

        /// <summary>
        /// 获取推荐游戏详细列表
        /// </summary>
        /// <returns></returns>
        public IList<GameRulesInfo> GetGameHelps(int top)
        {
            return webData.GetGameHelps(top);
        }

        /// <summary>
        /// 获取游戏详细信息
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public GameRulesInfo GetGameHelp(int kindID)
        {
            return webData.GetGameHelp(kindID);
        }

        #endregion

        #region 游戏比赛信息

        /// <summary>
        /// 得到比赛列表
        /// </summary>
        /// <returns></returns>
        public IList<GameMatchInfo> GetMatchList()
        {
            return webData.GetMatchList();
        }

        /// <summary>
        /// 得到比赛详细信息
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        public GameMatchInfo GetMatchInfo(int matchID)
        {
            return webData.GetMatchInfo(matchID);
        }

        /// <summary>
        /// 比赛报名
        /// </summary>
        /// <param name="userInfo"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        public Message AddGameMatch(GameMatchUserInfo userInfo, string password)
        {
            return webData.AddGameMatch(userInfo, password);
        }

        #endregion
    }
}
