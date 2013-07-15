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

using Game.Entity.Accounts;
using Game.Entity.Treasure;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.Pay
{
    public partial class PayDay : UCPageBase
    {
        protected void Page_Load( object sender , EventArgs e )
        {
            if ( !IsPostBack )
            {
                if ( Fetch.GetUserCookie( ) != null )
                {
                    this.txtPayAccounts.Text = Fetch.GetUserCookie( ).Accounts;
                    this.txtPayReAccounts.Text = this.txtPayAccounts.Text;
                }
            }
            Themes.Standard.Common_Header sHeader = ( Themes.Standard.Common_Header )this.FindControl( "sHeader" );
            sHeader.title = "充值中心";
        }
    }
}
