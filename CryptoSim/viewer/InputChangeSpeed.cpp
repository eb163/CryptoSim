#include "InputChangeSpeed.h"

InputChangeSpeed::InputChangeSpeed(SimRate speedmodifier)
{
	modifier = speedmodifier;
	setType(InputType::INPUT_SPEED_CHANGE);
}


InputChangeSpeed::~InputChangeSpeed()
{
}

void InputChangeSpeed::setModifier(SimRate n)
{
	modifier = n;
}

SimRate InputChangeSpeed::getModifier()
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
