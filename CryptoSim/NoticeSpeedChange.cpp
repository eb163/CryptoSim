#include "NoticeSpeedChange.h"



void NoticeSpeedChange::setRate(time_t rate)
{
	newRate = rate;
}

NoticeSpeedChange::NoticeSpeedChange(time_t rate)
{
	setType(NoticeType::NOTICE_SPEED_CHANGE);
	setRate(rate);
}


NoticeSpeedChange::~NoticeSpeedChange()
{
}

time_t NoticeSpeedChange::getRate()
{
	return newRate;
}
