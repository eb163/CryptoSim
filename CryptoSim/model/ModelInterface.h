#pragma once
#include "Event.h"
#include "../viewer/Input.h"
#include "../viewer/Notice.h"

class ModelInterface
{
public:
	virtual void update() = 0;
	virtual void notifyViewer(Notice* n) = 0;
	virtual void updateModel(Event* e) = 0;
	virtual void takeEvent(Event* e) = 0;
};