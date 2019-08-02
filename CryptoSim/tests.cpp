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

	printBlockchainContents(chain);

	pause();
}

void unitTestNode()
{
	Node n1, n2, n3;
	n1.setID("n1");
	n2.setID("n2");
	n3.setID("n3");

	cout << "Testing Node connections..." << endl;

	cout << "Created nodes n1 and n2" << endl;
	cout << "Is n1 connected to n2? " << n1.isConnected(&n2) << endl;
	cout << "Is n2 connected to n1? " << n2.isConnected(&n1) << endl;
	cout << "Connecting them now..." << endl; n2.addConnection(&n1);
	cout << "Is n1 connected to n2? " << n1.isConnected(&n2) << endl;
	cout << "Is n2 connected to n1? " << n2.isConnected(&n1) << endl;
	pause();


	cout << "Testing Node updating Blockchains and Notifications..." << endl;
	Transaction t1(time(0), 1.0, "B2", "B1"), t2(time(0), 2.0, "B1", "B2"), t3(time(0), 3.0, "B1", "B3");
	Block b1(1, t1), b2(2, t2), b3(3, t3);
	Blockchain masterchain;
	masterchain.AddBlock(b1);
	masterchain.AddBlock(b2);
	masterchain.AddBlock(b3);

	cout << n1.getID() << " = " << &n1 << endl;
	cout << n2.getID() << " = " << &n2 << endl;
	cout << n3.getID() << " = " << &n3 << endl;

	cout << "Printing master blockchain..." << endl;
	printBlockchainContents(masterchain);
	pause();

	n1.addConnection(&n2);
	n3.addConnection(&n1);
	n3.addConnection(&n2);
	n1.addTransaction(t1);
	n2.addTransaction(t2);
	n3.addTransaction(t3);

	cout << "Printing blockchains in each Node..." << endl;
	cout << "Node 1:" << endl;
	printBlockchainContents(n1.getBlockchain());
	pause();
	cout << "Node 2:" << endl;
	printBlockchainContents(n2.getBlockchain());
	pause();
	cout << "Node 3:" << endl;
	printBlockchainContents(n3.getBlockchain());
	pause();

}

void printNetworkNodes(Network* nw)
{
	for (int i = 0; i < nw->getSize(); ++i)
	{
		cout << nw->getNode(i)->getID() << endl;
		cout << "Connections: " << nw->getNode(i)->getTotalConnections() << endl;
		for (int j = 0; j < nw->getNode(i)->getTotalConnections(); ++j)
		{
			cout << "Connection " << j << ": " << nw->getNode(i)->getConnection(j)->getID() << " = " << nw->getNode(i)->getConnection(j) << endl;
		}
		cout << endl;
	}
}

void unitTestNetwork()
{
	cout << "Testing Network object and methods..." << endl;
	int nodeLimit = 11;
	DataManager mngr;
	Network* nw;

	for (int i = 0; i < nodeLimit; ++i)
	{
		cout << "Creating a Network with " << i << " Nodes." << endl;
		nw = new Network(&mngr, i);
		printNetworkNodes(nw);

		pause();

		if (nw != nullptr)
		{
			delete nw;
			nw = nullptr;
		}
	}
}

void unitTestDriver()
{
	cout << "Testing Driver methods..." << endl;

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
		cout << "Press 'y' to repeat the loop, or" << endl;
		ch = pause();
	} while (ch == 'y' || ch == 'Y');
}

void unitTestDataManager()
{

}

void unitTestViewer()
{
	Controller c;
	Model m;
	Viewer v;
	m.init(3, 3, 999);
	c.connectModel(&m);
	c.connectViewer(&v);
	m.connectViewer(&v);
	v.connectModel(&m);
	v.connectController(&c);
	
	time_t pollStart = 0;
	time_t pollCurr = 0;
	time_t pollStop = 1;
	time_t pollDiff = 0;

	while (c.isRunning() && v.isOpen())
	{
		v.updateDisplay();

		
		NoticeSimPause* pauseN = new NoticeSimPause;
		pauseN->pause();
		cout << "Testing SimPauseNotice.isPaused..." << endl;
		v.processNotice(pauseN);
		bool gotInput = false, timeOut = false;
		pollStart = time(0);
		while (gotInput == false && timeOut == false) 
		{ 
			gotInput = v.pollWindow(); 
			pollCurr = time(0);
			pollDiff = pollCurr - pollStart;
			if(pollDiff > pollStop)
			{
				timeOut = true;
			}

		}

		v.updateDisplay();

		NoticeSimPause* runN = new NoticeSimPause;
		runN->run();
		cout << "Testing SimPauseNotice.isRunning..." << endl;
		v.processNotice(runN);
		gotInput = false; timeOut = false;
		pollStart = time(0);
		while (gotInput == false && timeOut == false) 
		{ 
			gotInput = v.pollWindow();
			pollCurr = time(0);
			pollDiff = pollCurr - pollStart;
			if (pollDiff > pollStop)
			{
				timeOut = true;
			}
		};
		
	}
}

void connect(Model* m, Viewer* view, Controller* ctrl)
{
	ctrl->connectModel(m);
	ctrl->connectViewer(view);
	m->connectViewer(view);
	view->connectModel(m);
	view->connectController(ctrl);
}

void systemTestMVC()
{
	int nodeCount = 3;
	float cryptoRate = 5;
	time_t updateRate = 9;
	Model* m = new Model();
	Viewer* v = new Viewer();
	Controller* c = new Controller();
	m->init(3, 5, 9);
	connect(m, v, c);

	//test Viewer parsing inputs and sending them to Controller and Model

	time_t pollStart = 0;
	time_t pollCurr = 0;
	time_t pollStop = 1;
	time_t pollDiff = 0;

	while (v->isOpen())
	{
		v->updateDisplay();
		bool input = false, timeout = false;
		//v->pollWindow();
		v->loop();
		c->loop();
	}



	delete m; m = nullptr;
	delete v; v = nullptr;
	delete c; c = nullptr;
}
