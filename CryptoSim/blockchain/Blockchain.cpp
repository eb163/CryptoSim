#include "Blockchain.h"
Blockchain::Blockchain() {
    bChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 3; //originally 10, but 10 takes a while for testing
}
void Blockchain::AddBlock(Block bNew) {
    bNew.sPrevHash = GetLastBlock().GetHash();
    bNew.MineBlock(_nDifficulty);
    bChain.push_back(bNew);
}
Block Blockchain::GetLastBlock() const {
    return bChain.back();
}

int Blockchain::getSize()
{
	return bChain.size();
}

Block Blockchain::getBlock(int i) const
{
	return bChain.at(i);
}

