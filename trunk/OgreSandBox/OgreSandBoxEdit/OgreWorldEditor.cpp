#include "stdafx.h"
#include "OgreWorldEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	WorldEditor::WorldEditor(const String& szName)
		: Editor(szName)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	WorldEditor::~WorldEditor()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	WorldEditorFactory::WorldEditorFactory(const String& typeName)
		: EditorFactory(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	WorldEditorFactory::~WorldEditorFactory()
	{
		
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Editor*		WorldEditorFactory::create(const String& szName, const SEditorAdp& seadp, Editor* pParent)
	{
		const SWorldAdp& adp = static_cast<const SWorldAdp&>(seadp);

		// create world editor
		WorldEditor* pEditor = new WorldEditor(szName);
		if (pEditor)
		{
			try{
				if(!pEditor->create(seadp))
				{
					OGRE_EXCEPT(Exception::ERR_RT_ASSERTION_FAILED, 
						"create edtiro : " + szName + " failed", "WorldEditorFactory::create");
				}

				// register parent
				if (pParent)
					pParent->registerEditor(pEditor);

				return pEditor;
			}
			catch(Exception& e)
			{
				MessageBox(NULL, e.getDescription().c_str(), NULL, NULL);
			}

			SAFE_DELETE(pEditor)
		}

		return NULL;
	}
}