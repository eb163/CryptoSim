#include "NoticeSimPause.h"

NoticeSimPause::NoticeSimPause()
{
	setType(NoticeType::NOTICE_SIM_PAUSE);
	status = false;
	setMessage("undefined");
}


NoticeSimPause::~NoticeSimPause()
{

}

bool NoticeSimPause::isPaused()
{
	return (status == true);
}

bool NoticeSimPause::isRunning()
{
	return (status == false);
}

void NoticeSimPause::pause()
{
	status = true;
	setMessage("Sim is paused!");
}

void NoticeSimPause::run()
{
	status = false;
	setMessage("Sim is running!");
}
