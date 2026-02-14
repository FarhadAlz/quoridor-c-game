#ifndef AI_H
#define AI_H

#include "game.h"
#include "movement.h"
#include "wall.h"

enum ComputerAction randomComputerAction(struct Player *computer);

void computerMove(struct Game *game, struct Player *computer);
void computerPlaceWall(struct Game *game, struct Player *computer);

#endif
