#ifndef _____Og2dException_H_
#define _____Og2dException_H_

#include "Og2dTypes.h"
#include <sstream>
#include <iosfwd>

namespace Og2d
{
	//! ö���쳣
	enum EXCEPTION_CODE
	{
		//! ����д�ļ�
		EC_CANNOT_WRITE_TO_FILE,

		//! ��Ч״̬
		EC_INVALID_STATE,

		//! ��Ч����
		EC_INVALIDPARAMS,

		//! ��Ⱦ����
		EC_RENDERINGAPI_ERROR,

		//! ��ͬ��
		EC_DUPLICATE_ITEM,

		//! �����ҵ�ָ����
		EC_ITEM_NOT_FOUND,
 
		//! �����ҵ�ָ���ļ�
		EC_FILE_NOT_FOUND,

		//! �ڲ�����
		EC_INTERNAL_ERROR,

		//! ����ʧ��
		EC_RT_ASSERTION_FAILED,

		//! ���ܴ��ļ�
		EC_CANNOT_OPEN_FILE,
		
		//! δ�ܷ��䵽�ڴ�
		EC_ALLOC_MEMORY_ERROR,
		
		//! ����ʧ��
		EC_CREATE_FAILED,

		//!
		EC_NOT_IMPLEMENTED,
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API Exception : public std::exception
	{
	public:
		//! ���캯��
		/**
		*
		* \param nCode			�쳣����
		* \param &description	�쳣����
		* \param &source		�쳣����λ��
		* \return 
		*/
		Exception(int nCode, const String &description, const String &source);
		
			
		//! ���캯��
		/**
		*
		* \param nCode			�쳣����
		* \param &description	�쳣����
		* \param &source		�쳣����λ��
		* \param type			�쳣����
		* \param file			�쳣�����ļ�
		* \param line			�쳣�����ļ�������
		* \return 
		*/
		Exception(int nCode, const String &description, const String &source, const char* type, const char* file, long line);

		//! ��������
		/**
		*
		* \param &rhs 
		* \return 
		*/
		Exception(const Exception &rhs)
			:m_line(rhs.m_line), m_code(rhs.m_code), m_description(rhs.m_description), m_source(rhs.m_source), m_file(rhs.m_file)
		{

		}

		//! ��������
		/**
		*
		* \return 
		*/
		~Exception() throw() {}

		//! ���� = 
		/**
		*
		* \param &rhs 
		*/
		void operator = (const Exception &rhs)
		{
			m_description	= rhs.m_description;
			m_code			= rhs.m_code;
			m_source		= rhs.m_source;
			m_file			= rhs.m_file;
			m_line			= rhs.m_line;
			m_typeName		= rhs.m_typeName;
		}

		//! ��ȡ����
		/**
		*
		* \param void 
		* \return 
		*/
		virtual const String&	getFullDescription(void) const;

		//! ��ȡ����
		/**
		*
		* \param void 
		* \return 
		*/
		virtual int				getCode(void) const throw()
		{
			return m_code;
		}

		//! ��ȡ�쳣����λ��
		/**
		*
		* \return 
		*/
		virtual const String&	getSource() const
		{ 
			return m_source; 
		}

		//! ��ȡ�����ļ�
		/**
		*
		* \return 
		*/
		virtual const String&	getFile() const
		{ 
			return m_file;
		}

		//! ��ȡ������
		/**
		*
		* \return 
		*/
		virtual long			getLine() const 
		{
			return m_line; 
		}

		//! ��ȡ����
		/**
		*
		* \param void 
		* \return 
		*/
		virtual const String&	getDescription(void) const 
		{ 
			return m_description;
		}

		//! ��ȡ�쳣����
		/**
		*
		* \return 
		*/
		const char*				what() const throw()
		{ 
			return getFullDescription().c_str();
		}

	protected:
		long		m_line;
		int			m_code;
		String m_typeName;
		String m_description;
		String m_source;
		String m_file;
		mutable String m_fullDesc;
	};


	template <int num>
	struct ExceptionCodeType
	{
		enum { CODE = num };
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API UnimplementedException : public Exception 
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		UnimplementedException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "UnimplementedException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API FileNotFoundException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		FileNotFoundException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "FileNotFoundException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API IOException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		IOException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "IOException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InvalidStateException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		InvalidStateException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "InvalidStateException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InvalidParametersException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		InvalidParametersException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "InvalidParametersException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API ItemIdentityException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		ItemIdentityException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "ItemIdentityException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InternalErrorException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		InternalErrorException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "InternalErrorException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API RenderingAPIException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		RenderingAPIException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "RenderingAPIException", file, line) {}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API RuntimeAssertionException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param &description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		RuntimeAssertionException(int nCode, const String &description, const String &source, const char* file, long line)
			: Exception(nCode, description, source, "RuntimeAssertionException", file, line) {}
	};


	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API CannotOpenFileException : public Exception
	{
	public:
		CannotOpenFileException(int nCode, const String& description, const String &source, const char* file, long line)
			: Exception(nCode, description, source,"CannotOpenFileException", file,line){}
	};


	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API AllocMemoryException : public Exception
	{
	public:
		//!
		/**
		 *
		 * \param nCode 
		 * \param description 
		 * \param &source 
		 * \param file 
		 * \param line 
		 * \return 
		 */
		AllocMemoryException(int nCode, const String& description, const String &source, const char* file, long line)
			: Exception(nCode, description, source,"AllocMemoryException", file,line){}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API CreateFailedException : public Exception
	{
	public:
		//!
		/**
		*
		* \param nCode 
		* \param description 
		* \param &source 
		* \param file 
		* \param line 
		* \return 
		*/
		CreateFailedException(int nCode, const String& description, const String &source, const char* file, long line)
			: Exception(nCode, description, source,"CreateFailedException", file,line){}
	};

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API ExceptionFactory
	{
	private:
		//!
		/**
		*
		* \return 
		*/
		ExceptionFactory() {}
	public:
		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static UnimplementedException create(
			ExceptionCodeType<EC_NOT_IMPLEMENTED> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return UnimplementedException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static FileNotFoundException create(
			ExceptionCodeType<EC_FILE_NOT_FOUND> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return FileNotFoundException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static IOException create(
			ExceptionCodeType<EC_CANNOT_WRITE_TO_FILE> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return IOException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static InvalidStateException create(
			ExceptionCodeType<EC_INVALID_STATE> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return InvalidStateException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static InvalidParametersException create(
			ExceptionCodeType<EC_INVALIDPARAMS> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return InvalidParametersException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static ItemIdentityException create(
			ExceptionCodeType<EC_ITEM_NOT_FOUND> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return ItemIdentityException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static ItemIdentityException create(
			ExceptionCodeType<EC_DUPLICATE_ITEM> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return ItemIdentityException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static InternalErrorException create(
			ExceptionCodeType<EC_INTERNAL_ERROR> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return InternalErrorException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static RenderingAPIException create(
			ExceptionCodeType<EC_RENDERINGAPI_ERROR> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return RenderingAPIException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static RuntimeAssertionException create(
			ExceptionCodeType<EC_RT_ASSERTION_FAILED> code, 
			const String &desc, 
			const String &src, const char* file, long line)
		{
			return RuntimeAssertionException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		 *
		 * \param code 
		 * \param &desc 
		 * \param &src 
		 * \param file 
		 * \param line 
		 * \return 
		 */
		static CannotOpenFileException	create(
			ExceptionCodeType<EC_CANNOT_OPEN_FILE> code,
			const String &desc,
			const String &src, const char* file, long line)
		{
			return CannotOpenFileException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		 *
		 * \param code 
		 * \param &desc 
		 * \param &src 
		 * \param file 
		 * \param line 
		 * \return 
		 */
		static AllocMemoryException	create(
			ExceptionCodeType<EC_ALLOC_MEMORY_ERROR> code,
			const String &desc,
			const String &src, const char* file, long line)
		{
			return AllocMemoryException(code.CODE, desc, src, file, line);
		}

		//!
		/**
		*
		* \param code 
		* \param &desc 
		* \param &src 
		* \param file 
		* \param line 
		* \return 
		*/
		static CreateFailedException	create(
			ExceptionCodeType<EC_CREATE_FAILED> code,
			const String &desc,
			const String &src, const char* file, long line)
		{
			return CreateFailedException(code.CODE, desc, src, file, line);
		}
	};
}

#ifndef tryException
#define tryException(num, desc, src) throw Og2d::ExceptionFactory::create(Og2d::ExceptionCodeType<num>(), desc, src, __FILE__, __LINE__ );
#endif

#endif
