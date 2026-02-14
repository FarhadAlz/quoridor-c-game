#ifndef MAGIC_H
#define MAGIC_H

#include "player.h"


enum MagicCategory chooseCategory();

enum MagicEffect chooseEffect(enum MagicCategory category);

void spellRemoveAllWalls(struct Game *game);

void spellReduceWalls(struct Player *player);

void spellBlockPlayer(struct Player *player);

void increaseWall(struct Player *player);

void takeWalls(struct Player *player, struct Player *other);

void applyMagicEffect(struct Game *game, struct Player *current, struct Player *other);

void magicBox(struct Game *game, struct Player *player1, struct Player *player2);

#endif
