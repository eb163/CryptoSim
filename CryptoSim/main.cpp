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
#include "Node.h"
#include "Network.h"
#include "Driver.h"

#include "blockchain/sha256.h"
#include "blockchain/Block.h"
#include "blockchain/Blockchain.h"

#include "SFML/Main.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

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