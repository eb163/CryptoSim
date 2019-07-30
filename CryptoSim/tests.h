#pragma once
#include "blockchain\Block.h"
#include "blockchain\Blockchain.h"
#include "Node.h"
#include "Driver.h"
#include "mvc\debug.h"
#include "mvc\Viewer.h"

#include "SFML/Main.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

char pause();

void printBlockData(Block& b);

void printBlockchainContents(Blockchain &bc);

void printDataManager(DataManager& m);

void printNetworkNodes(Network* nw);

void unitTestBlockchain();

void unitTestNode();

void unitTestNetwork();

void unitTestDriver();

void unitTestDataManager();

void unitTestViewer();

//void unitTestModel();

//void unitTestController();