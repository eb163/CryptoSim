#include "Node.h"

Node::Node()
{
	balance = 0;
	manager = nullptr;
}


Node::~Node()
{

}

void Node::connectDataManager(DataManager * mngr)
{
	manager = mngr;
}

string Node::getID()
{
	return ID;
}

void Node::setID(string id)
{
	ID = id;
}

Block Node::getBlock(int i)
{
	return chain.getBlock(i);
}

int Node::getChainSize()
{
	int size = 0;
	if (chain.getSize() > 0)
	{
		size = chain.getSize() - 1;
	}
	return size;
}

Blockchain Node::getBlockchain() const
{
	return chain;
}

void Node::addConnection(Node * nptr)
{
	//cout << "Node(" << this->getID() << ").addConnection(" << nptr->getID() <<")" << endl;
	if (isConnected(nptr) == false)
	{
		//debug
		//cout << "Connecting " << this->getID() << " to " << nptr->getID() << endl;
		connections.push_back(nptr);
		nptr->addConnection(this);
	}
}

bool Node::isConnected(Node * nptr)
{
	bool result = false;
	bool go = true;
	int i = 0;
	do
	{
		if (i >= connections.size())
		{
			go = false;
		}
		else if (connections.at(i) == nptr)
		{
			result = true;
			go = false;
		}
		++i;
	} while (go);

	return result;
}

Node * Node::getConnection(int i)
{
	Node* ptr = connections.at(i);
	return ptr;
}

int Node::getTotalConnections()
{
	return connections.size();
}

int Node::getBalance()
{
	return balance;
}

void Node::editBalance(float delta)
{
	balance += delta;
}

void Node::addTransaction(Transaction t)
{
	float amt = t.getAmount();
	if(getID() == t.getSenderID())
	{
		amt = abs(amt) * -1; //sets to negative
	}
	else if (getID() == t.getReceiverID())
	{
		amt = abs(amt) * 1; //sets to positive
	}
	editBalance(amt);

	Block b(chain.getSize() + 1, t);
	chain.AddBlock(b);

	generateCrypto();

	notifyNeighbors();
}

void Node::notifyNeighbors()
{
	//cout << "Node(" << getID() <<") is notifying all Neighbor nodes..." << endl;

	//process: for each connection
	//call connection(i)->updateBlockChain(this.getBlockChain())

	if (connections.size() > 0)
	{
		for (int i = 0; i < connections.size(); ++i)
		{
			//cout << "Next node: " << connections.at(i)->getID() << endl;
			connections.at(i)->updateBlockChain(this);
		}
	}
}

bool compareBlocks(Block& b1, Block& b2)
{
	//blocks are equivalent if

	//crypto amount is equal
	float amt1 = b1.GetData().getAmount();
	float amt2 = b2.GetData().getAmount();

	//sender id is equal
	string s1 = b1.GetData().getSenderID();
	string s2 = b2.GetData().getSenderID();

	//receiver id is equal
	string r1 = b1.GetData().getReceiverID();
	string r2 = b2.GetData().getReceiverID();

	return ((amt1 == amt2) && (s1 == s2) && (r1 == r2));
}

void Node::updateBlockChain(Node* nptr)
{
	//cout << "Node("<<getID()<<").updateBlockChain()..." << endl;

	//method: this Node copies latest block from nptr's chain and pushes it to this Node's chain

	Block newBlock = nptr->getBlockchain().GetLastBlock();

	//block comparison to avoid duplicates
	//if two blocks have the same amt, sender id, and receiver id, the blocks are basically identical
	bool equal = false;
	for (int i = 1; i < chain.getSize(); ++i)
	{
		equal = compareBlocks(newBlock, chain.getBlock(i));
		if (equal) { i = chain.getSize() + 1; } //end loop early if a match is found
	}

	if (equal == false)
	{
		chain.AddBlock(newBlock);
		generateCrypto();

		notifyNeighbors();
	}

}

bool Node::generateCrypto()
{
	bool result = false;
	if (manager != nullptr)
	{
		balance += manager->getCryptoPerMine();
		manager->addToTotalCrypto(manager->getCryptoPerMine());
		cout << "Node(" << getID() << ") earned " << manager->getCryptoPerMine() << " crypto for modifying its Blockchain!" << endl;
		result = true;
	}
	else
	{
		cout << "ERROR: Node ptr to manager is nullptr!" << endl;
	}
	return result;
}
