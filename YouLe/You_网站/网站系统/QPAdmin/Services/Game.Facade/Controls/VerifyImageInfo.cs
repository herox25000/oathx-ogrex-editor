using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Imaging;
using System.Drawing;

namespace Game.Facade.Controls
{
    /// <summary>
    /// 验证码图片信息
    /// </summary>
    public class VerifyImageInfo
    {
        private Bitmap m_image;
        private string m_contentType = "image/pjpeg";
        private ImageFormat m_imageFormat = ImageFormat.Jpeg;

        /// <summary>
        /// 初始化对象实例
        /// </summary>
        public VerifyImageInfo()
        { }

        /// <summary>
        /// 初始化对象实例
        /// </summary>
        /// <param name="contentType"></param>
        /// <param name="imageFormat"></param>
        public VerifyImageInfo(string contentType, ImageFormat imageFormat)
        {
            m_contentType = contentType;
            m_imageFormat = imageFormat;
        }

        /// <summary>
        /// 生成出的图片
        /// </summary>
        public Bitmap Image
        {
            get { return m_image; }
            set { m_image = value; }
        }

        /// <summary>
        /// 输出的图片类型，如 image/pjpeg
        /// </summary>
        public string ContentType
        {
            get { return m_contentType; }
            set { m_contentType = value; }
        }

        /// <summary>
        /// 图片的格式
        /// </summary>
        public ImageFormat ImageFormat
        {
            get { return m_imageFormat; }
            set { m_imageFormat = value; }
        }
    }
}
