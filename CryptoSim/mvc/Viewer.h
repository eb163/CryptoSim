#pragma once
#ifndef VIEWER_H
#define VIEWER_H
#include "ViewerInterface.h"
#include "Controller.h"
#include "Model.h"
#include <queue>
#include <exception>

#include "SFML/Main.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

#include "debug.h"

class Controller; //avoids recursive includes

using std::queue;

class Viewer : public ViewerInterface
{
private:
	Model *mptr = nullptr;
	Controller *cptr = nullptr;

protected:
	queue<Input*> inputQueue;
	queue<Notice*> noticeQueue;

	string windowTitle = "CryptoSim: A Simulation of a Cryptocurrency network powered by blockchain!";
	sf::RenderWindow* windowptr = nullptr;
	sf::VideoMode* videomodeptr = nullptr;

	string fontPath = "cour.ttf";
	sf::Font font;

	string cryptoStr = "Crypto: ";
	sf::Text cryptoText;
	sf::Vector2f cryptoTextPos;

	string transacStr = "Transactions: ";
	sf::Text transacText;
	sf::Vector2f transacTextPos;

	sf::Vector2f pauseButtonSize;
	sf::Vector2f pauseButtonPos;
	sf::RectangleShape pauseButton;
	sf::Color pausedColor = sf::Color::Red;
	sf::Color goColor = sf::Color::Green;

public:
	Viewer();
	~Viewer();

	void resizeWindow(int width, int height);

	bool pollWindow();

	void connectModel(Model& m);

	void connectController(Controller& c);

	//void takeEvent(Event* e); //adds an event to the queue to be processed by the Viewer
	void takeNotice(Notice* n); //adds a notice to the queue

	//viewer must:
	//update graphics when model sends a notification
	//send input to controller
	//todo:
	//implement Interface methods
	void processNotice(Notice* n);
	void updateDisplay(Notice* n);
	void updateDisplay(); //redraw the whole window's contents
	bool pollInput();
	Input* getInput();
	void loop();
	void update();
};

#endif

