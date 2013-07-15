using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using Game.Entity.NativeWeb;
using System.Data.Common;

namespace Game.Data
{
    /// <summary>
    /// 网站数据访问层
    /// </summary>
    public class NativeWebDataProvider : BaseDataProvider, INativeWebDataProvider
    {
        #region 构造方法

        public NativeWebDataProvider( string connString )
            : base( connString )
        {

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
        public IList<News> GetTopNewsList( int typeID, int hot, int elite, int top )
        {
            StringBuilder sqlQuery = new StringBuilder( )
            .AppendFormat( "SELECT TOP({0}) ", top )
            .Append( "NewsID, Subject,OnTop,OnTopAll,IsElite,IsHot,IsLinks,LinkUrl,HighLight,ClassID,IssueDate,LastModifyDate " )
            .Append( "FROM News " );

            //查询条件
            sqlQuery.Append( " WHERE IsLock=1 AND IsDelete=0 " );

            //新闻类别
            if ( typeID != 0 )
            {
                sqlQuery.AppendFormat( " AND {0}={1} ", "ClassID", typeID );
            }

            //新闻状态            
            if ( hot > 0 )
            {
                sqlQuery.AppendFormat( " AND {0}={1} ", "IsHot", hot );
            }

            if ( elite > 0 )
            {
                sqlQuery.AppendFormat( " AND {0}={1} ", "IsElite", elite );
            }

            //排序
            sqlQuery.Append( " ORDER By OnTopAll DESC,OnTop DESC,IssueDate DESC ,NewsID DESC" );

            return Database.ExecuteObjectList<News>( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 获取新闻列表
        /// </summary>
        /// <returns></returns>
        public IList<News> GetNewsList( )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "SELECT NewsID,Subject,OnTop,OnTopAll,IsElite,IsHot,IsLinks,LinkUrl,ClassID,IssueDate, HighLight " )
                    .Append( "FROM News " )
                    .Append( "WHERE  IsLock=1 AND IsDelete=0 AND IssueDate <= '" )
                    .Append( DateTime.Now.Date.ToString( ) )
                    .Append( "' ORDER By OnTopAll DESC,OnTop DESC,IssueDate DESC ,NewsID DESC" );

            return Database.ExecuteObjectList<News>( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 获取分页新闻列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetNewsList( int pageIndex, int pageSize )
        {
            string whereQuery = "WHERE  IsLock=1 AND IsDelete=0 ";
            string orderQuery = "ORDER By OnTopAll DESC,OnTop DESC,IssueDate DESC ,NewsID DESC";
            string[ ] returnField = new string[11] { "NewsID", "Subject", "OnTop", "OnTopAll", "IsElite", "IsHot", "Islinks", "LinkUrl", "ClassID", "IssueDate", "HighLight" };
            PagerParameters pager = new PagerParameters( News.Tablename, orderQuery, whereQuery, pageIndex, pageSize );

            pager.Fields = returnField;
            pager.CacherSize = 2;

            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取新闻 by newsID
        /// </summary>
        /// <param name="newsID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        public News GetNewsByNewsID( int newsID, byte mode )
        {
            News news = null;

            switch ( mode )
            {
                case 1:
                    List<DbParameter> prams = new List<DbParameter>( );
                    prams.Add( Database.MakeInParam( "dwNewsID", newsID ) );
                    prams.Add( Database.MakeInParam( "dwMode", 1 ) );
                    news = Database.RunProcObject<News>( "NET_PW_GetNewsInfoByID", prams );
                    break;
                case 2:
                    List<DbParameter> pram = new List<DbParameter>( );
                    pram.Add( Database.MakeInParam( "dwNewsID", newsID ) );
                    pram.Add( Database.MakeInParam( "dwMode", 2 ) );
                    news = Database.RunProcObject<News>( "NET_PW_GetNewsInfoByID", pram );
                    break;
                case 0:
                default:
                    news = Database.ExecuteObject<News>( string.Format( "SELECT * FROM News(NOLOCK) WHERE IsLock=1 AND IsDelete=0 AND NewsID={0}", newsID ) );
                    break;
            }

            return news;
        }

        /// <summary>
        /// 获取公告
        /// </summary>
        /// <param name="noticeID"></param>
        /// <returns></returns>
        public Notice GetNotice( int noticeID )
        {
            string sqlQuery = string.Format( "SELECT * FROM Notice(NOLOCK) WHERE NoticeID={0}", noticeID );
            Notice notice = Database.ExecuteObject<Notice>( sqlQuery );
            return notice;
        }

        #endregion

        #region 网站问题

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <param name="issueType"></param>
        /// <param name="top"></param>
        /// <returns></returns>
        public IList<GameIssueInfo> GetTopIssueList( int top )
        {
            StringBuilder sqlQuery = new StringBuilder( )
            .AppendFormat( "SELECT TOP({0}) ", top )
            .Append( "IssueID,IssueTitle,IssueContent,Nullity,CollectDate,ModifyDate " )
            .Append( "FROM GameIssueInfo " );

            //查询条件
            sqlQuery.Append( " WHERE Nullity=0 " );

            //排序
            sqlQuery.Append( " ORDER By CollectDate DESC" );

            return Database.ExecuteObjectList<GameIssueInfo>( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 获取问题列表
        /// </summary>
        /// <returns></returns>
        public IList<GameIssueInfo> GetIssueList( )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "SELECT IssueID,IssueTitle,IssueContent,Nullity,CollectDate,ModifyDate " )
                    .Append( "FROM GameIssueInfo " )
                    .Append( "WHERE  Nullity=0 AND CollectDate <= '" )
                    .Append( DateTime.Now.Date.ToString( ) )
                    .Append( "' ORDER By CollectDate DESC" );

            return Database.ExecuteObjectList<GameIssueInfo>( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 获取分页问题列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetIssueList( int pageIndex, int pageSize )
        {
            string whereQuery = "WHERE  Nullity=0 ";
            string orderQuery = "ORDER By CollectDate DESC";
            string[ ] returnField = new string[6] { "IssueID", "IssueTitle", "IssueContent", "Nullity", "CollectDate", "ModifyDate" };
            PagerParameters pager = new PagerParameters( GameIssueInfo.Tablename, orderQuery, whereQuery, pageIndex, pageSize );

            pager.Fields = returnField;
            pager.CacherSize = 2;

            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取问题实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        public GameIssueInfo GetIssueByIssueID( int issueID, byte mode )
        {
            GameIssueInfo Issue = null;

            switch ( mode )
            {
                case 2:
                    Issue = Database.ExecuteObject<GameIssueInfo>( string.Format( "SELECT * FROM GameIssueInfo(NOLOCK) WHERE Nullity=-0 AND IssueID<{0} ORDER BY CollectDate DESC", issueID ) );
                    break;
                case 1:
                    Issue = Database.ExecuteObject<GameIssueInfo>( string.Format( "SELECT * FROM GameIssueInfo(NOLOCK) WHERE Nullity=0 AND IssueID>{0} ORDER BY CollectDate ASC", issueID ) );
                    break;
                case 0:
                default:
                    Issue = Database.ExecuteObject<GameIssueInfo>( string.Format( "SELECT * FROM GameIssueInfo(NOLOCK) WHERE Nullity=0 AND IssueID={0}", issueID ) );
                    break;
            }

            return Issue;
        }
        #endregion

        #region 反馈意见

        /// <summary>
        /// 获取分页反馈意见列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetFeedbacklist( int pageIndex, int pageSize )
        {
            string whereQuery = "WHERE  Nullity=0 ";
            string orderQuery = "ORDER By FeedbackDate DESC";
            string[ ] returnField = new string[9] { "FeedbackID", "FeedbackTitle", "FeedbackContent", "Nullity", "Accounts", "FeedbackDate", "ViewCount", "RevertContent", "RevertDate" };
            PagerParameters pager = new PagerParameters( GameFeedbackInfo.Tablename, orderQuery, whereQuery, pageIndex, pageSize );

            pager.Fields = returnField;
            pager.CacherSize = 2;

            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 获取反馈意见实体
        /// </summary>
        /// <param name="issueID"></param>
        /// <param name="mode">模式选择, 0=当前主题, 1=上一主题, 2=下一主题</param>
        /// <returns></returns>
        public GameFeedbackInfo GetGameFeedBackInfo( int feedID, byte mode )
        {
            GameFeedbackInfo Issue = null;

            switch ( mode )
            {
                case 1:
                    Issue = Database.ExecuteObject<GameFeedbackInfo>( string.Format( "SELECT * FROM GameFeedbackInfo(NOLOCK) WHERE Nullity=-0 AND FeedbackID<{0} ORDER BY FeedbackID DESC", feedID ) );
                    break;
                case 2:
                    Issue = Database.ExecuteObject<GameFeedbackInfo>( string.Format( "SELECT * FROM GameFeedbackInfo(NOLOCK) WHERE Nullity=0 AND FeedbackID>{0} ORDER BY FeedbackID ASC", feedID ) );
                    break;
                case 0:
                default:
                    Issue = Database.ExecuteObject<GameFeedbackInfo>( string.Format( "SELECT * FROM GameFeedbackInfo(NOLOCK) WHERE Nullity=0 AND FeedbackID={0}", feedID ) );
                    break;
            }

            return Issue;
        }

        /// <summary>
        /// 更新浏览量
        /// </summary>
        /// <param name="feedID"></param>
        public void UpdateFeedbackViewCount( int feedID )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "dwFeedbackID", feedID ) );

            Database.RunProc( "NET_PW_UpdateViewCount", parms );
        }

        /// <summary>
        /// 发表留言
        /// </summary>
        /// <returns></returns>
        public Message PublishFeedback( GameFeedbackInfo info )
        {
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "strAccounts", info.Accounts ) );

            parms.Add( Database.MakeInParam( "strTitle", info.FeedbackTitle ) );
            parms.Add( Database.MakeInParam( "strContent", info.FeedbackContent ) );

            parms.Add( Database.MakeInParam( "strClientIP", info.ClientIP ) );
            parms.Add( Database.MakeOutParam( "strErrorDescribe", typeof( string ), 127 ) );

            return MessageHelper.GetMessage( Database, "NET_PW_AddGameFeedback", parms );
        }

        #endregion

        #region 游戏帮助数据

        /// <summary>
        /// 获取推荐游戏详细列表
        /// </summary>
        /// <returns></returns>
        public IList<GameRulesInfo> GetGameHelps( int top )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.AppendFormat( "SELECT TOP({0}) ", top )
                    .Append( "KindID, KindName, ImgRuleUrl, HelpIntro, HelpRule, HelpGrade, JoinIntro, Nullity, CollectDate, ModifyDate " )
                    .Append( "FROM GameRulesInfo " )
                    .Append( "WHERE  Nullity=0 " )
                    .Append( " ORDER By CollectDate DESC" );

            return Database.ExecuteObjectList<GameRulesInfo>( sqlQuery.ToString( ) );
        }

        /// <summary>
        /// 获取游戏详细信息
        /// </summary>
        /// <param name="kindID"></param>
        /// <returns></returns>
        public GameRulesInfo GetGameHelp( int kindID )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "SELECT KindID, KindName, ImgRuleUrl, HelpIntro, HelpRule, HelpGrade, JoinIntro, Nullity, CollectDate, ModifyDate " )
                    .Append( "FROM GameRulesInfo " )
                    .AppendFormat( "WHERE KindID={0} ", kindID )
                    .Append( " ORDER By CollectDate DESC" );

            return Database.ExecuteObject<GameRulesInfo>( sqlQuery.ToString( ) );
        }

        #endregion

        #region 游戏比赛信息

        /// <summary>
        /// 得到比赛列表
        /// </summary>
        /// <returns></returns>
        public IList<GameMatchInfo> GetMatchList( )
        {
            string sql = "SELECT * FROM GameMatchInfo WHERE Nullity = 0 ORDER BY CollectDate DESC";
            return Database.ExecuteObjectList<GameMatchInfo>( sql );
        }

        /// <summary>
        /// 得到比赛详细信息
        /// </summary>
        /// <param name="matchID"></param>
        /// <returns></returns>
        public GameMatchInfo GetMatchInfo( int matchID )
        {
            string sql = @"SELECT * FROM GameMatchInfo WHERE MatchID = @MatchID";
            List<DbParameter> parms = new List<DbParameter>( );
            parms.Add( Database.MakeInParam( "MatchID", matchID ) );
            return Database.ExecuteObject<GameMatchInfo>( sql, parms );
        }

        /// <summary>
        /// 比赛报名
        /// </summary>
        /// <param name="userInfo"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        public Message AddGameMatch( GameMatchUserInfo userInfo, string password )
        {
            List<DbParameter> prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "dwMatchID", userInfo.MatchID ) );
            prams.Add( Database.MakeInParam( "strAccounts", userInfo.Accounts ) );
            prams.Add( Database.MakeInParam( "strPassword", password ) );
            prams.Add( Database.MakeInParam( "strCompellation", userInfo.Compellation ) );
            prams.Add( Database.MakeInParam( "dwGender", userInfo.Gender ) );
            prams.Add( Database.MakeInParam( "strPassportID", userInfo.PassportID ) );
            prams.Add( Database.MakeInParam( "strMobilePhone", userInfo.MobilePhone ) );
            prams.Add( Database.MakeInParam( "strEMail", userInfo.EMail ) );
            prams.Add( Database.MakeInParam( "strQQ", userInfo.QQ ) );
            prams.Add( Database.MakeInParam( "strDwellingPlace", userInfo.DwellingPlace ) );
            prams.Add( Database.MakeInParam( "strPostalCode", userInfo.PostalCode ) );
            prams.Add( Database.MakeInParam( "strClientIP", userInfo.ClientIP ) );
            prams.Add( Database.MakeOutParam( "strErrorDescribe", typeof( string ), 127 ) );

            return MessageHelper.GetMessage( Database, "NET_PW_AddGameMatchUser", prams );
        }

        #endregion
    }
}
