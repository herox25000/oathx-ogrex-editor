using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace Game.Facade
{
    /// <summary>
    /// 读取天天付银行类型XML配置文件类
    /// </summary>
    public class DayPayMessage
    {
        public string path;

        public DayPayMessage( string path )
        {
            this.path = path;
        }

        public string GetDayPayMessage( string typeID )
        {
            string Message = "未知原因";
            XmlReader reader = XmlReader.Create( path );

            while ( reader.Read( ) )
            {
                if ( reader.HasAttributes )
                {
                    if ( reader.GetAttribute( "MessageID" ) == typeID )
                    {
                        reader.Read( );
                        reader.Read( );
                        Message = reader.ReadString( );
                        break;
                    }
                }
            }
            reader.Close( );
            return Message;
        }
    }
}
