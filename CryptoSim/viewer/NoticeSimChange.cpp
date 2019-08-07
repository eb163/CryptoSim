#include "NoticeSimChange.h"



NoticeSimChange::NoticeSimChange()
{
	setType(NoticeType::NOTICE_SIM_CHANGE);
}


NoticeSimChange::~NoticeSimChange()
{
}

void NoticeSimChange::setCryptoChange(float amt)
{
	crypto = amt;
}

float NoticeSimChange::getCryptoChange()
{
	return crypto;
}

void NoticeSimChange::setTransactionChange(int amt)
{
	transaction = amt;
}

int NoticeSimChange::getTransactionChange()
{
	return transaction;
}

void NoticeSimChange::setDeltaTime(time_t delta)
{
	dt = delta;
}

time_t NoticeSimChange::getDeltaTime()
{
	return dt;
}
