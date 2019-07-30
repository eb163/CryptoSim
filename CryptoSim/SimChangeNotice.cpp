#include "SimChangeNotice.h"



SimChangeNotice::SimChangeNotice()
{
	setType(NoticeType::NOTICE_SIM_CHANGE);
}


SimChangeNotice::~SimChangeNotice()
{
}

void SimChangeNotice::setCryptoChange(float amt)
{
	crypto = amt;
}

float SimChangeNotice::getCryptoChange()
{
	return crypto;
}

void SimChangeNotice::setTransactionChange(int amt)
{
	transaction = amt;
}

int SimChangeNotice::getTransactionChange()
{
	return transaction;
}

void SimChangeNotice::setDeltaTime(time_t delta)
{
	dt = delta;
}

time_t SimChangeNotice::getDeltaTime()
{
	return dt;
}
