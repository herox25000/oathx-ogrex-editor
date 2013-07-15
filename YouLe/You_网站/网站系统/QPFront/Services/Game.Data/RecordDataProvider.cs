using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using Game.Entity.Record;

namespace Game.Data
{
    /// <summary>
    /// 记录库数据访问层
    /// </summary>
    public class RecordDataProvider : BaseDataProvider, IRecordDataProvider
    {
        #region 构造方法

        public RecordDataProvider(string connString)
            : base(connString)
        {

        }
        #endregion

        #region  查询记录

        /// <summary>
        /// 魅力兑换记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetLovesRecord( string whereQuery , int pageIndex , int pageSize )
        {
            string orderQuery = "ORDER By CollectDate DESC";
            string[] returnField = new string[11] { "RecordID" , "UserID" , "KindID" , "ServerID" , "CurInsureScore" , "CurPresent" , "ConvertPresent" , "ConvertRate" , "IsGamePlaza" , "ClientIP" , "CollectDate" };
            PagerParameters pager = new PagerParameters( RecordConvertPresent.Tablename , orderQuery , whereQuery , pageIndex , pageSize );
            pager.Fields = returnField;
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        /// <summary>
        /// 奖牌兑换记录
        /// </summary>
        /// <param name="whereQuery">查询条件</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <returns></returns>
        public PagerSet GetMedalConvertRecord( string whereQuery , int pageIndex , int pageSize )
        {
            string orderQuery = "ORDER By CollectDate DESC";
            string[] returnField = new string[9] { "RecordID" , "UserID" , "CurInsureScore" , "CurUserMedal" , "ConvertUserMedal" , "ConvertRate" , "IsGamePlaza" , "ClientIP" , "CollectDate" };
            PagerParameters pager = new PagerParameters( RecordConvertUserMedal.Tablename , orderQuery , whereQuery , pageIndex , pageSize );
            pager.Fields = returnField;
            pager.CacherSize = 2;
            return GetPagerSet2( pager );
        }

        #endregion
        
    }
}
