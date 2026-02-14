#ifndef UI_H
#define UI_H

#include "player.h"

void welcome();
void choosePlayer();
void withPlayer(struct Game *game);
void withComputer(struct Game *game);
void selectActionPlayer(struct Game *game, struct Player *player);
void printGameBoard(struct Game *game);

#endif
