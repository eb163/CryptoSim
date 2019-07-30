#include "SimPauseNotice.h"

SimPauseNotice::SimPauseNotice()
{
	setType(NoticeType::NOTICE_SIM_PAUSE);
	status = false;
	setMessage("undefined");
}


SimPauseNotice::~SimPauseNotice()
{

}

bool SimPauseNotice::isPaused()
{
	return (status == true);
}

bool SimPauseNotice::isRunning()
{
	return (status == false);
}

void SimPauseNotice::pause()
{
	status = true;
	setMessage("Sim is paused!");
}

void SimPauseNotice::run()
{
	status = false;
	setMessage("Sim is running!");
}
