#include "Transaction.h"


Transaction::Transaction()
{
	canEdit = true;
	timestamp = 0;
	cryptoAmount = 0;
}

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

void Transaction::makeConstant()
{
	canEdit = false;
}

time_t Transaction::getTimestamp()
{
	return timestamp;
}

float Transaction::getAmount()
{
	return abs(cryptoAmount);
}

std::string Transaction::getSenderID()
{
	return senderID;
}

std::string Transaction::getReceiverID()
{
	return receiverID;
}

bool Transaction::setTimestamp(time_t time)
{
	if (canEdit)
	{
		timestamp = time;
	}
	return canEdit;
}

bool Transaction::setAmount(float amt)
{
	if (canEdit)
	{
		cryptoAmount = amt;
	}
	return canEdit;
}

bool Transaction::setSenderID(std::string id)
{
	if (canEdit)
	{
		senderID = id;
	}
	return canEdit;
}

bool Transaction::setReceiverID(std::string id)
{
	if (canEdit)
	{
		receiverID = id;
	}
	return canEdit;
}
