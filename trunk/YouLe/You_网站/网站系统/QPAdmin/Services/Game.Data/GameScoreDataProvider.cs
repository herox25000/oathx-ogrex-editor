using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using System.Data;
using Game.Entity.GameScore;
using System.Data.Common;

namespace Game.Data
{
    public class GameScoreDataProvider : BaseDataProvider,IGameScoreDataProvider
    {
        #region Fields

        private ITableProvider aideGameScoreInfo;

        #endregion

        #region 构造方法

        /// <summary>
        /// 构造函数
        /// </summary>
        public GameScoreDataProvider( string connString )
            : base( connString )
        {
            aideGameScoreInfo = GetTableProvider( GameScoreInfo.Tablename );
        }

        #endregion

        /// <summary>
        /// 根据用户ID获取积分实体
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns></returns>
        public GameScoreInfo GetSocreInfoByUserId( int userId )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= N'{0}'" , userId );
            GameScoreInfo model = aideGameScoreInfo.GetObject<GameScoreInfo>( sqlQuery );
            return model;
        }
    }
}
