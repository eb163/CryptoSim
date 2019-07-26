#pragma once
#include <vector>
#include <string>
#include <cmath>
#include "Transaction.h"
#include "blockchain/Blockchain.h"
#include "mvc/debug.h"
#include "DataManager.h"


using std::vector;
using std::string;

class Node
{
private:
	vector<Node*> connections;
	string ID;
	Blockchain chain;
	float balance = 0;
	DataManager* manager = nullptr;

public:
	Node();
	~Node();

	void connectDataManager(DataManager* mngr);

	string getID();
	void setID(string id);
	Block getBlock(int i);
	int getChainSize();
	Blockchain getBlockchain() const;

	void addConnection(Node* nptr);
	bool isConnected(Node* nptr);
	Node* getConnection(int i); //for debugging
	int getTotalConnections(); //for debugging

	int getBalance();
	void editBalance(float delta);
	
	void addTransaction(Transaction t);
	void notifyNeighbors();
	void updateBlockChain(Node* nptr);

	bool generateCrypto();
};

