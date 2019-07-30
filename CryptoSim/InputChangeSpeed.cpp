#include "InputChangeSpeed.h"

InputChangeSpeed::InputChangeSpeed(int speedmodifier)
{
	modifier = speedmodifier;
	setType(InputType::SPEED_CHANGE);
}


InputChangeSpeed::~InputChangeSpeed()
{
}

void InputChangeSpeed::setModifier(int n)
{
	modifier = n;
}

int InputChangeSpeed::getModifier()
{
	return modifier;
}

bool InputChangeSpeed::isIncrease()
{
	return (modifier > 0);
}

bool InputChangeSpeed::isDecrease()
{
	return (modifier < 0);
}
