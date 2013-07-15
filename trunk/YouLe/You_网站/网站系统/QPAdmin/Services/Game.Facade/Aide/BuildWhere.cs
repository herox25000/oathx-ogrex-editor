using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Game.Utils
{
    public class BuildWheres
    {
        object obj;

        public BuildWheres()
        {
            obj = " where ";
        }

        public void Append( string where)
        {
            if ( obj.ToString( ).Trim()!="where" )
            {
                obj = obj + " and " + where;
            }
            else
            {
                obj = obj + where;
            }
        }

        public override string ToString( )
        {
            if ( obj == null || obj.ToString().Trim() =="where" )
            {
                return "";
            }
            else
            {
                return obj.ToString( );
            }
        }
    }
}
