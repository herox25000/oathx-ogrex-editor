/*
 * 版本：4.0
 * 时间：2012-3-15
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
	/// 实体类 GameGameItem。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameGameItem  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameGameItem" ;

		/// <summary>
		/// 游戏号码
		/// </summary>
		public const string _GameID = "GameID" ;

		/// <summary>
		/// 游戏名字
		/// </summary>
		public const string _GameName = "GameName" ;

		/// <summary>
		/// 支持类型
		/// </summary>
		public const string _SuporType = "SuporType" ;

		/// <summary>
		/// 连接地址
		/// </summary>
		public const string _DataBaseAddr = "DataBaseAddr" ;

		/// <summary>
		/// 数据库名
		/// </summary>
		public const string _DataBaseName = "DataBaseName" ;

		/// <summary>
		/// 服务器版本
		/// </summary>
		public const string _ServerVersion = "ServerVersion" ;

		/// <summary>
		/// 客户端版本
		/// </summary>
		public const string _ClientVersion = "ClientVersion" ;

		/// <summary>
		/// 服务端名字
		/// </summary>
		public const string _ServerDLLName = "ServerDLLName" ;

		/// <summary>
		/// 客户端名字
		/// </summary>
		public const string _ClientExeName = "ClientExeName" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _DataBaseNameT = "DataBaseNameT" ;
		#endregion

		#region 私有变量
		private int m_gameID;				//游戏号码
		private string m_gameName;			//游戏名字
		private int m_suporType;			//支持类型
		private string m_dataBaseAddr;		//连接地址
		private string m_dataBaseName;		//数据库名
		private int m_serverVersion;		//服务器版本
		private int m_clientVersion;		//客户端版本
		private string m_serverDLLName;		//服务端名字
		private string m_clientExeName;		//客户端名字
		private string m_dataBaseNameT;		//
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameGameItem
		/// </summary>
		public GameGameItem()
		{
			m_gameID=0;
			m_gameName="";
			m_suporType=0;
			m_dataBaseAddr="";
			m_dataBaseName="";
			m_serverVersion=0;
			m_clientVersion=0;
			m_serverDLLName="";
			m_clientExeName="";
			m_dataBaseNameT="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 游戏号码
		/// </summary>
		public int GameID
		{
			get { return m_gameID; }
			set { m_gameID = value; }
		}

		/// <summary>
		/// 游戏名字
		/// </summary>
		public string GameName
		{
			get { return m_gameName; }
			set { m_gameName = value; }
		}

		/// <summary>
		/// 支持类型
		/// </summary>
		public int SuporType
		{
			get { return m_suporType; }
			set { m_suporType = value; }
		}

		/// <summary>
		/// 连接地址
		/// </summary>
		public string DataBaseAddr
		{
			get { return m_dataBaseAddr; }
			set { m_dataBaseAddr = value; }
		}

		/// <summary>
		/// 数据库名
		/// </summary>
		public string DataBaseName
		{
			get { return m_dataBaseName; }
			set { m_dataBaseName = value; }
		}

		/// <summary>
		/// 服务器版本
		/// </summary>
		public int ServerVersion
		{
			get { return m_serverVersion; }
			set { m_serverVersion = value; }
		}

		/// <summary>
		/// 客户端版本
		/// </summary>
		public int ClientVersion
		{
			get { return m_clientVersion; }
			set { m_clientVersion = value; }
		}

		/// <summary>
		/// 服务端名字
		/// </summary>
		public string ServerDLLName
		{
			get { return m_serverDLLName; }
			set { m_serverDLLName = value; }
		}

		/// <summary>
		/// 客户端名字
		/// </summary>
		public string ClientExeName
		{
			get { return m_clientExeName; }
			set { m_clientExeName = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public string DataBaseNameT
		{
			get { return m_dataBaseNameT; }
			set { m_dataBaseNameT = value; }
		}
		#endregion
	}
}
