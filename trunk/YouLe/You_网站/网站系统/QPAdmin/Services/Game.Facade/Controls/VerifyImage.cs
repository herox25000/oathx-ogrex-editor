using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Security.Cryptography;

namespace Game.Facade.Controls
{
    /// <summary>
    /// 验证码图片类
    /// </summary>
    public class VerifyImage
    {
        #region Fields

        private static byte[] randb = new byte[4];
        private static RNGCryptoServiceProvider rand = new RNGCryptoServiceProvider();

        private static Matrix m = new Matrix();
        private static Font font = new Font("宋体", 9.2F, FontStyle.Bold);

        #endregion

        #region 随机因子

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

        #endregion

        #region 生成验证码

        /// <summary>
        /// 生成验证码
        /// </summary>
        /// <param name="code"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="bgcolor"></param>
        /// <returns></returns>
        public VerifyImageInfo GenerateImage(string code, int width, int height, Color bgcolor)
        {
            VerifyImageInfo verifyimage = new VerifyImageInfo("image/pjpeg", ImageFormat.Jpeg);

            //直接指定尺寸, 而不使用外部参数中的建议尺寸
            width = 47;
            height = 20;

            Bitmap bitmap = new Bitmap(width, height, PixelFormat.Format32bppArgb);
            Graphics g = Graphics.FromImage(bitmap);
            g.SmoothingMode = SmoothingMode.HighSpeed;
            g.Clear(bgcolor);

            //画干扰线
            int fixedNumber = 60;
            Pen linePen = new Pen(Color.FromArgb(Next(50) + fixedNumber, Next(50) + fixedNumber, Next(50) + fixedNumber), 1);
            SolidBrush drawBrush = new SolidBrush(Color.FromArgb(Next(100), Next(100), Next(100)));
            for (int i = 0; i < 3; i++)
            {
                g.DrawArc(linePen, Next(20) - 10, Next(20) - 10, Next(width) + 10, Next(height) + 10, Next(-100, 100), Next(-200, 200));
            }

            //画验证码
            for (int i = 0; i < code.Length; i++)
            {
                drawBrush = new SolidBrush(Color.Black);
                PointF point = new PointF((i * 7.2F) + 4.2F, 2.6F);
                g.DrawString(code[i].ToString(), font, drawBrush, point);
            }

            //释放资源
            drawBrush.Dispose();
            g.Dispose();

            verifyimage.Image = bitmap;

            return verifyimage;
        }

        #endregion
    }
}
