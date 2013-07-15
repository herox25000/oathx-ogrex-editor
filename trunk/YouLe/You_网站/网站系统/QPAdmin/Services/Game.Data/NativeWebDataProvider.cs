using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.Common;

using Game.Kernel;
using Game.Utils;
using Game.Entity;
using Game.IData;
using Game.Entity.NativeWeb;

namespace Game.Data
{
    /// <summary>
    /// 网站数据层
    /// </summary>
    public class NativeWebDataProvider : BaseDataProvider, INativeWebDataProvider
    {
        #region Fields

        private ITableProvider aideNewsProvider;
        private ITableProvider aideGameRulesProvider;
        private ITableProvider aideGameIssueProvider;
        private ITableProvider aideGameFeedbackProvider;
        private ITableProvider aideNoticeProvider;
        private ITableProvider aideGameMatchInfoProvider;

        #endregion

        #region 构造方法

        /// <summary>
        /// 构造函数
        /// </summary>
        public NativeWebDataProvider( string connString )
            : base( connString )
        {

            aideNewsProvider = GetTableProvider( News.Tablename );
            aideGameRulesProvider = GetTableProvider( GameRulesInfo.Tablename );
            aideGameIssueProvider = GetTableProvider( GameIssueInfo.Tablename );
            aideGameFeedbackProvider = GetTableProvider( GameFeedbackInfo.Tablename );
            aideNoticeProvider = GetTableProvider( Notice.Tablename );

            aideGameMatchInfoProvider = GetTableProvider( GameMatchInfo.Tablename );

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
        public PagerSet GetNewsList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( News.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取新闻实体
        /// </summary>
        /// <param name="newsID"></param>
        /// <returns></returns>
        public News GetNewsInfo( int newsID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE NewsID= {0}", newsID );
            News news = aideNewsProvider.GetObject<News>( sqlQuery );
            return news;
        }

        /// <summary>
        /// 新增新闻
        /// </summary>
        /// <param name="news"></param>
        public void InsertNews( News news )
        {
            DataRow dr = aideNewsProvider.NewRow( );

            dr[News._NewsID] = news.NewsID;
            dr[News._PopID] = news.PopID;
            dr[News._Subject] = news.Subject;
            dr[News._Subject1] = news.Subject1;
            dr[News._OnTop] = news.OnTop;
            dr[News._OnTopAll] = news.OnTopAll;
            dr[News._IsElite] = news.IsElite;
            dr[News._IsHot] = news.IsHot;
            dr[News._IsLock] = news.IsLock;
            dr[News._IsDelete] = news.IsDelete;
            dr[News._IsLinks] = news.IsLinks;
            dr[News._LinkUrl] = news.LinkUrl;
            dr[News._Body] = news.Body;
            dr[News._FormattedBody] = news.FormattedBody;
            dr[News._HighLight] = news.HighLight;
            dr[News._ClassID] = news.ClassID;
            dr[News._UserID] = news.UserID;
            dr[News._IssueIP] = news.IssueIP;
            dr[News._LastModifyIP] = news.LastModifyIP;
            dr[News._IssueDate] = news.IssueDate;
            dr[News._LastModifyDate] = news.LastModifyDate;

            aideNewsProvider.Insert( dr );
        }

        /// <summary>
        /// 更新新闻
        /// </summary>
        /// <param name="news"></param>
        public void UpdateNews( News news )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE News SET " )
                    .Append( "PopID=@PopID ," )
                    .Append( "Subject=@Subject," )
                    .Append( "Subject1= @Subject1 ," )

                    .Append( "OnTop= @OnTop ," )
                    .Append( "OnTopAll= @OnTopAll," )
                    .Append( "IsElite=@IsElite ," )
                    .Append( "IsHot= @IsHot," )
                    .Append( "IsLock= @IsLock ," )
                    .Append( "IsDelete=@IsDelete," )
                    .Append( "IsLinks=@IsLinks," )
                    .Append( "LinkUrl=@LinkUrl ," )

                    .Append( "Body= @Body ," )
                    .Append( "FormattedBody= @FormattedBody," )

                    .Append( "HighLight= @HighLight," )
                    .Append( "ClassID= @ClassID," )

                    .Append( "UserID=@UserID," )
                    .Append( "IssueIP=@IssueIP," )
                    .Append( "LastModifyIP=@LastModifyIP ," )
                    .Append( "LastModifyDate=@LastModifyDate  " )

                    .Append( "WHERE NewsID= @NewsID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "PopID", news.PopID ) );
            prams.Add( Database.MakeInParam( "Subject", news.Subject ) );
            prams.Add( Database.MakeInParam( "Subject1", news.Subject1 ) );

            prams.Add( Database.MakeInParam( "OnTop", news.OnTop ) );
            prams.Add( Database.MakeInParam( "OnTopAll", news.OnTopAll ) );
            prams.Add( Database.MakeInParam( "IsElite", news.IsElite ) );
            prams.Add( Database.MakeInParam( "IsHot", news.IsHot ) );
            prams.Add( Database.MakeInParam( "IsLock", news.IsLock ) );
            prams.Add( Database.MakeInParam( "IsDelete", news.IsDelete ) );
            prams.Add( Database.MakeInParam( "IsLinks", news.IsLinks ) );
            prams.Add( Database.MakeInParam( "LinkUrl", news.LinkUrl ) );

            prams.Add( Database.MakeInParam( "Body", news.Body ) );
            prams.Add( Database.MakeInParam( "FormattedBody", news.FormattedBody ) );

            prams.Add( Database.MakeInParam( "HighLight", news.HighLight ) );
            prams.Add( Database.MakeInParam( "ClassID", news.ClassID ) );

            prams.Add( Database.MakeInParam( "UserID", news.UserID ) );
            prams.Add( Database.MakeInParam( "IssueIP", news.IssueIP ) );
            prams.Add( Database.MakeInParam( "LastModifyIP", news.LastModifyIP ) );
            prams.Add( Database.MakeInParam( "IssueDate", news.IssueDate ) );
            prams.Add( Database.MakeInParam( "LastModifyDate", news.LastModifyDate ) );

            prams.Add( Database.MakeInParam( "NewsID", news.NewsID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除新闻
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteNews( string sqlQuery )
        {
            aideNewsProvider.Delete( sqlQuery );
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
        public PagerSet GetGameRulesList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameRulesInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取规则实体
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public GameRulesInfo GetGameRulesInfo( int kindID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE KindID= {0}", kindID );
            GameRulesInfo gameRules = aideGameRulesProvider.GetObject<GameRulesInfo>( sqlQuery );
            return gameRules;
        }

        /// <summary>
        /// 新增规则
        /// </summary>
        /// <param name="gameRules"></param>
        public void InsertGameRules( GameRulesInfo gameRules )
        {
            DataRow dr = aideGameRulesProvider.NewRow( );

            dr[GameRulesInfo._KindID] = gameRules.KindID;
            dr[GameRulesInfo._KindName] = gameRules.KindName;
            dr[GameRulesInfo._ImgRuleUrl] = gameRules.ImgRuleUrl;
            dr[GameRulesInfo._HelpIntro] = gameRules.HelpIntro;
            dr[GameRulesInfo._HelpRule] = gameRules.HelpRule;
            dr[GameRulesInfo._HelpGrade] = gameRules.HelpGrade;

            dr[GameRulesInfo._JoinIntro] = gameRules.JoinIntro;
            dr[GameRulesInfo._Nullity] = gameRules.Nullity;
            dr[GameRulesInfo._CollectDate] = gameRules.CollectDate;
            dr[GameRulesInfo._ModifyDate] = gameRules.ModifyDate;

            aideGameRulesProvider.Insert( dr );
        }

        /// <summary>
        /// 更新规则
        /// </summary>
        /// <param name="gameRules">规则实体</param>
        /// <param name="kindID">需要更新规则的游戏ID</param>
        public void UpdateGameRules( GameRulesInfo gameRules,int kindID )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameRulesInfo SET " )
                    .Append( "KindID = @KindID ," )
                    .Append( "KindName = @KindName ," )
                    .Append( "ImgRuleUrl = @ImgRuleUrl," )
                    .Append( "HelpIntro = @HelpIntro ," )
                    .Append( "HelpRule = @HelpRule," )
                    .Append( "HelpGrade = @HelpGrade," )
                    .Append( "JoinIntro = @JoinIntro," )
                    .Append( "Nullity = @Nullity," )
                    .Append( "ModifyDate = @ModifyDate " )
                    .Append( "WHERE KindID = @OldKindID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "KindID" , gameRules.KindID ) );
            prams.Add( Database.MakeInParam( "KindName" , gameRules.KindName ) );
            prams.Add( Database.MakeInParam( "ImgRuleUrl", gameRules.ImgRuleUrl ) );
            prams.Add( Database.MakeInParam( "HelpIntro", gameRules.HelpIntro ) );
            prams.Add( Database.MakeInParam( "HelpRule", gameRules.HelpRule ) );
            prams.Add( Database.MakeInParam( "HelpGrade", gameRules.HelpGrade ) );


            prams.Add( Database.MakeInParam( "JoinIntro", gameRules.JoinIntro ) );
            prams.Add( Database.MakeInParam( "Nullity", gameRules.Nullity ) );
            prams.Add( Database.MakeInParam( "ModifyDate", gameRules.ModifyDate ) );
            prams.Add( Database.MakeInParam( "OldKindID" , kindID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除规则
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameRules( string sqlQuery )
        {
            aideGameRulesProvider.Delete( sqlQuery );
        }

        ///<summary>
        ///判断游戏规则是否存在
        ///</summary>
        ///<paraparam name="kindID">游戏ID</paraparam>
        ///<returns>存在返回true,不存在返回false</returns>
        public bool JudgeRulesIsExistence( int kindID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE KindID= {0}" , kindID );
            GameRulesInfo gameRules = aideGameRulesProvider.GetObject<GameRulesInfo>( sqlQuery );
            if ( gameRules == null )
            {
                return false;
            }
            else
            {
                return true;
            }
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
        public PagerSet GetGameIssueList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameIssueInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取问题实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <returns></returns>
        public GameIssueInfo GetGameIssueInfo( int issueID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE IssueID= {0}", issueID );
            GameIssueInfo gameIssue = aideGameIssueProvider.GetObject<GameIssueInfo>( sqlQuery );
            return gameIssue;
        }

        /// <summary>
        /// 新增问题
        /// </summary>
        /// <param name="gameIssue"></param>
        public void InsertGameIssue( GameIssueInfo gameIssue )
        {
            DataRow dr = aideGameIssueProvider.NewRow( );

            dr[GameIssueInfo._IssueID] = gameIssue.IssueID;
            dr[GameIssueInfo._IssueTitle] = gameIssue.IssueTitle;
            dr[GameIssueInfo._IssueContent] = gameIssue.IssueContent;
            dr[GameIssueInfo._Nullity] = gameIssue.Nullity;
            dr[GameIssueInfo._CollectDate] = gameIssue.CollectDate;
            dr[GameIssueInfo._ModifyDate] = gameIssue.ModifyDate;

            aideGameIssueProvider.Insert( dr );
        }

        /// <summary>
        /// 更新问题
        /// </summary>
        /// <param name="gameIssue"></param>
        public void UpdateGameIssue( GameIssueInfo gameIssue )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameIssueInfo SET " )
                    .Append( "IssueTitle=@IssueTitle ," )
                    .Append( "IssueContent=@IssueContent," )
                    .Append( "Nullity= @Nullity ," )
                    .Append( "ModifyDate= @ModifyDate " )

                    .Append( "WHERE IssueID= @IssueID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "IssueTitle", gameIssue.IssueTitle ) );
            prams.Add( Database.MakeInParam( "IssueContent", gameIssue.IssueContent ) );
            prams.Add( Database.MakeInParam( "Nullity", gameIssue.Nullity ) );
            prams.Add( Database.MakeInParam( "ModifyDate", gameIssue.ModifyDate ) );

            prams.Add( Database.MakeInParam( "IssueID", gameIssue.IssueID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除问题
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameIssue( string sqlQuery )
        {
            aideGameIssueProvider.Delete( sqlQuery );
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
        public PagerSet GetGameFeedbackList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( GameFeedbackInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取反馈实体
        /// </summary>
        /// <param name="feedbackID"></param>
        /// <returns></returns>
        public GameFeedbackInfo GetGameFeedbackInfo( int feedbackID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE FeedbackID= {0}", feedbackID );
            GameFeedbackInfo gameFeedback = aideGameFeedbackProvider.GetObject<GameFeedbackInfo>( sqlQuery );
            return gameFeedback;
        }

        /// <summary>
        /// 回复反馈
        /// </summary>
        /// <param name="gameFeedback"></param>
        public void RevertGameFeedback( GameFeedbackInfo gameFeedback )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameFeedbackInfo SET " )
                    .Append( "RevertUserID=@RevertUserID ," )
                    .Append( "RevertContent=@RevertContent," )
                    .Append( "RevertDate= @RevertDate, " )
                    .Append( "Nullity= @Nullity " )

                    .Append( "WHERE FeedbackID= @FeedbackID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "RevertUserID", gameFeedback.RevertUserID ) );
            prams.Add( Database.MakeInParam( "RevertContent", gameFeedback.RevertContent ) );
            prams.Add( Database.MakeInParam( "RevertDate", gameFeedback.RevertDate ) );
            prams.Add( Database.MakeInParam( "Nullity", gameFeedback.Nullity ) );

            prams.Add( Database.MakeInParam( "FeedbackID", gameFeedback.FeedbackID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameFeedback( string sqlQuery )
        {
            aideGameFeedbackProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 禁用反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetFeedbackDisbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameFeedbackInfo SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 启用反馈
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetFeedbackEnbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameFeedbackInfo SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
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
        public PagerSet GetNoticeList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( Notice.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取公告实体
        /// </summary>
        /// <param name="noticeID"></param>
        /// <returns></returns>
        public Notice GetNoticeInfo( int noticeID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE NoticeID= {0}", noticeID );
            Notice notice = aideNoticeProvider.GetObject<Notice>( sqlQuery );
            return notice;
        }

        /// <summary>
        /// 新增公告
        /// </summary>
        /// <param name="notice"></param>
        public void InsertNotice( Notice notice )
        {
            DataRow dr = aideNoticeProvider.NewRow( );

            dr[Notice._Subject] = notice.Subject;
            dr[Notice._IsLink] = notice.IsLink;
            dr[Notice._LinkUrl] = notice.LinkUrl;
            dr[Notice._Body] = notice.Body;
            dr[Notice._Location] = notice.Location;
            dr[Notice._Width] = notice.Width;
            dr[Notice._Height] = notice.Height;
            dr[Notice._StartDate] = notice.StartDate;
            dr[Notice._OverDate] = notice.OverDate;
            dr[Notice._Nullity] = notice.Nullity;
            aideNoticeProvider.Insert( dr );
        }

        /// <summary>
        /// 更新公告
        /// </summary>
        /// <param name="notice"></param>
        public void UpdateNotice( Notice notice )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE Notice SET " )
                    .Append( "Subject=@Subject ," )
                    .Append( "IsLink=@IsLink," )
                    .Append( "LinkUrl= @LinkUrl ," )
                    .Append( "Body= @Body," )
                    .Append( "Location= @Location," )
                    .Append( "Width=@Width," )
                    .Append( "Height= @Height," )
                    .Append( "StartDate= @StartDate," )
                    .Append( "OverDate=@OverDate," )
                    .Append( "Nullity=@Nullity " )

                    .Append( "WHERE NoticeID= @NoticeID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "Subject", notice.Subject ) );
            prams.Add( Database.MakeInParam( "IsLink", notice.IsLink ) );
            prams.Add( Database.MakeInParam( "LinkUrl", notice.LinkUrl ) );
            prams.Add( Database.MakeInParam( "Body", notice.Body ) );
            prams.Add( Database.MakeInParam( "Location", notice.Location ) );
            prams.Add( Database.MakeInParam( "Width", notice.Width ) );
            prams.Add( Database.MakeInParam( "Height", notice.Height ) );
            prams.Add( Database.MakeInParam( "StartDate", notice.StartDate ) );
            prams.Add( Database.MakeInParam( "OverDate", notice.OverDate ) );
            prams.Add( Database.MakeInParam( "Nullity", notice.Nullity ) );

            prams.Add( Database.MakeInParam( "NoticeID", notice.NoticeID ) );
            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteNotice( string sqlQuery )
        {
            aideNoticeProvider.Delete( sqlQuery );
        }
        /// <summary>
        /// 禁用公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetNoticeDisbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE Notice SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 启用公告
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetNoticeEnbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE Notice SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
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
            PagerParameters pagerPrams = new PagerParameters( GameMatchInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取比赛实体
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        public GameMatchInfo GetGameMatchInfo( int matchID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE MatchID= {0}", matchID );
            GameMatchInfo match = aideGameMatchInfoProvider.GetObject<GameMatchInfo>( sqlQuery );
            return match;
        }

        /// <summary>
        /// 新增比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void InsertGameMatchInfo( GameMatchInfo gameMatch )
        {
            DataRow dr = aideGameMatchInfoProvider.NewRow( );

            dr[GameMatchInfo._MatchID] = gameMatch.MatchID;
            dr[GameMatchInfo._MatchTitle] = gameMatch.MatchTitle;
            dr[GameMatchInfo._MatchSummary] = gameMatch.MatchSummary;
            dr[GameMatchInfo._MatchContent] = gameMatch.MatchContent;
            dr[GameMatchInfo._ApplyBeginDate] = gameMatch.ApplyBeginDate;
            dr[GameMatchInfo._ApplyEndDate] = gameMatch.ApplyEndDate;
            dr[GameMatchInfo._MatchStatus] = gameMatch.MatchStatus;
            dr[GameMatchInfo._Nullity] = gameMatch.Nullity;
            dr[GameMatchInfo._CollectDate] = gameMatch.CollectDate;
            dr[GameMatchInfo._ModifyDate] = gameMatch.ModifyDate;

            aideGameMatchInfoProvider.Insert( dr );
        }

        /// <summary>
        /// 更新比赛
        /// </summary>
        /// <param name="gameMatch"></param>
        public void UpdateGameMatchInfo( GameMatchInfo gameMatch )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE GameMatchInfo SET " )
                    .Append( "MatchTitle=@MatchTitle ," )
                    .Append( "MatchSummary=@MatchSummary," )
                    .Append( "MatchContent= @MatchContent ," )
                    .Append( "ApplyBeginDate= @ApplyBeginDate," )
                    .Append( "ApplyEndDate= @ApplyEndDate," )
                    .Append( "MatchStatus=@MatchStatus," )
                    .Append( "Nullity= @Nullity," )
                    .Append( "ModifyDate=@ModifyDate " )
                    .Append( "WHERE MatchID= @MatchID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "MatchTitle", gameMatch.MatchTitle ) );
            prams.Add( Database.MakeInParam( "MatchSummary", gameMatch.MatchSummary ) );
            prams.Add( Database.MakeInParam( "MatchContent", gameMatch.MatchContent ) );
            prams.Add( Database.MakeInParam( "ApplyBeginDate", gameMatch.ApplyBeginDate ) );
            prams.Add( Database.MakeInParam( "ApplyEndDate", gameMatch.ApplyEndDate ) );
            prams.Add( Database.MakeInParam( "MatchStatus", gameMatch.MatchStatus ) );
            prams.Add( Database.MakeInParam( "Nullity", gameMatch.Nullity ) );
            prams.Add( Database.MakeInParam( "ModifyDate", gameMatch.ModifyDate ) );
            prams.Add( Database.MakeInParam( "MatchID", gameMatch.MatchID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }

        /// <summary>
        /// 删除比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteGameMatchInfo( string sqlQuery )
        {
            aideGameMatchInfoProvider.Delete( sqlQuery );
        }
        /// <summary>
        /// 禁用比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetMatchDisbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameMatchInfo SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 启用比赛
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetMatchEnbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameMatchInfo SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
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
            PagerParameters pagerPrams = new PagerParameters( GameMatchUserInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }
        /// <summary>
        /// 禁用参赛用户
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetUserMatchDisbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameMatchUserInfo SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 启用参赛用户
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void SetUserMatchEnbale( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE GameMatchUserInfo SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        #endregion
    }
}
