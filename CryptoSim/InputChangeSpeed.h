#pragma once
#include "mvc\Input.h"
class InputChangeSpeed :
	public Input
{
private:
	int modifier;
protected:

public:
	InputChangeSpeed(int speedmodifier);
	~InputChangeSpeed();

	void setModifier(int n);
	int getModifier();

	bool isIncrease();
	bool isDecrease();
};

