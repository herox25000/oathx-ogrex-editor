// RobotManagerDlg.cpp : ʵ���ļ�
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


// CRobotManagerDlg �Ի���

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


// CRobotManagerDlg ��Ϣ�������

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	HRESULT hres=NULL;
	hres =  CoInitializeEx(0, COINIT_MULTITHREADED );
	if (FAILED(hres))
	{
		return FALSE; //��ʼ��COM�쳣��ע�⣬COMֻ��Ҳֻ�ܳ�ʼ��һ��
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

	//��ȡע����
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

	//ȡCPU���
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
	case 1:if(IsDigit(strText.GetAt(0)))//�������к�
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

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRobotManagerDlg::ModifyName()
{
	CString arr[]= { "","����֮��", "����Ů��Ե��˧��", "��ʱ�����������", "������", "������", "fzhangkebin", "�ɰ�Ů��", "����֮��", "102919243", "��������", "����ѩɽ", "��������", 
		"Ԭ��", "�²���", "��ҹ�İ����޵�", "a102919243", "�Ƶ�", "����", "������", "��ս�����", "sudie33", "��ô��������˧", "����ɣ��", "dhwsjz88888888", "ղķʿ.���", "��ˮ����", "����ҹ����",
		"���", "���", "����������", "jjsfd", "ִ���о�", "ֱ׿", "ֻ����һ��1314", "jacky318", "ָ����", "huwu520523", "�й��Ͼ�", "�й��侯528", "�ս���İ���", "huwu320320", "��˹�Ļƹ�", 
		"���в�����ӱ�", "קק�������", "רɱhg", "שʯ������", "f3291469", "�Ϸ�", "��������Ů", "��������", "huwu520520", "��ɫ�����", "��ɫżȻ����", "��ʯӢ", "��β����" ,"cjd1102","cjd11022","wana"
		,"���µ���","����(����)","�����к�","�����Ÿ�ͤ","���ŵĺ���","��������","����������","�������ڵ�����","lilith88","�����","����������","���¶�","hhblyt","����_��","(����)���","(����)Ϧ��ˮ��"
		,"(Ʈ��)�Ƿ�����","�������","����С����","*����*","*������*","[��֮��]","[����]","bahakao91","�t��r������","����","ɺɺ","kakaaa1234","Ѭ�²�","����ս��","hhbshj","���С˦��","�˽�","������",
		"yu0108fang ","shenghr ","TZJJYY ","huntter ","Andy ","��һ��","Ҽ����Ե","�����η��","��ħ������","�ۺ�ɫ��Ů��","�°��ɰ���","���girl","��Ӱ��","�ۺ�ɫ��С����","�°�ս��","�������ѵ�","�Ż���no.1","��������",
		"DNA","sex","��һƷ","���޵�Ů��","����","������","���Լ�","xiangxiang0110","����Ů��","��������","���","������","112233adc","����","���ٰ���","��֪��","fgtrytrrtrrttr","����","����","99887787","����","����Ͼ�����Ϻ��","���Ͼ���ĭ����",
		"������ü","����","����","����","���⽣Ӱ","��Ѫ����","����","����","seahiller","��������","����С����","��������","������","����С��Ѫ","��ɧСŮ��","�Ա�ǫǫ","�����˿�","��Ц�к�TT","99887786","�Թ����ض�",
		"�Ǻ�","���","davidVSpeggy","���M����","�����޵�","�ƻ�","���辫��","����а��","���ٷ�ɷ","sadada","asderf","sfcasdx","��������","��ͷҰ��","����Ů��","vivigogo","����","wsmat","���","kimuynumjn","����","����",
		"�����","��õ��","��Ѫ����","davidbrown02","����̫��","������","����","enson5218","ĺ��","����A","����","������ʦ","sandraterry","ɫ��","��ë","ˢ��","catchoo","��ʹ����","edwingang","��������","��Ҫ�޸���Ǯ��","��û������",
		"�޵к���","����ɱ����","zhengweihao","���Ů��","�����Ϲ�","Сɧ��","޹��","������ɢ","����","13170442046","ҹӥ","lliinngghhaaoo","��ɫָ��","����","��ε","��Ƹ�Ϲ�","zhengweihao","��ɫ������","������Ѫ","��ϣ","���̶�","��֮��Ы",
		"��.������","missibbi","��ĭӰ��","chenxia719103","�׸��ʻ���","��","xhnr8025","ʥ�𿡿�","ʥ�ӵ�","������","MM Jacky","����","˦�ӽ��忩","lichao870316","��絹","caobao870316","�����","jy838383","�Ը�Ů����","�Ұ�����ô��","�ҹ��Һ�",
		"�޻ڰ�","С����","С����","Сƽ","СС���","������","xielilove","�������","Ԭ����","Windows","����","���𺳺���","��ɫ����","�����춨","��ˢ��������","����ҲҪʡ","��ţ������","������","iyvelp01","bfghnjnjn1","gxs0642","jiexuan0 ",
		"�����Ϲ�","С����","jy185020","Yjk838383","xx164733407","gelwiewoooiei","guoewliewoo","���ٵ�","���������ĸо�","44_96","zengyu110","Ʈ�ŵ�˼��","һ·������ͺ�","31hua","�����Ķ�ħ","��������","woool44425561","����������ѧԺ","wszwyq2","������","yjjyyytf","�й��Ͼ�","���ʹ��","a64197748",
		"woool66996403","��Լ������","ˮ�Ϸ羰","caoa123","������","beamwithjoy","����ľ���","��Hң","�۶ǹٷ�","�־�֮��","���¸���","�������","yyandrsgy","ϵͳ��Ϣ","ż��С��Ӵ","��į��ȹ�� ","����ɧ"
		,"bichisha","����","����","�й����������","yirui1228","391532744","��������","���������","�߶���","he48773791","���ֽ�ͷ","��ai��","2008sst","������˵�ҳ���˧","taobao_x","��ǽС�ƺ�","����Ҫ��������","wszwyq4","�����ʽ�","������¥",
		"fdgdfhfkjgjk","���","��������","��ϯ��Ӫʦ","ʧ��Ů��","ŷ���ٵ�","dfsdghg","��������","�������","˧��˦��","��Զ������","����С����","ɱ���Ƕ�","dfsdddgsf","������","������","�Ӿ����",
		"mizuih4ux","˧������","dghdfjhgkjhl","�꽭ҽԺ","dgshgfjhdj","342699803","������������","dgafhgfjhk","��ɫ�Ŀ��ȱ�","��СѼ�е��","������","ӥ������","������ע��","Ѱ����̳","�Ϲ�����","��ҵ�з�","������"
		,"lgw1305","8825518","ɵ����","honker2","honker1","����ѩ�������","¶¶","fgdgyuf78iu8","muguagege","��ɳ��","ip001","fguystfakshf","boyworld","aslcfnajkcd","δ��","ֻ����һҹ","thrththrtrd","leikesaisi","ְ��",
		"83338498","�����ӵ�Ů��","��������","ɳ����","�̴���","ǹ��V4","һ����","���ņ�ѩ","����СDIO�Ļ�ë","����ΪҲΪ����","��֪����","����֮��","�������","ż������","ֻ������","��ܿ","ϲ����Ӱ","�ɰ���"
		,"������","��Ҳ�����","pass880","blueww","����ɲ��","happyahua","efwfewfwe","����","����","�����","���","4w6fgse","bg4tyerg","5gtdfsfaw","׷��","adfdddddd","��������","˧������","rfedfsadfee","jingpinezhan","����Ů��",
		"��ɫ����","wuyubaby","greenearser","�����к�","huoyu0310","���ΰ���","645078560","��ҹ����","boyworld2","����","cuizhuli520","5xnetcom","rewianl1","green124","421616087","֯��Ӣ��","������","���R�龉","������Ұ","����Ħ��","��ɫ��Ů",
		"������","��Ϊ˧������ֱ","�������","��������","qoqoqo23qa1342","anycall9111","�����к�","����С��","����Ů��","�ƽ���","samsung858","����_����","���»�","����","�ε�����","zhou2848","��������","������","���ӵ���","��ͬ��","��̾��",
		"����̨","����������������","����һ��","��ʹ������","���ᷢ","Ͷ����������","��̫��","����ͼ��","����ͳһ�����","����һ��","����Ͷ��","ʩ����","��������","ɩ����","��ʹ�Ⱥ�㷺","���̨","f4bh5cf4h5ch","kokpvcbdfg","ikofigpfd","gohfoghoo"
		,"fg[hlfgpoh[","fhitykh","jkhikvhbjv","jkhj8ymhj","cvxcger6","cvbdfy547dr","fgdr645ycf","ersdr000sfsd033csxfdv","vbdf6yfcht","bcfgr5674cg6","jg875fy5","foiv9dt0943","fiu90we895045","ig90fd8436","bopie9063",
		"bvdi904e56pfc-","vocpkpsodit34p","sdflkjio34509xd","����������b","��ٸԵĻ���","���ڷ�������","�����ϴ�","����é����","��Ů��ģ���ϴ��","����ͯ���Ϸ�","��Ů��","�����̽��","QQjde","IUOC","1234567899798"
		,"����ķ��ɣ�","�������","����","̫��","��������","������","����","���۰�","����ѧУ","��湫˾","����","���չ�˾","������˾","ddmif","����","����","���Ƽ�","1886532","`12465-=","nicc","nihid","APPLE"
		,"ƻ����","����˵��","�׸�","������","������","BABY��","RIBB","��СѼ","��Ů��","�°���3","���Ͻ�","�л�","������","ӵ����","ӵ����","��ͷ","�������","����","������","wushan","xhani","weiwei","weiyi","only"
		,"olmbt","feiji","feiorn","wniermlkf","day","butkjb","SQ520","13989494993","4136420","188346","1986410","һ�޸�","��ˮ��","ŮŮ","���ڷ�","�̿�","�ɿ�","����Ҷ�","��ʯ","Ħ����","�ɻ�123","����","����",
		"����4113","�ķ���1212","FSA1R8E1234","FNEWIGHV","LESF","MMMMMM","QAZWSX","QINQIN","SBWUF","�����","������","������","���޹�","��","��","���","Ц����","xxxxxxxxxxxx","��Ϸϵ","����","��ôô","��Ů","��"
		,"��������","��ǿ��","��������","��ƶ��","̫ƽ��","����","�ɿ�","���ؿ�","��������","������","�۰�","ͷ����","Ű�󰮿�","��ű��","bueemr","bdyuqwer","JB","�����","��ž�","XIXIHAHA","SISI","XISFVB",
		"SSSSSSSSSSSSSSSS","NJFERNFNDSFDL��GJH","STUIM","KILDS","NVNV","LANLNA","LAILENF","BUTVJHK","C��S","C��K","BURNK��S","KLUIFEN","KLIMD","BIGJ","STSTI","WAHAHA","FIST","�����ɣ�","���㰡","��ѽ","��������",
		"ӴӴӴ","��������","����Ը�","����ʿ","ˮ�ඤ","����","����","����","��������","������","��Ű��Ⱦ","SDFGH","hahahaaaa","FRTSFRU","789456","�ҵİ�","�ɹ�����","1314520","00000000","UIHNKH","TURE","FMIDFM","SHUREN"
		,"TOW","ONE","SIX","ZXVBCN","YOYO","YIYI","AOKFH","MYGOD","CHENLIN","GIGI","PIG","TIME","NEW","TIANTIAN","LOVE","LUDOSJF","ADDAS","JSIPAKL","JOLE","COCO","CKCK","NICK","OLALA","ZHUZHU","DHUSIDE","127915246",
		"123456","��̸����","һ����","����","������","�����","��������","��Ǯ��","Ӵ��","�Ѱ���","������","����","���޵�","�˺�","���","����","������","��������","��ʱ��","�����","����","�ƶ�","Сʱ��","����","Ŷ����"
		,"Ŷ����","Ŷ����","ŶŶŶŶ","���Ŷ","����һ","������","����","���Ǽ��","��������","ţ","�Ｆ","���","���","��ͷ","��������","����","����110","��ɽ","��˽�","����հ�","������","ţ���ջ�","ħŮ","�ڰ�",
		"����","����","��ʲ����Ȩ��","�ĺ�","�¸°�","ɷ��","����","��ͷ��","������","�뿪��","��డ","��������","������","����","������","������","��Ů","���Ĳ���","����","����ߴ����ɽ��","�����ڵ�������","Ƥ��","����"
		,"IP","Ѽ��","�ؼ�","����","520A��","����","Թ��","����","��","����","����","���ð�","����","made","dior","alal","aaaa","wuliao","aini","lin","su","tyutuy","ertyry","dsdkjotvf","sdlkjbn","ghghh","56757658",
		"dfvbcgbfh","ddcvsdf4r6","vsdf346","cvxg57089-","bcvnfu68ghj","120","112","110","233851111","213123756451","21359+153244","12785+21186","125784324654","21316813675","4646846573","nbbcssxcsr","nmghj780-000",
		"dffvhft77onk","xcxcg45g","nmnh87fg","nbhr6y6hih","nkhgutyufgd","vgdft547ghfy","5346580-ghgfh","43434557i00=","9574u9789","sdfsertcvnnm",",ghjjvf","fgr7jfgvjh","����Ǹ�","�͹ۺ��ոۺ�","��","��ٸԺ�","�ڲ�",
		"�չ���С","������","������","���滮��","�涨��","ũ�������","�������","��������","����ȵ�","�����й�ҵ","���費��","�ַ�","��ͷ���","�˽�","����","�͹�","�е����","�ͼһ�","����ǵ���","bcv��໷��",
		"�㷺��ͬ","�Ů�绤��̨","cgeg��̸","���","�ն�","��Ů","ô�޷�","�ڲ�������","�Կ�ѧ��","����","ɱɱ���ǹ�","ɵ","wed238947xjhciuwe","007","xcsd46t9-","sdcsd45bhkj","xcsdf34bvcy","hbfgghbncv","5656hgvnhk,nm.",
		"hbfh567dgdf","`123546576","1122334455","cdf56rf6dyt","45568hgvgj","++++++","((&)_)_)_)","ffghfgyu6","~##ZZZ%#","211121659/","hjgj79889hjhj","sadsr435555555555","vbnu56fg56","cxvxcvxcvc","sd657ghjmnknk",
		"df346578jhgjhj","hgjgjghjghj","dfgeybg75","4534����","5674�������߰˾�","��Ͷ����","439","���ڻ���","�Ұ���423","3166","4324545324","88","8Ŷ","fh����","���滮��","��������","��˸˾���","�淶����","���컨��"
		,"5675673445","����65767","������56546","Ů��ũ��","�Ƽ�����","bdyt�����͹ۺ�","����̹","��������","û�����޺ӿù���","������","�ڲ�Ŀ��������","bcvũ����","��b��໷����","�ط���","gur���ɷ�̨","�ɹ������ؼ�"
		,"sdrvchhuyo","qwqwqwq","ghghghgh","127898626","1211354453","232346345","sdf6b6","sdddd5t68","nmvdbku","sdas4g77f","fdgdf6nhh8","saw4458779","xds4gg7iyu","dfsd5jgh8","dfsdr4fy","jkyi874fdf6","bvhy677889900-",
		"bnvnvnbnbnb","xzdcs456666668","dsfsd5657677","fdgffyy","sfsdvnu5678y","sdddddddddddddd","vbcvy566666666","sdfwefdyy54656","dfg456brt776","6012","0904","1985","330521","vfdef5555555555","bftghhhf","df34vgfgfg",
		"vbfy56hf6","nhj8ui,,i89o","er4rchh770lo","ghr6767","5475465345","1322343545","sdfff444466666","hhhhhhhhhhhhhhh","dgg43gcgr","324545","8796545114567","1111111111111","77789685234","123777/95465","05445610515",
		"��ʦ��������","������������","�͵ط��ٵط�","�������","�ָ��ǳ�","������","�����","�����","��̫̫��","�������","��Ұ","������","������","bcb����","��Ȼ�ط�","�����ط���","���Ժ�","�����","����","������",
		"����","��","�ɹ�����","�Ͻ�ֻ�","�����","�ڲ�Ŀ��","����","����","������","�滮��","�����˷���","���Բ�����","���������","�����ҵ���","��Ѫ��","123��","����","СС�ɻ�","СJJ","��BB","С����2","׬Ǯ��",
		"���һ����","��������������","������������","����","����","�㰮����","�ְֵ�","С����","�ٺ�","������","���޿�","������","����B","����B","����","�Ͻ�ּƻ�","bnxc�����ط���","�����ͼ��","��ɻ��ֹ⾵",
		"�ܵ�����","�ط���","�����Ʒ�","����������","��ʱ����","�ܵ������","78968456-=","896780-0-0-0-","09-89877789998",";lkio-p08p8io","dsfsr4354ednhk","4345354357667","d25edg45","sdfe53245ser","7ghjty8757656"
		,"sdf43grffffffffg","45640594561243","sdfsdf43563456","sdfw5sfvedf","k6hgbf65y","c4446ygbf","dfgsert345","fghgfhfh","dfvsdf","rstgbc66456","���","��ٸԶ���ʡ","��ʦ���ܵ���","����ط�ҵ","�׷�ʽ����","��n����"
		,"bdryʿ�����","��������","��ʦ��ʮ��","�ֹ⾵����","��ʦ���ܵ�","�����Ϸ���","ʮ��","����","JAY","������һ��","��У","���Ǵ�ҵ�","�����ҵ�","����������","����","�������","��2��","�ֵ�","br57uddt45","dsfse534"
		,"1314","hkjt68678","n56744535","sd2546546657","vbe457674","beseq557435","seegbbbb47667456","cvbrdtyhnds","ghjfedfsgfsd","fdgreumnb","˾�������","������``","�ҵ�BB�ô�Ŷ","Сѧ�ʹ���","����","bnvn�Ʒ���Ȼ",
		"�����Ϸ���","�ܵ���̸��","S����","��BҪ����","��2��Ҫ����","KKKKK��","ҡͷ","����","ŪŪŪ","��BBBBBBBBBB","��B��","��׳��","bfj�����ط�","��ٸԵط���","�Ҳ�����ĸ","�׵��B��","��˵��","����250","����123",
		"СС����","���Ǹ�����","����Ҫ����","�念��ɻ�","��·��","����ͷ","250","13��","OOBBB","�ǹ�С����","�����д�ͷ��","�Ϸ�","������","bnvdh����","������","���ɹŻ���","46����˵",",myyy874345","sadasrvv3456",
		"mhik869456","mngyufgsd","ada43rfdfy","nmbjkhhhhdfg","aaawecdf","vnvvyu789ec","vccxrtgvcc","vsddgt4y","XCZ3R45777777","XDER6DFF","VCXDFG4R6DFBF","SDFWE5GMNK","3423556768","VBCVXT54","XC544DGFFB,H","VBNNFGUJRDF",
		"VBCCCDSFCV","BDSR43DFTGDF","NBVHRFUYBF35445","DGDGDGDFGD","NBBBFFFF","VBDFYGVJ","FGDRTFG4565","����������","45�ߵ͸�445��ʦ��","��������","bfyr��ʳ���","�����̷�ͷ","�ܵ�4����","���ӹ涨��","�컨�ۻ��",
		"sdw54557543gf","14578646","cdser34545","80789796756gh","feds4335646","fg75763545","b5r6bed45t","gh644767456","fd4657yge4","f25vefgfyyyyvh","ngjr5544454","65753653463","bbfh4643fdsv","esf24rfss5","dsfewrbdf54r65",
		"�׷�ɫ��","453.123.132","�д�","���ͷ�����","�������","��ɻ��ػ�","ʿ����ϵط�����","ˮ����","bdrbˮ��������","��������6666667","�����ջ�","�ɿɿ���","��̽008","fesrvdf����","cfhf����","������̨�ǳ�",
		"������ɽɽˮˮ�幤��","drtfh�����","sdfvxdͶ��","ţ���ߺ���gn","ergvegd�����̸��","�й滮��","�ܷ����Ȼ�ձ�","��ͽ�Ѿ�","cxrtbfd","CVRERTBFH","CBFGDGG","MGJMNHGYU","FGHRTF576846","GFHTFGH","ADQDSSR","BABY",
		"�Ƽ�Ԥ��","�ӱ������","��Ϊɱ�˷�����","���ഺ��ɫ��ȥ","nn�����������","�Ⱥ�΢��΢","������","��������Ա��","����ɼ��⻷��","ʿ��򷸵���","��ٷ����˷�","��ĺܰ���","456456","�㽻�ᷢ��","�滮�ָ�",
		"ʿ���ʿ���","��ຽ��","�㷺�й�ȷ���","�ɹ�����ͬ���","��ʱ��23534","�㽻��ֽ�����","��ʹ�ݵ�����","hgj78ghu6544234","g54yfgy654fg","rrrrrrrrwewe","223244355drdtr","dfgdfgg545","xiiaodongwww3424",
		"kkk56574567","�Ͻ���Ѿ��ڲ�","�㽻�Ḵ����","�淶������ͤ","987645321","123456789","4567842456","���ܿ������","�Ͻ�Ů����","54345654245","������������","���ܿ�","��ٸ���ٸ�","�����","gfhtvvbdfg�ط�",
		"hgjygff4486","kj;iofgty","jhkjunhjk","gfftyhfgg","566413455","��ɻ�","����","13984237814","567456465","�����޵е�","�������","�ڹ�����","��������","������","�ط��ɹ���","ӪҵԱ","54874453478","����","������````"
		,"����������","�������B","���Ҷ�```","�����̵�","����������","���ȹ滮��","�ɹ���","7867854","��Ϊ��`","��������","57835993","�۹�ƻ�","ɵɵ��","��ò�","����ţ","������","����","�ҵ���","�ǺǺ�","����",
		"��ʦ��","����","���ܵ���в","�Ұ���","�ο���","�ɻ�","������","�ƽ�����","�ඡ","�Y�ن�ʄ��","���ܿ�ۼ�","ʿ���","�����㷨","�ֹ⾵����","���ʷ�","����","�׷�","dfsgdf4563","jmh","ǡʺ㶵���¨","�������"
		,"���ġ���ү","Ѧ��","�ϲ���","ҹ�ա�","�꣦��","�����к�","Ұ�ٺ�","78938028","����","����o������","ʧ��","9187009","���������","7758258","���v����","83974200","��õ��","����","��","����","*��EN.o��","����",
		"�ﱦ�컨","¶¶","�A�����","����","�ǶѶ�","�l&�c&�᠎�h","�ҡ�����˭��","/ka����","5555","xlt","ʮһ�µ���","������","��...Ӱ.","sdf4fgfy565","MAN��ʮ","����","1127197231","����","&���衤����~","������ʹ",
		"iloveyou","ʱ�պ���","��ͷ������","���ר��","������","˫����","11811791985","1106659702","�����롱����","����`Ȧo�য","С����","����","��W��ؐ�n","��ҽ","����.��ˬ","����ΰ","��ҹ������","@��*��&","����",
		"��߾���˭��","ľ��","����.����","��Ҷ","����h_/~","(���K���D~~","feeling","ǧ����ˮ","��EN.o��","������","�Ҹ�","�Ҹ����","������Ե","�ѵú�Ϳ",".����~","������","���פ��ݤ�","��","�u/�]�s_�y��","@�ߵ�[8]��"
		,"����","��ѩ","͵�����ݵ���","���S������","������GO��","���H�H","Ψһ�İ�","Angel&΢Ц","�Ҹ�Ů��","�����","�t*��EN.o��","�տ�","��������","Ů������ǿ","�椾Ե","���|���.","�ڂ���������","������","����",
		"С��","�܁�؈�O�m��","���Ą���","[ݭ]߀�Ǧ肀","��ؐ���\��",".���.����",":�q�s�� �T�٨y__","[����Ȣ]","�ʷɻ���[","lu8226421","jlyh7855688","kghu56845","582484245","jycvdrbg","hjhybvf","evdvfss","˧��",
		"�����baby�i","ؼ.���c�S�H","����������","�����z�挚�h","ë�ϼ���","��~[��]~��","�������Ʈ��","��ϰ�ߡ�����","D���g���Ψ�","���ס�������","����ܰ","cvbcvb","�糾����","��Ӱ�Ӥ�����","ʧ�����ǧ","С��","��Ĭ����"
		,"��������","��÷����","��ģ����","���Ωg�Υ�","����","������ս","��������","����Ȼŵ","������ɱ����","dandijunqi","α��","ҹ����","ժ��","mpstd","�ﲻ����","�������","������ɳ","������","������","��������",
		"С�ڹ�","sorry","������","��Ƭ��","����","����������","˫�ӻ���","����֮��","�w��","���˺�ķ","waynespz","��С��","��į��ȼ��","���","����","������Ӱ","�ʼ�����","��ӥ98","�ϵ�ҲDIY","ʦ̫���Ͱ�","�����ë","ϣ������"
		,"������","�������","���֮��","Ŵ������","��������","��֮��","��ã֮��","ǿ�˽�","ʯ������","��ʱ�ڷ�","������","������","ޭޭ","������","�F��","Ҧ���Q","�˻�����"};
	
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
			MessageBox("�޸ĳɹ���");

		}
		else
			MessageBox("�޸�ʧ�ܣ�");
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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
		MessageBox("��Ϣ��д��������","����");
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
	MessageBox("key.ini�ļ�������кŴ������QQ��306060847��ȡ");
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
			MessageBox("�޸ĳɹ���");

		}
		else
			MessageBox("�޸�ʧ�ܣ�");

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
			MessageBox("�޸ĳɹ���");

		}
		else
			MessageBox("�޸�ʧ�ܣ�");

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
		MessageBox("����������");
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
			MessageBox("�޸ĳɹ���");

		}
		else
			MessageBox("�޸�ʧ�ܣ�");
	}
	catch (_com_error &e)
	{
		MessageBox(e.Description());
	}
}

