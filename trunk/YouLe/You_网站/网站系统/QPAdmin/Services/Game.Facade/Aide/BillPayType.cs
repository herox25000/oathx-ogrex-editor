using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace Game.Facade
{
    /// <summary>
    /// 快钱支付方式
    /// </summary>
    public class BillPayType
    {
        private string path;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        public BillPayType(string path)
        {
            this.path = path;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="typeID"></param>
        /// <returns></returns>
        public string GetBillPayType(string typeID)
        {
            string Message = "未知支付方式";
            XmlReader reader = XmlReader.Create(path);

            while (reader.Read())
            {
                if (reader.HasAttributes)
                {
                    if (reader.GetAttribute("payTypeID") == typeID)
                    {
                        reader.Read();
                        reader.Read();
                        Message = reader.ReadString();
                        break;
                    }
                }
            }

            reader.Close();
            return Message;
        }
    }
}
