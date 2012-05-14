#include "stdafx.h"
#include "Xavier.h"
#include "ServerFactoryDialog.h"
#include "OgreSdk.h"

IMPLEMENT_DYNAMIC(CServerFactoryDialog, CDialog)

using namespace Ogre;

/**
 *
 * \param
 * \return 
 */
CServerFactoryDialog::CServerFactoryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CServerFactoryDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CServerFactoryDialog::~CServerFactoryDialog()
{
	for (int i=0; i<m_wFactoryBox.GetCount(); i++)
	{
		m_wFactoryBox.DeleteString(i);
	}
}

/**
 *
 * \param pDX 
 */
void CServerFactoryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_wFactoryBox);
}


BEGIN_MESSAGE_MAP(CServerFactoryDialog, CDialog)
	ON_LBN_DBLCLK(IDC_LIST2, &CServerFactoryDialog::OnLbnDblclkListServerFactoryItem)
END_MESSAGE_MAP()


/**
 *
 * \return 
 */
BOOL CServerFactoryDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
#ifdef _DEBUG
		System::getSingleton().loadPlugin("Plugin_Terrain_d.dll");
#else
		System::getSingleton().loadPlugin("Plugin_Terrain.dll");
#endif

	return TRUE;
}

/**
 *
 */
void CServerFactoryDialog::UpdateFactory()
{
	// 清空服务工厂
	for (int i=0; i<m_wFactoryBox.GetCount(); i++)
	{
		m_wFactoryBox.DeleteString(i);
	}
	
	// 添加可用的工厂
	ServerFactoryIter hashServerFactory = System::getSingletonPtr()->getHashServerFactory();
	for(ServerFactoryIter::iterator it=hashServerFactory.begin(); 
		it!=hashServerFactory.end(); it++)
	{
		m_wFactoryBox.AddString(it->first.c_str());
	}
}

/**
 *
 */
void CServerFactoryDialog::OnLbnDblclkListServerFactoryItem()
{
	int nCurSel = m_wFactoryBox.GetCurSel();
	if (nCurSel > 0 && nCurSel < m_wFactoryBox.GetCount())
	{
		CString typeName;
		m_wFactoryBox.GetText(nCurSel, typeName);

		if (!typeName.IsEmpty())
		{
		
		}
	}
}
