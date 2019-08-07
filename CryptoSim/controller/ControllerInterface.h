#pragma once

#include "../viewer/Input.h"

class ControllerInterface
{
public:
	virtual void loop() = 0;
	virtual void pause() = 0;
	virtual bool isRunning() = 0;
	virtual void parseInput(Input* i) = 0;
	virtual void notifyModel() = 0;
	virtual void refreshViewer() = 0;
};