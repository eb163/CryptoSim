#include "Viewer.h"

Viewer::Viewer()
{
	mptr = nullptr;
	cptr = nullptr;

	videomodeptr = new sf::VideoMode(800, 600);
	windowptr = new sf::RenderWindow(*videomodeptr, windowTitle);

	font.loadFromFile(fontPath);

	cryptoTextPos.x = 100; //arbitrary
	cryptoTextPos.y = 100; //arbitrary

	cryptoText.setPosition(cryptoTextPos);
	cryptoText.setString(cryptoStr);
	cryptoText.setFont(font);
	//cryptoText.setCharacterSize();

	transacTextPos.x = 100; //arbitrary
	transacTextPos.y = 200; //arbitrary

	transacText.setPosition(transacTextPos);
	transacText.setString(transacStr);
	transacText.setFont(font);

	clockTextPos.x = 100; //arbitrary
	clockTextPos.y = 300; //arbitrary

	clockText.setPosition(clockTextPos);
	clockText.setString(clockStr);
	clockText.setFont(font);

	pauseButtonSize.x = 100; //arbitrary
	pauseButtonSize.y = 100; //arbitrary
	pauseButtonPos.x = 400;	//arbitrary
	pauseButtonPos.y = 400; //arbitrary
	pauseButton.setOrigin(sf::Vector2f(pauseButtonSize.x / 2, pauseButtonSize.y / 2));
	pauseButton.setSize(pauseButtonSize);
	pauseButton.setPosition(pauseButtonPos);
	pauseButton.setFillColor(goColor);
	pauseButton.setOutlineColor(goColor);

	repositionUI();
}


Viewer::~Viewer()
{
	if (windowptr != nullptr)
	{
		windowptr->close();
		delete windowptr;
		windowptr = nullptr;
	}

	if (videomodeptr != nullptr)
	{
		delete videomodeptr;
		videomodeptr = nullptr;
	}
}

void Viewer::resizeWindow(int width, int height)
{
	videomodeptr->width = width;
	videomodeptr->height = height;
	windowptr->create(*videomodeptr, windowTitle);
	repositionUI();
}

void Viewer::repositionUI()
{
	/*
	-crypto / transaction positions : top left corner
		- clock position : under crypto / transaction displays
		- pause button : the bottom middle of the left half of the window
		- speed buttons : slow to the left of pause, speed up to the right of pause
		- message log : right half of window
	*/
	int textLength = 0;
	int textHeight = 0;
	int offsetX = 10, offsetY = 5;
	
	//crypto position
	textLength = cryptoText.getCharacterSize() * cryptoText.getString().getSize();
	textHeight = cryptoText.getCharacterSize();
	cryptoTextPos.x = 0 + offsetX;
	cryptoTextPos.y = 0 + textHeight + offsetY;
	cryptoText.setPosition(cryptoTextPos);

	//transaction position
	textLength = transacText.getCharacterSize() * transacText.getString().getSize();
	textHeight = transacText.getCharacterSize();
	transacTextPos.x = 0 + offsetX;
	transacTextPos.y = cryptoTextPos.y + textHeight + offsetY;
	transacText.setPosition(transacTextPos);

	//clock position
	textLength = clockText.getCharacterSize() * clockText.getString().getSize();
	textHeight = clockText.getCharacterSize();
	clockTextPos.x = 0 + offsetX;
	clockTextPos.y = transacTextPos.y + textHeight + offsetY;
	clockText.setPosition(clockTextPos);

	//pause button
	pauseButtonPos.y = videomodeptr->height - pauseButtonSize.y / 2 - offsetY * 5;
	pauseButtonPos.x = videomodeptr->width / 4;
	pauseButton.setPosition(pauseButtonPos);

	//slow down button

	//speed up button

	//message log
}

bool Viewer::pollWindow()
{
	sf::Event e;
	bool result = windowptr->pollEvent(e);
	//possible events:
	//1. closed
	if (e.type == sf::Event::Closed)
	{
		cout << "Window got an sf::Event: Closed" << endl;
		//create an input for closed event
		//push the input to the queue
	}
	if (e.type == sf::Event::KeyReleased)
	{
		cout << "Window got an sf::Event: KeyReleased" << endl;

		//2. space bar key is pressed

		//3. escape key is pressed (same as Closed event)
	}

	if (e.type == sf::Event::MouseButtonReleased)
	{
		cout << "Window got an sf::Event: MouseButtonRleased" << endl;

		//4. a mouse click is detected
		//4a. the click is on the speed up button
		//4b. the click is on the slow down button
		//4c. the click is on the pause / go button
	}

	return result;
}

void Viewer::updateText()
{
	cout << "Viewer.updateText()" << endl;
	cout << "mptr = " << mptr << endl;
	float crypto = mptr->getDataManager().getTotalCrypto();
	int transacs = mptr->getDataManager().getTotalTransactions();
	time_t currTime = mptr->getDataManager().getTimePassed();

	string newcryptostr = cryptoStr + std::to_string(crypto);
	string newtransacstr = transacStr + std::to_string(transacs);
	string newclockstr = clockStr + std::to_string(currTime);

	cryptoText.setString(newcryptostr);
	transacText.setString(newtransacstr);
	clockText.setString(newclockstr);

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
		windowptr->clear();

		//do stuff here

		windowptr->display();
	}
}

void Viewer::updateDisplay()
{
	windowptr->clear();

	//redraw all things here

	updateText();

	windowptr->draw(cryptoText);

	windowptr->draw(transacText);

	windowptr->draw(clockText);

	windowptr->draw(pauseButton);

	windowptr->display();
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
	this->pollWindow(); //check the window for any sf::Events
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
		if(n != nullptr)
		{
			updateDisplay(n);
		}
		else
		{
			updateDisplay();
		}
	}
	updateDisplay(); //temporary, want to display changes while no notices exist
}