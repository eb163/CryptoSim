#pragma once
#include <ctime>
#include <cmath>
#include <string>

class Transaction
{
private:
	time_t timestamp;
	float cryptoAmount;
	std::string senderID;
	std::string receiverID;
	bool canEdit = true;

public:
	Transaction();
	Transaction(time_t time, float amt, std::string sender, std::string receiver);
	~Transaction();

	void makeConstant(); //make the transaction instance uneditable

	time_t getTimestamp();
	float getAmount();
	std::string getSenderID();
	std::string getReceiverID();

	//mutators can only be used when canEdit is true
	bool setTimestamp(time_t time);
	bool setAmount(float amt);
	bool setSenderID(std::string id);
	bool setReceiverID(std::string id);
};

