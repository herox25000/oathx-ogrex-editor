#ifndef _____OgreDebugDrawer_H
#define _____OgreDebugDrawer_H
 
#include <OgreSingleton.h>
#include <map>
 
namespace Ogre
{
	typedef std::pair<Ogre::Vector3, Ogre::ColourValue> VertexPair;

#define DEFAULT_ICOSPHERE_RECURSION_LEVEL	1

	/**
	* \ingroup : Editor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-02-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class IcoSphere
	{
	public:
		struct TriangleIndices
		{
			int v1, v2, v3;

			/**
			 *
			 * \param _v1 
			 * \param _v2 
			 * \param _v3 
			 * \return 
			 */
			TriangleIndices(int _v1, int _v2, int _v3) 
				: v1(_v1), v2(_v2), v3(_v3) 
			{

			}

			/**
			 *
			 * \param &o 
			 * \return 
			 */
			bool operator < (const TriangleIndices &o) const
			{
				return v1 < o.v1 && v2 < o.v2 && v3 < o.v3;
			}
		};

		struct LineIndices
		{
			int v1, v2;

			/**
			 *
			 * \param _v1 
			 * \param _v2 
			 * \return 
			 */
			LineIndices(int _v1, int _v2)
				: v1(_v1), v2(_v2) 
			{

			}

			/**
			 *
			 * \param &o 
			 * \return 
			 */
			bool operator == (const LineIndices &o) const
			{
				return (v1 == o.v1 && v2 == o.v2) || (v1 == o.v2 && v2 == o.v1);
			}
		};

		/**
		 *
		 * \return 
		 */
		IcoSphere();

		/**
		 *
		 * \return 
		 */
		~IcoSphere();

		/**
		 *
		 * \param recursionLevel 
		 */
		void			create(int recursionLevel);

		/**
		 *
		 * \param baseIndex 
		 * \param *target 
		 */
		void			addToLineIndices(int baseIndex, std::list<int> *target);

		/**
		 *
		 * \param *target 
		 * \param &position 
		 * \param &colour 
		 * \param scale 
		 * \return 
		 */
		int				addToVertices(std::list<VertexPair> *target, 
			const Ogre::Vector3 &position, const Ogre::ColourValue &colour, float scale);

		/**
		 *
		 * \param baseIndex 
		 * \param *target 
		 */
		void			addToTriangleIndices(int baseIndex, std::list<int> *target);

	private:
		/**
		 *
		 * \param &vertex 
		 * \return 
		 */
		int				addVertex(const Ogre::Vector3 &vertex);

		/**
		 *
		 * \param index0 
		 * \param index1 
		 */
		void			addLineIndices(int index0, int index1);

		/**
		 *
		 * \param index0 
		 * \param index1 
		 * \param index2 
		 */
		void			addTriangleLines(int index0, int index1, int index2);

		/**
		 *
		 * \param index0 
		 * \param index1 
		 * \return 
		 */
		int				getMiddlePoint(int index0, int index1);

		/**
		 *
		 * \param index0 
		 * \param index1 
		 * \param index2 
		 */
		void			addFace(int index0, int index1, int index2);

		/**
		 *
		 * \param index0 
		 * \param index1 
		 */
		void			removeLineIndices(int index0, int index1);

	private:
		std::vector<Ogre::Vector3>	vertices;
		std::list<LineIndices>		lineIndices;
		std::list<int>				triangleIndices;
		std::list<TriangleIndices>	faces;
		std::map<__int64, int>		middlePointIndexCache;
		int							index;
	};

	/**
	* \ingroup : Editor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-02-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class DebugDrawer : public Ogre::Singleton<DebugDrawer>
	{
	public:
		/**
		 *
		 * \param *_sceneManager 
		 * \param _fillAlpha 
		 * \return 
		 */
		DebugDrawer(Ogre::SceneManager *_sceneManager, float _fillAlpha);

		/**
		 *
		 * \return 
		 */
		~DebugDrawer();

		/**
		 *
		 * \param void 
		 * \return 
		 */
		static DebugDrawer& getSingleton(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		static DebugDrawer* getSingletonPtr(void);

		/**
		 *
		 */
		void				build();

		/**
		 *
		 * \param recursionLevel 
		 */
		void				setIcoSphereRecursionLevel(int recursionLevel);

		/**
		 *
		 * \param &start 
		 * \param &end 
		 * \param &colour 
		 */
		void				drawLine(const Ogre::Vector3 &start, 
			const Ogre::Vector3 &end, const Ogre::ColourValue &colour);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param segmentsCount 
		 * \param colour 
		 * \param isFilled 
		 */
		void				drawCircle(const Ogre::Vector3 &centre, 
			float radius, int segmentsCount, const Ogre::ColourValue& colour, bool isFilled = false);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param segmentsCount 
		 * \param height 
		 * \param colour 
		 * \param isFilled 
		 */
		void				drawCylinder(const Ogre::Vector3 &centre, 
			float radius, int segmentsCount, float height, const Ogre::ColourValue& colour, bool isFilled = false);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param isFilled 
		 */
		void				drawQuad(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, bool isFilled = false);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param isFilled 
		 */
		void				drawCuboid(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, bool isFilled = false);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param colour 
		 * \param isFilled 
		 */
		void				drawSphere(const Ogre::Vector3 &centre, 
			float radius, const Ogre::ColourValue& colour, bool isFilled = false);

		/**
		 *
		 * \param &centre 
		 * \param scale 
		 * \param colour 
		 * \param isFilled 
		 */
		void				drawTetrahedron(const Ogre::Vector3 &centre, 
			float scale, const Ogre::ColourValue& colour, bool isFilled = false);
	
		/**
		 *
		 * \return 
		 */
		bool				getEnabled() 
		{
			return isEnabled;
		}

		/**
		 *
		 * \param _isEnabled 
		 */
		void				setEnabled(bool _isEnabled) 
		{ 
			isEnabled = _isEnabled; 
		}

		/**
		 *
		 */
		void				switchEnabled() 
		{
			isEnabled = !isEnabled;
		}

		/**
		 *
		 */
		void				clear();

	private:
		/**
		 *
		 */
		void				initialise();

		/**
		 *
		 */
		void				shutdown();

		/**
		 *
		 * \param start 
		 * \param end 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildLine(const Ogre::Vector3& start,
			const Ogre::Vector3& end, const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildQuad(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildFilledQuad(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildFilledTriangle(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildCuboid(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param *vertices 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildFilledCuboid(const Ogre::Vector3 *vertices, 
			const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param segmentsCount 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildCircle(const Ogre::Vector3 &centre, 
			float radius, int segmentsCount, const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param segmentsCount 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildFilledCircle(const Ogre::Vector3 &centre, 
			float radius, int segmentsCount, const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param segmentsCount 
		 * \param height 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildCylinder(const Ogre::Vector3 &centre, 
			float radius, int segmentsCount, float height, const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param &centre 
		 * \param radius 
		 * \param segmentsCount 
		 * \param height 
		 * \param colour 
		 * \param alpha 
		 */
		void				buildFilledCylinder(const Ogre::Vector3 &centre, 
			float radius, int segmentsCount, float height, const Ogre::ColourValue& colour, float alpha = 1.0f);

		/**
		 *
		 * \param &centre 
		 * \param scale 
		 * \param &colour 
		 * \param alpha 
		 */
		void				buildTetrahedron(const Ogre::Vector3 &centre, 
			float scale, const Ogre::ColourValue &colour, float alpha = 1.0f);

		/**
		 *
		 * \param &centre 
		 * \param scale 
		 * \param &colour 
		 * \param alpha 
		 */
		void				buildFilledTetrahedron(const Ogre::Vector3 &centre, 
			float scale, const Ogre::ColourValue &colour, float alpha = 1.0f);

		/**
		 *
		 * \param &vertex 
		 * \param &colour 
		 * \return 
		 */
		int					addLineVertex(const Ogre::Vector3 &vertex, const Ogre::ColourValue &colour);

		/**
		 *
		 * \param index1 
		 * \param index2 
		 */
		void				addLineIndices(int index1, int index2);

		/**
		 *
		 * \param &vertex 
		 * \param &colour 
		 * \return 
		 */
		int					addTriangleVertex(const Ogre::Vector3 &vertex, const Ogre::ColourValue &colour);

		/**
		 *
		 * \param index1 
		 * \param index2 
		 * \param index3 
		 */
		void				addTriangleIndices(int index1, int index2, int index3);

		/**
		 *
		 * \param index1 
		 * \param index2 
		 * \param index3 
		 * \param index4 
		 */
		void				addQuadIndices(int index1, int index2, int index3, int index4);
	private:

		Ogre::SceneManager*		sceneManager;
		Ogre::ManualObject*		manualObject;
		float					fillAlpha;
		IcoSphere				icoSphere;

		bool					isEnabled;

		std::list<VertexPair>	lineVertices, triangleVertices;
		std::list<int>			lineIndices, triangleIndices;

		int						linesIndex, trianglesIndex;
	};
}

 
#endif