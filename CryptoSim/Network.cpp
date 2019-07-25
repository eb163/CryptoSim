#include "Network.h"

Network::Network()
{
	manager = nullptr;
}

Network::Network(DataManager* manager, int nodeCount)
{
	connectManager(manager);
	for (int i = 0; i < nodeCount; ++i)
	{
		addNewNode();
	}

	//debug
	/*
	for (int i = 0; i < nodes.size(); ++i)
	{
		cout << nodes.at(i)->getID() << " has " << nodes.at(i)->getTotalConnections() << " connections" << endl;
		for (int j = 0; j < nodes.at(i)->getTotalConnections(); ++j)
		{
			Node* ptr = nodes.at(i)->getConnection(j);
			cout << "Connection: " << ptr << " = " << ptr->getID() << endl;
		}
	}
	*/
}


Network::~Network()
{
	if (nodes.empty() == false)
	{
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nodes.at(i) != nullptr)
			{
				Node* nptr = nodes.at(i);
				delete nptr;
				nodes[i] = nullptr;
			}
		}
	}
}

void Network::connectManager(DataManager * m)
{
	manager = m;
}

void Network::addNewNode()
{
	cout << "NETWORK SETUP: adding a new node...";
	Node* n = new Node();
	string id = "Node " + std::to_string(nodes.size());
	cout << "Node ID: " << id << endl;
	n->setID(id);
	n->connectDataManager(manager);
	nodes.push_back(n);
	if (nodes.size() > 0)
	{
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (n != nodes.at(i))
			{
				n->addConnection(nodes.at(i));
			}
			//cout << "Connecting " << nodes.at(nodes.size() - 1).getID() << " to " << (&nodes.at(i))->getID() << endl;
			//nodes.at(nodes.size() - 1).addConnection(&nodes.at(i));
		}
	}
	/*
	//debug
	cout << n.getID() << " connections: " << endl;
	for (int i = 0; i < nodes.size() - 1; ++i)
	{
		cout << nodes.at(nodes.size() - 1).getConnection(i) << endl;
	}
	*/
}

void Network::addNewNodes(int n)
{
	for (int i = 0; i < n; ++i)
	{
		addNewNode();
	}
}

Node* Network::getNode(int index)
{
	return nodes.at(index);
}

int Network::getSize()
{
	return nodes.size();
}
