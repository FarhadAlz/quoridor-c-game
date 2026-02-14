#ifndef AI_H
#define AI_H

#include "game.h"
#include "movement.h"
#include "wall.h"

int evaluateGame(struct Game *game);

enum ComputerAction computerDecideAction(struct Game *game, struct Player *computer, struct Player *opponent);

int bfsShortestPath(struct Game *game, int startX, int startY, int player);

void computerSmartMove(struct Game *game, struct Player *computer);

void computerPlaceWall(struct Game *game, struct Player *computer);

#endif
