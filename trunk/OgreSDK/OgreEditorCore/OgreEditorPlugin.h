#ifndef _____OgreEditorPlugin_H
#define _____OgreEditorPlugin_H

#include "OgreEditorInput.h"

namespace Ogre
{
	// ��������������
	struct SEditorPluginAdp
	{
		// �������
		String		pluginName;
	};

	//////////////////////////////////////////////////////////////////////////
	// ���ӳ���
	typedef HashMap<String, EditorPlugin*>		HashMapEditorPlugin;
	// ���������
	typedef MapIterator<HashMapEditorPlugin>	HashMapEditorPluginIter;

	enum{
		PRIORITY_LOWEST,
		PRIORITY_LOW,
		PRIORITY_NORMAL,
		PRIORITY_HEIGHT,
	};

	/**
	* \ingroup : OgreEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-14
	*
	* \Author  : lp
	*
	* \Desc    : �༭�������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPlugin : public EditorInput
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorPlugin(const String& pluginName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPlugin();

		/** ���ñ༭�����
		 *
		 * \param name 
		 */
		virtual	void					setName(const String& pluginName);

		/** ��ȡ�༭�����
		 *
		 * \return 
		 */
		virtual	String					getName() const;

		/** ע��༭���
		 *
		 * \param pPlugin 
		 * \return 
		 */
		virtual	bool					registerPlugin(EditorPlugin* pPlugin);

		/** ��ȡ�༭���
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorPlugin*			getPlugin(const String& pluginName);

		/**
		 *
		 * \param pluginName 
		 * \return 
		 */
		virtual	EditorPlugin*			findPlugin(const String& pluginName);

		/** ע���༭���
		 *
		 * \param pPlugin 
		 */
		virtual	void					unregisterPlugin(EditorPlugin* pPlugin, bool bDestroy=true);

		/** ���ø��༭��
		 *
		 * \param pParent 
		 */
		virtual	void					setParent(EditorPlugin* pParent);

		/** ��ȡ��ǰ�༭���ĸ���
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getParent() const;
		
		/** �������б༭��
		 *
		 */
		virtual	void					destroyAllPlugin();

		/** ��ȡ�Ӳ��������
		 *
		 * \return 
		 */
		virtual	HashMapEditorPluginIter	getPluginIter();
		

		/** �������ȼ��������ȼ��������༭�����ɾ��˳��
		 *
		 * \param nPriority 
		 */
		virtual void					setPriority(int nPriority);

		/** ��ȡ���ȼ�
		 *
		 * \return 
		 */
		virtual	int						getPriority() const;

	public:
		/** ���༭�������ڴ�С�����ı�ʱ����
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool					OnSize(int cx, int cy);

		/** �����ָı�ʱ����
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseWheel(float fzDelta, const Vector2& vPos);

		/** ����������
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonDown(const Vector2& vPos);

		/** ����������
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonUp(const Vector2& vPos);

		/** ����Ҽ�����
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonDown(const Vector2& vPos);

		/** ����������
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonUp(const Vector2& vPos);

		/** ����ƶ�
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseMove(const Vector2& vPos);

		/** ���̰�������
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** ���̰�������
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** �༭���Ըı�
		 *
		 * \param parentName 
		 * \param name 
		 * \param anyValue 
		 * \param nType 
		 * \return 
		 */
		virtual	bool					OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

	protected:
		HashMapEditorPlugin				m_HashMapEditorPlugin;
		String							m_Name;
		EditorPlugin*					m_pParent;
		int								m_nPriority;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : �����������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		EditorPluginFactory(const String& factoryName)
			: m_factoryName(factoryName)
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPluginFactory()
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual	String			getName() const
		{
			return m_factoryName;
		}
		
		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*	createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent) = 0;

	protected:
		String					m_factoryName;
	};
}

#endif