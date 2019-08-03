#pragma once
#include <ctime>

class DataManager
{
private:
	float totalCrypto = 0;
	float cryptoPerMine = 0;
	int totalTransactions = 0;
	int totalNodes = 0;
	//float rateOfCrypto;		//long term goal
	//float rateOfTransactions;	//long term goal
	time_t baseSimRate;
	time_t timePassed;

public:
	DataManager();
	~DataManager();

	float getTotalCrypto();
	void addToTotalCrypto(float amt);

	float getCryptoPerMine();
	void setCryptoPerMine(float amt);

	int getTotalTransactions();
	void addToTotalTransactions(int delta);

	int getTotalNodes();
	void addToTotalNodes(int delta);

	void setBaseSimRate(time_t rate);
	time_t getBaseSimRate();

	void addToTimePassed(time_t dT);
	time_t getTimePassed();
};

