#include "Blockchain.h"
Blockchain::Blockchain() {
    bChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 3; //originally 10, but 10 takes a while for testing
}
void Blockchain::AddBlock(Block bNew) {
    bNew.sPrevHash = _GetLastBlock().GetHash();
    bNew.MineBlock(_nDifficulty);
    bChain.push_back(bNew);
}
Block Blockchain::_GetLastBlock() const {
    return bChain.back();
}

