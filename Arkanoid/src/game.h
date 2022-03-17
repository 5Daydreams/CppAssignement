#pragma once

#include <vector>
#include "player.h"
#include "Library/Ball.h"
#include "Library/Block.h"

extern const int BLOCK_ROW_SIZE;
extern const int BLOCK_COL_SIZE;
extern bool resetAvailable;

extern Player player;
extern std::vector<Ball> balls;
extern Block blocks[];