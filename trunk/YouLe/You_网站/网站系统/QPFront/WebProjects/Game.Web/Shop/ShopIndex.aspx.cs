﻿using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

using Game.Entity.Accounts;
using Game.Entity.NativeWeb;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Shop
{
    public partial class ShopIndex :UCPageBase
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "兑换商城";

        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("商场首页 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }
    }
}
