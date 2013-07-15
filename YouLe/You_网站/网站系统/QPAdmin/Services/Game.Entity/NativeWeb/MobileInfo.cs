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
	/// 实体类 MobileInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class MobileInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "MobileInfo" ;

		/// <summary>
		/// 手机标识
		/// </summary>
		public const string _MobileID = "MobileID" ;

		/// <summary>
		/// 手机类型
		/// </summary>
		public const string _MobileType = "MobileType" ;

		/// <summary>
		/// 手机系列
		/// </summary>
		public const string _MobileSerial = "MobileSerial" ;

		/// <summary>
		/// 手机型号
		/// </summary>
		public const string _MobileModel = "MobileModel" ;

		/// <summary>
		/// 尺寸
		/// </summary>
		public const string _Size = "Size" ;

		/// <summary>
		/// 分辨率
		/// </summary>
		public const string _Resolution = "Resolution" ;

		/// <summary>
		/// 屏幕比例
		/// </summary>
		public const string _Screen = "Screen" ;

		/// <summary>
		/// 操作系统
		/// </summary>
		public const string _OperatingSystem = "OperatingSystem" ;

		/// <summary>
		/// 是否横屏
		/// </summary>
		public const string _IsHorizontal = "IsHorizontal" ;

		/// <summary>
		/// 备注信息
		/// </summary>
		public const string _Remark = "Remark" ;
		#endregion

		#region 私有变量
		private int m_mobileID;						//手机标识
		private string m_mobileType;				//手机类型
		private string m_mobileSerial;				//手机系列
		private string m_mobileModel;				//手机型号
		private string m_size;						//尺寸
		private string m_resolution;				//分辨率
		private string m_screen;					//屏幕比例
		private string m_operatingSystem;			//操作系统
		private byte m_isHorizontal;				//是否横屏
		private string m_remark;					//备注信息
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化MobileInfo
		/// </summary>
		public MobileInfo()
		{
			m_mobileID=0;
			m_mobileType="";
			m_mobileSerial="";
			m_mobileModel="";
			m_size="";
			m_resolution="";
			m_screen="";
			m_operatingSystem="";
			m_isHorizontal=0;
			m_remark="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 手机标识
		/// </summary>
		public int MobileID
		{
			get { return m_mobileID; }
			set { m_mobileID = value; }
		}

		/// <summary>
		/// 手机类型
		/// </summary>
		public string MobileType
		{
			get { return m_mobileType; }
			set { m_mobileType = value; }
		}

		/// <summary>
		/// 手机系列
		/// </summary>
		public string MobileSerial
		{
			get { return m_mobileSerial; }
			set { m_mobileSerial = value; }
		}

		/// <summary>
		/// 手机型号
		/// </summary>
		public string MobileModel
		{
			get { return m_mobileModel; }
			set { m_mobileModel = value; }
		}

		/// <summary>
		/// 尺寸
		/// </summary>
		public string Size
		{
			get { return m_size; }
			set { m_size = value; }
		}

		/// <summary>
		/// 分辨率
		/// </summary>
		public string Resolution
		{
			get { return m_resolution; }
			set { m_resolution = value; }
		}

		/// <summary>
		/// 屏幕比例
		/// </summary>
		public string Screen
		{
			get { return m_screen; }
			set { m_screen = value; }
		}

		/// <summary>
		/// 操作系统
		/// </summary>
		public string OperatingSystem
		{
			get { return m_operatingSystem; }
			set { m_operatingSystem = value; }
		}

		/// <summary>
		/// 是否横屏
		/// </summary>
		public byte IsHorizontal
		{
			get { return m_isHorizontal; }
			set { m_isHorizontal = value; }
		}

		/// <summary>
		/// 备注信息
		/// </summary>
		public string Remark
		{
			get { return m_remark; }
			set { m_remark = value; }
		}
		#endregion
	}
}
