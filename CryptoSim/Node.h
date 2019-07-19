#pragma once
#include <vector>
#include <string>
#include "Transaction.h"
#include "blockchain/Blockchain.h"
#include "mvc/debug.h"


using std::vector;
using std::string;

class Node
{
private:
	vector<Node*> connections;
	vector<Transaction> recentActivity;
	string ID;
	Blockchain chain;

public:
	Node();
	~Node();

	string getID();
	Block getBlock(int i);
	int getChainSize();

	void addConnection(Node* nptr);
	bool isConnected(Node* nptr);
	
	void notifyNeighbors();						//to implement later
	void updateBlockChain(Blockchain newBC);	//to implement later
};

