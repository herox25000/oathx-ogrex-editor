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

namespace Game.Entity.Platform
{
	/// <summary>
	/// 实体类 GameRoomInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameRoomInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameRoomInfo" ;

		/// <summary>
		/// 房间号码
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 房间名称
		/// </summary>
		public const string _ServerName = "ServerName" ;

		/// <summary>
		/// 挂接类型
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 挂接节点
		/// </summary>
		public const string _NodeID = "NodeID" ;

		/// <summary>
		/// 排列标识
		/// </summary>
		public const string _SortID = "SortID" ;

		/// <summary>
		/// 模块标识
		/// </summary>
		public const string _GameID = "GameID" ;

		/// <summary>
		/// 桌子数目
		/// </summary>
		public const string _TableCount = "TableCount" ;

		/// <summary>
		/// 房间类型
		/// </summary>
		public const string _ServerType = "ServerType" ;

		/// <summary>
		/// 服务端口
		/// </summary>
		public const string _ServerPort = "ServerPort" ;

		/// <summary>
		/// 数据库名
		/// </summary>
		public const string _DataBaseName = "DataBaseName" ;

		/// <summary>
		/// 连接地址
		/// </summary>
		public const string _DataBaseAddr = "DataBaseAddr" ;

		/// <summary>
		/// 单位积分
		/// </summary>
		public const string _CellScore = "CellScore" ;

		/// <summary>
		/// 税收比例
		/// </summary>
		public const string _RevenueRatio = "RevenueRatio" ;

		/// <summary>
		/// 服务费用
		/// </summary>
		public const string _ServiceScore = "ServiceScore" ;

		/// <summary>
		/// 限制积分
		/// </summary>
		public const string _RestrictScore = "RestrictScore" ;

		/// <summary>
		/// 最低积分
		/// </summary>
		public const string _MinTableScore = "MinTableScore" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MinEnterScore = "MinEnterScore" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MaxEnterScore = "MaxEnterScore" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MinEnterMember = "MinEnterMember" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _MaxEnterMember = "MaxEnterMember" ;

		/// <summary>
		/// 最大数目
		/// </summary>
		public const string _MaxPlayer = "MaxPlayer" ;

		/// <summary>
		/// 房间规则
		/// </summary>
		public const string _ServerRule = "ServerRule" ;

		/// <summary>
		/// 分组规则
		/// </summary>
		public const string _DistributeRule = "DistributeRule" ;

		/// <summary>
		/// 最少人数
		/// </summary>
		public const string _MinDistributeUser = "MinDistributeUser" ;

		/// <summary>
		/// 最多人数
		/// </summary>
		public const string _MaxDistributeUser = "MaxDistributeUser" ;

		/// <summary>
		/// 分组间隔
		/// </summary>
		public const string _DistributeTimeSpace = "DistributeTimeSpace" ;

		/// <summary>
		/// 分组局数
		/// </summary>
		public const string _DistributeDrawCount = "DistributeDrawCount" ;

		/// <summary>
		/// 开始延时
		/// </summary>
		public const string _DistributeStartDelay = "DistributeStartDelay" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _AttachUserRight = "AttachUserRight" ;

		/// <summary>
		/// 运行机器
		/// </summary>
		public const string _ServiceMachine = "ServiceMachine" ;

		/// <summary>
		/// 自定规则
		/// </summary>
		public const string _CustomRule = "CustomRule" ;

		/// <summary>
		/// 禁止服务
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 备注说明
		/// </summary>
		public const string _ServerNote = "ServerNote" ;

		/// <summary>
		/// 创建时间
		/// </summary>
		public const string _CreateDateTime = "CreateDateTime" ;

		/// <summary>
		/// 修改时间
		/// </summary>
		public const string _ModifyDateTime = "ModifyDateTime" ;
		#endregion

		#region 私有变量
		private int m_serverID;						//房间号码
		private string m_serverName;				//房间名称
		private int m_kindID;						//挂接类型
		private int m_nodeID;						//挂接节点
		private int m_sortID;						//排列标识
		private int m_gameID;						//模块标识
		private int m_tableCount;					//桌子数目
		private int m_serverType;					//房间类型
		private int m_serverPort;					//服务端口
		private string m_dataBaseName;				//数据库名
		private string m_dataBaseAddr;				//连接地址
		private long m_cellScore;					//单位积分
		private byte m_revenueRatio;				//税收比例
		private long m_serviceScore;				//服务费用
		private long m_restrictScore;				//限制积分
		private long m_minTableScore;				//最低积分
		private long m_minEnterScore;				//
		private long m_maxEnterScore;				//
		private int m_minEnterMember;				//
		private int m_maxEnterMember;				//
		private int m_maxPlayer;					//最大数目
		private int m_serverRule;					//房间规则
		private int m_distributeRule;				//分组规则
		private int m_minDistributeUser;			//最少人数
		private int m_maxDistributeUser;			//最多人数
		private int m_distributeTimeSpace;			//分组间隔
		private int m_distributeDrawCount;			//分组局数
		private int m_distributeStartDelay;			//开始延时
		private int m_attachUserRight;				//
		private string m_serviceMachine;			//运行机器
		private string m_customRule;				//自定规则
		private byte m_nullity;						//禁止服务
		private string m_serverNote;				//备注说明
		private DateTime m_createDateTime;			//创建时间
		private DateTime m_modifyDateTime;			//修改时间
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameRoomInfo
		/// </summary>
		public GameRoomInfo()
		{
			m_serverID=0;
			m_serverName="";
			m_kindID=0;
			m_nodeID=0;
			m_sortID=0;
			m_gameID=0;
			m_tableCount=0;
			m_serverType=0;
			m_serverPort=0;
			m_dataBaseName="";
			m_dataBaseAddr="";
			m_cellScore=0;
			m_revenueRatio=0;
			m_serviceScore=0;
			m_restrictScore=0;
			m_minTableScore=0;
			m_minEnterScore=0;
			m_maxEnterScore=0;
			m_minEnterMember=0;
			m_maxEnterMember=0;
			m_maxPlayer=0;
			m_serverRule=0;
			m_distributeRule=0;
			m_minDistributeUser=0;
			m_maxDistributeUser=0;
			m_distributeTimeSpace=0;
			m_distributeDrawCount=0;
			m_distributeStartDelay=0;
			m_attachUserRight=0;
			m_serviceMachine="";
			m_customRule="";
			m_nullity=0;
			m_serverNote="";
			m_createDateTime=DateTime.Now;
			m_modifyDateTime=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 房间号码
		/// </summary>
		public int ServerID
		{
			get { return m_serverID; }
			set { m_serverID = value; }
		}

		/// <summary>
		/// 房间名称
		/// </summary>
		public string ServerName
		{
			get { return m_serverName; }
			set { m_serverName = value; }
		}

		/// <summary>
		/// 挂接类型
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 挂接节点
		/// </summary>
		public int NodeID
		{
			get { return m_nodeID; }
			set { m_nodeID = value; }
		}

		/// <summary>
		/// 排列标识
		/// </summary>
		public int SortID
		{
			get { return m_sortID; }
			set { m_sortID = value; }
		}

		/// <summary>
		/// 模块标识
		/// </summary>
		public int GameID
		{
			get { return m_gameID; }
			set { m_gameID = value; }
		}

		/// <summary>
		/// 桌子数目
		/// </summary>
		public int TableCount
		{
			get { return m_tableCount; }
			set { m_tableCount = value; }
		}

		/// <summary>
		/// 房间类型
		/// </summary>
		public int ServerType
		{
			get { return m_serverType; }
			set { m_serverType = value; }
		}

		/// <summary>
		/// 服务端口
		/// </summary>
		public int ServerPort
		{
			get { return m_serverPort; }
			set { m_serverPort = value; }
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
		/// 连接地址
		/// </summary>
		public string DataBaseAddr
		{
			get { return m_dataBaseAddr; }
			set { m_dataBaseAddr = value; }
		}

		/// <summary>
		/// 单位积分
		/// </summary>
		public long CellScore
		{
			get { return m_cellScore; }
			set { m_cellScore = value; }
		}

		/// <summary>
		/// 税收比例
		/// </summary>
		public byte RevenueRatio
		{
			get { return m_revenueRatio; }
			set { m_revenueRatio = value; }
		}

		/// <summary>
		/// 服务费用
		/// </summary>
		public long ServiceScore
		{
			get { return m_serviceScore; }
			set { m_serviceScore = value; }
		}

		/// <summary>
		/// 限制积分
		/// </summary>
		public long RestrictScore
		{
			get { return m_restrictScore; }
			set { m_restrictScore = value; }
		}

		/// <summary>
		/// 最低积分
		/// </summary>
		public long MinTableScore
		{
			get { return m_minTableScore; }
			set { m_minTableScore = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public long MinEnterScore
		{
			get { return m_minEnterScore; }
			set { m_minEnterScore = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public long MaxEnterScore
		{
			get { return m_maxEnterScore; }
			set { m_maxEnterScore = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int MinEnterMember
		{
			get { return m_minEnterMember; }
			set { m_minEnterMember = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int MaxEnterMember
		{
			get { return m_maxEnterMember; }
			set { m_maxEnterMember = value; }
		}

		/// <summary>
		/// 最大数目
		/// </summary>
		public int MaxPlayer
		{
			get { return m_maxPlayer; }
			set { m_maxPlayer = value; }
		}

		/// <summary>
		/// 房间规则
		/// </summary>
		public int ServerRule
		{
			get { return m_serverRule; }
			set { m_serverRule = value; }
		}

		/// <summary>
		/// 分组规则
		/// </summary>
		public int DistributeRule
		{
			get { return m_distributeRule; }
			set { m_distributeRule = value; }
		}

		/// <summary>
		/// 最少人数
		/// </summary>
		public int MinDistributeUser
		{
			get { return m_minDistributeUser; }
			set { m_minDistributeUser = value; }
		}

		/// <summary>
		/// 最多人数
		/// </summary>
		public int MaxDistributeUser
		{
			get { return m_maxDistributeUser; }
			set { m_maxDistributeUser = value; }
		}

		/// <summary>
		/// 分组间隔
		/// </summary>
		public int DistributeTimeSpace
		{
			get { return m_distributeTimeSpace; }
			set { m_distributeTimeSpace = value; }
		}

		/// <summary>
		/// 分组局数
		/// </summary>
		public int DistributeDrawCount
		{
			get { return m_distributeDrawCount; }
			set { m_distributeDrawCount = value; }
		}

		/// <summary>
		/// 开始延时
		/// </summary>
		public int DistributeStartDelay
		{
			get { return m_distributeStartDelay; }
			set { m_distributeStartDelay = value; }
		}

		/// <summary>
		/// 
		/// </summary>
		public int AttachUserRight
		{
			get { return m_attachUserRight; }
			set { m_attachUserRight = value; }
		}

		/// <summary>
		/// 运行机器
		/// </summary>
		public string ServiceMachine
		{
			get { return m_serviceMachine; }
			set { m_serviceMachine = value; }
		}

		/// <summary>
		/// 自定规则
		/// </summary>
		public string CustomRule
		{
			get { return m_customRule; }
			set { m_customRule = value; }
		}

		/// <summary>
		/// 禁止服务
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 备注说明
		/// </summary>
		public string ServerNote
		{
			get { return m_serverNote; }
			set { m_serverNote = value; }
		}

		/// <summary>
		/// 创建时间
		/// </summary>
		public DateTime CreateDateTime
		{
			get { return m_createDateTime; }
			set { m_createDateTime = value; }
		}

		/// <summary>
		/// 修改时间
		/// </summary>
		public DateTime ModifyDateTime
		{
			get { return m_modifyDateTime; }
			set { m_modifyDateTime = value; }
		}
		#endregion
	}
}
