using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.Entity.GameScore;

namespace Game.IData
{
    public interface IGameScoreDataProvider
    {
        /// <summary>
        /// 根据用户ID获取积分实体
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns></returns>
        GameScoreInfo GetSocreInfoByUserId( int userId );
    }
}
