#ifndef _____OgreServerTerrainGlobalOption_H
#define _____OgreServerTerrainGlobalOption_H

#include "OgreServer.h"

namespace Ogre
{
	/**
	* \ingroup : Plugin_Terrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-13
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainGlobalOptionServer : public Server
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param fMaxPixelError 
		 * \param CompositeMapDistance 
		 * \param vLightMapDirection 
		 * \param clrAmbientLight 
		 * \param clrCompositeMapDiffuse 
		 * \return 
		 */
		TerrainGlobalOptionServer(const String& typeName, float fMaxPixelError, float CompositeMapDistance, 
			const Vector3& vLightMapDirection, const ColourValue& clrCompositeMapDiffuse);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainGlobalOptionServer();

	protected:
		TerrainGlobalOptions*			m_pGlobalOption;
	};

	// ����ȫ�����ò���
	struct STerrainGlobalOptionServerAdp : public SSAdp
	{
		float							fMaxPixelError;
		float							fCompositeMapDistance;
		Vector3							vLightMapDirection;
		ColourValue						clrCompositeMapDiffuse;
	};

	/**
	* \ingroup : Plugin_Terrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-13
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainGlobalOptionServerFactory : public ServerFactory
	{
	public:
		static const String		FactoryTypeName;

	public:
		/**
		 *
		 * \return 
		 */
		TerrainGlobalOptionServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainGlobalOptionServerFactory();

		/** ��ȡ������
		 *
		 * \return 
		 */
		virtual String			getTypeName() const;
	
		/** ��������
		 *
		 * \param pAdp	�����������
		 * \return 
		 */
		virtual Server*			createServer(const SSAdp& ssadp);
		
	};
}

#endif