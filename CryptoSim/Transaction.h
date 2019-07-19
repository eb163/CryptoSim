#pragma once
#include <ctime>
#include <string>

class Transaction
{
private:
	time_t timestamp;
	float cryptoAmount;
	std::string senderID;
	std::string receiverID;

public:
	Transaction(time_t time, float amt, std::string sender, std::string receiver);
	~Transaction();

	time_t getTimestamp();
	float getAmount();
	std::string getSenderID();
	std::string getReceiverID();
};

