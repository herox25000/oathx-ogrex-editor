using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Game.Entity.Platform;

namespace Game.Facade
{
    public class DataAccess
    {
        protected internal PlatformFacade aidePlatformFacade = new PlatformFacade( );
        public string GetConn( int kindID )
        {
            StringBuilder sb = new StringBuilder( );
            GameKindItem gamekind = aidePlatformFacade.GetGameKindItemInfo( kindID );
            GameGameItem game = aidePlatformFacade.GetGameGameItemInfo( gamekind.GameID );
            sb.AppendFormat( "Data Source={0}; Initial Catalog={1}; User ID={2}; Password={3}; Pooling=true", game.DataBaseAddr, game.DataBaseName, "sa", "3112546" );
            return sb.ToString( );
        }
    }
}
