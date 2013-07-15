using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Accounts;
using System.Data;
using Game.Entity.NativeWeb;

namespace Game.IData
{
    /// <summary>
    /// 网站库数据层接口
    /// </summary>
    public interface INativeWebDataProvider //: IProvider
    {
        #region 网站新闻

        /// <summary>
        /// 获取置顶新闻列表
        /// </summary>
        /// <param name="newsType"></param>
        /// <param name="hot"></param>
        /// <param name="elite"></param>
        /// <param name="top"></param>
        /// <returns></returns>
        IList<News> GetTopNewsList(int typeID, int hot, int elite, int top);

        /// <summary>
        /// 获取新闻列表
        /// </summary>
        /// <returns></returns>
        IList<News> GetNewsList();

        /// <summary>
        /// 获取分页新闻列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetNewsList(int pageIndex, int pageSize);

        /// <summary>
        /// 获取新闻 by newsID
        /// </summary>
        /// <param name="newsID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        News GetNewsByNewsID(int newsID, byte mode);

        /// <summary>
        /// 获取公告
        /// </summary>
        /// <param name="noticeID"></param>
        /// <returns></returns>
        Notice GetNotice(int noticeID);

        #endregion

        #region 网站问题

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <param name="issueType"></param>
        /// <param name="top"></param>
        /// <returns></returns>
        IList<GameIssueInfo> GetTopIssueList(int top);

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <returns></returns>
        IList<GameIssueInfo> GetIssueList();

        /// <summary>
        /// 获取分页问题列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetIssueList(int pageIndex, int pageSize);

        /// <summary>
        /// 获取问题实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        GameIssueInfo GetIssueByIssueID(int issueID, byte mode);

        #endregion

        #region 反馈意见

        /// <summary>
        /// 获取分页反馈意见列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetFeedbacklist(int pageIndex, int pageSize);

        /// <summary>
        /// 获取反馈意见实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        GameFeedbackInfo GetGameFeedBackInfo(int feedID, byte mode);

        /// <summary>
        /// 更新浏览量
        /// </summary>
        /// <param name="feedID"></param>
        void UpdateFeedbackViewCount(int feedID);

        /// <summary>
        /// 发表留言
        /// </summary>
        /// <returns></returns>
        Message PublishFeedback(GameFeedbackInfo info);

        #endregion

        #region 游戏帮助数据

        /// <summary>
        /// 获取推荐游戏详细列表
        /// </summary>
        /// <returns></returns>
        IList<GameRulesInfo> GetGameHelps(int top);

        /// <summary>
        /// 获取游戏详细信息
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        GameRulesInfo GetGameHelp(int kindID);

        #endregion

        #region 游戏比赛信息

        /// <summary>
        /// 得到比赛列表
        /// </summary>
        /// <returns></returns>
        IList<GameMatchInfo> GetMatchList();

        /// <summary>
        /// 得到比赛详细信息
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        GameMatchInfo GetMatchInfo(int matchID);

        /// <summary>
        /// 比赛报名
        /// </summary>
        /// <param name="userInfo"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        Message AddGameMatch(GameMatchUserInfo userInfo, string password);

        #endregion
    }
}
