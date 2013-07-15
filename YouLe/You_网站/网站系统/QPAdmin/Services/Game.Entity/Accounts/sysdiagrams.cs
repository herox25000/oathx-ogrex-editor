/*
 * 版本：4.0
 * 时间：2011-9-27
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.Accounts
{
	/// <summary>
	/// 实体类 Sysdiagrams。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class Sysdiagrams  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "sysdiagrams" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Name = "name" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Principal_id = "principal_id" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Diagram_id = "diagram_id" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Version = "version" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _Definition = "definition" ;
		#endregion

		#region 私有变量
		private string m_name;				//
		private int m_principal_id;			//
		private int m_diagram_id;			//
		private int m_version;				//
		private System.Byte[] m_definition;	//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化Sysdiagrams
		/// </summary>
		public Sysdiagrams()
		{
			m_name="";
			m_principal_id=0;
			m_diagram_id=0;
			m_version=0;
			m_definition=null;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public string Name
		{
			get { return m_name; }
			set { m_name = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int Principal_id
		{
			get { return m_principal_id; }
			set { m_principal_id = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int Diagram_id
		{
			get { return m_diagram_id; }
			set { m_diagram_id = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int Version
		{
			get { return m_version; }
			set { m_version = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public System.Byte[] Definition
		{
			get { return m_definition; }
			set { m_definition = value; }
		}
		#endregion
	}
}
