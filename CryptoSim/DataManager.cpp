#include "DataManager.h"



DataManager::DataManager()
{
	totalCrypto = 0;
	totalTransactions = 0;
	cryptoPerMine = 0;
	timePassed = 0;
}


DataManager::~DataManager()
{

}

float DataManager::getTotalCrypto()
{
	return totalCrypto;
}

void DataManager::addToTotalCrypto(float amt)
{
	totalCrypto += amt;
}

float DataManager::getCryptoPerMine()
{
	return cryptoPerMine;
}

void DataManager::setCryptoPerMine(float amt)
{
	cryptoPerMine = amt;
}

int DataManager::getTotalTransactions()
{
	return totalTransactions;
}

void DataManager::addToTotalTransactions(int delta)
{
	totalTransactions += delta;
}

void DataManager::setBaseSimRate(time_t rate)
{
	baseSimRate = rate;
}

time_t DataManager::getBaseSimRate()
{
	return baseSimRate;
}

void DataManager::addToTimePassed(time_t dT)
{
	timePassed += dT;
}

time_t DataManager::getTimePassed()
{
	return timePassed;
}
