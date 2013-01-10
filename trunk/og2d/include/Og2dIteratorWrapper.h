#ifndef _____Og2dIteratorWrapper_H
#define _____Og2dIteratorWrapper_H

namespace Og2d{

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T, typename IteratorType, typename ValType>
	class IteratorWrapper
	{
	private:
		/**
		 *
		 * \return 
		 */
		IteratorWrapper();

	protected:
		IteratorType mBegin;
		IteratorType mCurrent;
		IteratorType mEnd;
	
	public:
		typedef ValType			ValueType;
		typedef ValType*		PointerType;
		typedef IteratorType	iterator;
		
		typedef IteratorType	const_iterator;

		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		IteratorWrapper ( IteratorType start, IteratorType last )
			: mBegin( start ), mCurrent ( start ), mEnd ( last )
		{
		}

		/**
		 *
		 * \return 
		 */
		bool				hasMoreElements ( ) const
		{
			return mCurrent != mEnd;
		}

		/**
		 *
		 */
		void				moveNext (  )
		{
			++mCurrent;
		}

		/**
		 *
		 * \return 
		 */
		const IteratorType& begin() 
		{
			return mBegin;
		}
		
		/**
		 *
		 * \return 
		 */
		IteratorType&		current()
		{
			return mCurrent;
		}
		
		/**
		 *
		 * \return 
		 */
		const IteratorType& end()
		{
			return mEnd;
		}
	};


	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T, typename IteratorType> 
	class VectorIteratorWrapper : public IteratorWrapper<T, IteratorType, typename  T::value_type>
	{
	public:
		typedef typename IteratorWrapper<T, IteratorType, typename  T::value_type>::ValueType ValueType ; 
		typedef typename IteratorWrapper<T, IteratorType, typename  T::value_type>::PointerType PointerType ;
	
		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		VectorIteratorWrapper ( IteratorType start, IteratorType last )
		: IteratorWrapper<T, IteratorType, typename T::value_type>( start, last ) 
		{
		}

		/**
		 *
		 * \return 
		 */
		ValueType		peekNext() const
		{
			return *(this->mCurrent);
		}

		/**
		 *
		 * \return 
		 */
		PointerType		peekNextPtr()  const
		{
			return &(*(this->mCurrent) );
		}

		/**
		 *
		 * \return 
		 */
		ValueType		getNext() 
		{
			return *(this->mCurrent++);
		}	

	};


	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T> class VectorIterator : public VectorIteratorWrapper<T,  typename T::iterator>
	{
	public:
		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		VectorIterator( typename T::iterator start, typename T::iterator last )
			: VectorIteratorWrapper<T,  typename T::iterator>(start , last )
		{
		}

		/**
		 *
		 * \param c 
		 * \return 
		 */
		explicit VectorIterator( T& c )
			: VectorIteratorWrapper<T,  typename T::iterator> ( c.begin(), c.end() )
		{
		}
	};


	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T> class ConstVectorIterator : public VectorIteratorWrapper<T,  typename T::const_iterator>
	{
	public:
		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		ConstVectorIterator( typename T::const_iterator start, typename T::const_iterator last )
		: VectorIteratorWrapper<T,  typename T::const_iterator> (start , last )
		{
		}

		/**
		 *
		 * \param c 
		 * \return 
		 */
		explicit ConstVectorIterator ( const T& c )
		 : VectorIteratorWrapper<T,  typename T::const_iterator> (c.begin() , c.end() )
		{
		}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T, typename IteratorType> 
	class MapIteratorWrapper  : public IteratorWrapper<T, IteratorType, typename T::mapped_type>
	{
	public:
		typedef typename IteratorWrapper<T, IteratorType, typename  T::mapped_type>::ValueType ValueType; 
		typedef typename IteratorWrapper<T, IteratorType, typename  T::mapped_type>::PointerType PointerType;
		typedef typename T::value_type PairType ; 
		typedef typename T::key_type KeyType;
        
		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		MapIteratorWrapper ( IteratorType start, IteratorType last )
		: IteratorWrapper<T, IteratorType, typename T::mapped_type>( start, last ) 
		{
		}

		/**
		 *
		 * \param void 
		 * \return 
		 */
		KeyType				peekNextKey(void) const
		{
			return this->mCurrent->first;
		}

		/**
		 *
		 * \return 
		 */
		ValueType			peekNextValue (  ) const
		{
			return this->mCurrent->second;
		}

		/**
		 *
		 * \return 
		 */
		const PointerType	peekNextValuePtr (  )  const
		{
			return &(this->mCurrent->second);
		}

		/**
		 *
		 * \return 
		 */
		ValueType			getNext()
		{
			return ((this->mCurrent++)->second) ;
		}
	};


	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T> 
	class MapIterator : public MapIteratorWrapper<T,  typename T::iterator>
	{
	public:
		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		MapIterator( typename T::iterator start, typename T::iterator last )
			: MapIteratorWrapper<T,  typename T::iterator>(start , last )
		{
		}

		/**
		 *
		 * \param c 
		 * \return 
		 */
		explicit MapIterator( T& c )
			: MapIteratorWrapper<T,  typename T::iterator> ( c.begin(), c.end() )
		{
		}
			
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template <typename T> 
	class ConstMapIterator : public MapIteratorWrapper<T,  typename T::const_iterator>
	{
	public:
		/**
		 *
		 * \param start 
		 * \param last 
		 * \return 
		 */
		ConstMapIterator( typename T::const_iterator start, typename T::const_iterator last )
			: MapIteratorWrapper<T,  typename T::const_iterator> (start , last )
		{
		}

		/**
		 *
		 * \param c 
		 * \return 
		 */
		explicit ConstMapIterator ( const T& c )
			: MapIteratorWrapper<T,  typename T::const_iterator> (c.begin() , c.end() )
		{
		}
	};

}

#endif
