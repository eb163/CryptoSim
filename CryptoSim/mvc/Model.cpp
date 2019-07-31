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

void Model::connectViewer(Viewer* v)
{
	vptr = v;
}

void Model::notifyViewer(Notice* n)
{
	vptr->takeNotice(n);
}

void Model::updateModel(Event* e)
{
	cout << "Model.updateModel()" << endl;
	//do stuff based on what Event is passed and what data needs to be modified

	if (e->getType() == EventType::EVENT_CLOSE)
	{
		cout << "Model.Event = EventClose" << endl;

		Notice* n = new NoticeClose();
		noticeQueue.push(n);
	}

	if (e->getType() == EventType::EVENT_PAUSE)
	{
		cout << "Model.Event = EventPause" << endl;
		Notice* n = new NoticeSimPause();
		noticeQueue.push(n);
	}

	if (e->getType() == EventType::EVENT_SPEEDCHANGE)
	{
		cout << "Model.Event = EventSpeedChange" << endl;
		EventSpeedChange* eptr = static_cast<EventSpeedChange*>(e);
		if (eptr->getSimRate() == SimRate::PAUSE)
		{
			cout << "Model parsed Event = EventSpeedChange(PAUSE)" << endl;
			//how to pause?
			driver.setSimRate(manager.getBaseSimRate() * abs(eptr->getModifier()));
			//need to define NoticeSpeedChange
		}
		if (eptr->getSimRate() == SimRate::SPEED)
		{
			cout << "Model parsed Event = EventSpeedChange(SPEEDUP)" << endl;
			driver.setSimRate(manager.getBaseSimRate() / abs(eptr->getModifier()));
		}
		if (eptr->getSimRate() == SimRate::SLOW)
		{
			cout << "Model parsed Event = EventSpeedChange(SLOWDOWN)" << endl;
			driver.setSimRate(manager.getBaseSimRate() * abs(eptr->getModifier()));
		}
	}

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
