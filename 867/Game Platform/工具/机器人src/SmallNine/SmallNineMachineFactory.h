#pragma once

#include "SmallNineMachine.h"

class SmallNineMachineFactory : public IRobotFactory
{
public:
	SmallNineMachineFactory(const CString& name);
	virtual ~SmallNineMachineFactory();

	virtual	IRobot*			Create(DWORD dwUserID);
};