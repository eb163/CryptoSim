#include "Model.h"
#include "Viewer.h"

Model::Model()
{

}


Model::~Model()
{

}

Viewer * Model::getViewer()
{
	return vptr;
}

void Model::connectViewer(Viewer& v)
{
	vptr = &v;
}

void Model::notifyViewer(Notice* n)
{
	vptr->takeNotice(n);
}

void Model::updateModel(Event* e)
{
	cout << "Model.updateModel()" << endl;
	//do stuff based on what Event is passed and what data needs to be modified
}

void Model::takeEvent(Event* e)
{
	cout << "Model.takeInput()" << endl;
	eventsQueue.push(e);
}

void Model::update()
{
	cout << "Model.update()" << endl;
	while (eventsQueue.empty() == false)
	{
		cout << "Model is processing an event..." << endl;
		Event* e = eventsQueue.front();
		eventsQueue.pop();
		
		//update the model data
		updateModel(e);

		//create a Notice based on the Event
		Notice* n = nullptr;
		//notices need to be fleshed out according to the project requirements

		//push to queue to send to viewer
		noticeQueue.push(n);
	}

	while (noticeQueue.empty() == false)
	{
		cout << "Model is pushing a Notice to Viewer..." << endl;
		Notice* n = noticeQueue.front();
		noticeQueue.pop();
		notifyViewer(n);
	}
}
