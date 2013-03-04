#pragma once

class CRobotServer
{
public:
	CRobotServer(void);
	~CRobotServer(void);

	BOOL	BeginServer();
	void	EndServer();
	BOOL	IsWorking();

private:

};
