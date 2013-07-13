#include "Og2dInputManager.h"

namespace Og2d
{
	template<>	InputManager*	Singleton<InputManager>::mpSingleton = 0;
	/**
	 *
	 * \return 
	 */
	InputManager&	InputManager::getSingleton()
	{
		assert(mpSingleton != NULL); return (*mpSingleton);
	}

	/**
	 *
	 * \return 
	 */
	InputManager*	InputManager::getSingletonPtr()
	{
		assert(mpSingleton != NULL); return mpSingleton;
	}

	/**
	 *
	 * \return 
	 */
	InputManager::InputManager()
	{

	}

	/**
	 *
	 * \return 
	 */
	InputManager::~InputManager()
	{
		VectorInputListener::iterator it = m_vInput.begin();
		while ( it != m_vInput.end() )
		{
			SAFE_DELETE(*it); it = m_vInput.erase(it);
		}
	}

	/**
	 *
	 * \param pListener 
	 */
	void	InputManager::addInputListener(InputListener* pListener)
	{
		VectorInputListener::iterator it = find(m_vInput.begin(), m_vInput.end(),
			pListener);
		if ( it == m_vInput.end() )
		{
			m_vInput.push_back(pListener);
		}
	}

	/**
	 *
	 * \param pListener 
	 */
	void	InputManager::removeInputListener(
		InputListener* pListener)
	{
		VectorInputListener::iterator it = find(m_vInput.begin(), m_vInput.end(),
			pListener);
		if ( it != m_vInput.end() )
		{
			SAFE_DELETE(*it); m_vInput.erase(it);
		}
	}
	
	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool	InputManager::injectEvent(const SInputEvent& evt)
	{
		for (VectorInputListener::iterator it=m_vInput.begin();
			it!=m_vInput.end(); it++)
		{
			if ((*it)->OnEvent(evt))
				return true;
		}

		return 0;
	}
}