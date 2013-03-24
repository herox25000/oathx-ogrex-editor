#include "StdAfx.h"
#include "SmallNineMachineFactory.h"

//////////////////////////////////////////////////////////////////////////
SmallNineMachineFactory::SmallNineMachineFactory(const CString& name) 
: IRobotFactory(name)
{

}

SmallNineMachineFactory::~SmallNineMachineFactory()
{

}

IRobot*	SmallNineMachineFactory::Create(DWORD dwUserID)
{
	return new SmallNineMachine(dwUserID);
}