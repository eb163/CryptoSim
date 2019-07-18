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


#include "blockchain/sha256.h"
//#include "blockchain/Block.h"
#include "blockchain/Blockchain.h"

int main()
{
	Controller ctrl;
	Viewer view;
	Model model;

	ctrl.connectModel(model);
	ctrl.connectViewer(view);

	Block b1(1, "Block 1"), b2(2, "Block 2"), b3(3, "Block 3");

	//demonstrating the blockchain
	Blockchain chain;
	cout << "Created a Blockchain" << endl;
	chain.AddBlock(b1);
	chain.AddBlock(b2);
	chain.AddBlock(b3);
	
	//example loop of MVC framework
	//loop runs until Controller.pause() is called
	//right now this is an unending loop
	/*
	do
	{
		view.loop();	//View can check for input
		ctrl.loop();	//Ctrl activates an update cycle, checks for inputs from view, sends any events to model, and prompts model and view to update
	} while (ctrl.isRunning() == true);
	*/
	return 0;
}