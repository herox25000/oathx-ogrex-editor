using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.IData;
using Game.Data.Factory;
using Game.Kernel;
using Game.Entity.GameScore;

namespace Game.Facade.Facade
{
    public class GameScoreFacade
    {
        #region Fields

        private IGameScoreDataProvider aideGameScoreData;

        #endregion

        #region 构造函数

        /// <summary>
        /// 构造函数
        /// </summary>
        public GameScoreFacade( string conn )
        {
            aideGameScoreData = ClassFactory.GetIGameScoreDataProvider( conn );
        }

        #endregion

        /// <summary>
        /// 根据用户ID获取积分实体
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns></returns>
        public GameScoreInfo GetGameScoreInfoByUserId( int userId )
        {
            return aideGameScoreData.GetSocreInfoByUserId( userId );
        }

    }
}
