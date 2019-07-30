#pragma once
#include "mvc\Input.h"
#include "SimRates.h"

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

