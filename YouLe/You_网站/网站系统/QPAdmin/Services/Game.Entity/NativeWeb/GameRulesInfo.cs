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
	/// 实体类 GameRulesInfo。(属性说明自动提取数据库字段的描述信息)
	/// </summary>
	[Serializable]
	public partial class GameRulesInfo  
	{
		#region 常量

		/// <summary>
		/// 表名
		/// </summary>
		public const string Tablename = "GameRulesInfo" ;

		/// <summary>
		/// 游戏标识
		/// </summary>
		public const string _KindID = "KindID" ;

		/// <summary>
		/// 游戏名称
		/// </summary>
		public const string _KindName = "KindName" ;

		/// <summary>
		/// 游戏截图
		/// </summary>
		public const string _ImgRuleUrl = "ImgRuleUrl" ;

		/// <summary>
		/// 游戏介绍
		/// </summary>
		public const string _HelpIntro = "HelpIntro" ;

		/// <summary>
		/// 规则介绍
		/// </summary>
		public const string _HelpRule = "HelpRule" ;

		/// <summary>
		/// 等级介绍
		/// </summary>
		public const string _HelpGrade = "HelpGrade" ;

		/// <summary>
		/// 加入推荐
		/// </summary>
		public const string _JoinIntro = "JoinIntro" ;

		/// <summary>
		/// 冻结
		/// </summary>
		public const string _Nullity = "Nullity" ;

		/// <summary>
		/// 新增日期
		/// </summary>
		public const string _CollectDate = "CollectDate" ;

		/// <summary>
		/// 修改日期
		/// </summary>
		public const string _ModifyDate = "ModifyDate" ;
		#endregion

		#region 私有变量
		private int m_kindID;					//游戏标识
		private string m_kindName;				//游戏名称
		private string m_imgRuleUrl;			//游戏截图
		private string m_helpIntro;				//游戏介绍
		private string m_helpRule;				//规则介绍
		private string m_helpGrade;				//等级介绍
		private byte m_joinIntro;				//加入推荐
		private byte m_nullity;					//冻结
		private DateTime m_collectDate;			//新增日期
		private DateTime m_modifyDate;			//修改日期
		#endregion

		#region 构造方法

		/// <summary>
		/// 初始化GameRulesInfo
		/// </summary>
		public GameRulesInfo()
		{
			m_kindID=0;
			m_kindName="";
			m_imgRuleUrl="";
			m_helpIntro="";
			m_helpRule="";
			m_helpGrade="";
			m_joinIntro=0;
			m_nullity=0;
			m_collectDate=DateTime.Now;
			m_modifyDate=DateTime.Now;
		}

		#endregion

		#region 公共属性

		/// <summary>
		/// 游戏标识
		/// </summary>
		public int KindID
		{
			get { return m_kindID; }
			set { m_kindID = value; }
		}

		/// <summary>
		/// 游戏名称
		/// </summary>
		public string KindName
		{
			get { return m_kindName; }
			set { m_kindName = value; }
		}

		/// <summary>
		/// 游戏截图
		/// </summary>
		public string ImgRuleUrl
		{
			get { return m_imgRuleUrl; }
			set { m_imgRuleUrl = value; }
		}

		/// <summary>
		/// 游戏介绍
		/// </summary>
		public string HelpIntro
		{
			get { return m_helpIntro; }
			set { m_helpIntro = value; }
		}

		/// <summary>
		/// 规则介绍
		/// </summary>
		public string HelpRule
		{
			get { return m_helpRule; }
			set { m_helpRule = value; }
		}

		/// <summary>
		/// 等级介绍
		/// </summary>
		public string HelpGrade
		{
			get { return m_helpGrade; }
			set { m_helpGrade = value; }
		}

		/// <summary>
		/// 加入推荐
		/// </summary>
		public byte JoinIntro
		{
			get { return m_joinIntro; }
			set { m_joinIntro = value; }
		}

		/// <summary>
		/// 冻结
		/// </summary>
		public byte Nullity
		{
			get { return m_nullity; }
			set { m_nullity = value; }
		}

		/// <summary>
		/// 新增日期
		/// </summary>
		public DateTime CollectDate
		{
			get { return m_collectDate; }
			set { m_collectDate = value; }
		}

		/// <summary>
		/// 修改日期
		/// </summary>
		public DateTime ModifyDate
		{
			get { return m_modifyDate; }
			set { m_modifyDate = value; }
		}
		#endregion
	}
}
