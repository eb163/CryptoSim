#pragma once
#include "mvc\Notice.h"
#include <string>
#include <ctime>

using std::string;

class SimChangeNotice :
	public Notice
{
private:
	string message;
	float crypto;
	int transaction;
	time_t dt;

protected:

public:
	SimChangeNotice();
	~SimChangeNotice();

	void setMessage(string str);
	string getMessage();

	void setCryptoChange(float amt);
	float getCryptoChange();

	void setTransactionChange(int amt);
	int getTransactionChange();

	void setDeltaTime(time_t delta);
	time_t getDeltaTime();
};

