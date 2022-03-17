#include "game.h"

const int BLOCK_ROW_SIZE = 10;
const int BLOCK_COL_SIZE = 6;
bool resetAvailable = false;

Player player;
std::vector<Ball> balls = {};
Block blocks[BLOCK_ROW_SIZE * BLOCK_COL_SIZE];