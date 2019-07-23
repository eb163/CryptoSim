
#include "tests.h"
char pause()
{
	char ch;
	cout << "Press any key to continue..." << endl;
	cin >> ch;
	return ch;
}

void printBlockData(Block& b)
{
	cout << "Block: " << b.GetHash() << endl;
	cout << "Data: "
		 << "Timestamp: " << b.GetData().getTimestamp()
		 << ", Amount: " << b.GetData().getAmount() << " crypto"
		 << ", sender: " << b.GetData().getSenderID()
		 << ", receiver: " << b.GetData().getReceiverID() << endl;
}

void printBlockchainContents(Blockchain &bc)
{
	cout << "Blockchain(" << &bc << ") " << endl;
	cout << "contains " << bc.getSize() << " blocks" << endl;
	for (int i = 0; i < bc.getSize(); ++i)
	{
		printBlockData(bc.getBlock(i));
	}
}

void printDataManager(DataManager & m)
{
	cout << "DataManager: " << &m << endl;
	cout << "DataManager.totalCrypto = " << m.getTotalCrypto() << endl;
	cout << "DataManager.totalTransactions = " << m.getTotalTransactions() << endl;
	cout << "DataManager.cryptoPerMine = " << m.getCryptoPerMine() << endl;
}

void unitTestBlockchain()
{
	cout << "Testing a Blockchain..." << endl;

	Transaction t1(time(0), 1.0, "B2", "B1"), t2(time(0), 2.0, "B1", "B2"), t3(time(0), 3.0, "B1", "B3");
	Block b1(1, t1), b2(2, t2), b3(3, t3);

	//demonstrating the blockchain
	Blockchain chain;
	cout << "Created a Blockchain" << endl;
	chain.AddBlock(b1);
	chain.AddBlock(b2);
	chain.AddBlock(b3);
}

void unitTestNode()
{
	Node n1, n2, n3;

//	cout << "Testing Node connections..." << endl;
/*
	cout << "Created nodes n1 and n2" << endl;
	cout << "Is n1 connected to n2? " << n1.isConnected(&n2) << endl;
	cout << "Is n2 connected to n1? " << n2.isConnected(&n1) << endl;
	cout << "Connecting them now..." << endl; n2.addConnection(&n1);
	cout << "Is n1 connected to n2? " << n1.isConnected(&n2) << endl;
	cout << "Is n2 connected to n1? " << n2.isConnected(&n1) << endl;
	pause();
*/

	cout << "Testing Node updating Blockchains and Notifications..." << endl;
//	Block b1(1, "b1"), b2(2, "b2"), b3(3, "b3");
	Transaction t1(time(0), 1.0, "B2", "B1"), t2(time(0), 2.0, "B1", "B2"), t3(time(0), 3.0, "B1", "B3");
	Block b1(1, t1), b2(2, t2), b3(3, t3);
	Blockchain masterchain;
	masterchain.AddBlock(b1);
	masterchain.AddBlock(b2);
	masterchain.AddBlock(b3);

	cout << "Node1 = " << &n1 << endl;
	cout << "Node2 = " << &n2 << endl;
	cout << "Node3 = " << &n3 << endl;

	printBlockchainContents(masterchain);

	n1.addConnection(&n2);
	n3.addConnection(&n1);
	n3.addConnection(&n2);
	n1.addTransaction(t1);
	n2.addTransaction(t2);
	n3.addTransaction(t3);

	printBlockchainContents(n1.getBlockchain());
	printBlockchainContents(n2.getBlockchain());
	printBlockchainContents(n3.getBlockchain());

	pause();

}

void unitTestDriver()
{
	cout << "Testng Driver methods..." << endl;

	DataManager manager;
	manager.setCryptoPerMine(12.00);
	
	cout << "Manager: " << &manager << endl;
	
	int nodeCount = 3;
	Network network(&manager, nodeCount);

	cout << "Network: " << &network << endl;

	Driver driver;

	cout << "Driver: " << &driver << endl;

	driver.connectDataManager(&manager);
	driver.connectNetwork(&network);

	char ch = 'y';
	do
	{
		driver.takeAction();
		printDataManager(manager);
		ch = pause();
	} while (ch == 'y' || ch == 'Y');
}

void unitTestDataManager()
{

}