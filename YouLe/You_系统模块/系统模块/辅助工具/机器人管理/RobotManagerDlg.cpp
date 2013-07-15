// RobotManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RobotManager.h"
#include "RobotManagerDlg.h"
#include "Encrypt.h"

#include <comdef.h>
#include <Wbemidl.h>

# pragma comment(lib, "wbemuuid.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRobotManagerDlg 对话框

#define EfficacyResult(hResult) { if (FAILED(hResult)) _com_issue_error(hResult); }

CRobotManagerDlg::CRobotManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRobotManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	FunModifyPswTemp=ModifyPsw;
	FunModifyNameTemp=ModifyName;
}

void CRobotManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRobotManagerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_FACE, OnBnClickedButtonFace)
	ON_BN_CLICKED(IDC_BUTTON_SEX, OnBnClickedButtonSex)
	ON_BN_CLICKED(IDC_BUTTON_NAME, OnBnClickedButtonName)
	ON_BN_CLICKED(IDC_BUTTON_PWS, OnBnClickedButtonPws)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRobotManagerDlg 消息处理程序

BOOL IsDigit(TCHAR ch)
{
	if(ch>=48 && ch<=57) return TRUE;
	return FALSE;
}

int CharToInt(TCHAR ch)
{
	return (ch-48);
}

BOOL CRobotManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	HRESULT hres=NULL;
	hres =  CoInitializeEx(0, COINIT_MULTITHREADED );
	if (FAILED(hres))
	{
		return FALSE; //初始化COM异常：注意，COM只须也只能初始化一次
	}


	SetDlgItemText(IDC_EDIT_ADDR,_T("127.0.0.1,1433"));
	SetDlgItemText(IDC_EDIT_DBNAME,_T("QPGameUserDB"));
	SetDlgItemText(IDC_EDIT_USER_NAME,_T("sa"));
	SetDlgItemText(IDC_EDIT_USER_PSW,_T(""));

	FunModifyPsw=KeyError;
	FunModifyName=KeyError;

	CString strCpu;
	CString &strText=strCpu;
	CString strResult="";
	CString strTemp;

	//读取注册码
	CFile file;CString key;
	TCHAR* lpBuffer=NULL;
	if(file.Open("key.ini",CFile::modeRead))
	{
		DWORD dwLen=(DWORD)file.GetLength();
		lpBuffer=new TCHAR[dwLen+1];
		memset(lpBuffer,0,dwLen+1);
		file.Read(lpBuffer,dwLen);	
		file.Close();
	}
	key.Format("%s",lpBuffer);
	delete lpBuffer;

	//取CPU序号
	IWbemLocator *pLoc = NULL;char* szID=NULL;
	hres = CoCreateInstance(CLSID_WbemLocator,0,CLSCTX_INPROC_SERVER,IID_IWbemLocator, (LPVOID *) &pLoc);
	if (FAILED(hres))	{	return FALSE;	}
	IWbemServices *pSvc = NULL;
	hres = pLoc->ConnectServer(	_bstr_t(L"ROOT\\CIMV2"), NULL,NULL,0,NULL,0,0,&pSvc);
	if (FAILED(hres)){	pLoc->Release(); return FALSE;	}	
	hres = CoSetProxyBlanket(pSvc,RPC_C_AUTHN_WINNT,RPC_C_AUTHZ_NONE,NULL,RPC_C_AUTHN_LEVEL_CALL,RPC_C_IMP_LEVEL_IMPERSONATE,NULL,EOAC_NONE);
	if (FAILED(hres)){pSvc->Release();pLoc->Release();return FALSE;}
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_Processor"),WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,NULL,&pEnumerator);
	if (FAILED(hres)){pSvc->Release();pLoc->Release();return FALSE;	}
	IWbemClassObject *pclsObj;	ULONG uReturn = 0;
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if(0 == uReturn){	break;	}
		VARIANT vtProp;
		VariantInit(&vtProp);
		hr = pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);
		char* szCpu=_com_util::ConvertBSTRToString(vtProp.bstrVal);
		strCpu.Format("%s",szCpu); delete szCpu;
	}
	pSvc->Release();pLoc->Release();pEnumerator->Release();	pclsObj->Release();

	switch(17>= 16 )
	{
	case 0:		break;
	case 1:if(IsDigit(strText.GetAt(0)))//计算序列号
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(0))*5);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+=strText.GetAt(0);
			strResult+="F";
			if(key.Find(strResult)!=0)break;
		}

		if(IsDigit(strText.GetAt(1)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(1))*2);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="ku";
			if(key.Find(strResult)!=0)break;
		}

		if(IsDigit(strText.GetAt(2)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(2))*8);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="9K";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(3)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(3))*14);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="fFQ";
			if(key.Find(strResult)!=0)break;
		}

		if(IsDigit(strText.GetAt(4)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(4))*7);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="PUB";
			if(key.Find(strResult)!=0)break;
		}

		if(IsDigit(strText.GetAt(5)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(5))*8);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="H";
			if(key.Find(strResult)!=0)break;
		}

		if(IsDigit(strText.GetAt(6)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(6))+65);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="O";
			if(key.Find(strResult)!=0)break;
		}

		if(IsDigit(strText.GetAt(7)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(7))+75);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="W";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(8)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(8))*4);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="b";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(9)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(9))*3);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="V";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(10)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(10))*2);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="G";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(11)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(11))*1);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="Y";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(12)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(12))*45);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="wqY";
			if(key.Find(strResult)!=0)break;
		}


		if(IsDigit(strText.GetAt(13)))
		{
			strTemp.Format(_T("%d"),CharToInt(strText.GetAt(13))*14);
			strResult+=strTemp;
			if(key.Find(strResult)!=0)break;
		}
		else
		{
			strResult+="SD";
			if(key.Find(strResult)!=0)break;
		}

		FunModifyPsw=FunModifyPswTemp;
		FunModifyName=FunModifyNameTemp;


	}
	

	SetDlgItemText(IDC_EDIT_CODE,strCpu);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRobotManagerDlg::ModifyName()
{
	CString arr[]= { "","娱乐之子", "与美女无缘的帅哥", "与时俱进带两个表", "宇文乐", "宇无涯", "fzhangkebin", "可爱女孩", "雨中之人", "102919243", "玉兰花香", "玉龙雪山", "欲劲浪子", 
		"袁龙", "月不亮", "月夜的阿布罗狄", "a102919243", "云淡", "风清", "云悠幽", "在战零距离", "sudie33", "怎么看都比你帅", "曾经桑海", "dhwsjz88888888", "詹姆士.邦德", "真水无香", "真午夜人狼",
		"甄别", "峥怡", "正版项少龙", "jjsfd", "执行判决", "直卓", "只爱你一个1314", "jacky318", "指间烟", "huwu520523", "中国南京", "中国武警528", "终结你的爱情", "huwu320320", "宙斯的黄瓜", 
		"猪行不义鼻子闭", "拽拽狂摆疼疼", "专杀hg", "砖石王老五", "f3291469", "紫飞", "紫龙和龙女", "紫梦来啦", "huwu520520", "紫色麽麽茶", "紫色偶然邂逅", "紫石英", "紫尾银狐" ,"cjd1102","cjd11022","wana"
		,"紫衣碟舞","紫幽(日月)","紫韵男孩","紫竹雅阁亭","自信的孩子","自由男人","自由抛射体","自由自在的鱼鱼","lilith88","最爱慈鲷","最富争议的男人","最后孤独","hhblyt","尊贵的_狼","(风云)狂客","(乱世)夕慈水晶"
		,"(飘渺)非凡公子","单身贵族","哈日小不点","*阿龙*","*咖啡屋*","[风之子]","[花形]","bahakao91","╰☆╮无限嚣","阿健","珊珊","kakaaa1234","熏衣草","蝙蝠战车","hhbshj","酷酷小甩仔","了解","蓝娃娃",
		"yu0108fang ","shenghr ","TZJJYY ","huntter ","Andy ","嗷嗷一刀","壹切随缘","不死の凤凰","恶魔不浪漫","粉红色的女孩","孤傲可爱多","搞怪girl","风影狂","粉红色的小猪猪","孤傲战狼","交保护费的","古惑妹no.1","初恋回忆",
		"DNA","sex","红一品","爱哭的女孩","笨虎","啊咕达","爱自己","xiangxiang0110","宝贝女孩","北海爱神","飚神","冰柠檬","112233adc","冰吻","不再爱了","不知春","fgtrytrrtrrttr","苍月","超人","99887787","晨晨","抽红南京的龙虾王","抽南京泡沫美媚",
		"大眼美眉","带电","带走","道道","刀光剑影","滴血剑心","断翼","多情","seahiller","风流倜傥","风流小处男","风情浪子","风情容","风情小冷血","风骚小女人","乖宝谦谦","风中浪客","搞笑男孩TT","99887786","乖乖龙地东",
		"呵呵","恒恒","davidVSpeggy","椛訫神神","华仔无敌","黄黄","火舞精灵","火云邪神","极速风煞","sadada","asderf","sfcasdx","金牌浪子","街头野猪","焦点女生","vivigogo","军总","wsmat","珂儿","kimuynumjn","可心","恐龙",
		"狂次郎","冷玫瑰","冷血骷髅","davidbrown02","乱世太子","囨囚囨図","鹏鹏","enson5218","暮雨","闹钟A","禽兽","禽兽律师","sandraterry","色狼","三毛","刷神","catchoo","天使妹妹","edwingang","完美废人","我要嫁给有钱人","我没那种命",
		"无敌和尚","无情杀人王","zhengweihao","香草女孩","潇洒老公","小骚货","薰儿","烟消云散","炎男","13170442046","夜鹰","lliinngghhaaoo","银色指轮","忧郁","雨蔚","招聘老公","zhengweihao","蓝色靓妹妹","米兰的血","恋希","柳烟儿","龙之天蝎",
		"乔.布莱克","missibbi","泡沫影儿","chenxia719103","米格朗基咯","韬韬","xhnr8025","圣甜俊俊","圣子到","张卫健","MM Jacky","释容","甩子进村咯","lichao870316","随风倒","caobao870316","王文婧","jy838383","性感女枭王","我爱你那么多","我哈我韩",
		"无悔爱","小德鸟","小巫仙","小平","小小鱼儿","新人类","xielilove","驿城浪子","袁新仪","Windows","游龙","震震撼撼猪","紫色冰吻","緣是天定","我刷分能怎样","五万也要省","放牛的星星","冷稔鼋","iyvelp01","bfghnjnjn1","gxs0642","jiexuan0 ",
		"曦曦老公","小富婆","jy185020","Yjk838383","xx164733407","gelwiewoooiei","guoewliewoo","卧琴蝶","爱上聆听的感觉","44_96","zengyu110","飘逝的思念","一路上有你就好","31hua","收网的恶魔","淘气天尊","woool44425561","东华拉萨尔学院","wszwyq2","蛋白质","yjjyyytf","中国南京","朝彩光电","a64197748",
		"woool66996403","大约在拉萨","水上风景","caoa123","于批斗","beamwithjoy","游落的惊梦","逍H遥","佰肚官方","恐惧之谜","明月高照","服务快乐","yyandrsgy","系统消息","偶素小淑哟","寂寞的裙摆 ","大闷骚"
		,"bichisha","真淑","留洋","中共中央总书记","yirui1228","391532744","五蕴六尘","火焰舞飞扬","高尔夫","he48773791","乞讨街头","菲ai拉","2008sst","周总理说我长的帅","taobao_x","靠墙小破孩","就是要问你问题","wszwyq4","无心问今","海市蜃楼",
		"fdgdfhfkjgjk","李榜超","星雨遐想","首席运营师","失败女生","欧阳仲德","dfsdghg","寒秋凛凛","凤舞九天","帅天甩地","永远的罪鱼","厂白小青争","杀即是渡","dfsdddgsf","怡蒹葭","静别离","视觉设计",
		"mizuih4ux","帅的邋遢","dghdfjhgkjhl","申江医院","dgshgfjhdj","342699803","想早恋已晚了","dgafhgfjhk","紫色的咖啡杯","丑小鸭有点酷","爱保留","鹰冠王旭","号码已注册","寻觅论坛","南宫轩门","创业有方","飞天武"
		,"lgw1305","8825518","傻吇健","honker2","honker1","→冷雪☆冰儿←","露露","fgdgyuf78iu8","muguagege","瓦沙七","ip001","fguystfakshf","boyworld","aslcfnajkcd","未婚","只爱你一夜","thrththrtrd","leikesaisi","职务",
		"83338498","扎辫子的女生","天若有秦","沙瀑我","刺刺猬猬","枪迷V4","一招死","西门喫雪","开着小DIO的黄毛","生何为也为何生","求知不得","开心之后","凯撒大帝","偶尔放弃","只考央美","景芸","喜欢摄影","可爱嘟嘟"
		,"韩贺亮","咱也过把瘾","pass880","blueww","幽蓝刹星","happyahua","efwfewfwe","真名","眼泪","玉蝴蝶","搞酒","4w6fgse","bg4tyerg","5gtdfsfaw","追钟","adfdddddd","飞龙在天","帅气磊磊","rfedfsadfee","jingpinezhan","另类女孩",
		"红色冰力","wuyubaby","greenearser","叛逆男孩","huoyu0310","总嫖把子","645078560","雨夜浪漫","boyworld2","婷婷","cuizhuli520","5xnetcom","rewianl1","green124","421616087","织田英明","两个他","相識為緣","雷霆狂野","岳上摩天","冰色美女",
		"情义堂","因为帅所以正直","最冷的天","玩世不恭","qoqoqo23qa1342","anycall9111","另类男孩","三载小子","靓靓女孩","黄金胸","samsung858","菠萝_萝蜜","刘德华","财神","拔吊无情","zhou2848","卡卡主人","七赖葵","妻子的诱","共同语","感叹句",
		"夫人台","勿忘我勿忘我勿忘","高热一天","骨痛热眼是","工会发","投入眼退热他","犹太人","工会图样","工人统一体会议","工人一天","退热投入","施工人","热天人体","嫂夫人","骨痛热后广泛","烽火台","f4bh5cf4h5ch","kokpvcbdfg","ikofigpfd","gohfoghoo"
		,"fg[hlfgpoh[","fhitykh","jkhikvhbjv","jkhj8ymhj","cvxcger6","cvbdfy547dr","fgdr645ycf","ersdr000sfsd033csxfdv","vbdf6yfcht","bcfgr5674cg6","jg875fy5","foiv9dt0943","fiu90we895045","ig90fd8436","bopie9063",
		"bvdi904e56pfc-","vocpkpsodit34p","sdflkjio34509xd","化工呼叫土b","梵蒂冈的化工","分内法车道沟","问世老大","晚上茅屋人","妇女日模范老大哥","发儿童法南方","妇女热","防波堤解放","QQjde","IUOC","1234567899798"
		,"人民的法律；","代表秒第","信心","太阳","日日日日","分蘖日","死眼","我累啊","试验学校","广告公司","呃逆","保险公司","电力公司","ddmif","电子","疯子","嗫嚅科技","1886532","`12465-=","nicc","nihid","APPLE"
		,"苹果因","大力说手","亲个","化工年","宁可眼","BABY你","RIBB","丑小鸭","美女吧","新按讲3","西南奖","中华","恩日土","拥护名","拥护们","分头","大出发点","语言","而呢绒","wushan","xhani","weiwei","weiyi","only"
		,"olmbt","feiji","feiorn","wniermlkf","day","butkjb","SQ520","13989494993","4136420","188346","1986410","一宿个","阿水泥","女女","分内法","刻苦","可靠","深刻我额","麦饭石","摩尔法","飞机123","方法","狒狒",
		"世界4113","的反对1212","FSA1R8E1234","FNEWIGHV","LESF","MMMMMM","QAZWSX","QINQIN","SBWUF","大夫人","死恩是","卡挖仪","娃娃够","大东","大动","大的","笑嘻嘻","xxxxxxxxxxxx","嬉戏系","啊门","啊么么","处女","男"
		,"机器，袄","加强们","爱啊啊的","诡计多端","太平洋","伤心","可可","大呢可","我是你吗","的我是","累啊","头大量","虐大爱矿","瘅疟人","bueemr","bdyuqwer","JB","计算机","解放军","XIXIHAHA","SISI","XISFVB",
		"SSSSSSSSSSSSSSSS","NJFERNFNDSFDL，GJH","STUIM","KILDS","NVNV","LANLNA","LAILENF","BUTVJHK","C。S","C。K","BURNK。S","KLUIFEN","KLIMD","BIGJ","STSTI","WAHAHA","FIST","浮夸风可；","怕你啊","来呀","打呃工人",
		"哟哟哟","案例几米","封泥对付","卫道士","水泥钉","夏天","秋天","朋友","大那死敌","臭豆腐","防虐污染","SDFGH","hahahaaaa","FRTSFRU","789456","我的啊","飞过海啊","1314520","00000000","UIHNKH","TURE","FMIDFM","SHUREN"
		,"TOW","ONE","SIX","ZXVBCN","YOYO","YIYI","AOKFH","MYGOD","CHENLIN","GIGI","PIG","TIME","NEW","TIANTIAN","LOVE","LUDOSJF","ADDAS","JSIPAKL","JOLE","COCO","CKCK","NICK","OLALA","ZHUZHU","DHUSIDE","127915246",
		"123456","会谈安康","一天秒","其他","我诶我","外磅磅","案例机可","有钱人","哟黑","把把拉","啊拉把","死贵","哀哭的","人海","如何","后来","袄爱饿","案件考虑","那时候","天空在","天亮","云朵","小时候","回忆","哦类类"
		,"哦拉拉","哦理论","哦哦哦哦","年纪哦","世界一","垃圾你","拉几","我是检查","计量局了","牛","田鸡","天机","天际","光头","湖州人民","德清","杭州110","唐山","猪八戒","孙悟空啊","我们内","牛马航空机","魔女","黑暗",
		"红了","案例","喀什居留权我","心海","嘎嘎啊","煞笔","兔子","老头子","我来了","离开了","艰苦啊","世界明日","啊我我","无论","几几几","机器人","美女","不的不爱","不得","旧咔叽昆仑山机","丹江口丹江口了","皮球","迫切"
		,"IP","鸭子","素鸡","啊素","520A啊","差异","怨恨","柒柒","买","爱秒","不发","防得吧","防地","made","dior","alal","aaaa","wuliao","aini","lin","su","tyutuy","ertyry","dsdkjotvf","sdlkjbn","ghghh","56757658",
		"dfvbcgbfh","ddcvsdf4r6","vsdf346","cvxg57089-","bcvnfu68ghj","120","112","110","233851111","213123756451","21359+153244","12785+21186","125784324654","21316813675","4646846573","nbbcssxcsr","nmghj780-000",
		"dffvhft77onk","xcxcg45g","nmnh87fg","nbhr6y6hih","nkhgutyufgd","vgdft547ghfy","5346580-ghgfh","43434557i00=","9574u9789","sdfsertcvnnm",",ghjjvf","fgr7jfgvjh","许多是个","客观航空港后","热","梵蒂冈后","内部",
		"日工程小","朋友人","吨亿日","艰苦规划局","规定个","农民氟化钙","免耕法感","河南美国","电风扇的","宝鸡市工业","饿蔫不唧","吨分","口头语后","了解","退热","客观","男电风扇","客家话","扩大非导体","bcv艰苦环境",
		"广泛合同","婢女辩护人台","cgeg会谈","天空","日度","玉女","么无法","内部防寒服","性科学才","动词","杀杀害是哈","傻","wed238947xjhciuwe","007","xcsd46t9-","sdcsd45bhkj","xcsdf34bvcy","hbfgghbncv","5656hgvnhk,nm.",
		"hbfh567dgdf","`123546576","1122334455","cdf56rf6dyt","45568hgvgj","++++++","((&)_)_)_)","ffghfgyu6","~##ZZZ%#","211121659/","hjgj79889hjhj","sadsr435555555555","vbnu56fg56","cxvxcvxcvc","sd657ghjmnknk",
		"df346578jhgjhj","hgjgjghjghj","dfgeybg75","4534人体","5674七六九七八九","而投入眼","439","鸡冠花机","我爱你423","3166","4324545324","88","8哦","fh而特","个规划局","环，今天","结核杆菌棵","规范化法","我天花粉"
		,"5675673445","发挥65767","人体眼56546","女伴农户","科技联合","bdyt环境客观后","波茨坦","法国泥土","没，尼罗河棵工会","怀仁堂","内部目标巴拿马吧","bcv农民部门","大b艰苦环境棵","地方官","gur归纳法台","飞过海伏特加"
		,"sdrvchhuyo","qwqwqwq","ghghghgh","127898626","1211354453","232346345","sdf6b6","sdddd5t68","nmvdbku","sdas4g77f","fdgdf6nhh8","saw4458779","xds4gg7iyu","dfsd5jgh8","dfsdr4fy","jkyi874fdf6","bvhy677889900-",
		"bnvnvnbnbnb","xzdcs456666668","dsfsd5657677","fdgffyy","sfsdvnu5678y","sdddddddddddddd","vbcvy566666666","sdfwefdyy54656","dfg456brt776","6012","0904","1985","330521","vfdef5555555555","bftghhhf","df34vgfgfg",
		"vbfy56hf6","nhj8ui,,i89o","er4rchh770lo","ghr6767","5475465345","1322343545","sdfff444466666","hhhhhhhhhhhhhhh","dgg43gcgr","324545","8796545114567","1111111111111","77789685234","123777/95465","05445610515",
		"大师傅上人体","巴拿马体育界","就地方官地方","如果人体","恢复非常","饿饭个","人体后","泥灰岩","姨太太眼","急口令后","田野","人眼人","热特外","bcb热特","忽然地方","环境地方官","反对和","大哥大感","而外","人体眼",
		"雨天","而","飞过海法","合金钢机","撒大的","内部目标","保持","撒大","喘吁吁","规划局","被告人法和","可以才你吗","我是你的吗","你是我的吗","六血了","123买单","射了","小小飞机","小JJ","大BB","小请人2","赚钱了",
		"大家一起来","我是是是是是是","你你你是是是","黑天","天天","你爱我吗","爸爸的","小死人","嘿嘿","猪呐呐","孙无空","德清人","奶奶B","妈妈B","但是","合金钢计划","bnxc法国地方官","军火库和艰苦","烘干机分光镜",
		"受到发放","地方割","额外推翻","暴发户入土","按时但是","受到分袜个","78968456-=","896780-0-0-0-","09-89877789998",";lkio-p08p8io","dsfsr4354ednhk","4345354357667","d25edg45","sdfe53245ser","7ghjty8757656"
		,"sdf43grffffffffg","45640594561243","sdfsdf43563456","sdfw5sfvedf","k6hgbf65y","c4446ygbf","dfgsert345","fghgfhfh","dfvsdf","rstgbc66456","年代","梵蒂冈东三省","大师傅受到法","百年地方业","首发式的我","年n褐马鸡"
		,"bdry士大夫上","环境发挥","大师傅十分","分光镜法和","大师傅受到","国家南方后","十分","比三","JAY","潇洒走一回","少校","他是大家的","你是我的","晚上来陪我","开门","草你嘴巴","喝2口","兄弟","br57uddt45","dsfse534"
		,"1314","hkjt68678","n56744535","sd2546546657","vbe457674","beseq557435","seegbbbb47667456","cvbrdtyhnds","ghjfedfsgfsd","fdgreumnb","司法热天饿","手淫王``","我的BB好大哦","小学就吹消","日他","bnvn推翻忽然",
		"工会南方后","避弹服谈话","S你嘴","草B要带套","吸2口要伐啦","KKKKK粉","摇头","啊刚","弄弄弄","腆BBBBBBBBBB","舔B叼","寸白虫吧","bfj发发地方","梵蒂冈地方感","我草你老母","雷电草B王","他说的","我是250","你是123",
		"小小春春","荔波是个中伤","落社要霸王","五康打飞机","环路被","西门头","250","13。","OOBBB","城关小东东","西昌市带头人","南方","吨他他","bnvdh而褪","美国人","内蒙古环境","46大哥大说",",myyy874345","sadasrvv3456",
		"mhik869456","mngyufgsd","ada43rfdfy","nmbjkhhhhdfg","aaawecdf","vnvvyu789ec","vccxrtgvcc","vsddgt4y","XCZ3R45777777","XDER6DFF","VCXDFG4R6DFBF","SDFWE5GMNK","3423556768","VBCVXT54","XC544DGFFB,H","VBNNFGUJRDF",
		"VBCCCDSFCV","BDSR43DFTGDF","NBVHRFUYBF35445","DGDGDGDFGD","NBBBFFFF","VBDFYGVJ","FGDRTFG4565","团体他他他","45高低杠445大师傅","传达室热","bfyr副食店分","防波堤分头","受到4功夫","电视规定法","天花粉活动房",
		"sdw54557543gf","14578646","cdser34545","80789796756gh","feds4335646","fg75763545","b5r6bed45t","gh644767456","fd4657yge4","f25vefgfyyyyvh","ngjr5544454","65753653463","bbfh4643fdsv","esf24rfss5","dsfewrbdf54r65",
		"白肤色法","453.123.132","男大","不耐烦工会","大幅度人","烘干机关怀","士大夫上地方热特","水豆腐","bdrb水豆腐商人","比拟若非6666667","绝对诱惑","可可可乐","密探008","fesrvdf撒额","cfhf发挥","不得已台非常",
		"传达室山山水水体工队","drtfh电风扇","sdfvxd投入","牛肺疫河南gn","ergvegd半边人谈话","男规划局","避风港仍然日本","教徒已经","cxrtbfd","CVRERTBFH","CBFGDGG","MGJMNHGYU","FGHRTF576846","GFHTFGH","ADQDSSR","BABY",
		"科技预计","河北人体后不","成为杀人犯但是","册青春期色调去","nn下叙述电风扇","度毫微度微","额外日","人体眼人员人","工会可见光环境","士大夫犯得上","半官方别人法","真的很爱你","456456","广交会发挥","规划局感",
		"士大夫士大夫","艰苦航空","广泛感光度法国","飞过海如同宇航服","按时沓儿23534","广交会钢筋铁骨","大使馆地热田","hgj78ghu6544234","g54yfgy654fg","rrrrrrrrwewe","223244355drdtr","dfgdfgg545","xiiaodongwww3424",
		"kkk56574567","合金钢已经内部","广交会复古眼","规范化丰乐亭","987645321","123456789","4567842456","辉钴矿机构就","孟姜女户口","54345654245","昏聩化工环境","辉钴矿","梵蒂冈梵蒂冈","军火库","gfhtvvbdfg地方",
		"hgjygff4486","kj;iofgty","jhkjunhjk","gfftyhfgg","566413455","烘干机","国法","13984237814","567456465","我是无敌的","功夫真好","挖哈哈啊","环境不好","翻跟斗","地方飞过海","营业员","54874453478","今天","不开花````"
		,"日死你妈妈","草你妈个B","跟我斗```","你奶奶的","交换机工会","幅度规划局","飞过海","7867854","因为爱`","化工航空","57835993","聚光灯机","傻傻的","你好菜","我真牛","西西西","大大的","我的日","呵呵和","哈哈",
		"大师傅","体育","不受到威胁","我爱你","何苦呢","飞机","防寒服","黄金洋子","苦丁","℡①嗰亽蕜傷","辉钴矿痕迹","士大夫","花鲫鱼法","分光镜复古","国际法","鬼画符","首发","dfsgdf4563","jmh","恰屎愣嫡吻篓","翩翩蝶舞"
		,"花心№少爷","薛冬","紫布丁","夜空‰","娟＆兒","快乐男孩","野百合","78938028","豪福","爱ヤo灬她恨","失恋","9187009","咖喱在作损","7758258","︶ㄣ僾よろ伱","83974200","黄玫瑰","麦子","蝶","春天","*ＷEN.oо","老曾",
		"秋宝红花","露露","篈惢鎻恋","成少","糖堆儿","誰&與&涐爭鋒","我、、是谁？","/ka紫灵","5555","xlt","十一月的猪","尹庆武","龙...影.","sdf4fgfy565","MAN三十","东东","1127197231","啊德","&蝶舞·飞扬~","快乐天使",
		"iloveyou","时空恒星","街头、狂吻","柔道专家","天龙中","双面人","11811791985","1106659702","“白码”王子","┊煙`圈oоΟ","小不点","宝宝","ら歐卡貝﹏","神医","调酷.气爽","温朗伟","月夜づ修罗","@箭*鱼&","无忧",
		"最高境界谁？","木林","不够.完美","枫叶","╄舞玥_/~","(尐↘苯疍~~","feeling","千年清水","ＷEN.oо","逗你玩","幸福","幸福点滴","爱々随缘","难得糊涂",".君君~","流星雨","よ米べ妮づ","皓皓","╱/註蓅_▂堕","@七颠[8]倒"
		,"你我","冷雪","偷听＠妮的心","筷♀楽々★柳","─━☆GOづ","咗咹咹","唯一的爱","Angel&微笑","幸福女人","大灰狼","╰*ＷEN.oо","空空","豪迈人生","女儿当自强","随ぞ缘","爺褆︷穷亽.","在傷、吔是疼","深蓝冰","深蓝",
		"小三","嬡仩貓哋秏ふ","硪心動了","[莪]還是﹁個","寶貝ル賊懷",".醉′.傀儡",":╭籹孓 乀少▂__","[非祢卜娶]","ナ飞机王[","lu8226421","jlyh7855688","kghu56845","582484245","jycvdrbg","hjhybvf","evdvfss","帅哥",
		"☆愛你baby豬","丶.僬點釹孒","恋恋北极星","ぃ尐瀦℃寶唄","毛氏集团","真~[皧]~伱","●别碰我飘了","∮习惯∮囿祢","D调ゞ簡單ㄟ","铠甲·￥猛兽","康乃馨","cvbcvb","风尘日月","黑影子すそみ","失落的秋千","小胖","沉默寡言"
		,"非你勿扰","沁梅锁寒","來模‖我","ㄣ涛ゞ涛ナ","雨田","骁勇善战","狼牙迦南","不轻然诺","灬遇神杀神彡","dandijunqi","伪神","夜花开","摘星","mpstd","语不惊人","最爱珍珠泪","西域流沙","狂点鼠标","星亠云","随心所欲",
		"小乌龟","sorry","狂点鼠标","刀片仔","宁三","菜鸟走天下","双子幻神","化外之民","飛帆","贝克汉姆","waynespz","灬小霸","寂寞在燃烧","武魂","冰舞","蓝光月影","皇家卫队","老鹰98","上帝也DIY","师太将就吧","雁过拔毛","希尔伯伦"
		,"东郭逸","烽火连城","镇地之神","糯米糖糖","哈利波特","阳之罚","迷茫之心","强彼今","石家摸妮","分时第发","苍瑶姬","紫幽灵","蕲蕲","云梦轩","僃鞴","姚明鳴","匪祸星星"};
	
	int i=sizeof(arr);

	try
	{
		CString gameid = "00000";

		for (DWORD i = 0; i <= m_dwRecordCount; i++)
		{
			if (i == 10)
				gameid = "0000";
			else if (i == 100)
				gameid = "000";
			else if (i == 1000)
				gameid = "00";
			else if (i == 10000)
				gameid = "0";
			else if (i == 100000)
				gameid = "";
			else if (i >=sizeof(arr))
				break;

			CString strUpdt;// = "update AccountsInfo set Accounts='"+arr[i]+"' where RegAccounts='" + gameid + i + "'";          
			strUpdt.Format("update AccountsInfo set Accounts='%s' where RegAccounts='%s%d'",arr[i],gameid,i);
			m_DB.Exec(strUpdt);
		}
		if (gameid != "00000")
		{
			MessageBox("修改成功！");

		}
		else
			MessageBox("修改失败！");
	}
	catch (_com_error &e)
	{
		MessageBox(e.Description());
	}

}

void CRobotManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CRobotManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRobotManagerDlg::OnBnClickedOk()
{


	GetDlgItemText(IDC_EDIT_ADDR,m_strServer);
	GetDlgItemText(IDC_EDIT_DBNAME,m_strDbName);
	GetDlgItemText(IDC_EDIT_USER_NAME,m_strDbUser);
	GetDlgItemText(IDC_EDIT_USER_PSW,m_strUserPW);

	if(m_strServer.GetLength()==0 ||
	   m_strDbName.GetLength()==0 ||
	   m_strDbUser.GetLength()==0 ||
	   m_strUserPW.GetLength()==0)
	{
		MessageBox("信息填写不完整！","错误");
		return;
	}

	m_DB.m_LinkString.Format(TEXT("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s;"),m_strUserPW, m_strDbUser, m_strDbName, m_strServer/*, m_wPort*/);
    
	if(!m_DB.Conn())	return;

	CString strComm=_T("select * from AccountsInfo");

	_RecordsetPtr rs=m_DB.Exec(strComm);
	if(rs==NULL)	return;

	m_dwRecordCount=rs->GetRecordCount();


	GetDlgItem(IDC_EDIT_ADDR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_DBNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_USER_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_USER_PSW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ADDR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DB_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USER_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USER_PSW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_FACE)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_BUTTON_NAME)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_BUTTON_PWS)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_BUTTON_SEX)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_EDIT_ROBOT_PSW)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_EDIT_CODE)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_SHOWNORMAL);

}

void CRobotManagerDlg::KeyError()
{
	MessageBox("key.ini文件里的序列号错误，请加QQ：306060847索取");
}

void CRobotManagerDlg::OnBnClickedButtonFace()
{
		try
	{
		static int b=0;

		CString gameid = "00000";
		for (DWORD i = 0; i <= m_dwRecordCount; i++)
		{
			b++;
			if (i == 10)
				gameid = "0000";
			else if (i == 100)
				gameid = "000";
			else if (i == 1000)
				gameid = "00";
			else if (i == 10000)
				gameid = "0";
			else if (i == 100000)
				gameid = "";
			else if (b == 129)
				b = 1;

			CString strUpdt; //= "update AccountsInfo set FaceID='" + b + "' where RegAccounts='" + gameid + i + "'";
			strUpdt.Format("update AccountsInfo set FaceID='%d' where RegAccounts='%s%d'",b,gameid,i);
			
		}
		if (gameid != "00000")
		{
			MessageBox("修改成功！");

		}
		else
			MessageBox("修改失败！");

	}
	catch (_com_error& e)
	{
		MessageBox(e.Description());
	}
}

void CRobotManagerDlg::OnBnClickedButtonSex()
{
	
	try
	{
		static int age=0;
		CString gameid = "00000";
		for (DWORD i = 0; i <= m_dwRecordCount; i++)
		{
			age++;
			if (i == 10)
				gameid = "0000";
			else if (i == 100)
				gameid = "000";
			else if (i == 1000)
				gameid = "00";
			else if (i == 10000)
				gameid = "0";
			else if (i == 100000)
				gameid = "";
			else if (age == 3)
				age = 0;

			
			CString strUpdt;// = "update AccountsInfo set Gender='" + age + "' where RegAccounts='" + gameid + i + "'";
			strUpdt.Format("update AccountsInfo set Gender='%d' where RegAccounts='%s%d'",age,gameid,i);
			m_DB.Exec(strUpdt);
		}
		if (gameid != "00000")
		{
			MessageBox("修改成功！");

		}
		else
			MessageBox("修改失败！");

	}

	catch (_com_error& e)
	{
		MessageBox(e.Description());
	}
}

void CRobotManagerDlg::OnBnClickedButtonName()
{
	
	(this->*FunModifyName)();
}

void CRobotManagerDlg::OnBnClickedButtonPws()
{
	
	(this->*FunModifyPsw)();
}

void CRobotManagerDlg::OnDestroy()
{
	CDialog::OnDestroy();

	m_DB.Close();

	CoUninitialize();
}



void CRobotManagerDlg::ModifyPsw()
{
	CString strPsw;
	GetDlgItemText(IDC_EDIT_ROBOT_PSW,strPsw);
	if(strPsw.GetLength()==0)
	{
		MessageBox("请输入密码");
		return;
	}
	TCHAR szPassword[33];
	CMD5Encrypt::EncryptData(strPsw,szPassword);

	try
	{
		CString gameid = "00000";
		for (DWORD i = 0; i <= m_dwRecordCount; i++)
		{
			if (i == 10)
				gameid = "0000";
			else if (i == 100)
				gameid = "000";
			else if (i == 1000)
				gameid = "00";
			else if (i == 10000)
				gameid = "0";
			else if (i == 100000)
				gameid = "";

			CString strUpdt;//= "update AccountsInfo set LogonPass='" + UserMd5(textBox1.Text) + "' where RegAccounts='" + gameid + i + "'";
			strUpdt.Format("update AccountsInfo set LogonPass='%s' where RegAccounts='%s%d'",szPassword,gameid,i);
			m_DB.Exec(strUpdt);
		}
		if (gameid != "00000")
		{
			MessageBox("修改成功！");

		}
		else
			MessageBox("修改失败！");
	}
	catch (_com_error &e)
	{
		MessageBox(e.Description());
	}
}

