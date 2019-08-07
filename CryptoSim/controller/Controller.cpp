#include "Controller.h"

Controller::Controller()
{
	mptr = nullptr;
	vptr = nullptr;
	lastUpdate = 0;
}

Controller::Controller(Model* m, Viewer* v)
{
	mptr = m;
	vptr = v;

	mptr->connectViewer(vptr);
	
	vptr->connectModel(mptr);
	vptr->connectController(this);
}

Controller::~Controller()
{

}

void Controller::connectModel(Model* m)
{
	mptr = m;
}

Model* Controller::getModel()
{
	return mptr;
}

void Controller::connectViewer(Viewer* v)
{
	vptr = v;
}

Viewer * Controller::getViewer()
{
	return vptr;
}

bool Controller::isRunning()
{
	return running;
}

void Controller::parseInput(Input* i)
{
	cout << "Controller.parseInput()" << endl;
	cout << "Controller is parsing an input..." << endl;
	Event* e = nullptr; 

	//parse Input here
	//close Input
	if (i->getType() == InputType::INPUT_CLOSE)
	{
		cout << "Controller got an InputClose" << endl;
		e = new EventClose();
	}

	//spacebar input
	if (i->getType() == InputType::INPUT_SPACEBAR)
	{
		cout << "Controller got an InputSpacebar" << endl;
		e = new EventPause();
	}

	//speed change input
	if (i->getType() == InputType::INPUT_SPEED_CHANGE)
	{
		cout << "Controller got an InputSpeedChange" << endl;
		bool incr = static_cast<InputChangeSpeed*>(i)->isIncrease();
		bool decr = static_cast<InputChangeSpeed*>(i)->isDecrease();
		cout << "SpeedChange is an increase: " << incr << endl;
		cout << "SpeedChange is a decrease: " << decr << endl;
		if (incr)
		{
			e = new EventSpeedChange(SimRate::SPEED);
		}
		else if (decr)
		{
			e = new EventSpeedChange(SimRate::SLOW);
		}
		else
		{
			e = new EventSpeedChange(SimRate::PAUSE);
		}
	}


	if (e != nullptr)
	{
		cout << "Controller produced an Event of EventType:";
		switch (e->getType())
		{
		case EventType::EVENT_CLOSE: cout << " EventClose" << endl; break;
		case EventType::EVENT_PAUSE: cout << " EventPause" << endl; break;
		case EventType::EVENT_SPEEDCHANGE: cout << " EventSpeedChange" << endl; break;
		}
		eventQueue.push(e);
	}

	//deallocate memory
	if (i != nullptr)
	{
		delete i;
		i = nullptr;
	}
}

void Controller::notifyModel()
{
	//send events to model
	cout << "Controller.notifyModel()" << endl;
	while (eventQueue.empty() == false)
	{
		cout << "Sending an event to Model..." << endl;
		Event* e = eventQueue.front();
		eventQueue.pop();
		mptr->takeEvent(e);
	}
}

void Controller::refreshViewer()
{
	cout << "Controller.refreshViewer() (not implemented yet)" << endl;
	//vptr->updateDisplay();
}

void Controller::takeInput()
{
	cout << "Controller.takeInput()" << endl;
	while (vptr->pollInput())
	{
		try 
		{
		cout << "Reading input from Viewer..." << endl;
		inputQueue.push(vptr->getInput());
		}
		catch (std::out_of_range err)
		{
			cout << err.what() << endl;
		}
	}
}

void Controller::loop()
{
	running = true;
	cout << "Controller.loop()" << endl;
		cout << "----------------\nNew Controller.loop() iteration" << endl;
		//0. update clock
		time_t currTime = 0;
		time_t dT = 0;
		if (mptr->isRunning())
		{
			currTime = time(0);
			dT = currTime - getLastUpdate();
		}

		//1. poll Viewer for Inputs and add any Inputs to queue
		this->takeInput();

		//2. process Inputs from InputQueue into Events for EventQueue
		while (inputQueue.empty() == false)
		{
			Input* i = inputQueue.front();
			inputQueue.pop();
			this->parseInput(i);
		}

		//3. push Events from EventQueue to Model
		this->notifyModel();

		//4. ping Model to update and then push notices to Viewer
		if (mptr != nullptr)
		{
			mptr->update();
			//4.5 notify Model of time change
			if (mptr->isRunning())
			{
				mptr->simUpdate(dT);
			}
		}

		//5. ping Viewer to update
		if (vptr != nullptr)
		{
			vptr->update();
		}

		//6. update counter for time since prev iteration
		if (mptr != nullptr)
		{
			if (mptr->isRunning())
			{
				setLastupdate(currTime);
			}
		}


}

void Controller::pause()
{
	running = false;
}

void Controller::setLastupdate(time_t time)
{
	lastUpdate = time;
}

time_t Controller::getLastUpdate()
{
	return lastUpdate;
}
