#pragma once
#include "Notice.h"
#include <string>
#include <ctime>

using std::string;

class NoticeSimChange :
	public Notice
{
private:
	float crypto;
	int transaction;
	time_t dt;

protected:

public:
	NoticeSimChange();
	~NoticeSimChange();

	void setCryptoChange(float amt);
	float getCryptoChange();

	void setTransactionChange(int amt);
	int getTransactionChange();

	void setDeltaTime(time_t delta);
	time_t getDeltaTime();
};

