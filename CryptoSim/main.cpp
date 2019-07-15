#include "mvc/ControllerInterface.h"
#include "mvc/Controller.h"
#include "mvc/debug.h"
#include "mvc/Event.h"
#include "mvc/Input.h"
#include "mvc/Model.h"
#include "mvc/ModelInterface.h"
#include "mvc/Notice.h"
#include "mvc/Viewer.h"
#include "mvc/ViewerInterface.h"

int main()
{
	Controller ctrl;
	Viewer view;
	Model model;

	ctrl.connectModel(model);
	ctrl.connectViewer(view);
	
	//example loop of MVC framework
	//loop runs until Controller.pause() is called
	//right now this is an unending loop
	do
	{
		view.loop();	//View can check for input
		ctrl.loop();	//Ctrl activates an update cycle, checks for inputs from view, sends any events to model, and prompts model and view to update
	} while (ctrl.isRunning() == true);
	return 0;
}