#pragma once
#include "Notice.h"
class NoticeSpeedChange :
	public Notice
{
private:
	time_t newRate;

protected:
	void setRate(time_t rate);

public:
	NoticeSpeedChange(time_t rate);
	~NoticeSpeedChange();

	time_t getRate();
};

