#include "Model.h"
#include "Viewer.h"
#include "../tests.h"

Model::Model()
{

}


Model::~Model()
{

}

Viewer * Model::getViewer()
{
	return vptr;
}

void Model::connectViewer(Viewer& v)
{
	vptr = &v;
}

void Model::notifyViewer(Notice* n)
{
	vptr->takeNotice(n);
}

void Model::updateModel(Event* e)
{
	cout << "Model.updateModel()" << endl;
	//do stuff based on what Event is passed and what data needs to be modified
}

void Model::takeEvent(Event* e)
{
	cout << "Model.takeInput()" << endl;
	eventsQueue.push(e);
}

void Model::update()
{
	cout << "Model.update()" << endl;
	while (eventsQueue.empty() == false)
	{
		cout << "Model is processing an event..." << endl;
		Event* e = eventsQueue.front();
		eventsQueue.pop();
		
		//update the model data
		updateModel(e);

		//create a Notice based on the Event
		Notice* n = nullptr;
		//notices need to be fleshed out according to the project requirements

		//push to queue to send to viewer
		noticeQueue.push(n);
	}

	while (noticeQueue.empty() == false)
	{
		cout << "Model is pushing a Notice to Viewer..." << endl;
		Notice* n = noticeQueue.front();
		noticeQueue.pop();
		notifyViewer(n);
	}
}

void Model::init(int nodesInNetwork, float baseCryptoRate, time_t baseTimeRate)
{
	//initialize the network
	netw.connectManager(&manager);
	netw.addNewNodes(nodesInNetwork);
	//printNetworkNodes(&netw);
	

	//initialize the DataManager
	manager.setCryptoPerMine(baseCryptoRate);
	manager.setBaseSimRate(baseTimeRate);

	//initialize the driver
	driver.setSimRate(manager.getBaseSimRate());
	driver.setTimeSinceLastAction(0);
	driver.connectDataManager(&manager);
	driver.connectNetwork(&netw);
}

DataManager Model::getDataManager()
{
	return manager;
}

void Model::simUpdate(time_t deltaT)
{
	manager.addToTimePassed(deltaT);
	driver.modifyTimeSinceLastAction(deltaT);
	driver.pollForAction(); //driver checks time and decides whether or not to act on sim system
	
}
