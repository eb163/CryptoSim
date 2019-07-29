#pragma once
#include "mvc\Notice.h"
class SimPauseNotice :
	public Notice
{
private:
	bool status;

protected:

public:
	SimPauseNotice();
	~SimPauseNotice();

	bool isPaused();
	bool isRunning();
	void pause();
	void run();
};

