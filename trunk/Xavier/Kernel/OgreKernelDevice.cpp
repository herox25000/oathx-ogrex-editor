#include "OgreKernelDevice.h"

namespace kernel
{
	OgreKernelDevice::OgreKernelDevice(void)
		:m_pRoot(NULL)
	{
	}

	OgreKernelDevice::~OgreKernelDevice(void)
	{
		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
	}

	bool		OgreKernelDevice::create(const String& sName)
	{

		return 0;	
	}

	extern "C"{

		IKernelDevice* createKernelDevice(const String& sName)
		{
			IKernelDevice* pKernel = new OgreKernelDevice();
			return pKernel;
		}
	}
}

