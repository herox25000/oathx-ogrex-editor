using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Game.Utils;

namespace Game.Entity.Enum
{
    /// <summary>
    ///道具发行范围
    /// </summary>
    [Serializable]
    [EnumDescription( "道具发行范围" )]
    public enum IssueArea : int
    {
        /// <summary>
        /// 商城道具
        /// </summary>
        [EnumDescription( "商城道具" )]
        A_MALL = 1,

        /// <summary>
        /// 游戏道具
        /// </summary>
        [EnumDescription( "游戏道具" )]
        A_GAME = 2,

        /// <summary>
        /// 房间道具 
        /// </summary>
        [EnumDescription( "房间道具" )]
        A_GAMEROOM = 4

      
    }

    /// <summary>
    /// 辅助类
    /// </summary>
    public class IssueAreaHelper
    {
        /// <summary>
        /// 获取描述
        /// </summary>
        /// <param name="status"></param>
        /// <returns></returns>
        public static string GetIssueAreaDes( IssueArea status )
        {
            return EnumDescription.GetFieldText(status);
        }

        /// <summary>
        /// 获取列表
        /// </summary>
        /// <param name="t"></param>
        /// <returns></returns>
        public static IList<EnumDescription> GetIssueAreaList( Type t )
        {
            IList<EnumDescription> list = EnumDescription.GetFieldTexts(t);
            return list;
        }       
    }
}
