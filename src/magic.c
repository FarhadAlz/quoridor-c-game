#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.h"
#include "wall.h"
#include "magic.h"


enum MagicCategory chooseCategory()
{
    return (rand() % 2) ? POSITIVE_MAGIC : NEGETIVE_MAGIC;
}

enum MagicEffect chooseEffect(enum MagicCategory category)
{
    if (category == POSITIVE_MAGIC)
    {
        enum MagicEffect posetiveEffects[] = {POS_INCREASE_WALLS, POS_TAKEN_WALLS};
        return posetiveEffects[rand() % 2];
    }
    else
    {
        enum MagicEffect negetiveEffects[] = {NEG_BLOCK_PLAYER, NEG_REDUCE_WALLS, NEG_REMOVE_ALL_WALLS};
        return negetiveEffects[rand() % 3];
    }
}


void spellRemoveAllWalls(struct Game *game)
{
    game->wall_count = 0;
    Sleep(500);
    printf("All walls removed from board!\n");
}

void spellReduceWalls(struct Player *player)
{
    int reduce = 0;
    switch (player->canwall)
    {
    case 0:
    case 1: reduce = 0; break;
    case 2: reduce = 2; break;
    case 3:
    case 4: reduce = (rand() % 2) ? 2 : 3; break;
    default:
        {
            int r = rand() % 3;
            if (r == 0) reduce = 2;
            else if (r == 1) reduce = 3;
            else reduce = 5;
        }
    }
    if(reduce > player->canwall) reduce = player->canwall;
    player->canwall -= reduce;
    printf("%d walls reduced\n", reduce);
}

void spellBlockPlayer(struct Player *player)
{
    player->blockTurns = (rand() % 2) ? 1 : 2;
    printf("Player blocked for %d turns!\n", player->blockTurns);
}

void increaseWall(struct Player *player)
{
    int options[] = {2, 3, 5};
    int add = options[rand() % 3];
    player->canwall += add;
    printf("%d walls added!\n", add);
}

void takeWalls(struct Player *player, struct Player *other)
{
    int takenWalls = 0;
    switch(other->canwall)
    {
    case 0: takenWalls = 0; break;
    case 1: takenWalls = 1; break;
    default: takenWalls = (rand() % 2) ? 1 : 2; break;
    }
    if(takenWalls > other->canwall) takenWalls = other->canwall;
    other->canwall -= takenWalls;
    player->canwall += takenWalls;
    printf("%d walls were taken and given to current player.\n", takenWalls);
}


void applyMagicEffect(struct Game *game, struct Player *current, struct Player *other)
{
    switch(current->activeEffect)
    {
        case NEG_REMOVE_ALL_WALLS: spellRemoveAllWalls(game); break;
        case NEG_REDUCE_WALLS: spellReduceWalls(current); break;
        case NEG_BLOCK_PLAYER: spellBlockPlayer(current); break;
        case POS_INCREASE_WALLS: increaseWall(current); break;
        case POS_TAKEN_WALLS: takeWalls(current, other); break;
        default: break;
    }
    current->activeEffect = NONE_EFFECT;
}


void magicBox(struct Game *game, struct Player *player1, struct Player *player2)
{
    if(game->turnCounter % 2 == 0)
    {
        int chosenPlayer = rand() % 2;
        struct Player *targetPlayer = (chosenPlayer == 0) ? player1 : player2;
        struct Player *otherPlayer = (chosenPlayer == 0) ? player2 : player1;

        enum MagicCategory category = chooseCategory();
        enum MagicEffect effect = chooseEffect(category);

        targetPlayer->activeEffect = effect;
        printf("Magic box given to %s", targetPlayer->name);

        for(int i=0;i<3;i++)
        {
            printf(".");
            fflush(stdout);
            Sleep(800);
        }
        printf("\n");
        Sleep(500);
        applyMagicEffect(game, targetPlayer, otherPlayer);
    }
}
