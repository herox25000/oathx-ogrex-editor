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

using System.Drawing;
using Game.Facade;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Security.Cryptography;

namespace Game.Web
{
    /// <summary>
    /// 验证码
    /// </summary>
    public partial class ValidateImage : Page, System.Web.SessionState.IRequiresSessionState
    {
        private static Bitmap charbmp = new Bitmap(40, 40);
        private static Matrix m = new Matrix();
        private static byte[] randb = new byte[4];
        private static RNGCryptoServiceProvider rand = new RNGCryptoServiceProvider();
        private static Font[] fonts = {
                                        new Font(new FontFamily("Times New Roman"), 16 + Next(3), FontStyle.Regular),
                                        new Font(new FontFamily("Georgia"), 16 + Next(3), FontStyle.Regular),
                                        new Font(new FontFamily("Arial"), 16 + Next(3), FontStyle.Regular),
                                        new Font(new FontFamily("Comic Sans MS"), 16 + Next(3), FontStyle.Regular),
                                        new Font(new FontFamily("Verdana"), 16 + Next(3), FontStyle.Regular)
                                     };

        private void Page_Load(object sender, System.EventArgs e)
        {
            string randomcode = Game.Utils.TextUtility.CreateAuthStr(4, true);
            Game.Utils.SessionState.Set(Fetch.UC_VERIFY_CODE_KEY, randomcode);
            Utils.Utility.WriteCookie(Fetch.UC_VERIFY_CODE_KEY, Utils.CWHEncryptNet.XorEncrypt(randomcode));
            this.CreateImage(randomcode);

        }

        /// <summary>
        /// 获得下一个随机数
        /// </summary>
        /// <param name="max">最大值</param>
        /// <returns></returns>
        private static int Next(int max)
        {
            rand.GetBytes(randb);
            int value = BitConverter.ToInt32(randb, 0);
            value = value % (max + 1);
            if (value < 0)
                value = -value;
            return value;
        }

        /// <summary>
        /// 获得下一个随机数
        /// </summary>
        /// <param name="min">最小值</param>
        /// <param name="max">最大值</param>
        /// <returns></returns>
        private static int Next(int min, int max)
        {
            int value = Next(max - min) + min;
            return value;
        }

        ///  <summary>
        ///  创建随机码图片
        ///  </summary>
        ///  <param  name="randomcode">随机码</param>
        private void CreateImage(string randomcode)
        {
            int width = 90;
            int height = 28;

            Bitmap bitmap = new Bitmap(width, height, PixelFormat.Format32bppArgb);

            Graphics g = Graphics.FromImage(bitmap);
            g.SmoothingMode = SmoothingMode.HighSpeed;
            g.Clear(Color.White);
            g.DrawRectangle(new Pen(Color.Black, 0), 0, 0, bitmap.Width - 1, bitmap.Height - 1);//

            int fixedNumber = 60;
            Pen linePen = new Pen(Color.FromArgb(Next(50) + fixedNumber, Next(50) + fixedNumber, Next(50) + fixedNumber), 1);

            SolidBrush drawBrush = new SolidBrush(Color.FromArgb(Next(100), Next(100), Next(100)));
            for (int i = 0; i < 2; i++)
            {
                g.DrawArc(linePen, Next(20) - 10, Next(20) - 10, Next(width) + 10, Next(height) + 10, Next(-100, 100), Next(-200, 200));
            }

            Graphics charg = Graphics.FromImage(charbmp);

            float charx = -18;
            for (int i = 0; i < randomcode.Length; i++)
            {
                m.Reset();
                m.RotateAt(Next(50) - 25, new PointF(Next(3) + 7, Next(3) + 7));

                charg.Clear(Color.Transparent);
                charg.Transform = m;
                //定义前景色为黑色
                drawBrush.Color = Color.Black;

                charx = charx + 18 + Next(5);
                PointF drawPoint = new PointF(charx, 2.0F);
                charg.DrawString(randomcode[i].ToString(), fonts[Next(fonts.Length - 1)], drawBrush, new PointF(0, 0));

                charg.ResetTransform();

                g.DrawImage(charbmp, drawPoint);
            }
            drawBrush.Dispose();
            g.Dispose();
            //生成图片
            System.IO.MemoryStream ms = new System.IO.MemoryStream();
            bitmap.Save(ms, System.Drawing.Imaging.ImageFormat.Gif);
            Response.ClearContent();
            Response.ContentType = "image/gif";
            Response.BinaryWrite(ms.ToArray());
            
            bitmap.Dispose();
        }
    }
}
