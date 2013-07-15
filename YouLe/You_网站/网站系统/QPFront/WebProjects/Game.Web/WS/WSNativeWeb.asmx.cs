using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Xml.Linq;

using Game.Entity.Accounts;
using Game.Entity.NativeWeb;
using Game.Facade;
using Game.Utils;
using Game.Kernel;
using System.Text;

namespace Game.Web.WS
{
    /// <summary>
    /// WSNativeWeb 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
     [System.Web.Script.Services.ScriptService]
    public class WSNativeWeb : System.Web.Services.WebService
    {
        private NativeWebFacade webFacade = new NativeWebFacade();

        [WebMethod]
        public string GetFeedBack(int feedID)
        {
            GameFeedbackInfo feedback = webFacade.GetGameFeedBackInfo(feedID, 0);
            if (feedback != null)
            {
                webFacade.UpdateFeedbackViewCount(feedID);
                return "{success:'success',userName:'" + (feedback.Accounts == "" ? "匿名用户" : feedback.Accounts) + "',fcon:'" + feedback.FeedbackContent + "',rcon:'" +  feedback.RevertContent + "',count:'" + (feedback.ViewCount + 1) + "'}";
            }
            else
            {
                return "{success:'error'}";
            }
        }
    }
}
