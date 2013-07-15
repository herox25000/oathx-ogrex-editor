using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Game.Entity.Accounts
{
    public class User:UserInfo
    {
        #region

        private AccountsProtect protect;            //密保信息
        private IndividualDatum contact;            //个人联系信息

        #endregion

        #region 公共属性

        /// <summary>
        /// 密保信息
        /// </summary>
        public AccountsProtect Protect
        {
            get { return protect; }
            set { protect = value; }
        }

        /// <summary>
        /// 个人联系信息
        /// </summary>
        public IndividualDatum Contact
        {
            get { return contact; }
            set { contact = value; }
        }

        #endregion

        #region 构造方法

        public User()
        {
            protect = new AccountsProtect();
            contact = new IndividualDatum();
        }

        #endregion


        private long goldScore;

        public long GoldScore
        {
          get { return goldScore; }
          set { goldScore = value; }
        }
    }
}
