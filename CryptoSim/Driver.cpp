#include "Driver.h"

Driver::Driver()
{
	srand(time(0)); //seeds rng
}


Driver::~Driver()
{
}

void Driver::connectDataManager(DataManager* m)
{
	manager = m;
}

void Driver::connectNetwork(Network * n)
{
	nw = n;
}

void Driver::setSimRate(time_t rate)
{
	simRate = rate;
}

time_t Driver::getSimRate()
{
	return simRate;
}

void Driver::setTimeSinceLastAction(time_t time)
{
	timeSinceLastAction = time;
}

void Driver::modifyTimeSinceLastAction(time_t deltaTime)
{
	timeSinceLastAction += deltaTime;
}

time_t Driver::getTimeSinceLastAction()
{
	return timeSinceLastAction;
}

void Driver::takeAction()
{
	int action = rand() % numberOfActions + 1;

	switch (action)
	{
	case ADD_TRANSACTION: addTransaction(); break;
	case DO_NOTHING: cout << "Driver did nothing this cycle. " << endl;  break;
	default: cout << "Driver did nothing this cycle. " << endl; break;

	}
}

void Driver::addTransaction()
{
	cout << "Driver is adding a new Transaction to the Blockchain this cycle." << endl;
	int n1 = 0, n2 = 0;
	//get 2 different random index values between 0 and nw.getSize()
	n1 = rand() % nw->getSize();
	n2 = rand() % nw->getSize();
	cout << "Transaction sender = " << nw->getNode(n1)->getID() << endl;
	cout << "Transaction receiver = " << nw->getNode(n2)->getID() << endl;

	//create a transaction between the two nodes
	Transaction t;
	t.setTimestamp(time(0));
	t.setSenderID(nw->getNode(n1)->getID());
	t.setReceiverID(nw->getNode(n2)->getID());
	float amt = 0;
	if (nw->getNode(n1)->getBalance() > 0) { amt = rand() % nw->getNode(n1)->getBalance(); }
	t.setAmount(amt);

	t.makeConstant(); //disable editing

	//add the Transactions to receiver Node
	//the receiver Node will update the rest of the network
	nw->getNode(n2)->addTransaction(t); //receiver

	manager->addToTotalTransactions(1); //increment transaction counter
}
