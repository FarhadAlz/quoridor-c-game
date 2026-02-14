#ifndef PLAYER_H
#define PLAYER_H

#include "game_types.h"

struct Player constructPlayer(int x, int y, int wallcount,char name[]);
struct Game constructGame(struct Player player_1, struct Player player_2, int dimention);


#endif
