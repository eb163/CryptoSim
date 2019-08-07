#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ControllerInterface.h"
#include <queue>
#include <ctime>
#include "../model/Model.h"
#include "../viewer/Viewer.h"
#include "../debug.h"

#include "../model/EventClose.h"
#include "../model/EventPause.h"
#include "../model/EventSpeedChange.h"

using std::queue;

class Controller : public ControllerInterface
{
private:
	Model* mptr = nullptr;
	Viewer* vptr = nullptr;
	time_t lastUpdate = 0;

protected:
	queue<Input*> inputQueue;
	queue<Event*> eventQueue;
	bool running = true; //for running the main loop

public:
	Controller();
	Controller(Model* m, Viewer* v);
	~Controller();

	void connectModel(Model* m);
	void connectViewer(Viewer* v);
	Model* getModel();
	Viewer* getViewer();

	bool isRunning();

	//controller must:
	//parse input from user
	//pass commands and parsed input to model
	//force viewer to update as necessary

	//todo
	//implement Interface methods
	void parseInput(Input* i);
	void notifyModel();
	void takeInput(); //read all inputs from View
	void refreshViewer();

	void loop();
	void pause();

	void setLastupdate(time_t time);
	time_t getLastUpdate();

};

#endif

