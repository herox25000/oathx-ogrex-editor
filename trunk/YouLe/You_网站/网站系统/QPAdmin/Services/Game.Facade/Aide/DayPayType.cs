using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace Game.Facade
{
    /// <summary>
    /// 读取天天付支付类型XML配置文件类
    /// </summary>
    public class DayPayType
    {
        private string path;

        public DayPayType( string path )
        {
            this.path = path;
        }

        public string GetDayPayType( string typeID )
        {
            string Message = "未知支付方式";
            XmlReader reader = XmlReader.Create( path );

            while ( reader.Read( ) )
            {
                if ( reader.HasAttributes )
                {
                    if ( reader.GetAttribute( "payTypeID" ) == typeID )
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
