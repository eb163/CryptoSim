#include "Viewer.h"

Viewer::Viewer()
{
}


Viewer::~Viewer()
{

}

void Viewer::connectModel(Model& m)
{
	mptr = &m;
}

void Viewer::connectController(Controller& c)
{
	cptr = &c;
}

void Viewer::takeNotice(Notice* n)
{
	cout << "Viewer.takeNotice()" << endl;
	noticeQueue.push(n);
}

void Viewer::processNotice(Notice* n)
{
	cout << "Viewer.processNotice()" << endl;
	//do stuff here

	this->updateDisplay(n); //to update the graphical display

	if (n!= nullptr)
	{
		delete n;
		n = nullptr;
	}
}

void Viewer::updateDisplay(Notice* n)
{
	cout << "Viewer.updateDisplay()" << endl;
	if (n != nullptr)
	{
		//do stuff here
	}
}

bool Viewer::pollInput()
{
	return (!inputQueue.empty());
}

Input* Viewer::getInput()
{
	if (inputQueue.empty())
	{
		throw std::out_of_range("Input queue is empty");
	}
	Input* i = inputQueue.front();
	inputQueue.pop();
	return i;
}

void Viewer::loop()
{
	//method of things to be done repeatedly
	//for example:
	this->update(); //to check for notices in queue, parse them, and modify display
}

void Viewer::update()
{
	cout << "Viewer.update()" << endl;
	//process each event in queue
	while (noticeQueue.empty() == false)
	{
		cout << "Viewer is processing a Notice" << endl;
		Notice* n = noticeQueue.front();
		noticeQueue.pop();
		processNotice(n);
	}
}