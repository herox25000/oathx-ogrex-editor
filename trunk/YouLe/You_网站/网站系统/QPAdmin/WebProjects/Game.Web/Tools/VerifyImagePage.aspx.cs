using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Facade.Controls;
using System.Drawing;

namespace Game.Web.Tools
{
    public partial class VerifyImagePage : System.Web.UI.Page
    {
        /// <summary>
        /// 初始化页面
        /// </summary>
        /// <param name="e"></param>
        override protected void OnInit(EventArgs e)
        {
            base.OnInit(e);
            string verifyCode = Game.Utils.TextUtility.CreateAuthStr(5, true);
            HttpContext.Current.Session["CheckCode"] = verifyCode;
            VerifyImageInfo verifyimg = new VerifyImageVer2().GenerateImage(verifyCode, 0, 0, Color.FromArgb(227, 227, 227),2);
            Bitmap image = verifyimg.Image;
            Response.ContentType = verifyimg.ContentType;
            image.Save(Response.OutputStream, verifyimg.ImageFormat);
        }
    }
}
