#pragma once
#include "blockchain\Block.h"
#include "blockchain\Blockchain.h"
#include "Node.h"
#include "Driver.h"
#include "mvc\debug.h"

char pause();

void printBlockData(Block& b);

void printBlockchainContents(Blockchain &bc);

void printDataManager(DataManager& m);

void unitTestBlockchain();

void unitTestNode();

void unitTestNetwork();

void unitTestDriver();

void unitTestDataManager();