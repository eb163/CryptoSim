#pragma once
#include "Input.h"
#include "../model/SimRates.h"

class InputChangeSpeed :
	public Input
{
private:
	SimRate modifier;
protected:

public:
	InputChangeSpeed(SimRate modifier);
	~InputChangeSpeed();

	void setModifier(SimRate n);
	SimRate getModifier();

	bool isIncrease();
	bool isDecrease();
};

