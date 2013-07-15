using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using Game.Utils;

namespace Game.Data.Factory
{
    /// <summary>
    /// 数据服务创建工厂
    /// </summary>
    public class ClassFactory
    {
        /// <summary>
        /// 创建后台库对象实例
        /// </summary>
        /// <returns></returns>
        public static IPlatformManagerDataProvider GetIPlatformManagerDataProvider( )
        {
            return ProxyFactory.CreateInstance<PlatformManagerDataProvider>( ApplicationSettings.Get( "DBPlatformManager" ) );
        }

        /// <summary>
        /// 创建前台库对象实例
        /// </summary>
        /// <returns></returns>
        public static INativeWebDataProvider GetINativeWebDataProvider( )
        {
            return ProxyFactory.CreateInstance<NativeWebDataProvider>( ApplicationSettings.Get( "DBNativeWeb" ) );
        }

        /// <summary>
        /// 创建帐号库对象实例
        /// </summary>
        /// <returns></returns>
        public static IAccountsDataProvider IAccountsDataProvider( )
        {
            return ProxyFactory.CreateInstance<AccountsDataProvider>( ApplicationSettings.Get( "DBAccounts" ) );
        }

        /// <summary>
        /// 创建平台库对象实例
        /// </summary>
        /// <returns></returns>
        public static IPlatformDataProvider GetIPlatformDataProvider( )
        {
            return ProxyFactory.CreateInstance<PlatformDataProvider>( ApplicationSettings.Get( "DBPlatform" ) );
        }

        /// <summary>
        /// 创建金币库对象实例
        /// </summary>
        /// <returns></returns>
        public static ITreasureDataProvider GetITreasureDataProvider( )
        {
            return ProxyFactory.CreateInstance<TreasureDataProvider>( ApplicationSettings.Get( "DBTreasure" ) );
        }

        /// <summary>
        /// 创建积分库对象实例
        /// </summary>
        /// <returns></returns>
        public static ITreasureDataProvider GetITreasureDataProvider( int KindID )
        {
            return ProxyFactory.CreateInstance<TreasureDataProvider>( new PlatformDataProvider( ApplicationSettings.Get( "DBPlatform" ) ).GetConn( KindID ) );
        }

        /// <summary>
        /// 创建记录库对象实例
        /// </summary>
        /// <returns></returns>
        public static IRecordDataProvider GetIRecordDataProvider( )  
        {
            return ProxyFactory.CreateInstance<RecordDataProvider>( ApplicationSettings.Get( "DBRecord" ) );
        }

        /// <summary>
        /// 创建游戏库对象实例
        /// </summary>
        /// <returns></returns>
        public static IGameScoreDataProvider GetIGameScoreDataProvider( string conn )
        {
            return ProxyFactory.CreateInstance<GameScoreDataProvider>( conn );
        }

        /// <summary>
        /// 创建比赛库对象实例
        /// </summary>
        /// <returns></returns>
        public static IGameMatchProvider GetIGameMatchProvider( )
        {
            return ProxyFactory.CreateInstance<GameMatchDataProvider>( ApplicationSettings.Get( "DBGameMatch" ) );
        }
    }
}
