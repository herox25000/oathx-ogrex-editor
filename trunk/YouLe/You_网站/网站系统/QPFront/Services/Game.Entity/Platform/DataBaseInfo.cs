/*
 * 版本：4.0
 * 时间：2011-10-8
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.Platform
{
	/// <summary>
	/// 实体类 DataBaseInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class DataBaseInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "DataBaseInfo" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DBInfoID = "DBInfoID" ;

		/// <summary>
		/// 网络地址
		/// </summary>
		public const string _DBAddr = "DBAddr" ;

		/// <summary>
		/// 数据库端口
		/// </summary>
		public const string _DBPort = "DBPort" ;

		/// <summary>
		/// 数据库用户
		/// </summary>
		public const string _DBUser = "DBUser" ;

		/// <summary>
		/// 数据库密码
		/// </summary>
		public const string _DBPassword = "DBPassword" ;

		/// <summary>
		/// 机器标识
		/// </summary>
		public const string _MachineID = "MachineID" ;

		/// <summary>
		/// 备注信息
		/// </summary>
		public const string _Information = "Information" ;
		#endregion

		#region 私有变量
		private int m_dBInfoID;					//
		private string m_dBAddr;				//网络地址
		private int m_dBPort;					//数据库端口
		private string m_dBUser;				//数据库用户
		private string m_dBPassword;			//数据库密码
		private string m_machineID;				//机器标识
		private string m_information;			//备注信息
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化DataBaseInfo
		/// </summary>
		public DataBaseInfo()
		{
			m_dBInfoID=0;
			m_dBAddr="";
			m_dBPort=0;
			m_dBUser="";
			m_dBPassword="";
			m_machineID="";
			m_information="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int DBInfoID
		{
			get { return m_dBInfoID; }
			set { m_dBInfoID = value; }
		}

		/// <summary>
		/// 网络地址
		/// </summary>
		public string DBAddr
		{
			get { return m_dBAddr; }
			set { m_dBAddr = value; }
		}

		/// <summary>
		/// 数据库端口
		/// </summary>
		public int DBPort
		{
			get { return m_dBPort; }
			set { m_dBPort = value; }
		}

		/// <summary>
		/// 数据库用户
		/// </summary>
		public string DBUser
		{
			get { return m_dBUser; }
			set { m_dBUser = value; }
		}

		/// <summary>
		/// 数据库密码
		/// </summary>
		public string DBPassword
		{
			get { return m_dBPassword; }
			set { m_dBPassword = value; }
		}

		/// <summary>
		/// 机器标识
		/// </summary>
		public string MachineID
		{
			get { return m_machineID; }
			set { m_machineID = value; }
		}

		/// <summary>
		/// 备注信息
		/// </summary>
		public string Information
		{
			get { return m_information; }
			set { m_information = value; }
		}
		#endregion
	}
}
