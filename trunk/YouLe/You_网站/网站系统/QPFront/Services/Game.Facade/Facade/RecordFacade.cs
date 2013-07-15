using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Data.Factory;
using Game.IData;
using Game.Kernel;
using Game.Utils;
using Game.Entity.Record;
using System.Data;

namespace Game.Facade
{
    /// <summary>
    /// 记录库外观
    /// </summary>
    public class RecordFacade
    {
        #region Fields

        private IRecordDataProvider recordData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public RecordFacade()
        {
            recordData = ClassFactory.GetIRecordDataProvider();
        }
        #endregion

        #region 查询记录

        /// <summary>
        /// 魅力兑换记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        public PagerSet GetLovesRecord( string whereQuery , int pageIndex , int pageSize )
        {
            return recordData.GetLovesRecord( whereQuery , pageIndex , pageSize );
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
            return recordData.GetMedalConvertRecord( whereQuery , pageIndex , pageSize );
        }

        #endregion
       
    }
}
