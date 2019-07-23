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
		cout << "Connecting " << this->getID() << " to " << nptr->getID() << endl;
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
	cout << "Node(" << getID() <<") is notifying all Neighbor nodes..." << endl;

	//process: for each connection
	//call connection(i)->updateBlockChain(this.getBlockChain())

	if (connections.size() > 0)
	{
		for (int i = 0; i < connections.size(); ++i)
		{
			cout << "Next node: " << connections.at(i) << endl;
			connections.at(i)->updateBlockChain(this);
		}
	}
}

void Node::updateBlockChain(Node* nptr)
{
	cout << "Node("<<getID()<<").updateBlockChain()..." << endl;
	
	//method: find the difference in size between this blockchain and newBlockchain
	//copy any blocks from the newBC located past the index difference

	int diff = (nptr->getChainSize()) - (this->getChainSize());
	if (diff <= 0) //if nptr's chain is smaller than or equal to this node's chain, this node doesn't need to update
		return;
	else
	{
		cout << "Node(" << getID() << ").blockChain.size() = " << getChainSize() << endl;
		cout << "Node(" << nptr->getID() << ").blockChain.size() = " << nptr->getChainSize() << endl;
		cout << "diff = " << diff << endl;

		for (int i = this->getChainSize(); i < nptr->getChainSize(); ++i)
		{
			cout << "i = " << i << endl;
			Block newBlock = nptr->getBlockchain().getBlock(i);
			cout << "Node(" << getID() << ") loaded Block(" << newBlock.GetHash() << ")" << endl;
			chain.AddBlock(newBlock);

			generateCrypto();
		}
		notifyNeighbors(); //update neighbor nodes
	}

}

bool Node::generateCrypto()
{
	bool result = false;
	if (manager != nullptr)
	{
		balance += manager->getCryptoPerMine();
		manager->addToTotalCrypto(manager->getCryptoPerMine());
		cout << "Node(" << this << ") earned " << manager->getCryptoPerMine() << " crypto for modifying its Blockchain!" << endl;
		result = true;
	}
	return result;
}
