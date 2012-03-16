#ifndef _____OgreRefCounted_h_
#define _____OgreRefCounted_h_

// Start of Ogre namespace section
namespace Ogre
{
	/*!
	\brief
		Simple, generic, reference counted pointer class.  This is primarily here
		for use by the Events system to track when to delete slot bindings.
	*/
	template<typename T>
	class RefCounted
	{
	public:
		/*!
		\brief
			Default constructor.
		*/
		RefCounted() :
			d_object(0),
			d_count(0)
		{
		}

		/*!
		\brief
			Contruct a RefCounted object that wraps the pointer \a ob.
		*/
		RefCounted(T* ob) :
			d_object(ob),
			d_count((ob != 0) ? new unsigned int(1) : 0)
		{
		}

		/*!
		\brief
			Copy constructor
		*/
		RefCounted(const RefCounted<T>& other) :
			d_object(other.d_object),
			d_count(other.d_count)
		{
			if (d_count)
				addRef();
		}

		/*!
		\brief
			Destructor.  Only deletes the associated object if no further references
			exist.
		*/
		~RefCounted()
		{
			if (d_object)
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
				if (d_object)
					release();

				d_object = other.d_object;
				d_count = d_object ? other.d_count : 0;

				if (d_count)
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
			return d_object == other.d_object;
		}

		/*!
		\brief
			Return whether the two RefCounted ptrs are not equal
			(point to different objects)
		*/
		bool operator!=(const RefCounted<T>& other) const
		{
			return d_object != other.d_object;
		}

		/*!
		\brief
			Return the object referred to by the wrapped pointer.
			(beware of null pointers when using this!)
		*/
		const T& operator*() const
		{
			return *d_object;
		}

		T& operator*()
		{
			return *d_object;
		}

		/*!
		\brief
			Return the wrapped pointer.
		*/
		const T* operator->() const
		{
			return d_object;
		}

		T* operator->()
		{
			return d_object;
		}

		/*!
		\brief
			Return whether the wrapped pointer is valid.  i.e. that it is not null.
		*/
		bool isValid() const
		{
			return d_object != 0;
		}

	private:
		/*!
		\brief
			Increases the reference count for the wrapped object.
		*/
		void addRef()
		{
			++*d_count;
		}

		/*!
		\brief
			Decreases the reference count for the wrapped object, and if the count
			has reached zero, the object and the shared counter are deleted.
		*/
		void release()
		{
			if (!--*d_count)
			{
				delete d_object;
				delete d_count;
				d_object = 0;
				d_count = 0;
			}
		}

		T* d_object;            //! pointer to the object.
		unsigned int* d_count;  //! pointer to the shared counter object.
	};

} // End of  Ogre namespace section

#endif  // end of guard _CEGUIRefCounted_h_
