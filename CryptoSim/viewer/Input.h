#pragma once

enum InputType {INPUT_CLOSE, INPUT_SPACEBAR, INPUT_SPEED_CHANGE};

class Input
{
private:
	InputType type;

protected:
	void setType(InputType t);

public:
	InputType getType();

};