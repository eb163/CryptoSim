#pragma once

enum InputType {CLOSE, SPACEBAR};

class Input
{
private:
	InputType type;

protected:
	void setType(InputType t);

public:
	InputType getType();

};