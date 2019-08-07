#pragma once
#include "model\blockchain\Block.h"
#include "model\blockchain\Blockchain.h"
#include "model\Node.h"
#include "model\Driver.h"
#include "debug.h"
#include "viewer\Viewer.h"

/*
#include "viewer/SFML/Main.hpp"
#include "viewer/SFML/Window.hpp"
#include "viewer/SFML/Graphics.hpp"
#include "viewer/SFML/Network.hpp"
#include "viewer/SFML/System.hpp"
*/

char pause();

void printBlockData(Block& b);

void printBlockchainContents(Blockchain &bc);

void printDataManager(DataManager& m);

void printNetworkNodes(Network* nw);

void printTransaction(Transaction& t);

void unitTestTransaction();

void unitTestBlock();

void unitTestBlockchain();

void unitTestNode();

void unitTestNetwork();

void unitTestDataManager();

void unitTestDriver();

void unitTestViewer();

void unitTestModel();

void unitTestController();

void systemTestDriver();

void systemTestMVC();