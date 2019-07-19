#include "Node.h"

Node::Node()
{

}


Node::~Node()
{

}

string Node::getID()
{
	return ID;
}

Block Node::getBlock(int i)
{
	return chain.getBlock(i);
}

int Node::getChainSize()
{
	return chain.getSize();
}

void Node::addConnection(Node * nptr)
{
	if (isConnected(nptr) == false)
	{
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
		if (connections.at(i) == nptr)
		{
			result = true;
			go = false;
		}
		if (i > connections.size())
		{
			go = false;
		}
		++i;
	} while (go);

	return result;
}

void Node::notifyNeighbors()
{
	cout << "NEED TO IMPLEMENT Node.notifyNeighbors()" << endl;
}

void Node::updateBlockChain(Blockchain newBC)
{
	cout << "NEED TO IMPLEMENT Node.updateBlockChain(Blockchain newBC)" << endl;
}
