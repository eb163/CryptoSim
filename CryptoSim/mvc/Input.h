#pragma once

enum InputType {INPUT_CLOSE, INPUT_LEFTMOUSECLICK};

class Input
{
private:
	InputType type;

protected:
	void setType(InputType t);

public:
	InputType getType();

};