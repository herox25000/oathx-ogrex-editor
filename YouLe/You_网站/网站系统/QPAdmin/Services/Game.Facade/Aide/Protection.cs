using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace Game.Facade.Aide
{
    /// <summary>
    /// 密码提示问题辅助类
    /// </summary>
    public class Protection
    {
        private string path;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="path"></param>
        public Protection(string path)
        {
            this.path = path;
        }

        public List<string> GetProtectionQuestions()
        {
            List<string> m_protectionQuestiongs = new List<string>();

            DataSet ds = new DataSet();
            ds.ReadXml(path);
            DataRow[] drSet = ds.Tables["Item"].Select("Questions_ID=0");

            foreach (DataRow dr in drSet)
            {
                m_protectionQuestiongs.Add(dr[0].ToString());
            }

            return m_protectionQuestiongs;
        }
    }
}
