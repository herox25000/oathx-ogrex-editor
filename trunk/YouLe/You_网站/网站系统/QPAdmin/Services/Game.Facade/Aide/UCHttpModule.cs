using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;

namespace Game.Facade
{
    /// <summary>
    /// 网站HttpModule类
    /// </summary>
    public class UCHttpModule : IHttpModule
    {
        #region 常量

        private const int HTTP_ERROR_CODE = 404;                           //404错误

        #endregion

        #region IHttpModule Members

        /// <summary>
        /// 实现接口的Init方法
        /// </summary>
        /// <param name="context"></param>
        public void Init(HttpApplication context)
        {
            context.Error += new EventHandler(Application_OnError);
        }
        
        /// <summary>
        /// 释放
        /// </summary>
        public void Dispose()
        {      
            
        }

        #endregion

        #region 错误处理
        /// <summary>
        /// 错误处理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Application_OnError(Object sender, EventArgs e)
        {
            HttpApplication application = (HttpApplication)sender;
            HttpContext context = application.Context;
            Exception contextExcp = context.Server.GetLastError();

            //404错误
            if (contextExcp is HttpException)
            {
                HttpException httpExcp = contextExcp as HttpException;
                if (httpExcp.GetHttpCode() == HTTP_ERROR_CODE)
                {
                    string page = application.Request.PhysicalPath;
                    Game.Utils.TextLogger.Write(string.Format("文件不存在:{0}", application.Request.Url.AbsoluteUri));
                    return;
                }
            }

            if (contextExcp.InnerException != null) contextExcp = contextExcp.InnerException;
            StringBuilder builderExcp = new StringBuilder()
                .AppendFormat("访问路径:{0}", Game.Utils.GameRequest.GetRawUrl())
                .AppendLine()
                .AppendFormat("{0} thrown {1}", contextExcp.Source, contextExcp.GetType().ToString())
                .AppendLine()
                .Append(contextExcp.Message)
                .Append(contextExcp.StackTrace);

            Game.Utils.TextLogger.Write(builderExcp.ToString());
        }

        #endregion
    }
}
