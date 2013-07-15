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
	/// 实体类 T_jiaozhu。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class T_jiaozhu  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "t_jiaozhu" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Jiaozhu = "jiaozhu" ;
		#endregion

		#region 私有变量
		private string m_jiaozhu;			//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化T_jiaozhu
		/// </summary>
		public T_jiaozhu()
		{
			m_jiaozhu="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public string Jiaozhu
		{
			get { return m_jiaozhu; }
			set { m_jiaozhu = value; }
		}
		#endregion
	}
}
