#include "Transaction.h"


Transaction::Transaction(time_t time, float amt, std::string sender, std::string receiver)
{
	timestamp = time;
	cryptoAmount = amt;
	senderID = sender;
	receiverID = receiver;
}

Transaction::~Transaction()
{

}

time_t Transaction::getTimestamp()
{
	return timestamp;
}

std::string Transaction::getSenderID()
{
	return senderID;
}

std::string Transaction::getReceiverID()
{
	return receiverID;
}
