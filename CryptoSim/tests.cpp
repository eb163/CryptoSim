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
	cout << "DataManager.totalNodes = " << m.getTotalNodes() << endl;
	cout << "DataManager.timeRate = " << m.getBaseSimRate() << endl;
	cout << "DataManager.timePassed = " << m.getTimePassed() << endl;
}

void printTransaction(Transaction& t)
{
	cout << "Transaction: " << &t << endl;
	cout << "Transaction.timestamp = " << t.getTimestamp() << endl;
	cout << "Transaction.amount = " << t.getAmount() << endl;
	cout << "Transaction.sender = " << t.getSenderID() << endl;
	cout << "Transaction.receiver = " << t.getReceiverID() << endl;
}

void unitTestTransaction()
{
	cout << "Running unitTestTransaction \n----------------------------------------" << endl;

	//test data
	time_t timestamp = time(0);
	float amt = 5.56;
	string s = "Node A";
	string r = "Node B";

	cout << "Test Data: Timestamp = " << timestamp << " | Amount = " << amt << " | Sender = " << s << " | Receiver = " << r << endl;
	cout << "Creating empty Transaction...";
	Transaction t;
	cout << " done.\n" << endl;

	printTransaction(t);
	
	cout << "\nSetting data attributes to test data...";
	t.setTimestamp(timestamp);
	t.setAmount(amt);
	t.setSenderID(s);
	t.setReceiverID(r);
	cout << " done.\n" << endl;

	printTransaction(t);

	cout << "\nSetting Transaction to uneditable state...";
	t.makeConstant();
	cout << " done.\n" << endl;

	cout << "Attmepting to modify Transaction.\n" << endl;
	t.setTimestamp(0);
	t.setAmount(amt - 3);
	t.setSenderID(r);
	t.setReceiverID(s);

	printTransaction(t);

	cout << "\nunitTestTransaction completed" << endl;
	pause();
}

void unitTestBlock()
{
	cout << "Running unitTestBlock \n----------------------------------------" << endl;

	//test data
	time_t stamp = 0; //by having timestamp be a constant value, hash should be a constant value
	float amt = 328.99;
	string s = "Node A";
	string r = "Node B";
	Transaction t(stamp, amt, s, r);

	cout << "Test Data: Time: " << stamp << " | Amount: " << amt << " | Sender: " << s << " | Receiver: " << r << endl;
	cout << "\nCreating a Block holding the Transaction data: ";
	Block b(1, t);
	b.MineBlock(1); //to generate hash
	cout << " done.\n" << endl;

	cout << "Block hash: " << b.GetHash() << endl;
	printBlockData(b);

	cout << "\nCreating a second Block with the same data" << endl;
	Block b2(1, t);
	b2.MineBlock(1); //to generate hash
	cout << "Block 2 hash: " << b2.GetHash() << endl;

	cout << "\nCopying a Block from Block 1..." << endl;
	Block b3 = b;
	printBlockData(b3);

	cout << "\nunitTestBlock completed" << endl;
	pause();
}

void unitTestBlockchain()
{
	cout << "Running unitTestBlockchain \n----------------------------------------" << endl;

	time_t time1 = 1111, time2 = 2222, time3 = 3333;
	float amt1 = 1.0, amt2 = 2.0, amt3 = 3.0;
	string block1 = "B1", block2 = "B2", block3 = "B3";
	Transaction t1(time1, amt1, block2, block1), t2(time2, amt2, block1, block2), t3(time3, amt3, block1, block3);
	Block b1(1, t1), b2(2, t2), b3(3, t3);

	cout << "\nTest data: " << endl;
	cout << "Block 1: Time: " << time1 << " | Amount: " << amt1 << " | Sender: " << block2 << " | Receiver: " << block1 << endl;
	cout << "Block 2: Time: " << time2 << " | Amount: " << amt2 << " | Sender: " << block1 << " | Receiver: " << block2 << endl;
	cout << "Block 3: Time: " << time3 << " | Amount: " << amt3 << " | Sender: " << block1 << " | Receiver: " << block3 << endl;

	//demonstrating the blockchain
	Blockchain chain;
	cout << "\nCreated a Blockchain" << endl;
	cout << "Blockchain size: " << chain.getSize() << " (should be 1)" << endl;
	
	chain.AddBlock(b1);
	chain.AddBlock(b2);
	chain.AddBlock(b3);

	cout << "\nAdded blocks to chain... (New size should be 4)" << endl;

	printBlockchainContents(chain);

	cout << "\nunitTestBlockchain completed" << endl;
	pause();
}

void unitTestNode()
{
	cout << "Running unitTestNode \n----------------------------------------" << endl;
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
	time_t time1 = 1111, time2 = 2222, time3 = 3333;
	float amt1 = 1.0, amt2 = 2.0, amt3 = 3.0;
	string block1 = "B1", block2 = "B2", block3 = "B3";
	Transaction t1(time1, amt1, block2, block1), t2(time2, amt2, block1, block2), t3(time3, amt3, block1, block3);
	Block b1(1, t1), b2(2, t2), b3(3, t3);
	Blockchain masterchain;
	masterchain.AddBlock(b1);
	masterchain.AddBlock(b2);
	masterchain.AddBlock(b3);

	cout << n1.getID() << " = " << &n1 << endl;
	cout << n2.getID() << " = " << &n2 << endl;
	cout << n3.getID() << " = " << &n3 << endl;

	cout << "\nTest data: " << endl;
	cout << "Block 1: Time: " << time1 << " | Amount: " << amt1 << " | Sender: " << block2 << " | Receiver: " << block1 << endl;
	cout << "Block 2: Time: " << time2 << " | Amount: " << amt2 << " | Sender: " << block1 << " | Receiver: " << block2 << endl;
	cout << "Block 3: Time: " << time3 << " | Amount: " << amt3 << " | Sender: " << block1 << " | Receiver: " << block3 << endl;

	cout << "\nPrinting master blockchain..." << endl;
	printBlockchainContents(masterchain);
	pause();

	n1.addConnection(&n2);
	n3.addConnection(&n1);
	n3.addConnection(&n2);
	n1.addTransaction(t1);
	n2.addTransaction(t2);
	n3.addTransaction(t3);

	cout << "\nPrinting blockchains in each Node..." << endl;
	cout << "Node 1:" << endl;
	printBlockchainContents(n1.getBlockchain());

	cout << "\nNode 2:" << endl;
	printBlockchainContents(n2.getBlockchain());
	
	cout << "\nNode 3:" << endl;
	printBlockchainContents(n3.getBlockchain());

	cout << "\nunitTestNode completed" << endl;
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
	cout << "Running unitTestDriver \n--------------------------------------" << endl;
	
	//test data
	time_t rate = 12;
	time_t iteration1 = rate * 1;
	time_t iteration2 = rate * 2;

	cout << "Test data: Time Rate = " << rate << endl;

	cout << "Creating an empty Driver" << endl;
	Driver dr;
	cout << "Driver.timeSinceLastAction = " << dr.getTimeSinceLastAction() << endl;

	cout << "\nCalling driver.modifyTimeSinceLastAction(" << rate <<") " << endl;
	dr.modifyTimeSinceLastAction(rate);
	cout << "Driver.timeSinceLastAction = " << dr.getTimeSinceLastAction() << "(should be: "<< iteration1 << ")" << endl;

	cout << "\nCalling driver.modifyTimeSinceLastAction(" << rate << ") " << endl;
	dr.modifyTimeSinceLastAction(rate);
	cout << "Driver.timeSinceLastAction = " << dr.getTimeSinceLastAction() << "(should be: " << iteration2 << ")" << endl;

	cout << "\nunitTestDriver completed" << endl;
	pause();
}

void systemTestDriver()
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
	cout << "Running unitTestDataManager \n-------------------------------------" << endl;

	//test data
	float initAmount = 11.25;
	int initTransact = 0;
	int initNodes = 3, deltaNodes = 2;
	float cryptoRate = 3.5;
	time_t timeRate = 10;

	float endAmount = initAmount + cryptoRate;
	int endNodes = initNodes + deltaNodes;
	int endTransact = 1;

	cout << "\nTest Data: Initial Amount: " << initAmount << " | Initial Transactions: " << initTransact << " | Initial Nodes: " << initNodes
		<< "\nCryptoRate: " << cryptoRate << " | New Nodes: " << deltaNodes << " | Time Rate: " << timeRate
		<< "\nEnd Amount: " << endAmount << " | End Transactions: " << endTransact << " | End Nodes: " << endNodes << endl;

	DataManager mgr;
	cout << "\nCreated empty DataManager" << endl;
	printDataManager(mgr);

	cout << "\nSetting DataManager initial values" << endl;
	mgr.setBaseSimRate(timeRate);
	mgr.setCryptoPerMine(cryptoRate);
	mgr.setTotalNodes(initNodes);
	mgr.addToTotalCrypto(initAmount);
	mgr.addToTotalTransactions(initTransact);
	printDataManager(mgr);

	cout << "\nModifying DataManager values" << endl;
	mgr.addToTotalCrypto(cryptoRate);
	mgr.addToTotalNodes(deltaNodes);
	mgr.addToTotalTransactions(1);
	mgr.addToTimePassed(timeRate);
	printDataManager(mgr);

	cout << "\nunitTestDataManager completed" << endl;
	pause();
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

void unitTestModel()
{
	cout << "Executing unitTestModel()\n----------------------------" << endl;

	//Events to test
	Event* pauseptr = new EventPause();
	Event* speedptr = nullptr;
	Event* closeptr = new EventClose();

	Model m;

	//EventPause (confirm that model is paused)
	cout << "Model.running = " << m.isRunning() << " (should be 1) " << endl;

	cout << "\nPausing Model...";
	m.takeEvent(pauseptr);
	m.update();
	cout << " done." << endl;

	cout << "Model.running = " << m.isRunning() << " (should be 0) " << endl;

	pauseptr = new EventPause();

	//EventPause again (confirm that model is unpaused)
	cout << "\nNow unpausing Model..." << endl;
	m.takeEvent(pauseptr);
	m.update();
	cout << "...done." << endl;

	cout << "Model.running = " << m.isRunning() << " (should be 1) " << endl;

	//EventSpeedChange(HIGH speed) (confirm that model rate is set to high speed)

	speedptr = new EventSpeedChange(SimRate::SPEED);
	cout << "\nIncreasing Model speed..." << endl;
	m.takeEvent(speedptr);
	m.update();
	cout << "...done." << endl;

	//EventSpeedChange(LOW speed) (confirm that model rate is set to low speed)

	speedptr = new EventSpeedChange(SimRate::SLOW);
	cout << "\nDecreasing Model speed..." << endl;
	m.takeEvent(speedptr);
	m.update();
	cout << "..done." << endl;

	//EventClose (confirm that a close notice is sent out)

	cout << "unitTestModel() ending..." << endl;
	pause();
}

void unitTestController()
{
	cout << "Executing unitTestModel()\n----------------------------" << endl;

	Controller ctrl;

	//data to test:
	Input* pauseptr = new InputSpacebar();
	Input* speedPtr = nullptr;
	Input* closeptr = new InputClose();

	cout << "\nTesting InputSpacebar...Controller should produce an EventPause type Event." << endl;
	ctrl.parseInput(pauseptr);

	cout << "\nTesting InputSpeedChange(HIGH)...Controller should produce an EventSpeedChange type event." << endl;
	speedPtr = new InputChangeSpeed(SimRate::SPEED);
	ctrl.parseInput(speedPtr);

	cout << "\nTesting InputSpeedChange(LOW)...Controller should produce an EventSpeedChange type event." << endl;
	speedPtr = new InputChangeSpeed(SimRate::SLOW);
	ctrl.parseInput(speedPtr);

	cout << "\nTesting InputSpeedChange(PAUSE)...Controller should produce an EventSpeedChange type event." << endl;
	speedPtr = new InputChangeSpeed(SimRate::PAUSE);
	ctrl.parseInput(speedPtr);

	cout << "\nTesting InputClose...Controller should produce an EventClose." << endl;
	ctrl.parseInput(closeptr);

	cout << "\nunitTestModel() ending..." << endl;
	pause();
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

	while (v->isOpen())
	{
		v->updateDisplay();
		//bool input = false, timeout = false;
		//v->pollWindow();
		v->loop();
		c->loop();
	}



	delete m; m = nullptr;
	delete v; v = nullptr;
	delete c; c = nullptr;
}
