#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "player.h"
enum MoveStatus validateMove(struct Player *player, struct Game *gameBoard, enum Direction direction, int *out_x, int *out_y);
enum GameStatus action(struct Game *game, struct Player *player, enum Direction direction);
enum winner checkwinner(struct Game *game);

#endif
