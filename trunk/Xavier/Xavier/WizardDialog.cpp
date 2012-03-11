#include "stdafx.h"
#include "Xavier.h"
#include "WizardDialog.h"
#include "OgreEditor.h"


IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

using namespace Ogre;

/**
 *
 * \param /* 
 * \return 
 */
CWizardDialog::CWizardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CWizardDialog::~CWizardDialog()
{
}

/**
 *
 * \param pDX 
 */
void	CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCENEMANAGER, m_cbSceneTypeMask);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDOK,							&CWizardDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,						&CWizardDialog::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENEMANAGER,	&CWizardDialog::OnCbnSelchangeComboScenemanager)
END_MESSAGE_MAP()

/**
 *
 * \param typeMask 
 * \return 
 */
Ogre::SceneTypeMask		GetSceneTypeMask(const CString& typeMask)
{
	if (typeMask == "ST_EXTERIOR_CLOSE")
		return ST_EXTERIOR_CLOSE;

	if (typeMask == "ST_EXTERIOR_FAR")
		return ST_EXTERIOR_FAR;

	if (typeMask == "ST_EXTERIOR_REAL_FAR")
		return ST_EXTERIOR_REAL_FAR;

	if (typeMask == "ST_INTERIOR")
		return ST_INTERIOR;

	return ST_GENERIC;
}

/**
 *
 * \return 
 */
BOOL	CWizardDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	/** Classification of a scene to allow a decision of what type of
	SceenManager to provide back to the application.
	
	enum SceneType
	{
		ST_GENERIC = 1,
		ST_EXTERIOR_CLOSE = 2,
		ST_EXTERIOR_FAR = 4,
		ST_EXTERIOR_REAL_FAR = 8,
		ST_INTERIOR = 16
	};
	*/

	m_cbSceneTypeMask.AddString("ST_GENERIC");
	m_cbSceneTypeMask.AddString("ST_EXTERIOR_CLOSE");
	m_cbSceneTypeMask.AddString("ST_EXTERIOR_FAR");
	m_cbSceneTypeMask.AddString("ST_EXTERIOR_REAL_FAR");
	m_cbSceneTypeMask.AddString("ST_INTERIOR");

	return TRUE;
}

/**
 *
 */
void	CWizardDialog::OnBnClickedOk()
{
	BaseEditorFactory* pSceneFactory = EditSystem::getSingletonPtr()->getEditorFactory(FACTORY_SCENEMANAGER);
	if (pSceneFactory != NULL)
	{
		SSceneManagerCreateParam cm;
		cm.sName				= NAME_SCENEMANAGER;
		cm.typeMask				= GetSceneTypeMask(m_typeMask);

		EditSystem::getSingletonPtr()->addEditor(pSceneFactory->create(&cm));
	}

	BaseEditorFactory* pCameraFactory = EditSystem::getSingletonPtr()->getEditorFactory(FACTORY_CAMERA);
	if (pCameraFactory != NULL)
	{
		SCameraCreateParam cm;
		cm.vPos					= Vector3(0,50,500);
		cm.vLookAt				= Vector3(0,100,-300);
		cm.fNearClipDistance	= 5;
		cm.fFarClipDistance		= 10;
		cm.fYaw					= 0;
		cm.fPitch				= 0;

		EditSystem::getSingletonPtr()->addEditor(pCameraFactory->create(&cm));
	}

	BaseEditorFactory* pViewFactory	= EditSystem::getSingletonPtr()->getEditorFactory(FACTORY_VIEWPORT);
	if (pViewFactory != NULL)
	{
		SViewPortCreateParam cm;
		cm.background			= ColourValue(0,0,0,0);

		EditSystem::getSingletonPtr()->addEditor(pViewFactory->create(&cm));
	}

	OnOK();
}

/**
 *
 */
void	CWizardDialog::OnBnClickedCancel()
{

	OnCancel();
}

/**
 *
 */
void	CWizardDialog::OnCbnSelchangeComboScenemanager()
{
	m_cbSceneTypeMask.GetLBText(m_cbSceneTypeMask.GetCurSel(),
		m_typeMask);
}
