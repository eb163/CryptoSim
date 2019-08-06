#include "Model.h"
#include "Viewer.h"
#include "../tests.h"

Model::Model()
{
}

void Model::init(int nodesInNetwork, float baseCryptoRate, time_t baseTimeRate)
{
	running = true;

	//initialize the network
	netw.connectManager(&manager);
	netw.addNewNodes(nodesInNetwork);
	//printNetworkNodes(&netw);

	//initialize the DataManager
	manager.setCryptoPerMine(baseCryptoRate);
	manager.setBaseSimRate(baseTimeRate);
	manager.setTotalNodes(nodesInNetwork);

	//initialize the driver
	driver.setSimRate(manager.getBaseSimRate());
	driver.setTimeSinceLastAction(0);
	driver.connectDataManager(&manager);
	driver.connectNetwork(&netw);
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
		n->setMessage("Closing the program!");
		noticeQueue.push(n);
	}

	if (e->getType() == EventType::EVENT_PAUSE)
	{
		cout << "Model.Event = EventPause" << endl;
		if (this->isRunning())
		{
			this->pause();
		}
		else
		{
			this->run();
		}
		Notice* n = new NoticeSimPause();
		if (isRunning())
		{
			n->setMessage("The Sim is running!");
		}
		else
		{
			n->setMessage("The Sim is paused!");
		}
		noticeQueue.push(n);
	}

	if (e->getType() == EventType::EVENT_SPEEDCHANGE)
	{
		cout << "Model.Event = EventSpeedChange" << endl;
		EventSpeedChange* eptr = static_cast<EventSpeedChange*>(e);
		if (eptr->getSimRate() == SimRate::PAUSE)
		{
			cout << "Model parsed Event = EventSpeedChange(PAUSE)" << endl;
			driver.setSimRate(0);
			Notice* n = new NoticeSpeedChange(driver.getSimRate());
			string msg = "Changing speed to: "; msg += to_string(driver.getSimRate());
			n->setMessage(msg);
			noticeQueue.push(n);
		}
		if (eptr->getSimRate() == SimRate::SPEED)
		{
			cout << "Model parsed Event = EventSpeedChange(SPEEDUP)" << endl;
			driver.setSimRate(manager.getBaseSimRate() / abs(eptr->getModifier()));
			Notice* n = new NoticeSpeedChange(driver.getSimRate());
			string msg = "Changing speed to: "; msg += to_string(driver.getSimRate());
			n->setMessage(msg);
			noticeQueue.push(n);
		}
		if (eptr->getSimRate() == SimRate::SLOW)
		{
			cout << "Model parsed Event = EventSpeedChange(SLOWDOWN)" << endl;
			driver.setSimRate(manager.getBaseSimRate() * abs(eptr->getModifier()));
			Notice* n = new NoticeSpeedChange(driver.getSimRate());
			string msg = "Changing speed to: "; msg += to_string(driver.getSimRate());
			n->setMessage(msg);
			noticeQueue.push(n);
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

		//notices are created and queued in updateModel

		if (e != nullptr)
		{
			delete e;
			e = nullptr;
		}
	}

	while (noticeQueue.empty() == false)
	{
		cout << "Model is pushing a Notice to Viewer..." << endl;
		Notice* n = noticeQueue.front();
		noticeQueue.pop();
		notifyViewer(n);
	}
}

bool Model::isRunning()
{
	return running;
}

void Model::run()
{
	running = true;
}

void Model::pause()
{
	running = false;
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

Blockchain Model::getBlockchain(int index)
{
	return netw.getNode(index)->getBlockchain();
}
