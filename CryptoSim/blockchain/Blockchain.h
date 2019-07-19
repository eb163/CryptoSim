#include <cstdint>
#include <vector>
#include "Block.h"
 
using namespace std;
	
class Blockchain {
public:
    Blockchain();
 
    void AddBlock(Block bNew);
	Block getBlock(int i) const;
	Block GetLastBlock() const; //need to be able to access Blocks of data
	int getSize();
 
private:
    uint32_t _nDifficulty;
    vector<Block> bChain;
};
