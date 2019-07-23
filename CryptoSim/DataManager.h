#pragma once
#include <ctime>

class DataManager
{
private:
	float totalCrypto = 0;
	float cryptoPerMine = 0;
	int totalTransactions = 0;
	//float rateOfCrypto;		//long term goal
	//float rateOfTransactions;	//long term goal
	time_t simRate;

public:
	DataManager();
	~DataManager();

	float getTotalCrypto();
	void addToTotalCrypto(float amt);

	float getCryptoPerMine();
	void setCryptoPerMine(float amt);

	int getTotalTransactions();
	void addToTotalTransactions(int delta);
};

