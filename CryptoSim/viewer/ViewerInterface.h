#pragma once

#include "../model/Event.h"
#include "Input.h"
#include "Notice.h"

class ViewerInterface
{
public:
	virtual void loop() = 0;
	virtual void update() = 0;
	virtual bool pollInput() = 0;
	virtual Input* getInput() = 0;
	virtual void processNotice(Notice* n) = 0;
	virtual void takeNotice(Notice* n) = 0;
	virtual void updateDisplay(Notice* n) = 0;
};