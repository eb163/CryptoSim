#include "DataManager.h"



DataManager::DataManager()
{

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
