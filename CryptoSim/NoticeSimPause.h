#pragma once
#include "mvc\Notice.h"
class NoticeSimPause :
	public Notice
{
private:
	bool status;

protected:

public:
	NoticeSimPause();
	~NoticeSimPause();

	bool isPaused();
	bool isRunning();
	void pause();
	void run();
};

