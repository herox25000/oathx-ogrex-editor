/*
 * 版本：4.0
 * 时间：2011-9-28
 * 作者：http://www.foxuc.com
 *
 * 描述：实体类
 *
 */

using System;
using System.Collections.Generic;

namespace Game.Entity.Treasure
{
	/// <summary>
	/// 实体类 RecordInsure。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class RecordInsure  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "RecordInsure" ;

		/// <summary>
		/// 
		/// </summary>
		public const string _RecordID = "RecordID" ;

		/// <summary>
		/// 类型标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 房间标识
		/// </summary>
		public const string _ServerID = "ServerID" ;

		/// <summary>
		/// 源用户ID
		/// </summary>
		public const string _SourceUserID = "SourceUserID" ;

		/// <summary>
		/// 当前金币数目
		/// </summary>
		public const string _SourceGold = "SourceGold" ;

		/// <summary>
		/// 当前银行数目
		/// </summary>
		public const string _SourceBank = "SourceBank" ;

		/// <summary>
		/// 目标用户ID
		/// </summary>
		public const string _TargetUserID = "TargetUserID" ;

		/// <summary>
		/// 当前金币数目
		/// </summary>
		public const string _TargetGold = "TargetGold" ;

		/// <summary>
		/// 当前银行数目
		/// </summary>
		public const string _TargetBank = "TargetBank" ;

		/// <summary>
		/// 流通金币数目
		/// </summary>
		public const string _SwapScore = "SwapScore" ;

		/// <summary>
		/// 税收数目
		/// </summary>
		public const string _Revenue = "Revenue" ;

		/// <summary>
		/// 转账场所(0:大厅,1:网页)
		/// </summary>
		public const string _IsGamePlaza = "IsGamePlaza" ;

		/// <summary>
		/// 交易类别,存 1,取 2,转 3
		/// </summary>
		public const string _TradeType = "TradeType" ;

		/// <summary>
		/// 连接地址
		/// </summary>
		public const string _ClientIP = "ClientIP" ;

		/// <summary>
		/// 录入时间
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 备注
		/// </summary>
		public const string _CollectNote = "CollectNote" ;
		#endregion

		#region 私有变量
		private int m_recordID;				//
		private int m_kindID;				//类型标识
		private int m_serverID;				//房间标识
		private int m_sourceUserID;			//源用户ID
		private long m_sourceGold;			//当前金币数目
		private long m_sourceBank;			//当前银行数目
		private int m_targetUserID;			//目标用户ID
		private long m_targetGold;			//当前金币数目
		private long m_targetBank;			//当前银行数目
		private long m_swapScore;			//流通金币数目
		private long m_revenue;				//税收数目
		private byte m_isGamePlaza;			//转账场所(0:大厅,1:网页)
		private byte m_tradeType;			//交易类别,存 1,取 2,转 3
		private string m_clientIP;			//连接地址
		private DateTime m_collectDate;		//录入时间
		private string m_collectNote;		//备注
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化RecordInsure
		/// </summary>
		public RecordInsure()
		{
			m_recordID=0;
			m_kindID=0;
			m_serverID=0;
			m_sourceUserID=0;
			m_sourceGold=0;
			m_sourceBank=0;
			m_targetUserID=0;
			m_targetGold=0;
			m_targetBank=0;
			m_swapScore=0;
			m_revenue=0;
			m_isGamePlaza=0;
			m_tradeType=0;
			m_clientIP="";
			m_collectDate=DateTime.Now;
			m_collectNote="";
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 
		/// </summary>
		public int RecordID
		{
			get { return m_recordID; }
			set { m_recordID = value; }
		}

		/// <summary>
		/// 类型标识
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 房间标识
		/// </summary>
		public int ServerID
		{
			get { return m_serverID; }
			set { m_serverID = value; }
		}

		/// <summary>
		/// 源用户ID
		/// </summary>
		public int SourceUserID
		{
			get { return m_sourceUserID; }
			set { m_sourceUserID = value; }
		}

		/// <summary>
		/// 当前金币数目
		/// </summary>
		public long SourceGold
		{
			get { return m_sourceGold; }
			set { m_sourceGold = value; }
		}

		/// <summary>
		/// 当前银行数目
		/// </summary>
		public long SourceBank
		{
			get { return m_sourceBank; }
			set { m_sourceBank = value; }
		}

		/// <summary>
		/// 目标用户ID
		/// </summary>
		public int TargetUserID
		{
			get { return m_targetUserID; }
			set { m_targetUserID = value; }
		}

		/// <summary>
		/// 当前金币数目
		/// </summary>
		public long TargetGold
		{
			get { return m_targetGold; }
			set { m_targetGold = value; }
		}

		/// <summary>
		/// 当前银行数目
		/// </summary>
		public long TargetBank
		{
			get { return m_targetBank; }
			set { m_targetBank = value; }
		}

		/// <summary>
		/// 流通金币数目
		/// </summary>
		public long SwapScore
		{
			get { return m_swapScore; }
			set { m_swapScore = value; }
		}

		/// <summary>
		/// 税收数目
		/// </summary>
		public long Revenue
		{
			get { return m_revenue; }
			set { m_revenue = value; }
		}

		/// <summary>
		/// 转账场所(0:大厅,1:网页)
		/// </summary>
		public byte IsGamePlaza
		{
			get { return m_isGamePlaza; }
			set { m_isGamePlaza = value; }
		}

		/// <summary>
		/// 交易类别,存 1,取 2,转 3
		/// </summary>
		public byte TradeType
		{
			get { return m_tradeType; }
			set { m_tradeType = value; }
		}

		/// <summary>
		/// 连接地址
		/// </summary>
		public string ClientIP
		{
			get { return m_clientIP; }
			set { m_clientIP = value; }
		}

		/// <summary>
		/// 录入时间
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}

		/// <summary>
		/// 备注
		/// </summary>
		public string CollectNote
		{
			get { return m_collectNote; }
			set { m_collectNote = value; }
		}
		#endregion
	}
}
