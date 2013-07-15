/*
 * 版本：4.0
 * 时间：2011-9-30
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.NativeWeb
{
	/// <summary>
	/// 实体类 GameMobileInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameMobileInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameMobileInfo" ;

		/// <summary>
		/// 游戏ID
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 手机品牌ID
		/// </summary>
		public const string _MobileID = "MobileID" ;

		/// <summary>
		/// 游戏下载地址
		/// </summary>
		public const string _DownloadUrl = "DownloadUrl" ;
		#endregion

		#region 私有变量
		private int m_kindID;					//游戏ID
		private int m_mobileID;					//手机品牌ID
		private string m_downloadUrl;			//游戏下载地址
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameMobileInfo
		/// </summary>
		public GameMobileInfo()
		{
			m_kindID=0;
			m_mobileID=0;
			m_downloadUrl="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 游戏ID
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 手机品牌ID
		/// </summary>
		public int MobileID
		{
			get { return m_mobileID; }
			set { m_mobileID = value; }
		}

		/// <summary>
		/// 游戏下载地址
		/// </summary>
		public string DownloadUrl
		{
			get { return m_downloadUrl; }
			set { m_downloadUrl = value; }
		}
		#endregion
	}
}
