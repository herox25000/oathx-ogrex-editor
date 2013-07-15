using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace Game.Facade
{
    /// <summary>
    /// 快钱错误消息
    /// </summary>
    public class BillErrorMsg
    {
        private string path;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        public BillErrorMsg(string path)
        {
            this.path = path;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="errorID"></param>
        /// <returns></returns>
        public string GetBillErrorMsgByErrorID(string errorID)
        {
            string Message = "未知错误";
            XmlReader reader = XmlReader.Create(path);

            while (reader.Read())
            {
                if (reader.HasAttributes)
                {
                    if (reader.GetAttribute("ErrorID") == errorID)
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
