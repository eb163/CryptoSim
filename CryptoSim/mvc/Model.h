#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "ModelInterface.h"
#include <queue>
#include <cmath>
#include "debug.h"
//#include "Viewer.h"

#include "../Driver.h"
#include "../Network.h"
#include "../DataManager.h"

#include "../EventClose.h"
#include "../EventPause.h"
#include "../EventSpeedChange.h"

class Viewer; //avoids recursive includes

using std::queue;

class Model : public ModelInterface
{
private:

protected:
	Viewer *vptr = nullptr;
	queue<Event*> eventsQueue; //for events from controller
	queue<Notice*> noticeQueue; //for notices to send to viewer

	Driver driver;
	Network netw;
	DataManager manager;

public:
	Model();
	~Model();

	Viewer* getViewer();
	void connectViewer(Viewer* v);

	//model must:
	//take commands or processed input from controller
	//operate on internal data structures
	//pass notifications to viewer

	void notifyViewer(Notice* n);
	void updateModel(Event* e);
	void takeEvent(Event* e);
	void update();

	void init(int nodesInNetwork, float baseCryptoRate, time_t baseTimeRate); //initialize the simulation system

	DataManager getDataManager();

	void simUpdate(time_t deltaT);
};

#endif