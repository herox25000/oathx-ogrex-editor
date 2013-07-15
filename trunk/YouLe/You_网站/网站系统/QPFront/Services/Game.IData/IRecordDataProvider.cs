using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.Accounts;
using System.Data;

namespace Game.IData
{
    /// <summary>
    /// 记录库数据层接口
    /// </summary>
    public interface IRecordDataProvider //: IProvider
    {
        #region 查询记录

        /// <summary>
        /// 魅力兑换记录
        /// </summary>
        /// <param name="whereQuery"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <returns></returns>
        PagerSet GetLovesRecord( string whereQuery , int pageIndex , int pageSize );

          /// <summary>
        /// 奖牌兑换记录
        /// </summary>
        /// <param name="whereQuery">查询条件</param>
        /// <param name="pageIndex">页索引</param>
        /// <param name="pageSize">页大小</param>
        /// <returns></returns>
        PagerSet GetMedalConvertRecord( string whereQuery , int pageIndex , int pageSize );

        #endregion
    }
}
