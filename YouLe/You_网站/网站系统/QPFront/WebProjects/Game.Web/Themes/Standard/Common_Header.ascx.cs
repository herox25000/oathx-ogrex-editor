using System;
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
using Game.Utils;

using Game.Facade;

namespace Game.Web.Themes.Standard
{
    public partial class Common_Header : System.Web.UI.UserControl
    {
        public string title = "";
        protected string domain = string.Empty;

        protected void Page_Load(object sender, EventArgs e)
        {
            domain = Utils.GameRequest.GetServerDomain( );
        }
    }
}