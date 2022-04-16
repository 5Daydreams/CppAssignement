#pragma once

#include <vector>
#include "player.h"
#include "Library/Ball.h"
#include "Library/Block.h"

// feedback: seems like this file is a storage for some variables that are used elsewhere. Would be more suitable to have a Game class that holds
// these variables and some functionality around it.

extern const int BLOCK_ROW_SIZE;
extern const int BLOCK_COL_SIZE;
extern bool resetAvailable;

extern Player player;
extern std::vector<Ball> balls;
extern Block blocks[];