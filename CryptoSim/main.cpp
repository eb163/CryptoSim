#include "controller/ControllerInterface.h"
#include "controller/Controller.h"
#include "debug.h"
#include "model/Event.h"
#include "viewer/Input.h"
#include "model/Model.h"
#include "model/ModelInterface.h"
#include "viewer/Notice.h"
#include "viewer/Viewer.h"
#include "viewer/ViewerInterface.h"
#include "model/Node.h"
#include "model/Network.h"
#include "model/Driver.h"

#include "model/blockchain/sha256.h"
#include "model/blockchain/Block.h"
#include "model/blockchain/Blockchain.h"

/*
#include "viewer/SFML/Main.hpp"
#include "viewer/SFML/Window.hpp"
#include "viewer/SFML/Graphics.hpp"
#include "viewer/SFML/Network.hpp"
#include "viewer/SFML/System.hpp"
*/

#include "tests.h"

int main()
{

	////////////////////////////////////////////////////
	//TESTS
	///////////////////////////////////////////////////


	//unitTestTransaction();
	//unitTestBlock();
	//unitTestBlockchain();
	//unitTestNode();
	//unitTestDataManager();
	//unitTestNetwork();
	//unitTestDriver();

	//unitTestModel();
	//unitTestViewer();
	//unitTestController();

	//systemTestDriver();
	//systemTestMVC();


	/////////////////////////////////////////////////
	//MAIN
	/////////////////////////////////////////////////

	Controller ctrl;
	Viewer view;
	Model model;

	ctrl.connectModel(&model);
	ctrl.connectViewer(&view);
	view.connectController(&ctrl);
	view.connectModel(&model);
	model.connectViewer(&view);

	int totalNodes = 3;
	float baseCryptoRate = 5.00;
	time_t baseTicRate = 9;

	model.init(totalNodes, baseCryptoRate, baseTicRate);

	//main loop
	do
	{
		view.loop();	//View can check for input
		ctrl.loop();	//Ctrl activates an update cycle, checks for inputs from view, sends any events to model, and prompts model and view to update
	} while (ctrl.isRunning() == true && view.isOpen());
	return 0;
}