#include "game.h"
#include "player.h"

struct Player constructPlayer(int x, int y, int wallcount, char name[])
{
    struct Player player;
    strcpy(player.name, name);
    player.x = x;
    player.y = y;
    player.canwall = wallcount;
    player.blockTurns = 0;
    player.activeEffect = NONE_EFFECT;

    return player;
}

struct Game constructGame(struct Player player_1, struct Player player_2, int dimention)
{
    struct Game game;
    game.dim = dimention;
    game.player1 = player_1;
    game.player2 = player_2;
    game.wall_count = 0;
    game.currentPlayer = 0;

    return game;
}
