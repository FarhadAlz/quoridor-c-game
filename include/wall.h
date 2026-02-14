#ifndef WALL_H
#define WALL_H

#include "game_types.h"

void addWall(struct Game *game, int x, int y, char d, int owner);
int hasHorizontalWall(struct Game *game, int x, int y);
int hasVerticalWall(struct Game *game, int x, int y);

#endif
