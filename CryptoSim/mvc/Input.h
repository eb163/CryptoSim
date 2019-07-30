#pragma once

enum InputType {CLOSE, SPACEBAR, SPEED_CHANGE};

class Input
{
private:
	InputType type;

protected:
	void setType(InputType t);

public:
	InputType getType();

};