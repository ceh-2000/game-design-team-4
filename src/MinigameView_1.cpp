#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic> MinigameLogic_1) : MinigameView(MinigameLogic_1)
{
    this->miniLogic = MinigameLogic_1;
}