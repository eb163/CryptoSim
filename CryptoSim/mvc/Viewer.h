#pragma once
#ifndef VIEWER_H
#define VIEWER_H
#include "ViewerInterface.h"
#include "Controller.h"
#include "Model.h"
#include <queue>
#include <exception>

#include "debug.h"

class Controller; //avoids recursive includes

using std::queue;

class Viewer : public ViewerInterface
{
private:
	Model *mptr = nullptr;
	Controller *cptr = nullptr;

protected:
	queue<Input*> inputQueue;
	queue<Notice*> noticeQueue;

public:
	Viewer();
	~Viewer();

	void connectModel(Model& m);

	void connectController(Controller& c);

	//void takeEvent(Event* e); //adds an event to the queue to be processed by the Viewer
	void takeNotice(Notice* n); //adds a notice to the queue

	//viewer must:
	//update graphics when model sends a notification
	//send input to controller
	//todo:
	//implement Interface methods
	void processNotice(Notice* n);
	void updateDisplay(Notice* n);
	bool pollInput();
	Input* getInput();
	void loop();
	void update();
};

#endif

