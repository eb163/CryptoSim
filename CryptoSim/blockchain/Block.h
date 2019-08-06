#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>
#include <ctime>
#include "../Transaction.h"

using namespace std;

class Block {
public:
    string sPrevHash;
 
    //Block(uint32_t nIndexIn, const string &sDataIn);
	Block(uint32_t nIndexIn, Transaction sDataIn);

	uint32_t getIndex();
 
    string GetHash();
	//string GetData(); //to easily check if blocks are duplicates of data
	Transaction GetData();
 
    void MineBlock(uint32_t nDifficulty);
 
private:
    uint32_t _nIndex;
    int64_t _nNonce;
    //string _sData;
	Transaction _sData;
    string _sHash;
    time_t _tTime;
 
    string _CalculateHash();
};
