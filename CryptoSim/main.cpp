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
	//sf::RenderWindow win(sf::VideoMode(800, 600), "This is an example window");

	Controller ctrl;
	Viewer view;
	Model model;

	ctrl.connectModel(model);
	ctrl.connectViewer(view);

	int totalNodes = 10;
	float baseCryptoRate = 5.00;
	time_t baseTicRate = 1; //time_t counts seconds, base rate would be 1 second

	model.init(totalNodes, baseCryptoRate, baseTicRate);

	//time values for sim
	time_t prevTimestamp = time(0);
	time_t curTimestamp;
	time_t deltaTime = 0;
	
	//example loop of MVC framework and using SFML
	//loop runs until Controller.pause() is called or the window is closed

	//unitTestBlockchain();
	//unitTestNode();
	//unitTestNetwork();
	//unitTestDriver();

	//example loop of MVC framework
	//loop runs until Controller.pause() is called
	//or the window is closed
	
	do
	{
		//update clock
		curTimestamp = time(0);
		deltaTime = curTimestamp - prevTimestamp;

		view.loop();	//View can check for input
		//ctrl.loop();	//Ctrl activates an update cycle, checks for inputs from view, sends any events to model, and prompts model and view to update
		//model.simUpdate(deltaTime); //force the model to take a sim update cycle
		//printDataManager(model.getDataManager()); //print data to console to confirm it's working
	
		//code for checking window sf::events
		sf::Event e;
		/*
		while (win.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				win.close(); //closes window 
			}
		}
		*/

		//code for updating the window display
		//win.clear();

		//draw objects to window with win.draw(object)

		//win.display(); //when finished drawing objects to window, call win.display()

	} while (ctrl.isRunning() == true /*&& win.isOpen()*/);
	return 0;
}