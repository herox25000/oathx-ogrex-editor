using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Xml;

namespace Game.Facade
{
    /// <summary>
    /// 快钱支持的支付银行
    /// </summary>
    public class BillBanks
    {
        private string path;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        public BillBanks(string path)
        {
            this.path = path;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="bCode"></param>
        /// <returns></returns>
        public string GetBillBanksByCode(string bCode)
        {
            string Message = "未知银行";
            XmlReader reader = XmlReader.Create(path);

            while (reader.Read())
            {
                if (reader.HasAttributes)
                {
                    if (reader.GetAttribute("Code") == bCode)
                    {
                        reader.Read();
                        reader.Read();
                        Message = reader.GetAttribute("CnName");
                        break;
                    }
                }
            }
            reader.Close();
            return Message;
        }
    }
}
