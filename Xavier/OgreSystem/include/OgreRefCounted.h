#ifndef _____OgreRefCounted_h_
#define _____OgreRefCounted_h_

namespace Ogre
{
	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	template<typename T> class RefCounted
	{
	public:
		/*!
		\brief
			Default constructor.
		*/
		RefCounted() :
			m_object(0),
			m_count(0)
		{
		}

		/*!
		\brief
			Contruct a RefCounted object that wraps the pointer \a ob.
		*/
		RefCounted(T* ob) :
			m_object(ob),
			m_count((ob != 0) ? new unsigned int(1) : 0)
		{
		}

		/*!
		\brief
			Copy constructor
		*/
		RefCounted(const RefCounted<T>& other) :
			m_object(other.m_object),
			m_count(other.m_count)
		{
			if (m_count)
				addRef();
		}

		/*!
		\brief
			Destructor.  Only deletes the associated object if no further references
			exist.
		*/
		~RefCounted()
		{
			if (m_object)
				release();
		}

		/*!
		\brief
			Assignment operator.  Previously held object gets its reference count
			reduced, and is deleted if no further references exist.  The newly
			assigned object, taken from \a other, gets its count increased.
		*/
		RefCounted<T>& operator=(const RefCounted<T>& other)
		{
			if (*this != other)
			{
				if (m_object)
					release();

				m_object = other.m_object;
				m_count = m_object ? other.m_count : 0;

				if (m_count)
					addRef();
			}

			return *this;
		}

		/*!
		\brief
			Return whether the two RefCounted ptrs are equal
			(point to the same object)
		*/
		bool operator==(const RefCounted<T>& other) const
		{
			return m_object == other.m_object;
		}

		/*!
		\brief
			Return whether the two RefCounted ptrs are not equal
			(point to different objects)
		*/
		bool operator!=(const RefCounted<T>& other) const
		{
			return m_object != other.m_object;
		}

		/*!
		\brief
			Return the object referred to by the wrapped pointer.
			(beware of null pointers when using this!)
		*/
		const T& operator*() const
		{
			return *m_object;
		}

		T& operator*()
		{
			return *m_object;
		}

		/*!
		\brief
			Return the wrapped pointer.
		*/
		const T* operator->() const
		{
			return m_object;
		}

		T* operator->()
		{
			return m_object;
		}

		/*!
		\brief
			Return whether the wrapped pointer is valid.  i.e. that it is not null.
		*/
		bool isValid() const
		{
			return m_object != 0;
		}

	private:
		/*!
		\brief
			Increases the reference count for the wrapped object.
		*/
		void addRef()
		{
			++*m_count;
		}

		/*!
		\brief
			Decreases the reference count for the wrapped object, and if the count
			has reached zero, the object and the shared counter are deleted.
		*/
		void release()
		{
			if (!--*m_count)
			{
				delete m_object;
				delete m_count;
				m_object = 0;
				m_count = 0;
			}
		}

		T*				m_object; //! pointer to the object.
		unsigned int*	m_count;  //! pointer to the shared counter object.
	};
}

#endif
